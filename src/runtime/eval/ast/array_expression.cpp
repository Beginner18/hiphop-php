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

#include <runtime/eval/ast/array_expression.h>
#include <runtime/eval/ast/lval_expression.h>
#include <runtime/eval/runtime/variable_environment.h>
#include <runtime/eval/ast/scalar_value_expression.h>

namespace HPHP {
namespace Eval {
///////////////////////////////////////////////////////////////////////////////

ArrayPair::ArrayPair(CONSTRUCT_ARGS) : Construct(CONSTRUCT_PASS) {}
ArrayPair::ArrayPair(CONSTRUCT_ARGS, ExpressionPtr key)
  : Construct(CONSTRUCT_PASS), m_key(key) {}


Variant ArrayPair::key(VariableEnvironment &env) const {
  if (m_key) {
    return m_key->eval(env);
  }
  return Variant();
}

ArrayPairVal::ArrayPairVal(CONSTRUCT_ARGS, ExpressionPtr key, ExpressionPtr val)
  : ArrayPair(CONSTRUCT_PASS, key), m_val(val) {}
ArrayPairVal::ArrayPairVal(CONSTRUCT_ARGS, ExpressionPtr val)
  : ArrayPair(CONSTRUCT_PASS), m_val(val) {}

Variant ArrayPairVal::val(VariableEnvironment &env) const {
  return m_val->eval(env);
}

ArrayPair *ArrayPairVal::optimize(VariableEnvironment &env) {
  Eval::optimize(env, m_key);
  Eval::optimize(env, m_val);
  return NULL;
}

void ArrayPairVal::set(VariableEnvironment &env, Array &arr) const {
  if (m_key) {
    arr.set(key(env), val(env));
  } else {
    arr.append(val(env));
  }
}

void ArrayPairVal::dump(std::ostream &out) const {
  if (m_key) {
    m_key->dump(out);
    out << " => ";
  }
  m_val->dump(out);
}

ArrayPairRef::ArrayPairRef(CONSTRUCT_ARGS, ExpressionPtr key,
                           LvalExpressionPtr val)
  : ArrayPair(CONSTRUCT_PASS, key), m_val(val) {}
ArrayPairRef::ArrayPairRef(CONSTRUCT_ARGS, LvalExpressionPtr val) :
  ArrayPair(CONSTRUCT_PASS), m_val(val) {}


ArrayPair *ArrayPairRef::optimize(VariableEnvironment &env) {
  Eval::optimize(env, m_key);
  return NULL;
}

Variant &ArrayPairRef::val(VariableEnvironment &env) const {
  return m_val->lval(env);
}

void ArrayPairRef::set(VariableEnvironment &env, Array &arr) const {
  if (m_key) {
    arr.set(key(env), ref(val(env)));
  } else {
    arr.append(ref(val(env)));
  }
}

void ArrayPairRef::dump(std::ostream &out) const {
  if (m_key) {
    m_key->dump(out);
    out << " => ";
  }
  out << "&";
  m_val->dump(out);
}

ArrayExpression::ArrayExpression(EXPRESSION_ARGS,
                                 const std::vector<ArrayPairPtr> &elems)
  : Expression(KindOfArrayExpression, EXPRESSION_PASS), m_elems(elems) {}


Variant ArrayExpression::eval(VariableEnvironment &env) const {
  Array arr(Array::Create());
  for (std::vector<ArrayPairPtr>::const_iterator it = m_elems.begin();
       it != m_elems.end(); ++it) {
    (*it)->set(env, arr);
  }
  return arr;
}

void optimize(VariableEnvironment &env, ArrayPairPtr &ap) {
  if (!ap) return;
  if (ArrayPairPtr optAp = ap->optimize(env)) {
    ap = optAp;
  }
}

Expression *ArrayExpression::optimize(VariableEnvironment &env) {
  for (unsigned int i = 0; i < m_elems.size(); i++) {
    Eval::optimize(env, m_elems[i]);
  }
  Variant v;
  if (evalScalar(env, v)) {
    return new ScalarValueExpression(v, loc());
  }
  return NULL;
}

bool ArrayExpression::evalScalar(VariableEnvironment &env, Variant &r)
  const {
  Array arr(Array::Create());
  for (std::vector<ArrayPairPtr>::const_iterator it = m_elems.begin();
       it != m_elems.end(); ++it) {
    Variant v;
    if (!(*it)->evalScalar(env, v)) {
      r = null;
      return false;
    }
    (*it)->set(env, arr);
  }
  r = arr;
  return true;
}

bool ArrayExpression::evalStaticScalar(VariableEnvironment &env, Variant &r)
  const {
  Array arr(Array::Create());
  for (std::vector<ArrayPairPtr>::const_iterator it = m_elems.begin();
       it != m_elems.end(); ++it) {
    if (!(*it)->checkStaticScalar(env)) {
      r = null;
      return false;
    }
    (*it)->set(env, arr);
  }
  r = arr;
  return true;
}

void ArrayExpression::dump(std::ostream &out) const {
  out << "array(";
  dumpVector(out, m_elems);
  out << ")";
}

///////////////////////////////////////////////////////////////////////////////
}
}

