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

#include <runtime/eval/debugger/debugger.h>
#include <runtime/eval/debugger/debugger_server.h>
#include <runtime/eval/debugger/debugger_client.h>
#include <runtime/eval/debugger/cmd/cmd_interrupt.h>
#include <system/gen/sys/system_globals.h>
#include <util/text_color.h>
#include <util/util.h>

using namespace std;

namespace HPHP { namespace Eval {
///////////////////////////////////////////////////////////////////////////////

Debugger Debugger::s_debugger;

void Debugger::StartServer() {
  DebuggerServer::Start();
}

void Debugger::StartClient(const std::string &host, int port) {
  SmartPtr<Socket> localProxy = DebuggerClient::Start(host, port);
  if (localProxy.get()) {
    RegisterProxy(localProxy, false);
  }
}

void Debugger::Stop() {
  DebuggerServer::Stop();
  DebuggerClient::Stop();
  s_debugger.stop();
}

///////////////////////////////////////////////////////////////////////////////

void Debugger::RegisterSandbox(const SandboxInfo &sandbox) {
  s_debugger.addSandbox(sandbox);
}

void Debugger::GetRegisteredSandboxes(StringVec &ids) {
  s_debugger.getSandboxes(ids);
}

void Debugger::RegisterProxy(SmartPtr<Socket> socket, bool dummy) {
  s_debugger.addProxy(socket, dummy);
}

void Debugger::RemoveProxy(DebuggerProxyPtr proxy) {
  s_debugger.removeProxy(proxy);
}

void Debugger::SwitchSandbox(DebuggerProxyPtr proxy,
                             const SandboxInfo &sandbox) {
  s_debugger.switchSandbox(proxy, sandbox);
}

///////////////////////////////////////////////////////////////////////////////

DebuggerProxyPtrSet Debugger::GetProxies() {
  SystemGlobals *g = (SystemGlobals*)get_global_variables();
  Variant &server = g->gv__SERVER;
  SandboxInfo sandbox;
  sandbox.user = server["HPHP_SANDBOX_USER"].toString().data();
  sandbox.name = server["HPHP_SANDBOX_NAME"].toString().data();
  sandbox.path = server["HPHP_SANDBOX_PATH"].toString().data();
  return s_debugger.findProxies(sandbox);
}

void Debugger::InterruptSessionStarted() {
  Interrupt(CmdInterrupt::SessionStarted);
}

void Debugger::InterruptSessionEnded() {
  Interrupt(CmdInterrupt::SessionEnded);
}

void Debugger::InterruptRequestStarted() {
  Interrupt(CmdInterrupt::RequestStarted);
}

void Debugger::InterruptRequestEnded() {
  Interrupt(CmdInterrupt::RequestEnded);
}

void Debugger::InterruptPSPEnded() {
  Interrupt(CmdInterrupt::PSPEnded);
}

void Debugger::InterruptFileLine(const char *filename, int line) {
  Interrupt(CmdInterrupt::BreakPointReached, filename, line);
}

void Debugger::InterruptException(const char *filename, int line,
                                  const char *clsname) {
  Interrupt(CmdInterrupt::ExceptionThrown, filename, line, clsname);
}

void Debugger::Interrupt(int type, const char *file /* = NULL */,
                         int line /* = 0 */,
                         const char *clsname /* = NULL */) {
  ASSERT(RuntimeOption::EnableDebugger);

  DebuggerProxyPtrSet proxies = GetProxies();
  if (proxies.empty()) {
    // debugger clients are disconnected abnormally
    if (type == CmdInterrupt::SessionStarted ||
        type == CmdInterrupt::SessionEnded) {
      // for command line programs, we need this exception to exit from
      // the infinite execution loop
      throw DebuggerExitException();
    }
    return;
  }

  // validate break points
  if (type == CmdInterrupt::BreakPointReached ||
      type == CmdInterrupt::ExceptionThrown) {
    if (!file || !*file || line <= 0) {
      return;
    }
    if (type == CmdInterrupt::ExceptionThrown) {
      if (!clsname || !*clsname) {
        return;
      }
    }
  }

  for (DebuggerProxyPtrSet::const_iterator iter = proxies.begin();
       iter != proxies.end(); ++iter) {
    CmdInterrupt cmd((CmdInterrupt::SubType)type, file, line, clsname);
    (*iter)->interrupt(cmd);
  }
}

///////////////////////////////////////////////////////////////////////////////

void Debugger::SetTextColors() {
  Util::s_stdout_color = ANSI_COLOR_CYAN;
  Util::s_stderr_color = ANSI_COLOR_RED;
}

String Debugger::ColorStdout(CStrRef s) {
  if (Util::s_stdout_color) {
    return String(Util::s_stdout_color) + s + String(ANSI_COLOR_END);
  }
  return s;
}

String Debugger::ColorStderr(CStrRef s) {
  if (Util::s_stderr_color) {
    return String(Util::s_stderr_color) + s + String(ANSI_COLOR_END);
  }
  return s;
}

///////////////////////////////////////////////////////////////////////////////

void Debugger::stop() {
  WriteLock lock(m_mutex);
  m_proxies.clear();
}

void Debugger::addSandbox(const SandboxInfo &sandbox) {
  WriteLock lock(m_mutex);
  m_proxies.operator[](sandbox.id());
}

void Debugger::getSandboxes(StringVec &ids) {
  ReadLock lock(m_mutex);
  ids.reserve(m_proxies.size());
  for (StringToDebuggerProxyPtrSetMap::const_iterator iter =
         m_proxies.begin(); iter != m_proxies.end(); ++iter) {
    if (!iter->first.empty()) {
      ids.push_back(iter->first);
    }
  }
}

void Debugger::addProxy(SmartPtr<Socket> socket, bool dummy) {
  DebuggerProxyPtr proxy(new DebuggerProxy(socket));
  {
    WriteLock lock(m_mutex);
    m_proxies[proxy->getSandboxId()].insert(proxy);
  }
  if (dummy) {
    proxy->startDummySandbox();
  }
}

void Debugger::removeProxy(DebuggerProxyPtr proxy) {
  WriteLock lock(m_mutex);
  m_proxies[proxy->getSandboxId()].erase(proxy);
}

DebuggerProxyPtrSet Debugger::findProxies(const SandboxInfo &sandbox) {
  ReadLock lock(m_mutex);
  return m_proxies[sandbox.id()];
}

void Debugger::switchSandbox(DebuggerProxyPtr proxy,
                             const SandboxInfo &sandbox) {
  string oldId = proxy->getSandboxId();
  string newId = sandbox.id();
  if (newId != oldId) {
    WriteLock lock(m_mutex);
    m_proxies[oldId].erase(proxy);
    m_proxies[newId].insert(proxy);
  }
}

///////////////////////////////////////////////////////////////////////////////
}}
