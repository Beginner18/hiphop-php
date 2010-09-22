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
#ifndef __HPHP_ACCESS_LOG_H__
#define __HPHP_ACCESS_LOG_H__

#include <runtime/base/base_includes.h>
#include <util/thread_local.h>
#include <util/lock.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

class AccessLog {
public:
  class ThreadData {
  public:
    ThreadData() : log(NULL) {}
    FILE *log;
    int64 startTime;
  };
  typedef ThreadData* (*GetThreadDataFunc)();
  AccessLog(GetThreadDataFunc f) :
      m_initialized(false), m_fGetThreadData(f) {}
  ~AccessLog();
  bool init(const std::string &defaultFormat,
            std::vector<std::pair<std::string, std::string> > &files);
  bool init(const std::string &format, const std::string &file);
  void log(Transport *transport, const VirtualHost *vhost);
  bool setThreadLog(const char *file);
  void clearThreadLog();
  void onNewRequest();
  std::string &defaultFormat() { return m_defaultFormat; }
  std::vector<std::pair<std::string, std::string> > &files() {
    return m_files;
  }
private:
  bool parseConditions(const char* &format, int code);
  std::string parseArgument(const char* &format);
  bool genField(std::ostringstream &out, const char* &format,
                Transport *transport, const VirtualHost *vhost,
                const std::string &arg);
  void skipField(const char* &format);
  void writeLog(Transport *transport, const VirtualHost *vhost,
                FILE *outFile, const char *format);

  std::vector<FILE*> m_output;
  bool m_initialized;
  GetThreadDataFunc m_fGetThreadData;
  std::string m_defaultFormat;
  std::vector<std::pair<std::string, std::string> > m_files;

  bool openFiles();
  Mutex m_initLock;
};

///////////////////////////////////////////////////////////////////////////////
}

#endif // __HPHP_ACCESS_LOG_H__
