/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010 Facebook, Inc. (http://www.facebook.com)          |
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

#include "scanner.h"
#include <util/util.h>
#include <util/preprocess.h>

using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

Scanner::Scanner(const char *filename, int type)
    : m_source(NULL), m_len(0), m_pos(0), m_type(type), m_yyscanner(NULL),
      m_token(NULL), m_loc(NULL) {
  m_stream = new ifstream(filename);
  m_streamOwner = true;
  if (m_stream->bad()) {
    delete m_stream; m_stream = NULL;
    throw FileOpenException(filename);
  }
  if (type & PreprocessXHP) {
    istream *is = preprocessXHP(*m_stream, m_sstream, filename);
    if (m_stream != is) {
      delete m_stream;
      m_stream = is;
      m_streamOwner = false;
    }
  }
  init();
}

Scanner::Scanner(istream &stream, int type, const char *fileName /* = "" */)
    : m_source(NULL), m_len(0), m_pos(0), m_type(type), m_yyscanner(NULL),
      m_token(NULL), m_loc(NULL) {
  m_stream = &stream;
  m_streamOwner = false;
  if (type & PreprocessXHP) {
    istream *is = preprocessXHP(*m_stream, m_sstream, fileName);
    if (m_stream != is) {
      m_stream = is;
    }
  }
  init();
}

Scanner::Scanner(const char *source, int len, int type,
                 const char *fileName /* = "" */)
    : m_source(source), m_len(len), m_pos(0), m_type(type), m_yyscanner(NULL),
      m_token(NULL), m_loc(NULL) {
  ASSERT(m_source);
  m_stream = NULL;
  m_streamOwner = false;
  if (type & PreprocessXHP) {
    m_stream = new istringstream(string(source, len));
    m_streamOwner = true;
    istream *is = preprocessXHP(*m_stream, m_sstream, fileName);
    if (m_stream != is) {
      delete m_stream;
      m_stream = is;
      m_streamOwner = false;
    }
  }
  init();
}

Scanner::~Scanner() {
  reset();
  if (m_streamOwner) {
    delete m_stream;
  }
}

void Scanner::setHashBang(const char *rawText, int rawLeng) {
  if (m_type & ReturnAllTokens) {
    setToken(rawText, rawLeng);
  } else {
    setToken("", 0);
    incLoc(rawText, rawLeng);
  }
}

int Scanner::getNextToken(ScannerToken &t, Location &l) {
  m_token = &t;
  m_loc = &l;

  int tokid;
  bool done = false;
  do {
    tokid = scan();
    switch (tokid) {
      case T_COMMENT:
      case T_DOC_COMMENT:
      case T_OPEN_TAG:
      case T_WHITESPACE:
        break;
      default:
        done = true;
        break;
    }
  } while (!done && (m_type & ReturnAllTokens) == 0);

  return tokid;
}

int Scanner::read(char *text, int &result, int max) {
  if (m_stream) {
    if (!m_stream->eof()) {
      m_stream->read(text, max);
      if (!m_stream->bad()) {
        return (result = m_stream->gcount());
      }
    }
  } else if (m_source) {
    if (m_pos < m_len) {
      int count = m_len - m_pos;
      if (count > max) count = max;
      if (count > 0) {
        memcpy(text, m_source + m_pos, count);
        m_pos += count;
        return (result = count);
      }
    }
  }
  return (result = 0);
}

void Scanner::error(const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  Util::string_vsnprintf(m_error, fmt, ap);
  va_end(ap);
}

void Scanner::incLoc(const char *rawText, int rawLeng) {
  m_loc->line0 = m_loc->line1;
  m_loc->char0 = m_loc->char1;
  const char *p = rawText;
  for (int i = 0; i < rawLeng; i++) {
    if (*p++ == '\n') {
      m_loc->line1++;
      m_loc->char1 = 0;
    } else {
      m_loc->char1++;
    }
  }
}

string Scanner::escape(char *str, int len, char quote_type) const {
  string output;
  output.reserve(len);

  if (quote_type == '\'') {
    for (int i = 0; i < len; i++) {
      unsigned char ch = str[i];
      if (ch == '\\') {
        if (++i < len) {
          switch (str[i]) {
            case '\\': output += "\\"; break;
            case '\'': output += '\''; break;
            default: {
              output += ch;
              output += str[i];
              break;
            }
          }
        } else {
          ASSERT(false);
          output += ch;
        }
      } else {
        output += ch;
      }
    }
  } else {
    for (int i = 0; i < len; i++) {
      unsigned char ch = str[i];
      if (ch == '\\') {
        if (++i < len) {
          switch (str[i]) {
            case 'n':  output += '\n'; break;
            case 't':  output += '\t'; break;
            case 'r':  output += '\r'; break;
            case 'v':  output += '\v'; break;
            case 'f':  output += '\f'; break;
            case '\\': output += '\\'; break;
            case '$':  output += '$';  break;
            case '"':
              if (str[i] != quote_type) {
                output += '\\';
              }
              output += '"';
              break;
            case 'x':
            case 'X': {
              if (isxdigit(str[i+1])) {
                string shex;
                shex += str[++i]; // 0th hex digit
                if (isxdigit(str[i+1])) {
                  shex += str[++i]; // 1st hex digit
                }
                output += strtol(shex.c_str(), NULL, 16);
              } else {
                output += ch;
                output += str[i];
              }
              break;
            }
            default: {
              // check for an octal
              if ('0' <= str[i] && str[i] <= '7') {
                string soct;
                soct += str[i]; // 0th octal digit
                if ('0' <= str[i+1] && str[i+1] <= '7') {
                  soct += str[++i];   // 1st octal digit
                  if ('0' <= str[i+1] && str[i+1] <= '7') {
                    soct += str[++i]; // 2nd octal digit
                  }
                }
                output += strtol(soct.c_str(), NULL, 8);
              } else {
                output += ch;
                output += str[i];
              }
              break;
            }
          }
        } else {
          output += ch;
        }
      } else {
        output += ch;
      }
    }
  }
  return output;
}

///////////////////////////////////////////////////////////////////////////////
}
