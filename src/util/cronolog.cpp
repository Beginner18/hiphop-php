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

#include <util/cronolog.h>

using namespace std;

/* Default permissions for files and directories that are created */

#ifndef FILE_MODE
#define FILE_MODE       ( S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH )
#endif

namespace HPHP {

///////////////////////////////////////////////////////////////////////////////

/* Open a new log file: determine the start of the current
 * period, generate the log file name from the fileTemplate,
 * determine the end of the period and open the new log file.
 *
 * Returns the file descriptor of the new log file and also sets the
 * name of the file and the start time of the next period via pointers
 * supplied.
 */
static FILE *new_log_file(const char *fileTemplate, const char *linkname,
                          mode_t linktype, const char *prevlinkname,
                          PERIODICITY periodicity, int period_multiple,
                          int period_delay, char *pfilename,
                          size_t pfilename_len, time_t time_now,
                          time_t *pnext_period) {
  time_t start_of_period;
  struct tm   *tm;
  int log_fd;

  start_of_period = start_of_this_period(time_now, periodicity,
                                         period_multiple);
  tm = localtime(&start_of_period);
  strftime(pfilename, pfilename_len, fileTemplate, tm);
  *pnext_period = start_of_next_period(start_of_period, periodicity,
                                       period_multiple) + period_delay;

  DEBUG(("%s (%d): using log file \"%s\" from %s (%d) until %s (%d) "
        "(for %d secs)\n",
        timestamp(time_now), time_now, pfilename,
        timestamp(start_of_period), start_of_period,
        timestamp(*pnext_period), *pnext_period,
        *pnext_period - time_now));

  log_fd = open(pfilename, O_WRONLY|O_CREAT|O_APPEND, FILE_MODE);

#ifndef DONT_CREATE_SUBDIRS
  if ((log_fd == 0) && (errno == ENOENT)) {
    create_subdirs(pfilename);
    log_fd = open(pfilename, O_WRONLY|O_CREAT|O_APPEND, FILE_MODE);
  }
#endif

  if (log_fd < 0) {
    perror(pfilename);
    exit(2);
  }

  if (linkname) {
    create_link(pfilename, linkname, linktype, prevlinkname);
  }
  return fdopen(log_fd, "a");
}

void Cronolog::setPeriodicity() {
  if (m_periodicity == UNKNOWN) {
    m_periodicity = determine_periodicity((char *)m_template.c_str());
  }
}

FILE *Cronolog::getOutputFile() {
  if (m_template.empty()) return m_file;

  time_t time_now = time(NULL) + m_timeOffset;
  /* If the current period has finished and there is a log file
   * open, close the log file
   */
  if ((time_now >= m_nextPeriod) && (m_file)) {
    fclose(m_file);
    m_file = NULL;
  }

  /* If there is no log file open then open a new one. */
  if (m_file == NULL) {
    m_file = new_log_file(m_template.c_str(), m_linkName.c_str(), S_IFLNK,
                          m_prevLinkName, m_periodicity, m_periodMultiple,
                          m_periodDelay, m_fileName, sizeof(m_fileName),
                          time_now, &m_nextPeriod);
  }
  return m_file;
}

///////////////////////////////////////////////////////////////////////////////
}
