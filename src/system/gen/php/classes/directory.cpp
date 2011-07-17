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

#include <php/classes/directory.h>
#include <php/classes/directory.fws.h>

// Dependencies
#include <runtime/ext/ext.h>
#include <runtime/eval/eval.h>
namespace hphp_impl_starter {}

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

/* preface starts */
extern CallInfo ci_;
/* preface finishes */
/* SRC: classes/directory.php line 3 */
#ifndef OMIT_JUMP_TABLE_CLASS_STATIC_GETINIT_Directory
Variant c_Directory::os_getInit(CStrRef s) {
  DECLARE_SYSTEM_GLOBALS(g);
  int64 hash = s->hash();
  switch (hash & 3) {
    case 0:
      HASH_RETURN_NAMSTR(0x1429F792A6880074LL, NAMSTR(s_sys_ssf362b3c4, "path"),
                         null, 4);
      break;
    case 2:
      HASH_RETURN_NAMSTR(0x5C4CA333F4541532LL, NAMSTR(s_sys_ss46eeef5c, "handle"),
                         null, 6);
      break;
    default:
      break;
  }
  return c_ObjectData::os_getInit(s);
}
#endif // OMIT_JUMP_TABLE_CLASS_STATIC_GETINIT_Directory
#ifndef OMIT_JUMP_TABLE_CLASS_STATIC_GET_Directory
Variant c_Directory::os_get(CStrRef s) {
  return c_ObjectData::os_get(s);
}
#endif // OMIT_JUMP_TABLE_CLASS_STATIC_GET_Directory
#ifndef OMIT_JUMP_TABLE_CLASS_STATIC_LVAL_Directory
Variant &c_Directory::os_lval(CStrRef s) {
  return c_ObjectData::os_lval(s);
}
#endif // OMIT_JUMP_TABLE_CLASS_STATIC_LVAL_Directory
#ifndef OMIT_JUMP_TABLE_CLASS_realProp_Directory
Variant * c_Directory::o_realProp(CStrRef prop, int flags, CStrRef context) const {
  return o_realPropPublic(prop, flags);
}
#endif // OMIT_JUMP_TABLE_CLASS_realProp_Directory
#ifndef OMIT_JUMP_TABLE_CLASS_realProp_PUBLIC_Directory
Variant * c_Directory::o_realPropPublic(CStrRef s, int flags) const {
  int64 hash = s->hash();
  switch (hash & 3) {
    case 0:
      HASH_REALPROP_NAMSTR(0x1429F792A6880074LL, NAMSTR(s_sys_ssf362b3c4, "path"), 4, path);
      break;
    case 2:
      HASH_REALPROP_NAMSTR(0x5C4CA333F4541532LL, NAMSTR(s_sys_ss46eeef5c, "handle"), 6, handle);
      break;
    default:
      break;
  }
  return c_ObjectData::o_realPropPublic(s, flags);
}
#endif // OMIT_JUMP_TABLE_CLASS_realProp_PUBLIC_Directory
#ifndef OMIT_JUMP_TABLE_CLASS_realProp_PRIVATE_Directory
Variant * c_Directory::o_realPropPrivate(CStrRef s, int flags) const {
  return o_realPropPublic(s, flags);
}
#endif // OMIT_JUMP_TABLE_CLASS_realProp_PRIVATE_Directory
#ifndef OMIT_JUMP_TABLE_CLASS_CONSTANT_Directory
Variant c_Directory::os_constant(const char *s) {
  return c_ObjectData::os_constant(s);
}
#endif // OMIT_JUMP_TABLE_CLASS_CONSTANT_Directory
IMPLEMENT_CLASS_NO_DEFAULT_SWEEP(Directory)
bool c_Directory::o_instanceof(CStrRef s) const {
  int64 hash = s->hash();
  switch (hash & 1) {
    case 1:
      HASH_INSTANCEOF(0x34C95AF311506C8FLL, NAMSTR(s_sys_ss55fe8ad6, "Directory"));
      break;
    default:
      break;
  }
  return false;
}
ObjectData *c_Directory::cloneImpl() {
  ObjectData *obj = coo_Directory();
  c_Directory::cloneSet(obj);
  return obj;
}
void c_Directory::cloneSet(ObjectData *cl) {
  c_Directory *clone = static_cast<c_Directory*>(cl);
  ObjectData::cloneSet(clone);
  clone->m_path.setWithRef(m_path);
  clone->m_handle.setWithRef(m_handle);
}
CallInfo c_Directory::ci___construct((void*)&c_Directory::i___construct, (void*)&c_Directory::ifa___construct, 1, 4, 0x0000000000000000LL);
CallInfo c_Directory::ci_close((void*)&c_Directory::i_close, (void*)&c_Directory::ifa_close, 0, 4, 0x0000000000000000LL);
CallInfo c_Directory::ci_read((void*)&c_Directory::i_read, (void*)&c_Directory::ifa_read, 0, 4, 0x0000000000000000LL);
CallInfo c_Directory::ci_rewind((void*)&c_Directory::i_rewind, (void*)&c_Directory::ifa_rewind, 0, 4, 0x0000000000000000LL);
Variant c_Directory::i___construct(MethodCallPackage &mcp, CArrRef params) {
  if (UNLIKELY(mcp.obj == 0)) {
    return ObjectData::i_dummy(mcp, params, i___construct, coo_Directory);
  }
  c_Directory *self ATTRIBUTE_UNUSED (static_cast<c_Directory*>(mcp.obj));
  int count ATTRIBUTE_UNUSED = params.size();
  if (UNLIKELY(count != 1)) return throw_wrong_arguments("Directory::__construct", count, 1, 1, 2);
  {
    ArrayData *ad(params.get());
    ssize_t pos = ad ? ad->iter_begin() : ArrayData::invalid_index;
    CVarRef arg0((ad->getValue(pos)));
    return (self->t___construct(arg0), null);
  }
}
Variant c_Directory::i_close(MethodCallPackage &mcp, CArrRef params) {
  if (UNLIKELY(mcp.obj == 0)) {
    return ObjectData::i_dummy(mcp, params, i_close, coo_Directory);
  }
  c_Directory *self ATTRIBUTE_UNUSED (static_cast<c_Directory*>(mcp.obj));
  int count ATTRIBUTE_UNUSED = params.size();
  if (UNLIKELY(count > 0)) return throw_toomany_arguments("Directory::close", 0, 1);
  return (self->t_close(), null);
}
Variant c_Directory::i_read(MethodCallPackage &mcp, CArrRef params) {
  if (UNLIKELY(mcp.obj == 0)) {
    return ObjectData::i_dummy(mcp, params, i_read, coo_Directory);
  }
  c_Directory *self ATTRIBUTE_UNUSED (static_cast<c_Directory*>(mcp.obj));
  int count ATTRIBUTE_UNUSED = params.size();
  if (UNLIKELY(count > 0)) return throw_toomany_arguments("Directory::read", 0, 1);
  return (self->t_read());
}
Variant c_Directory::i_rewind(MethodCallPackage &mcp, CArrRef params) {
  if (UNLIKELY(mcp.obj == 0)) {
    return ObjectData::i_dummy(mcp, params, i_rewind, coo_Directory);
  }
  c_Directory *self ATTRIBUTE_UNUSED (static_cast<c_Directory*>(mcp.obj));
  int count ATTRIBUTE_UNUSED = params.size();
  if (UNLIKELY(count > 0)) return throw_toomany_arguments("Directory::rewind", 0, 1);
  return (self->t_rewind(), null);
}
Variant c_Directory::ifa___construct(MethodCallPackage &mcp, int count, INVOKE_FEW_ARGS_IMPL_ARGS) {
  if (UNLIKELY(mcp.obj == 0)) {
    return ObjectData::ifa_dummy(mcp, count, INVOKE_FEW_ARGS_PASS_ARGS, ifa___construct, coo_Directory);
  }
  c_Directory *self ATTRIBUTE_UNUSED (static_cast<c_Directory*>(mcp.obj));
  if (UNLIKELY(count != 1)) return throw_wrong_arguments("Directory::__construct", count, 1, 1, 2);
  CVarRef arg0(a0);
  return (self->t___construct(arg0), null);
}
Variant c_Directory::ifa_close(MethodCallPackage &mcp, int count, INVOKE_FEW_ARGS_IMPL_ARGS) {
  if (UNLIKELY(mcp.obj == 0)) {
    return ObjectData::ifa_dummy(mcp, count, INVOKE_FEW_ARGS_PASS_ARGS, ifa_close, coo_Directory);
  }
  c_Directory *self ATTRIBUTE_UNUSED (static_cast<c_Directory*>(mcp.obj));
  if (UNLIKELY(count > 0)) return throw_toomany_arguments("Directory::close", 0, 1);
  return (self->t_close(), null);
}
Variant c_Directory::ifa_read(MethodCallPackage &mcp, int count, INVOKE_FEW_ARGS_IMPL_ARGS) {
  if (UNLIKELY(mcp.obj == 0)) {
    return ObjectData::ifa_dummy(mcp, count, INVOKE_FEW_ARGS_PASS_ARGS, ifa_read, coo_Directory);
  }
  c_Directory *self ATTRIBUTE_UNUSED (static_cast<c_Directory*>(mcp.obj));
  if (UNLIKELY(count > 0)) return throw_toomany_arguments("Directory::read", 0, 1);
  return (self->t_read());
}
Variant c_Directory::ifa_rewind(MethodCallPackage &mcp, int count, INVOKE_FEW_ARGS_IMPL_ARGS) {
  if (UNLIKELY(mcp.obj == 0)) {
    return ObjectData::ifa_dummy(mcp, count, INVOKE_FEW_ARGS_PASS_ARGS, ifa_rewind, coo_Directory);
  }
  c_Directory *self ATTRIBUTE_UNUSED (static_cast<c_Directory*>(mcp.obj));
  if (UNLIKELY(count > 0)) return throw_toomany_arguments("Directory::rewind", 0, 1);
  return (self->t_rewind(), null);
}
bool c_Directory::os_get_call_info(MethodCallPackage &mcp, int64 hash) {
  CStrRef s ATTRIBUTE_UNUSED (*mcp.name);
  if (hash < 0) hash = s->hash();
  switch (hash & 7) {
    case 1:
      HASH_GUARD_LITSTR(0x78AE97BFBEBF5341LL, NAMSTR(s_sys_ssf052ec6b, "close")) {
        mcp.ci = &c_Directory::ci_close;
        return true;
      }
      HASH_GUARD_LITSTR(0x1F479267E49EF301LL, NAMSTR(s_sys_sse896cb09, "read")) {
        mcp.ci = &c_Directory::ci_read;
        return true;
      }
      break;
    case 2:
      HASH_GUARD_LITSTR(0x1670096FDE27AF6ALL, NAMSTR(s_sys_ss941ca25f, "rewind")) {
        mcp.ci = &c_Directory::ci_rewind;
        return true;
      }
      break;
    case 7:
      HASH_GUARD_LITSTR(0x0D31D0AC229C615FLL, NAMSTR(s_sys_ssa1b87da7, "__construct")) {
        mcp.ci = &c_Directory::ci___construct;
        return true;
      }
      break;
    default:
      break;
  }
  return c_ObjectData::os_get_call_info(mcp, hash);
}
bool c_Directory::o_get_call_info(MethodCallPackage &mcp, int64 hash) {
  mcp.obj = this;
  return os_get_call_info(mcp, hash);
}
c_Directory *c_Directory::create(CVarRef v_path) {
  CountableHelper h(this);
  init();
  t___construct(v_path);
  return this;
}
void c_Directory::dynConstruct(CArrRef params) {
  int count ATTRIBUTE_UNUSED = params.size();
  if (UNLIKELY(count != 1)) throw_wrong_arguments("Directory::__construct", count, 1, 1, 2);
  {
    ArrayData *ad(params.get());
    ssize_t pos = ad ? ad->iter_begin() : ArrayData::invalid_index;
    CVarRef arg0((ad->getValue(pos)));
    (t___construct(arg0));
  }
}
void c_Directory::getConstructor(MethodCallPackage &mcp) {
  mcp.ci = &c_Directory::ci___construct;
  mcp.obj = this;
}
struct ObjectStaticCallbacks cw_Directory = {
  c_Directory::os_getInit,
  c_Directory::os_get,
  c_Directory::os_lval,
  c_Directory::os_invoke,
  c_Directory::os_constant,
  c_Directory::os_get_call_info
};
/* SRC: classes/directory.php line 7 */
void c_Directory::t___construct(Variant v_path) {
  INSTANCE_METHOD_INJECTION_BUILTIN(Directory, Directory::__construct);
  bool oldInCtor = gasInCtor(true);
  m_path.assignVal(v_path);
  {
    const Variant &tmp0((x_opendir(toString(v_path))));
    m_handle.assignVal(tmp0);
  }
  gasInCtor(oldInCtor);
}
namespace hphp_impl_splitter {}
/* SRC: classes/directory.php line 12 */
Variant c_Directory::t_read() {
  INSTANCE_METHOD_INJECTION_BUILTIN(Directory, Directory::read);
  return x_readdir(toObject(m_handle));
}
namespace hphp_impl_splitter {}
/* SRC: classes/directory.php line 16 */
void c_Directory::t_rewind() {
  INSTANCE_METHOD_INJECTION_BUILTIN(Directory, Directory::rewind);
  x_rewinddir(toObject(m_handle));
}
namespace hphp_impl_splitter {}
/* SRC: classes/directory.php line 20 */
void c_Directory::t_close() {
  INSTANCE_METHOD_INJECTION_BUILTIN(Directory, Directory::close);
  x_closedir(toObject(m_handle));
}
namespace hphp_impl_splitter {}
ObjectData *coo_Directory() {
  return NEWOBJ(c_Directory)();
}
Variant pm_php$classes$directory_php(bool incOnce, LVariableTable* variables, Globals *globals) {
  PSEUDOMAIN_INJECTION_BUILTIN(run_init::classes/directory.php, pm_php$classes$directory_php);
  LVariableTable *gVariables ATTRIBUTE_UNUSED = (LVariableTable *)g;
  return true;
}
namespace hphp_impl_splitter {}

// Class tables
ClassPropTable cpt_Directory;
static int ctInitializer() {
  const char *ctMapData[] = {
    (const char *)2, (const char *)0, (const char *)&cpt_Directory, (const char *)NULL,
    (const char *)64, (const char *)&NAMSTR(s_sys_ssf362b3c4, "path"),
    (const char *)GET_PROPERTY_OFFSET(c_Directory, m_path),
    (const char *)10,
    (const char *)64, (const char *)&NAMSTR(s_sys_ss46eeef5c, "handle"),
    (const char *)GET_PROPERTY_OFFSET(c_Directory, m_handle),
    (const char *)10,

    NULL, NULL, NULL,
  };
  static ClassPropTableEntry entries[2];
  static ClassPropTableEntry *pentries[1];
  return ClassInfo::InitClassPropTable(ctMapData, entries, pentries);
}
static int ct_initializer = ctInitializer();

// o_getClassPropTable
const ClassPropTable *c_Directory::o_getClassPropTable() const { return &cpt_Directory; }

///////////////////////////////////////////////////////////////////////////////
}
