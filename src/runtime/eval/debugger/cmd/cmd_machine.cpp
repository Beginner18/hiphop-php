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

#include <runtime/eval/debugger/cmd/cmd_machine.h>
#include <runtime/base/runtime_option.h>
#include <runtime/base/intercept.h>
#include <runtime/base/array/array_init.h>
#include <runtime/base/util/libevent_http_client.h>
#include <util/process.h>

using namespace std;

namespace HPHP { namespace Eval {
///////////////////////////////////////////////////////////////////////////////

void CmdMachine::sendImpl(DebuggerThriftBuffer &thrift) {
  DebuggerCommand::sendImpl(thrift);
  thrift.write(m_sandboxes);
  thrift.write(m_rpcConfig);
}

void CmdMachine::recvImpl(DebuggerThriftBuffer &thrift) {
  DebuggerCommand::recvImpl(thrift);
  thrift.read(m_sandboxes);
  thrift.read(m_rpcConfig);
}

void CmdMachine::list(DebuggerClient *client) {
  if (client->argCount() == 0) {
    static const char *keywords[] =
      { "disconnect", "connect", "rpc", "list", "attach", NULL };
    client->addCompletion(keywords);
  }
}

bool CmdMachine::help(DebuggerClient *client) {
  client->helpTitle("Machine Command");
  client->helpCmds(
    "[m]achine [c]onnect {host}",         "debugging remote server natively",
    "[m]achine [c]onnect {host}:{port}",  "debugging remote server natively",
    "[m]achine [r]pc {host}",             "debugging remote server with RPC",
    "[m]achine [r]pc {host}:{port}",      "debugging remote server with RPC",
    "[m]achine [d]isconnect",             "debugging local script",
    "[m]achine [l]ist",                   "list all sandboxes",
    "[m]achine [a]ttach {index}",         "attach to a sandbox",
    NULL
  );
  client->helpBody(
    "Use this command to switch between different machines or "
    "sandboxes.\n"
    "\n"
    "If command prompt says \"hphpd\", all evaluation of PHP code happens "
    "locally within the debugger. This is the mode when debugger is started "
    "without a remote server name. No user libraries are pre-loaded in this "
    "mode.\n"
    "\n"
    "When connecting to a remote server, it will automatically attach "
    "to \"default\" sandbox under current user. If \"default\" sandbox "
    "does not exist, it will attach to a random sandbox under current "
    "user. In sandbox mode, a file specified in server's configuration "
    "of \"Eval.Debugger.StartupDocument\" is pre-loaded.\n"
    "\n"
    "If there is no sandbox available, it will create a \"dummy\" "
    "sandbox and attach to it.\n"
    "\n"
    "When your sandbox is not available, please hit it at least once "
    "from your browser. Then run '[m]achine [l]ist' command again.\n"
    "\n"
    "If a HipHop server has RPC port open, one can also debug the server in "
    "a very special RPC mode. In this mode, one can type in PHP scripts to "
    "run, but all functions will be executed on server through RPC. Because "
    "states are still maintained locally and only functions are executed "
    "remotely, it may not work with functions or scripts that depend on "
    "global variables or low-level raw resource pointers. As a simple rule, "
    "stateless functions will work just fine, even with objects and method "
    "calls. Currently, all built-in functions are still executed locally. "
    "We may move some of them to remote server, if they rely on machine "
    "specific information."
  );
  return true;
}

bool CmdMachine::processList(DebuggerClient *client,
                             bool output /* = true */) {
  m_body = "list";
  CmdMachinePtr res = client->xend<CmdMachine>(this);
  client->updateSandboxes(res->m_sandboxes);
  if (!output) return true;

  if (res->m_sandboxes.empty()) {
    client->info("(no sandbox was found)");
    client->tutorial(
      "Please hit the sandbox from browser at least once. Then run "
      "'[m]achine [l]ist' again."
    );
  } else {
    for (int i = 0; i < (int)res->m_sandboxes.size(); i++) {
      client->print("  %d\t%s", i + 1, res->m_sandboxes[i].c_str());
    }
    client->tutorial(
      "Use '[m]achine [a]ttach {index}' to attach to one sandbox. For "
      "example, 'm a 1'. If desired sandbox is not on the list, please "
      "hit the sandbox from browser once. Then run '[m]achine [l]ist' "
      "again."
    );
  }

  return true;
}

bool CmdMachine::AttachSandbox(DebuggerClient *client,
                               const char *user /* = NULL */,
                               const char *name /* = NULL */,
                               const char *path /* = NULL */) {
  string login;
  if (user == NULL) {
    login = Process::GetCurrentUser();
    user = login.c_str();
  }

  DSandboxInfo sandbox;
  sandbox.m_user = user ? user : "";
  sandbox.m_name = name ? name : "default";
  sandbox.m_path = path ? path : "";

  return AttachSandbox(client, sandbox);
}

bool CmdMachine::AttachSandbox(DebuggerClient *client,
                               const DSandboxInfo &sandbox) {
  CmdMachine cmd;
  cmd.m_body = "attach";
  cmd.m_sandboxes.push_back(sandbox.id());

  client->send(&cmd);
  client->info("Attached to %s's %s sandbox.", sandbox.m_user.c_str(),
               sandbox.m_name.c_str());
  throw DebuggerConsoleExitException();
}

bool CmdMachine::onClient(DebuggerClient *client) {
  if (DebuggerCommand::onClient(client)) return true;
  if (client->argCount() == 0) return help(client);

  bool rpc = client->arg(1, "rpc");
  if (rpc || client->arg(1, "connect")) {
    if (client->argCount() != 2) {
      return help(client);
    }
    string host = client->argValue(2);
    int port = 0;
    size_t pos = host.find(":");
    if (pos != string::npos) {
      if (!DebuggerClient::IsValidNumber(host.substr(pos + 1))) {
        client->error("Port needs to be a number");
        return help(client);
      }
      port = atoi(host.substr(pos + 1).c_str());
      host = host.substr(0, pos);
    }

    // connect to local first
    client->connect(host, port, rpc);

    // then set intercept for that thread
    CmdMachine cmd;
    cmd.m_body = "rpc";
    cmd.m_rpcConfig = CREATE_MAP4
      ("host", String(host),
       "port", port ? port : RuntimeOption::DebuggerDefaultRpcPort,
       "auth", String(RuntimeOption::DebuggerDefaultRpcAuth),
       "timeout", RuntimeOption::DebuggerDefaultRpcTimeout);
    client->send(&cmd);
    return true;
  }

  if (client->arg(1, "disconnect")) {
    client->disconnect();
    return true;
  }

  if (client->arg(1, "list")) {
    processList(client);
    return true;
  }

  if (client->arg(1, "attach")) {
    string snum = client->argValue(2);
    if (!DebuggerClient::IsValidNumber(snum)) {
      client->error("'[m]achine [a]attach' needs an {index} argument.");
      client->tutorial(
        "You will have to run '[m]achine [l]ist' first to see a list of valid "
        "numbers or indices to specify."
      );
      return true;
    }

    int num = atoi(snum.c_str());
    string id = client->getSandbox(num);
    if (id.empty()) {
      processList(client, false);
      id = client->getSandbox(num);
      if (id.empty()) {
        client->error("\"%s\" is not a valid sandbox index. Choose one from "
                      "this list:", snum.c_str());
        processList(client);
        return true;
      }
    }
    DSandboxInfo sandbox(id);
    return AttachSandbox(client, sandbox);
  }

  return help(client);
}

bool CmdMachine::onServer(DebuggerProxy *proxy) {
  if (m_body == "rpc") {
    String host = m_rpcConfig["host"].toString();
    int port = m_rpcConfig["port"].toInt32();
    LibEventHttpClient::SetCache(host.data(), port, 1);

    register_intercept("", "fb_rpc_intercept_handler", m_rpcConfig);
    return true;
  }
  if (m_body == "list") {
    Debugger::GetRegisteredSandboxes(m_sandboxes);
    return proxy->send(this);
  }
  if (m_body == "attach" && !m_sandboxes.empty()) {
    proxy->switchSandbox(m_sandboxes[0]);
    m_exitInterrupt = true;
    return true;
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////
}}
