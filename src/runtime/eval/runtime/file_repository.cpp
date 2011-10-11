/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#include <sys/stat.h>
#include <runtime/eval/ast/expression.h>
#include <runtime/eval/runtime/file_repository.h>
#include <runtime/eval/runtime/variable_environment.h>
#include <runtime/eval/ast/statement.h>
#include <runtime/eval/parser/parser.h>
#include <runtime/eval/ast/static_statement.h>
#include <runtime/base/runtime_option.h>
#include <util/process.h>
#include <runtime/eval/runtime/eval_state.h>
#include <runtime/base/server/source_root_info.h>
#include <runtime/eval/ast/scalar_value_expression.h>

using namespace std;

namespace HPHP {

extern bool (*file_dump)(const char *filename);

namespace Eval {
///////////////////////////////////////////////////////////////////////////////

set<string> FileRepository::s_names;

PhpFile::PhpFile(StatementPtr tree, const vector<StaticStatementPtr> &statics,
                 const Block::VariableIndices &variableIndices,
                 const string &fileName, const string &srcRoot,
                 const string &relPath, const string &md5)
  : Block(statics, variableIndices), m_refCount(0), m_tree(tree),
    m_profName(string("run_init::") + string(m_tree->loc()->file)),
    m_fileName(fileName), m_srcRoot(srcRoot), m_relPath(relPath), m_md5(md5) {
}

PhpFile::~PhpFile() {
  assert(m_refCount == 0);
}

Variant PhpFile::eval(LVariableTable *vars) {
  NestedVariableEnvironment env(vars, *this);
  DECLARE_THREAD_INFO_NOINIT
  EvalFrameInjection fi(empty_string, m_profName.c_str(), env,
                        m_tree->loc()->file, NULL,
                        FrameInjection::PseudoMain|FrameInjection::Function);
  restart:
  try {
    m_tree->eval(env);
  } catch (GotoException &e) {
    goto restart;
  } catch (UnlimitedGotoException &e) {
    goto restart;
  }
  if (env.isGotoing()) {
    throw FatalErrorException(0, "Unable to reach goto label %s",
                              env.getGoto().c_str());
  }
  if (env.isReturning()) {
    return env.getRet();
  } else if (env.isBreaking()) {
    throw FatalErrorException("Cannot break/continue out of a file");
  }
  return true;
}

ReadWriteMutex FileRepository::s_lock;
hphp_hash_map<string, PhpFileWrapper*, string_hash> FileRepository::s_files;
hphp_hash_map<string, PhpFile*, string_hash> FileRepository::s_md5Files;

static class FileDumpInitializer {
  public: FileDumpInitializer() {
    file_dump = FileRepository::fileDump;
  }
} s_fileDumpInitializer;

bool FileRepository::fileDump(const char *filename) {
  std::ofstream out(filename);
  if (out.fail()) return false;
  ReadLock lock(s_lock);
  out << "s_files: " << s_files.size() << endl;
  for (hphp_hash_map<string, PhpFileWrapper*, string_hash>::const_iterator it =
       s_files.begin(); it != s_files.end(); it++) {
    out << it->first.c_str() << endl;
  }
  out << "s_md5Files: " << s_md5Files.size() << endl;
  for (hphp_hash_map<string, PhpFile*, string_hash>::const_iterator it =
       s_md5Files.begin(); it != s_md5Files.end(); it++) {
    out << it->second->getMd5().c_str() << " "
        << it->second->getFileName().c_str() << endl;
  }
  out.close();
  return true;
}

void FileRepository::onDelete(PhpFile *f) {
  if (RuntimeOption::SandboxCheckMd5) {
    s_md5Files.erase(f->getMd5());
  }
  delete(f);
}

void FileRepository::onZeroRef(PhpFile *f) {
  ASSERT(f->getRef() == 0);
  if (RuntimeOption::SandboxCheckMd5) {
    WriteLock lock(s_lock);
    onDelete(f);
  } else {
    onDelete(f);
  }
}

PhpFile *FileRepository::checkoutFile(const string &rname,
                                      const struct stat &s) {
  FileInfo fileInfo;
  PhpFile *ret = NULL;
  string name;

  if (rname[0] == '/') {
    name = rname;
  } else if (RuntimeOption::SourceRoot.empty()) {
    name = Process::GetCurrentDirectory() + "/" + rname;
  } else {
    name = RuntimeOption::SourceRoot + "/" + rname;
  }

  bool changed = false;
  {
    ReadLock lock(s_lock);
    hphp_hash_map<string, PhpFileWrapper*, string_hash>::iterator it =
      s_files.find(name);
    if (it == s_files.end()) {
      if (!readFile(name, s, fileInfo)) return NULL;
      ret = fileInfo.m_phpFile;
    } else if (it->second->isChanged(s)) {
      if (!readFile(name, s, fileInfo)) return NULL;
      ret = fileInfo.m_phpFile;
      PhpFile *f = it->second->getPhpFile();
      if (ret == f) {
        if (RuntimeOption::SandboxCheckMd5) {
          ASSERT(s_md5Files.find(ret->getMd5())->second == ret);
        }
        ret->incRef();
        return ret;
      }
      changed = true;
    } else {
      // should be the common case after the initial startup
      ret = it->second->getPhpFile();
      ret->incRef();
      return ret;
    }
  }

  // parseFile is lock free
  bool created = false;
  if (!ret) {
    ret = parseFile(name, fileInfo);
    if (!ret) return NULL;
    created = true;
  }

  WriteLock lock(s_lock);
  hphp_hash_map<string, PhpFileWrapper*, string_hash>::iterator it =
    s_files.find(name);
  if (it == s_files.end()) {
    if (changed) {
      if (created) delete ret;
      return NULL;
    }
    s_files[name] = new PhpFileWrapper(s, ret);
    ret->incRef();
    if (created) {
      if (RuntimeOption::SandboxCheckMd5) {
        s_md5Files[ret->getMd5()] = ret;
      }
    } else {
      if (RuntimeOption::SandboxCheckMd5) {
        ASSERT(s_md5Files.find(ret->getMd5())->second == ret);
      }
    }
  } else {
    if (!changed || !it->second->isChanged(s)) {
      if (created) delete ret;
      ret = it->second->getPhpFile();
    } else {
      PhpFile *f = it->second->getPhpFile();
      string oldMd5 = f->getMd5();
      if (f->decRef() == 0) {
        onDelete(f);
      }
      if (RuntimeOption::SandboxCheckMd5) {
        s_md5Files[ret->getMd5()] = ret;
      }
      delete(it->second);
      it->second = new PhpFileWrapper(s, ret);
      ret->incRef();
    }
  }
  ret->incRef();
  return ret;
}

String FileRepository::translateFileName(const string &file) {
  ASSERT(RuntimeOption::SandboxCheckMd5);
  hphp_hash_map<string, PhpFileWrapper*, string_hash>::const_iterator iter =
    s_files.find(file);
  if (iter == s_files.end()) return file;
  string srcRoot(SourceRootInfo::GetCurrentSourceRoot());
  if (srcRoot.empty()) srcRoot = RuntimeOption::SourceRoot;
  if (srcRoot.empty()) return file;
  PhpFile *f = iter->second->getPhpFile();
  string parsedSrcRoot = f->getSrcRoot();
  if (srcRoot == parsedSrcRoot) return file;
  unsigned int len = parsedSrcRoot.size();
  if (len > 0 && file.size() > len &&
      strncmp(file.data(), parsedSrcRoot.c_str(), len) == 0) {
    return srcRoot + file.substr(len);
  }
  return file;
}

bool FileRepository::findFile(const string &path, struct stat *s) {
  return fileStat(path.c_str(), s) && !S_ISDIR(s->st_mode);
}

bool FileRepository::readFile(const string &name,
                              const struct stat &s,
                              FileInfo &fileInfo) {
  if (s.st_size > StringData::LenMask) {
    throw FatalErrorException(0, "file %s is too big", name.c_str());
  }
  int fileSize = s.st_size;
  if (!fileSize) return false;
  int fd = open(name.c_str(), O_RDONLY);
  if (!fd) return false; // ignore file open exception
  char *input = (char *)malloc(fileSize + 1);
  if (!input) return false;
  int nbytes = read(fd, input, fileSize);
  close(fd);
  input[fileSize] = 0;
  fileInfo.m_inputString = String(input, fileSize, AttachString);
  if (nbytes != fileSize) return false;

  if (RuntimeOption::SandboxCheckMd5) {
    fileInfo.m_md5 = StringUtil::MD5(fileInfo.m_inputString).c_str();
    fileInfo.m_srcRoot = SourceRootInfo::GetCurrentSourceRoot();
    if (fileInfo.m_srcRoot.empty()) {
      fileInfo.m_srcRoot = RuntimeOption::SourceRoot;
    }
    int srcRootLen = fileInfo.m_srcRoot.size();
    if (srcRootLen) {
      if (!strncmp(name.c_str(), fileInfo.m_srcRoot.c_str(), srcRootLen)) {
        fileInfo.m_relPath = string(name.c_str() + srcRootLen);
      }
    }
    hphp_hash_map<string, PhpFile*, string_hash>::iterator it =
      s_md5Files.find(fileInfo.m_md5);
    if (it != s_md5Files.end()) {
      PhpFile *f = it->second;
      if (!fileInfo.m_relPath.empty() &&
          fileInfo.m_relPath == f->getRelPath()) {
        fileInfo.m_phpFile = f;
      }
    }
  }
  return true;
}

PhpFile *FileRepository::parseFile(const std::string &name,
                                   const FileInfo &fileInfo) {
  vector<StaticStatementPtr> sts;
  Block::VariableIndices variableIndices;
  if (RuntimeOption::EnableEvalOptimization) {
    ScalarValueExpression::initScalarValues();
  }
  StatementPtr stmt =
    Parser::ParseString(fileInfo.m_inputString, name.c_str(),
                        sts, variableIndices);
  if (stmt && RuntimeOption::EnableEvalOptimization) {
    DummyVariableEnvironment env;
    stmt->optimize(env);
  }
  if (stmt) {
    if (RuntimeOption::EnableEvalOptimization) {
      ScalarValueExpression::registerScalarValues();
    } 
    PhpFile *p = new PhpFile(stmt, sts, variableIndices,
                             name, fileInfo.m_srcRoot,
                             fileInfo.m_relPath, fileInfo.m_md5);
    return p;
  }
  return NULL;
}

bool FileRepository::fileStat(const string &name, struct stat *s) {
  return stat(name.c_str(), s) == 0;
}

const char* FileRepository::canonicalize(const string &name) {
  return s_names.insert(name).first->c_str();
}

///////////////////////////////////////////////////////////////////////////////
}
}
