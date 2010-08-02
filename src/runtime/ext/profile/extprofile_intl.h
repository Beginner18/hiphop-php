/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010 Facebook, Inc. (http://www.facebook.com)          |
   | Copyright (c) 1997-2010 The PHP Group                                |
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

#ifndef __EXTPROFILE_INTL_H__
#define __EXTPROFILE_INTL_H__

// >>>>>> Generated by idl.php. Do NOT modify. <<<<<<

#include <runtime/ext/ext_intl.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

inline int64 x_intl_get_error_code() {
  FUNCTION_INJECTION_BUILTIN(intl_get_error_code);
  return f_intl_get_error_code();
}

inline String x_intl_get_error_message() {
  FUNCTION_INJECTION_BUILTIN(intl_get_error_message);
  return f_intl_get_error_message();
}

inline String x_intl_error_name(int64 error_code) {
  FUNCTION_INJECTION_BUILTIN(intl_error_name);
  return f_intl_error_name(error_code);
}

inline bool x_intl_is_failure(int64 error_code) {
  FUNCTION_INJECTION_BUILTIN(intl_is_failure);
  return f_intl_is_failure(error_code);
}

inline Variant x_collator_asort(CVarRef obj, Variant arr, int64 sort_flag = 0) {
  FUNCTION_INJECTION_BUILTIN(collator_asort);
  return f_collator_asort(obj, ref(arr), sort_flag);
}

inline Variant x_collator_compare(CVarRef obj, CStrRef str1, CStrRef str2) {
  FUNCTION_INJECTION_BUILTIN(collator_compare);
  return f_collator_compare(obj, str1, str2);
}

inline Variant x_collator_create(CStrRef locale) {
  FUNCTION_INJECTION_BUILTIN(collator_create);
  return f_collator_create(locale);
}

inline Variant x_collator_get_attribute(CVarRef obj, int64 attr) {
  FUNCTION_INJECTION_BUILTIN(collator_get_attribute);
  return f_collator_get_attribute(obj, attr);
}

inline Variant x_collator_get_error_code(CVarRef obj) {
  FUNCTION_INJECTION_BUILTIN(collator_get_error_code);
  return f_collator_get_error_code(obj);
}

inline Variant x_collator_get_error_message(CVarRef obj) {
  FUNCTION_INJECTION_BUILTIN(collator_get_error_message);
  return f_collator_get_error_message(obj);
}

inline Variant x_collator_get_locale(CVarRef obj, int64 type = 0) {
  FUNCTION_INJECTION_BUILTIN(collator_get_locale);
  return f_collator_get_locale(obj, type);
}

inline Variant x_collator_get_strength(CVarRef obj) {
  FUNCTION_INJECTION_BUILTIN(collator_get_strength);
  return f_collator_get_strength(obj);
}

inline Variant x_collator_set_attribute(CVarRef obj, int64 attr, int64 val) {
  FUNCTION_INJECTION_BUILTIN(collator_set_attribute);
  return f_collator_set_attribute(obj, attr, val);
}

inline Variant x_collator_set_strength(CVarRef obj, int64 strength) {
  FUNCTION_INJECTION_BUILTIN(collator_set_strength);
  return f_collator_set_strength(obj, strength);
}

inline Variant x_collator_sort_with_sort_keys(CVarRef obj, Variant arr) {
  FUNCTION_INJECTION_BUILTIN(collator_sort_with_sort_keys);
  return f_collator_sort_with_sort_keys(obj, ref(arr));
}

inline Variant x_collator_sort(CVarRef obj, Variant arr, int64 sort_flag = 0) {
  FUNCTION_INJECTION_BUILTIN(collator_sort);
  return f_collator_sort(obj, ref(arr), sort_flag);
}

inline Variant x_idn_to_ascii(CStrRef domain, Variant errorcode = null) {
  FUNCTION_INJECTION_BUILTIN(idn_to_ascii);
  return f_idn_to_ascii(domain, ref(errorcode));
}

inline Variant x_idn_to_unicode(CStrRef domain, Variant errorcode = null) {
  FUNCTION_INJECTION_BUILTIN(idn_to_unicode);
  return f_idn_to_unicode(domain, ref(errorcode));
}

inline Variant x_idn_to_utf8(CStrRef domain, Variant errorcode = null) {
  FUNCTION_INJECTION_BUILTIN(idn_to_utf8);
  return f_idn_to_utf8(domain, ref(errorcode));
}


///////////////////////////////////////////////////////////////////////////////
}

#endif // __EXTPROFILE_INTL_H__
