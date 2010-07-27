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

#include <runtime/eval/debugger/debugger_command.h>
#include <runtime/eval/debugger/debugger.h>
#include <runtime/eval/debugger/cmd/all.h>

#define POLLING_SECONDS 1

namespace HPHP { namespace Eval {
///////////////////////////////////////////////////////////////////////////////
// send/recv

bool DebuggerCommand::send(DebuggerThriftBuffer &thrift) {
  try {
    thrift.reset(false);
    sendImpl(thrift);
    thrift.flush();
  } catch (...) {
    Logger::Error("DebuggerCommand::send(): a socket error has happened");
    thrift.close();
    return false;
  }
  return true;
}

bool DebuggerCommand::recv(DebuggerThriftBuffer &thrift) {
  try {
    recvImpl(thrift);
  } catch (...) {
    Logger::Error("DebuggerCommand::recv(): a socket error has happened");
    thrift.close();
    return false;
  }
  return true;
}

void DebuggerCommand::sendImpl(DebuggerThriftBuffer &thrift) {
  thrift.write((int32)m_type);
  thrift.write(m_body);
}

void DebuggerCommand::recvImpl(DebuggerThriftBuffer &thrift) {
  thrift.read(m_body);
}

bool DebuggerCommand::Receive(DebuggerThriftBuffer &thrift,
                              DebuggerCommandPtr &cmd, const char *caller) {
  cmd.reset();

  struct pollfd fds[1];
  fds[0].fd = thrift.getSocket()->fd();
  fds[0].events = POLLIN|POLLERR|POLLHUP;
  int ret = poll(fds, 1, POLLING_SECONDS * 1000);
  if (ret == 0) {
    return false;
  }
  if (ret == -1 || !(fds[0].revents & POLLIN)) {
    return true;
  }

  int32 type;
  try {
    thrift.reset(true);
    thrift.read(type);
  } catch (...) {
    Logger::Error("%s => DebuggerCommand::Receive(): socket error", caller);
    return true;
  }

  // not all commands are here, as not all commands need to be sent over wire
  switch (type) {
    case KindOfBreak    :  cmd = DebuggerCommandPtr(new CmdBreak    ()); break;
    case KindOfContinue :  cmd = DebuggerCommandPtr(new CmdContinue ()); break;
    case KindOfDown     :  cmd = DebuggerCommandPtr(new CmdDown     ()); break;
    case KindOfException:  cmd = DebuggerCommandPtr(new CmdException()); break;
    case KindOfFrame    :  cmd = DebuggerCommandPtr(new CmdFrame    ()); break;
    case KindOfGlobal   :  cmd = DebuggerCommandPtr(new CmdGlobal   ()); break;
    case KindOfInfo     :  cmd = DebuggerCommandPtr(new CmdInfo     ()); break;
    case KindOfJump     :  cmd = DebuggerCommandPtr(new CmdJump     ()); break;
    case KindOfConstant :  cmd = DebuggerCommandPtr(new CmdConstant ()); break;
    case KindOfList     :  cmd = DebuggerCommandPtr(new CmdList     ()); break;
    case KindOfMachine  :  cmd = DebuggerCommandPtr(new CmdMachine  ()); break;
    case KindOfNext     :  cmd = DebuggerCommandPtr(new CmdNext     ()); break;
    case KindOfOut      :  cmd = DebuggerCommandPtr(new CmdOut      ()); break;
    case KindOfPrint    :  cmd = DebuggerCommandPtr(new CmdPrint    ()); break;
    case KindOfQuit     :  cmd = DebuggerCommandPtr(new CmdQuit     ()); break;
    case KindOfRun      :  cmd = DebuggerCommandPtr(new CmdRun      ()); break;
    case KindOfStep     :  cmd = DebuggerCommandPtr(new CmdStep     ()); break;
    case KindOfThread   :  cmd = DebuggerCommandPtr(new CmdThread   ()); break;
    case KindOfUp       :  cmd = DebuggerCommandPtr(new CmdUp       ()); break;
    case KindOfVariable :  cmd = DebuggerCommandPtr(new CmdVariable ()); break;
    case KindOfWhere    :  cmd = DebuggerCommandPtr(new CmdWhere    ()); break;
    case KindOfExtended :  cmd = DebuggerCommandPtr(new CmdExtended ()); break;
    case KindOfUser     :  cmd = DebuggerCommandPtr(new CmdUser     ()); break;
    case KindOfEval     :  cmd = DebuggerCommandPtr(new CmdEval     ()); break;
    case KindOfInterrupt:  cmd = DebuggerCommandPtr(new CmdInterrupt()); break;
    case KindOfShell    :  cmd = DebuggerCommandPtr(new CmdShell    ()); break;

    default:
      ASSERT(false);
      Logger::Error("%s => DebuggerCommand::Receive(): bad cmd type: %d",
                    caller, type);
      return true;
  }
  if (!cmd->recv(thrift)) {
    cmd.reset();
  }
  return true;
}

///////////////////////////////////////////////////////////////////////////////
// default handlers

void DebuggerCommand::list(DebuggerClient *client) {
}

bool DebuggerCommand::help(DebuggerClient *client) {
  ASSERT(false);
  return true;
}

bool DebuggerCommand::onClient(DebuggerClient *client) {
  if (client->arg(1, "help") || client->arg(1, "?")) {
    return help(client);
  }
  return false;
}

bool DebuggerCommand::onServer(DebuggerProxy *proxy) {
  ASSERT(false);
  Logger::Error("DebuggerCommand::onServer(): bad cmd type: %d", m_type);
  return false;
}

///////////////////////////////////////////////////////////////////////////////
}}
