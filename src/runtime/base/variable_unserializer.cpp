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

#include <runtime/base/variable_unserializer.h>
#include <runtime/base/complex_types.h>


using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

Variant VariableUnserializer::unserialize() {
  Variant v;
  v.unserialize(this);
  return v;
}

Variant VariableUnserializer::unserializeKey() {
  m_key = true;
  Variant v;
  v.unserialize(this);
  m_key = false;
  return v;
}

int64 VariableUnserializer::readInt() {
  check();
  char *newBuf;
  int64 r = strtoll(m_buf, &newBuf, 10);
  m_buf = newBuf;
  return r;
}

double VariableUnserializer::readDouble() {
  check();
  char *newBuf;
  double r = strtod(m_buf, &newBuf);
  m_buf = newBuf;
  return r;
}

void VariableUnserializer::read(char *buf, uint n) {
  check();
  uint i = 0;
  for (; i < n && m_buf != m_end; ++i) {
    buf[i] = *(m_buf++);
  }
}

///////////////////////////////////////////////////////////////////////////////
}
