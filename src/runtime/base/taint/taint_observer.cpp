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

#ifdef TAINTED

#include <runtime/base/complex_types.h>
#include <runtime/base/taint/taint_data.h>
#include <runtime/base/taint/taint_observer.h>
#include <runtime/base/taint/taint_trace.h>

namespace HPHP {

IMPLEMENT_THREAD_LOCAL(TaintObserver*, TaintObserver::instance);

void TaintObserver::RegisterAccessed(const TaintData& td) {
  if (!*instance || (*instance)->m_cap_stack) {
    return;
  }

  // Prevent recursive calls into the TaintObserver.
  TaintObserver *tc = *instance;
  TAINT_OBSERVER_CAP_STACK();

  // If the string is HTML-untainted, set the HTML_CLEAN flag.
  if (!(td.getTaint() & TAINT_BIT_HTML)) {
    tc->m_current_taint.setTaint(TAINT_FLAG_HTML_CLEAN);
  }

  // Absorb the taint and any trace data.
  tc->m_current_taint.setTaint(td.getTaint());
  tc->m_current_taint.attachTaintTrace(td.getTaintTrace());
}

void TaintObserver::RegisterMutated(TaintData& td, const char *s) {
  if (!*instance || (*instance)->m_cap_stack) {
    return;
  }

  // Prevent recursive calls into the TaintObserver.
  TaintObserver *tc = *instance;
  TAINT_OBSERVER_CAP_STACK();

  taint_t t = tc->m_current_taint.getTaint();
  taint_t set_mask = tc->m_set_mask;
  taint_t clear_mask = tc->m_clear_mask;

  // Trace the passed string if we're in an explicitly HTML-unsafe function.
  if ((set_mask & TAINT_BIT_HTML) && s) {
    td.attachTaintTrace(NEW(TaintTraceData)(TaintTracer::Trace(s, true)));
  }

  ASSERT(!(TAINT_ISSET_NO_TRACE(set_mask) &&
           TAINT_ISSET_NO_TRACE(clear_mask)));

  // Propagate TRACE, kill TRACE, or perform tracing as desired.
  if (TAINT_ISSET_NO_TRACE(set_mask)) {
    set_mask = TAINT_GET_TAINT(set_mask);
  } else if (TAINT_ISSET_NO_TRACE(clear_mask)) {
    t &= ~TAINT_BIT_TRACE;
  } else if ((t & TAINT_BIT_HTML) && (t & TAINT_BIT_TRACE) &&
             TAINT_ISSET_HTML_CLEAN(tc->m_current_taint.getRawTaint())) {
    t &= ~TAINT_BIT_TRACE;
    TaintTraceDataPtr ttd = TaintTracer::CreateTrace();
    tc->m_current_taint.attachTaintTrace(ttd);
  }

  // Propagate the taint and any trace data.
  td.setTaint(set_mask | (~clear_mask & t));
  td.setTaintTrace(tc->m_current_taint.getTaintTrace());
  ASSERT(td.getTaintTrace()->getCount() > 1);
}

}

#endif // TAINTED
