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
#include <runtime/base/array/array_init.h>
#include <runtime/base/array/zend_array.h>
#include <runtime/base/array/small_array.h>
#include <runtime/base/runtime_option.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////
// ArrayInit

ArrayInit::ArrayInit(ssize_t n, bool isVector /* = false */,
                     bool keepRef /* = false */) : m_data(NULL) {
  if (n == 0) {
    if (RuntimeOption::UseSmallArray && !keepRef) {
      m_data = StaticEmptySmallArray::Get();
    } else {
      m_data = StaticEmptyZendArray::Get();
    }
  } else if (n <= SmallArray::SARR_SIZE && !keepRef &&
             RuntimeOption::UseSmallArray) {
    m_data = NEW(SmallArray)();
  } else {
    m_data = NEW(ZendArray)(n);
  }
}

///////////////////////////////////////////////////////////////////////////////
}
