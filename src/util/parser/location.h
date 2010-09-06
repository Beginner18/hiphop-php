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

#ifndef __HPHP_UTIL_PARSER_LOCATION_H__
#define __HPHP_UTIL_PARSER_LOCATION_H__

#include <util/base.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

DECLARE_BOOST_TYPES(Location);
class Location {
public:
  Location() : file(""), line0(0), char0(0), line1(0), char1(0) {}

  const char *file;
  int line0;
  int char0;
  int line1;
  int char1;

  void first(int line, char pos) {
    line0 = line; char0 = pos;
  }
  void first(Location &loc) {
    line0 = loc.line0; char0 = loc.char0;
  }
  void last(int line, char pos) {
    line1 = line; char1 = pos;
  }
  void last(Location &loc) {
    line1 = loc.line1; char1 = loc.char1;
  }
};

///////////////////////////////////////////////////////////////////////////////
}

#endif // __HPHP_UTIL_PARSER_LOCATION_H__
