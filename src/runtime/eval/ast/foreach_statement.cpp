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

#include <runtime/eval/ast/foreach_statement.h>
#include <runtime/eval/ast/lval_expression.h>
#include <runtime/eval/ast/variable_expression.h>
#include <runtime/eval/runtime/variable_environment.h>

namespace HPHP {
namespace Eval {
///////////////////////////////////////////////////////////////////////////////

ForEachStatement::ForEachStatement(STATEMENT_ARGS, ExpressionPtr source,
                                   LvalExpressionPtr key,
                                   LvalExpressionPtr value, StatementPtr body)
  :  Statement(STATEMENT_PASS), m_source(source), m_key(key), m_value(value),
     m_body(body) {}

void ForEachStatement::eval(VariableEnvironment &env) const {
  ENTER_STMT;
  Variant map(m_source->eval(env));
  if (m_key) {
    if (m_key->cast<VariableExpression>()) {
      for (ArrayIterPtr iter = map.begin(env.currentContext()); !iter->end();
           iter->next()) {
        const Variant &value = iter->second();
        const Variant &key = iter->first();
        m_value->set(env, value);
        m_key->set(env, key);
        if (!m_body) continue;
        EVAL_STMT_HANDLE_BREAK(m_body, env);
      }
    } else {
      for (ArrayIterPtr iter = map.begin(env.currentContext()); !iter->end();
           iter->next()) {
        const Variant &value = iter->second();
        m_key->set(env, iter->first());
        m_value->set(env, value);
        if (!m_body) continue;
        EVAL_STMT_HANDLE_BREAK(m_body, env);
      }
    }
  } else {
    for (ArrayIterPtr iter = map.begin(env.currentContext()); !iter->end();
         iter->next()) {
      m_value->set(env, iter->second());
      if (!m_body) continue;
      EVAL_STMT_HANDLE_BREAK(m_body, env);
    }
  }
}

void ForEachStatement::dump(std::ostream &out) const {
  out << "foreach (";
  m_source->dump(out);
  out << " as ";
  if (m_key) {
    m_key->dump(out);
    out << " => ";
  }
  m_value->dump(out);
  out << ") {";
  if (m_body) {
    m_body->dump(out);
  }
  out << "}\n";
}

///////////////////////////////////////////////////////////////////////////////
}
}

