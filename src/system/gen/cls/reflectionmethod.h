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

#ifndef __GENERATED_cls_reflectionmethod_h__
#define __GENERATED_cls_reflectionmethod_h__

#include <cls/reflectionfunctionabstract.h>
#include <cls/reflector.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

/* SRC: classes/reflection.php line 1556 */
class c_reflectionmethod : public c_reflectionfunctionabstract {
  BEGIN_CLASS_MAP(ReflectionMethod)
    PARENT_CLASS(ReflectionFunctionAbstract)
    PARENT_CLASS(Reflector)
  END_CLASS_MAP(ReflectionMethod)
  DECLARE_CLASS_COMMON(reflectionmethod, ReflectionMethod)
  DECLARE_INVOKE_EX(reflectionmethod, ReflectionMethod, reflectionfunctionabstract)

  // DECLARE_STATIC_PROP_OPS
  public:
  static Variant os_getInit(CStrRef s);
#define OMIT_JUMP_TABLE_CLASS_STATIC_GET_reflectionmethod 1
#define OMIT_JUMP_TABLE_CLASS_STATIC_LVAL_reflectionmethod 1
  static Variant os_constant(const char *s);

  // DECLARE_INSTANCE_PROP_OPS
  public:
  virtual void o_getArray(Array &props) const;
#define OMIT_JUMP_TABLE_CLASS_SETARRAY_reflectionmethod 1
#define OMIT_JUMP_TABLE_CLASS_exists_reflectionmethod 1
#define OMIT_JUMP_TABLE_CLASS_exists_PRIVATE_reflectionmethod 1
#define OMIT_JUMP_TABLE_CLASS_get_reflectionmethod 1
#define OMIT_JUMP_TABLE_CLASS_get_PRIVATE_reflectionmethod 1
#define OMIT_JUMP_TABLE_CLASS_set_reflectionmethod 1
#define OMIT_JUMP_TABLE_CLASS_set_PRIVATE_reflectionmethod 1
#define OMIT_JUMP_TABLE_CLASS_lval_reflectionmethod 1
#define OMIT_JUMP_TABLE_CLASS_lval_PRIVATE_reflectionmethod 1

  // DECLARE_INSTANCE_PUBLIC_PROP_OPS
  public:
  virtual bool o_existsPublic(CStrRef s) const;
  virtual Variant o_getPublic(CStrRef s, bool error = true);
  virtual Variant o_setPublic(CStrRef s,
                              CVarRef v, bool forInit);
  virtual Variant &o_lvalPublic(CStrRef s);

  // DECLARE_COMMON_INVOKE
  static Variant os_invoke(const char *c, MethodIndex methodIndex,
                           const char *s, CArrRef ps, int64 h, bool f = true);
  virtual Variant o_invoke(MethodIndex methodIndex, const char *s,CArrRef ps, int64 h,
                           bool f = true);
  virtual Variant o_invoke_few_args(MethodIndex methodIndex, const char *s, int64 h,
                                    int count,
                                    INVOKE_FEW_ARGS_DECL_ARGS);

  public:
  DECLARE_INVOKES_FROM_EVAL
  void init();
  public: Variant m_name;
  public: Variant m_class;
  public: void t___construct(Variant v_cls, Variant v_name);
  public: c_reflectionmethod *create(Variant v_cls, Variant v_name);
  public: ObjectData *dynCreate(CArrRef params, bool init = true);
  public: void dynConstruct(CArrRef params);
  public: void dynConstructFromEval(Eval::VariableEnvironment &env, const Eval::FunctionCallExpression *call);
  public: String t___tostring();
  public: static Variant ti_export(const char* cls, Variant v_cls, CVarRef v_name, CVarRef v_ret);
  public: Variant t_invoke(int num_args, CVarRef v_obj, Array args = Array());
  public: Variant t_invokeargs(CVarRef v_obj, CVarRef v_args);
  public: Variant t_isfinal();
  public: Variant t_isabstract();
  public: bool t_ispublic();
  public: bool t_isprivate();
  public: bool t_isprotected();
  public: Variant t_isstatic();
  public: bool t_isconstructor();
  public: bool t_isdestructor();
  public: Variant t_getmodifiers();
  public: Variant t_getclosure();
  public: Variant t_getdeclaringclass();
  public: static Variant t_export(CVarRef v_cls, CVarRef v_name, CVarRef v_ret) { return ti_export("reflectionmethod", v_cls, v_name, v_ret); }
};
extern struct ObjectStaticCallbacks cw_reflectionmethod;

///////////////////////////////////////////////////////////////////////////////
}

#endif // __GENERATED_cls_reflectionmethod_h__
