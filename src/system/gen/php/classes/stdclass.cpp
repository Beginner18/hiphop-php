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
// @generated by HipHop Compiler

#include <php/classes/stdclass.h>
#include <php/classes/stdclass.fws.h>

// Dependencies
#include <runtime/ext/ext.h>
#include <runtime/eval/eval.h>
namespace hphp_impl_starter {}

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

/* preface starts */
extern CallInfo ci_;
/* preface finishes */
/* SRC: classes/stdclass.php line 4 */
#ifndef OMIT_JUMP_TABLE_CLASS_STATIC_GETINIT_stdClass
Variant c_stdClass::os_getInit(CStrRef s) {
  return c_ObjectData::os_getInit(s);
}
#endif // OMIT_JUMP_TABLE_CLASS_STATIC_GETINIT_stdClass
#ifndef OMIT_JUMP_TABLE_CLASS_STATIC_GET_stdClass
Variant c_stdClass::os_get(CStrRef s) {
  return c_ObjectData::os_get(s);
}
#endif // OMIT_JUMP_TABLE_CLASS_STATIC_GET_stdClass
#ifndef OMIT_JUMP_TABLE_CLASS_STATIC_LVAL_stdClass
Variant &c_stdClass::os_lval(CStrRef s) {
  return c_ObjectData::os_lval(s);
}
#endif // OMIT_JUMP_TABLE_CLASS_STATIC_LVAL_stdClass
#ifndef OMIT_JUMP_TABLE_CLASS_realProp_stdClass
Variant * c_stdClass::o_realProp(CStrRef prop, int flags, CStrRef context) const {
  return o_realPropPublic(prop, flags);
}
#endif // OMIT_JUMP_TABLE_CLASS_realProp_stdClass
#ifndef OMIT_JUMP_TABLE_CLASS_realProp_PUBLIC_stdClass
Variant * c_stdClass::o_realPropPublic(CStrRef s, int flags) const {
  return c_ObjectData::o_realPropPublic(s, flags);
}
#endif // OMIT_JUMP_TABLE_CLASS_realProp_PUBLIC_stdClass
#ifndef OMIT_JUMP_TABLE_CLASS_realProp_PRIVATE_stdClass
Variant * c_stdClass::o_realPropPrivate(CStrRef s, int flags) const {
  return o_realPropPublic(s, flags);
}
#endif // OMIT_JUMP_TABLE_CLASS_realProp_PRIVATE_stdClass
#ifndef OMIT_JUMP_TABLE_CLASS_CONSTANT_stdClass
Variant c_stdClass::os_constant(const char *s) {
  return c_ObjectData::os_constant(s);
}
#endif // OMIT_JUMP_TABLE_CLASS_CONSTANT_stdClass
IMPLEMENT_CLASS_NO_DEFAULT_SWEEP(stdClass)
bool c_stdClass::o_instanceof(CStrRef s) const {
  int64 hash = s->hash();
  switch (hash & 1) {
    case 1:
      HASH_INSTANCEOF(0x3D69936178BA13F7LL, NAMSTR(s_sys_ss426361a3, "stdClass"));
      break;
    default:
      break;
  }
  return false;
}
ObjectData *c_stdClass::cloneImpl() {
  ObjectData *obj = coo_stdClass();
  c_stdClass::cloneSet(obj);
  return obj;
}
void c_stdClass::cloneSet(ObjectData *cl) {
  c_stdClass *clone = static_cast<c_stdClass*>(cl);
  ObjectData::cloneSet(clone);
}
bool c_stdClass::os_get_call_info(MethodCallPackage &mcp, int64 hash) {
  CStrRef s ATTRIBUTE_UNUSED (*mcp.name);
  return c_ObjectData::os_get_call_info(mcp, hash);
}
bool c_stdClass::o_get_call_info(MethodCallPackage &mcp, int64 hash) {
  mcp.obj = this;
  return os_get_call_info(mcp, hash);
}
struct ObjectStaticCallbacks cw_stdClass = {
  c_stdClass::os_getInit,
  c_stdClass::os_get,
  c_stdClass::os_lval,
  c_stdClass::os_invoke,
  c_stdClass::os_constant,
  c_stdClass::os_get_call_info
};
/* SRC: classes/stdclass.php line 8 */
#ifndef OMIT_JUMP_TABLE_CLASS_STATIC_GETINIT___PHP_Incomplete_Class
Variant c___PHP_Incomplete_Class::os_getInit(CStrRef s) {
  return c_ObjectData::os_getInit(s);
}
#endif // OMIT_JUMP_TABLE_CLASS_STATIC_GETINIT___PHP_Incomplete_Class
#ifndef OMIT_JUMP_TABLE_CLASS_STATIC_GET___PHP_Incomplete_Class
Variant c___PHP_Incomplete_Class::os_get(CStrRef s) {
  return c_ObjectData::os_get(s);
}
#endif // OMIT_JUMP_TABLE_CLASS_STATIC_GET___PHP_Incomplete_Class
#ifndef OMIT_JUMP_TABLE_CLASS_STATIC_LVAL___PHP_Incomplete_Class
Variant &c___PHP_Incomplete_Class::os_lval(CStrRef s) {
  return c_ObjectData::os_lval(s);
}
#endif // OMIT_JUMP_TABLE_CLASS_STATIC_LVAL___PHP_Incomplete_Class
#ifndef OMIT_JUMP_TABLE_CLASS_realProp___PHP_Incomplete_Class
Variant * c___PHP_Incomplete_Class::o_realProp(CStrRef prop, int flags, CStrRef context) const {
  return o_realPropPublic(prop, flags);
}
#endif // OMIT_JUMP_TABLE_CLASS_realProp___PHP_Incomplete_Class
#ifndef OMIT_JUMP_TABLE_CLASS_realProp_PUBLIC___PHP_Incomplete_Class
Variant * c___PHP_Incomplete_Class::o_realPropPublic(CStrRef s, int flags) const {
  return c_ObjectData::o_realPropPublic(s, flags);
}
#endif // OMIT_JUMP_TABLE_CLASS_realProp_PUBLIC___PHP_Incomplete_Class
#ifndef OMIT_JUMP_TABLE_CLASS_realProp_PRIVATE___PHP_Incomplete_Class
Variant * c___PHP_Incomplete_Class::o_realPropPrivate(CStrRef s, int flags) const {
  return o_realPropPublic(s, flags);
}
#endif // OMIT_JUMP_TABLE_CLASS_realProp_PRIVATE___PHP_Incomplete_Class
#ifndef OMIT_JUMP_TABLE_CLASS_CONSTANT___PHP_Incomplete_Class
Variant c___PHP_Incomplete_Class::os_constant(const char *s) {
  return c_ObjectData::os_constant(s);
}
#endif // OMIT_JUMP_TABLE_CLASS_CONSTANT___PHP_Incomplete_Class
IMPLEMENT_CLASS_NO_DEFAULT_SWEEP(__PHP_Incomplete_Class)
bool c___PHP_Incomplete_Class::o_instanceof(CStrRef s) const {
  int64 hash = s->hash();
  switch (hash & 1) {
    case 0:
      HASH_INSTANCEOF(0x6576EACCCE24D694LL, NAMSTR(s_sys_ssd8c10a25, "__PHP_Incomplete_Class"));
      break;
    default:
      break;
  }
  return false;
}
ObjectData *c___PHP_Incomplete_Class::cloneImpl() {
  ObjectData *obj = coo___PHP_Incomplete_Class();
  c___PHP_Incomplete_Class::cloneSet(obj);
  return obj;
}
void c___PHP_Incomplete_Class::cloneSet(ObjectData *cl) {
  c___PHP_Incomplete_Class *clone = static_cast<c___PHP_Incomplete_Class*>(cl);
  ObjectData::cloneSet(clone);
}
bool c___PHP_Incomplete_Class::os_get_call_info(MethodCallPackage &mcp, int64 hash) {
  CStrRef s ATTRIBUTE_UNUSED (*mcp.name);
  return c_ObjectData::os_get_call_info(mcp, hash);
}
bool c___PHP_Incomplete_Class::o_get_call_info(MethodCallPackage &mcp, int64 hash) {
  mcp.obj = this;
  return os_get_call_info(mcp, hash);
}
struct ObjectStaticCallbacks cw___PHP_Incomplete_Class = {
  c___PHP_Incomplete_Class::os_getInit,
  c___PHP_Incomplete_Class::os_get,
  c___PHP_Incomplete_Class::os_lval,
  c___PHP_Incomplete_Class::os_invoke,
  c___PHP_Incomplete_Class::os_constant,
  c___PHP_Incomplete_Class::os_get_call_info
};
ObjectData *coo_stdClass() {
  return NEWOBJ(c_stdClass)();
}
ObjectData *coo___PHP_Incomplete_Class() {
  return NEWOBJ(c___PHP_Incomplete_Class)();
}
Variant pm_php$classes$stdclass_php(bool incOnce, LVariableTable* variables, Globals *globals) {
  PSEUDOMAIN_INJECTION_BUILTIN(run_init::classes/stdclass.php, pm_php$classes$stdclass_php);
  LVariableTable *gVariables ATTRIBUTE_UNUSED = (LVariableTable *)g;
  return true;
}
namespace hphp_impl_splitter {}

// Class tables

// o_getClassPropTable

///////////////////////////////////////////////////////////////////////////////
}
