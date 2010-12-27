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
// @generated by HipHop Compiler

#ifndef __GENERATED_cls_ReflectionExtension_h84b2b41d__
#define __GENERATED_cls_ReflectionExtension_h84b2b41d__

#include <cls/Reflector.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

/* SRC: classes/reflection.php line 1825 */
class c_ReflectionExtension : public ExtObjectData {
  public:

  // Properties
  Variant m_name;
  Variant m_info;

  // Class Map
  virtual bool o_instanceof(CStrRef s) const;
  DECLARE_CLASS_COMMON(ReflectionExtension, ReflectionExtension)
  DECLARE_INVOKE_EX(ReflectionExtension, ReflectionExtension, ObjectData)

  // DECLARE_STATIC_PROP_OPS
  public:
  static Variant os_getInit(CStrRef s);
  #define OMIT_JUMP_TABLE_CLASS_STATIC_GET_ReflectionExtension 1
  #define OMIT_JUMP_TABLE_CLASS_STATIC_LVAL_ReflectionExtension 1
  #define OMIT_JUMP_TABLE_CLASS_CONSTANT_ReflectionExtension 1

  // DECLARE_INSTANCE_PROP_OPS
  public:
  virtual void o_getArray(Array &props) const;
  virtual void o_setArray(CArrRef props);
  virtual Variant *o_realProp(CStrRef s, int flags,
                              CStrRef context = null_string) const;
  Variant *o_realPropPrivate(CStrRef s, int flags) const;

  // DECLARE_INSTANCE_PUBLIC_PROP_OPS
  public:
  #define OMIT_JUMP_TABLE_CLASS_realProp_PUBLIC_ReflectionExtension 1

  // DECLARE_COMMON_INVOKE
  static bool os_get_call_info(MethodCallPackage &mcp, int64 hash = -1);
  #define OMIT_JUMP_TABLE_CLASS_STATIC_INVOKE_ReflectionExtension 1
  virtual bool o_get_call_info(MethodCallPackage &mcp, int64 hash = -1);

  public:
  DECLARE_INVOKES_FROM_EVAL
  void init();
  public: void t___construct(Variant v_name);
  public: c_ReflectionExtension *create(Variant v_name);
  public: ObjectData *dynCreate(CArrRef params, bool init = true);
  public: void dynConstruct(CArrRef params);
  public: void getConstructor(MethodCallPackage &mcp);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: String t___tostring();
  public: static Variant ti_export(CStrRef cls, CVarRef v_name, CVarRef v_ret);
  public: Variant t_getname();
  public: Variant t_getversion();
  public: Variant t_getfunctions();
  public: Variant t_getconstants();
  public: Variant t_getinientries();
  public: Variant t_getclasses();
  public: Array t_getclassnames();
  public: Variant t_info();
  public: static Variant t_export(CVarRef v_name, CVarRef v_ret) { return ti_export(c_ReflectionExtension::s_class_name, v_name, v_ret); }
  DECLARE_METHOD_INVOKE_HELPERS(__tostring);
  DECLARE_METHOD_INVOKE_HELPERS(__construct);
  DECLARE_METHOD_INVOKE_HELPERS(getfunctions);
  DECLARE_METHOD_INVOKE_HELPERS(export);
  DECLARE_METHOD_INVOKE_HELPERS(info);
  DECLARE_METHOD_INVOKE_HELPERS(getinientries);
  DECLARE_METHOD_INVOKE_HELPERS(getconstants);
  DECLARE_METHOD_INVOKE_HELPERS(getclassnames);
  DECLARE_METHOD_INVOKE_HELPERS(getversion);
  DECLARE_METHOD_INVOKE_HELPERS(getname);
  DECLARE_METHOD_INVOKE_HELPERS(getclasses);
};
extern struct ObjectStaticCallbacks cw_ReflectionExtension;

///////////////////////////////////////////////////////////////////////////////
}

#endif // __GENERATED_cls_ReflectionExtension_h84b2b41d__
