/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010 Facebook, Inc. (http://www.facebook.com)          |
   | Copyright (c) 1997-2010 The PHP Group                                |
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

#include <runtime/ext/ext_debugger.h>
#include <runtime/ext/ext_string.h>
#include <runtime/eval/debugger/cmd/cmd_user.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

using namespace Eval;

const int64 q_debuggerclient_AUTO_COMPLETE_FILENAMES =
  (int64)DebuggerClient::AUTO_COMPLETE_FILENAMES;
const int64 q_debuggerclient_AUTO_COMPLETE_VARIABLES =
  (int64)DebuggerClient::AUTO_COMPLETE_VARIABLES;
const int64 q_debuggerclient_AUTO_COMPLETE_CONSTANTS =
  (int64)DebuggerClient::AUTO_COMPLETE_CONSTANTS;
const int64 q_debuggerclient_AUTO_COMPLETE_CLASSES   =
  (int64)DebuggerClient::AUTO_COMPLETE_CLASSES;
const int64 q_debuggerclient_AUTO_COMPLETE_FUNCTIONS =
  (int64)DebuggerClient::AUTO_COMPLETE_FUNCTIONS;

///////////////////////////////////////////////////////////////////////////////

bool f_hphpd_install_user_command(CStrRef cmd, CStrRef clsname) {
  return CmdUser::InstallCommand(cmd, clsname);
}

Array f_hphpd_get_user_commands() {
  return CmdUser::GetCommands();
}

///////////////////////////////////////////////////////////////////////////////

c_debuggerproxy::c_debuggerproxy() {
}

c_debuggerproxy::~c_debuggerproxy() {
}

void c_debuggerproxy::t___construct() {
}

bool c_debuggerproxy::t_islocal() {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerproxy, debuggerproxy::islocal);
  return m_proxy->isLocal();
}

Variant c_debuggerproxy::t_send(p_debuggercommand cmd) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerproxy, debuggerproxy::send);
  CmdUser cmdUser(cmd);
  return m_proxy->send(&cmdUser);
}

Variant c_debuggerproxy::t___destruct() {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerproxy, debuggerproxy::__destruct);
  return null;
}

///////////////////////////////////////////////////////////////////////////////

c_debuggerclient::c_debuggerclient() {
}

c_debuggerclient::~c_debuggerclient() {
}

void c_debuggerclient::t___construct() {
}

void c_debuggerclient::t_quit() {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::quit);
  m_client->quit();
}

static String format_string(DebuggerClient *client,
                            int _argc, CStrRef format, CArrRef _argv) {
  Variant ret = f_sprintf(_argc, format, _argv);
  if (ret.isString()) {
    return ret;
  }
  client->error("Debugger extension failed to format string: %s",
                 format.data());
  return "";
}

void c_debuggerclient::t_print(int _argc, CStrRef format,
                               CArrRef _argv /* = null_array */) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::print);
  String ret = format_string(m_client, _argc, format, _argv);
  m_client->print("%s", ret.data());
}

void c_debuggerclient::t_help(int _argc, CStrRef format,
                              CArrRef _argv /* = null_array */) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::help);
  String ret = format_string(m_client, _argc, format, _argv);
  m_client->help("%s", ret.data());
}

void c_debuggerclient::t_info(int _argc, CStrRef format,
                              CArrRef _argv /* = null_array */) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::info);
  String ret = format_string(m_client, _argc, format, _argv);
  m_client->info("%s", ret.data());
}

void c_debuggerclient::t_output(int _argc, CStrRef format,
                                CArrRef _argv /* = null_array */) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::output);
  String ret = format_string(m_client, _argc, format, _argv);
  m_client->output("%s", ret.data());
}

void c_debuggerclient::t_error(int _argc, CStrRef format,
                               CArrRef _argv /* = null_array */) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::error);
  String ret = format_string(m_client, _argc, format, _argv);
  m_client->error("%s", ret.data());
}

void c_debuggerclient::t_comment(int _argc, CStrRef format,
                                 CArrRef _argv /* = null_array */) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::comment);
  String ret = format_string(m_client, _argc, format, _argv);
  m_client->comment("%s", ret.data());
}

void c_debuggerclient::t_code(int _argc, CStrRef format,
                              CArrRef _argv /* = null_array */) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::code);
  String ret = format_string(m_client, _argc, format, _argv);
  m_client->code(ret.data());
}

Variant c_debuggerclient::t_ask(int _argc, CStrRef format,
                                CArrRef _argv /* = null_array */) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::ask);
  String ret = format_string(m_client, _argc, format, _argv);
  return String::FromChar(m_client->ask("%s", ret.data()));
}

String c_debuggerclient::t_wrap(CStrRef str) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::wrap);
  return m_client->wrap(str.data());
}

void c_debuggerclient::t_helptitle(CStrRef str) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::helptitle);
  m_client->helpTitle(str.data());
}

void c_debuggerclient::t_helpbody(CStrRef str) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::helpbody);
  m_client->helpBody(str.data());
}

void c_debuggerclient::t_helpsection(CStrRef str) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::helpsection);
  m_client->helpSection(str.data());
}

void c_debuggerclient::t_tutorial(CStrRef str) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::tutorial);
  m_client->tutorial(str.data());
}

String c_debuggerclient::t_getcode() {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::getcode);
  return m_client->getCode();
}

String c_debuggerclient::t_getcommand() {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::getcommand);
  return m_client->getCommand();
}

bool c_debuggerclient::t_arg(int index, CStrRef str) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::arg);
  return m_client->arg(index, str.data());
}

int c_debuggerclient::t_argcount() {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::argcount);
  return m_client->argCount();
}

String c_debuggerclient::t_argvalue(int index) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::argvalue);
  return m_client->argValue(index);
}

String c_debuggerclient::t_argrest(int index) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::argrest);
  return m_client->argRest(index);
}

Array c_debuggerclient::t_args() {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::args);
  StringVec *args = m_client->args();
  Array ret(Array::Create());
  for (unsigned int i = 0; i < args->size(); i++) {
    ret.append(String(args->at(i)));
  }
  return ret;
}

Variant c_debuggerclient::t_send(p_debuggercommand cmd) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::send);
  CmdUser cmdUser(cmd);
  m_client->send(&cmdUser);
  return true;
}

Variant c_debuggerclient::t_xend(p_debuggercommand cmd) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::xend);
  CmdUser cmdUser(cmd);
  CmdUserPtr ret = m_client->xend<CmdUser>(&cmdUser);
  return ret->getUserCommand();
}

Variant c_debuggerclient::t_getcurrentlocation() {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::getcurrentlocation);
  BreakPointInfoPtr bpi = m_client->getCurrentLocation();
  Array ret(Array::Create());
  if (bpi) {
    ret.set("file",      String(bpi->m_file));
    ret.set("line",      (int64)bpi->m_line1);
    ret.set("namespace", String(bpi->m_namespace));
    ret.set("class",     String(bpi->m_class));
    ret.set("function",  String(bpi->m_function));
    ret.set("text",      String(bpi->site()));
  }
  return ret;
}

Variant c_debuggerclient::t_getstacktrace() {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::getstacktrace);
  return m_client->getStackTrace();
}

int c_debuggerclient::t_getframe() {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::getframe);
  return m_client->getFrame();
}

void c_debuggerclient::t_printframe(int index) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::printframe);
  m_client->printFrame(index, m_client->getStackTrace()[index]);
}

void c_debuggerclient::t_addcompletion(CVarRef list) {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::addcompletion);
  if (list.isInteger()) {
    m_client->addCompletion((const char **)list.toInt64());
  } else {
    // TODO: support user completion list
  }
}

Variant c_debuggerclient::t___destruct() {
  INSTANCE_METHOD_INJECTION_BUILTIN(debuggerclient, debuggerclient::__destruct);
  return null;
}

///////////////////////////////////////////////////////////////////////////////
}
