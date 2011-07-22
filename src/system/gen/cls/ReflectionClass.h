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

#ifndef __GENERATED_cls_ReflectionClass_hf4d8c830__
#define __GENERATED_cls_ReflectionClass_hf4d8c830__

#include <cls/ReflectionClass.fw.h>
#include <cls/Reflector.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

/* SRC: classes/reflection.php line 538 */
FORWARD_DECLARE_CLASS(ReflectionClass);
extern ObjectStaticCallbacks cw_ReflectionClass;
class c_ReflectionClass : public ExtObjectData {
  public:

  // Properties
  Variant m_name;
  Variant m_info;

  // Class Map
  virtual bool o_instanceof(CStrRef s) const;
  DECLARE_CLASS_COMMON_NO_SWEEP(ReflectionClass, ReflectionClass)

  // DECLARE_STATIC_PROP_OPS
  public:
  static Variant os_getInit(CStrRef s);
  #define OMIT_JUMP_TABLE_CLASS_STATIC_GET_ReflectionClass 1
  #define OMIT_JUMP_TABLE_CLASS_STATIC_LVAL_ReflectionClass 1
  static Variant os_constant(const char *s);

  // DECLARE_INSTANCE_PROP_OPS
  public:
  virtual const ClassPropTable *o_getClassPropTable() const;
  virtual Variant *o_realProp(CStrRef s, int flags,
                              CStrRef context = null_string) const;
  Variant *o_realPropPrivate(CStrRef s, int flags) const;

  // DECLARE_INSTANCE_PUBLIC_PROP_OPS
  public:
  virtual Variant *o_realPropPublic(CStrRef s, int flags) const;

  // DECLARE_COMMON_INVOKE
  static const MethodCallInfoTable s_call_info_table[];
  static const int s_call_info_index[];

  public:
  c_ReflectionClass() : m_name(Variant::nullInit), m_info(Variant::nullInit) {}
  public: void t___construct(Variant v_name);
  public: c_ReflectionClass *create(CVarRef v_name);
  public: void dynConstruct(CArrRef params);
  public: void getConstructor(MethodCallPackage &mcp);
  public: Variant t_fetch(CVarRef v_what);
  public: bool t_test(CVarRef v_what, CVarRef v_name);
  public: String t___tostring();
  public: static Variant t_export(CVarRef v_name, CVarRef v_ret);
  public: Variant t_getname();
  public: Variant t_isinternal();
  public: bool t_isuserdefined();
  public: bool t_isinstantiable();
  public: bool t_hasconstant(CVarRef v_name);
  public: bool t_hasmethod(CVarRef v_name);
  public: bool t_hasproperty(CVarRef v_name);
  public: Variant t_getfilename();
  public: Variant t_getstartline();
  public: Variant t_getendline();
  public: Variant t_getdoccomment();
  public: Variant t_getconstructor();
  public: p_ReflectionMethod t_getmethod(CVarRef v_name);
  public: Array t_getmethods(CVarRef v_filter = NAMVAR(s_sys_svi5830e7c6, 65535LL));
  public: p_ReflectionProperty t_getproperty(CVarRef v_name);
  public: Array t_getproperties(CVarRef v_filter = NAMVAR(s_sys_svi5830e7c6, 65535LL));
  public: Variant t_getconstants();
  public: Variant t_getconstant(CVarRef v_name);
  public: Array t_getinterfaces();
  public: Array t_getinterfacenames();
  public: Variant t_isinterface();
  public: Variant t_isabstract();
  public: Variant t_isfinal();
  public: Variant t_getmodifiers();
  public: bool t_isinstance(CVarRef v_obj);
  public: Object t_newinstance(int num_args, Array args = Array());
  public: Object t_newinstanceargs(CVarRef v_args);
  public: Variant t_getparentclass();
  public: Variant t_issubclassof(Variant v_cls);
  public: Array t_getstaticproperties();
  public: Variant t_getstaticpropertyvalue(CVarRef v_name, CVarRef v_default = null_variant);
  public: void t_setstaticpropertyvalue(CVarRef v_name, CVarRef v_value);
  public: Array t_getdefaultproperties();
  public: Variant t_isiterateable();
  public: bool t_implementsinterface(Variant v_cls);
  public: Variant t_getextension();
  public: Variant t_getextensionname();
  DECLARE_METHOD_INVOKE_HELPERS(getmethods);
  DECLARE_METHOD_INVOKE_HELPERS(isiterateable);
  DECLARE_METHOD_INVOKE_HELPERS(getstaticpropertyvalue);
  DECLARE_METHOD_INVOKE_HELPERS(isuserdefined);
  DECLARE_METHOD_INVOKE_HELPERS(newinstance);
  DECLARE_METHOD_INVOKE_HELPERS(getextension);
  DECLARE_METHOD_INVOKE_HELPERS(getconstructor);
  DECLARE_METHOD_INVOKE_HELPERS(__tostring);
  DECLARE_METHOD_INVOKE_HELPERS(newinstanceargs);
  DECLARE_METHOD_INVOKE_HELPERS(getendline);
  DECLARE_METHOD_INVOKE_HELPERS(isinstance);
  DECLARE_METHOD_INVOKE_HELPERS(hasmethod);
  DECLARE_METHOD_INVOKE_HELPERS(__construct);
  DECLARE_METHOD_INVOKE_HELPERS(isfinal);
  DECLARE_METHOD_INVOKE_HELPERS(getmodifiers);
  DECLARE_METHOD_INVOKE_HELPERS(export);
  DECLARE_METHOD_INVOKE_HELPERS(getproperties);
  DECLARE_METHOD_INVOKE_HELPERS(hasconstant);
  DECLARE_METHOD_INVOKE_HELPERS(getmethod);
  DECLARE_METHOD_INVOKE_HELPERS(getextensionname);
  DECLARE_METHOD_INVOKE_HELPERS(getparentclass);
  DECLARE_METHOD_INVOKE_HELPERS(getfilename);
  DECLARE_METHOD_INVOKE_HELPERS(implementsinterface);
  DECLARE_METHOD_INVOKE_HELPERS(getinterfacenames);
  DECLARE_METHOD_INVOKE_HELPERS(getconstant);
  DECLARE_METHOD_INVOKE_HELPERS(getstartline);
  DECLARE_METHOD_INVOKE_HELPERS(getconstants);
  DECLARE_METHOD_INVOKE_HELPERS(getdoccomment);
  DECLARE_METHOD_INVOKE_HELPERS(isinterface);
  DECLARE_METHOD_INVOKE_HELPERS(issubclassof);
  DECLARE_METHOD_INVOKE_HELPERS(hasproperty);
  DECLARE_METHOD_INVOKE_HELPERS(getstaticproperties);
  DECLARE_METHOD_INVOKE_HELPERS(test);
  DECLARE_METHOD_INVOKE_HELPERS(getdefaultproperties);
  DECLARE_METHOD_INVOKE_HELPERS(setstaticpropertyvalue);
  DECLARE_METHOD_INVOKE_HELPERS(isinstantiable);
  DECLARE_METHOD_INVOKE_HELPERS(getinterfaces);
  DECLARE_METHOD_INVOKE_HELPERS(fetch);
  DECLARE_METHOD_INVOKE_HELPERS(isabstract);
  DECLARE_METHOD_INVOKE_HELPERS(getname);
  DECLARE_METHOD_INVOKE_HELPERS(getproperty);
  DECLARE_METHOD_INVOKE_HELPERS(isinternal);
};
ObjectData *coo_ReflectionClass() NEVER_INLINE;
extern const int64 q_ReflectionClass_IS_IMPLICIT_ABSTRACT;
extern const int64 q_ReflectionClass_IS_EXPLICIT_ABSTRACT;
extern const int64 q_ReflectionClass_IS_FINAL;

///////////////////////////////////////////////////////////////////////////////
}

#endif // __GENERATED_cls_ReflectionClass_hf4d8c830__
