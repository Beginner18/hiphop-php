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

#ifndef __HPHP_UTIL_PARSER_PARSER_H__
#define __HPHP_UTIL_PARSER_PARSER_H__

#include <util/parser/scanner.h>

#define IMPLEMENT_XHP_ATTRIBUTES                \
  Token m_xhpAttributes;                        \
  Token *xhpGetAttributes() {                   \
    if (m_xhpAttributes.num()) {                \
      return &m_xhpAttributes;                  \
    }                                           \
    return NULL;                                \
  }                                             \
  void xhpSetAttributes(Token &t) {             \
    m_xhpAttributes = t;                        \
    m_xhpAttributes = 1;                        \
  }                                             \
  void xhpResetAttributes() {                   \
    m_xhpAttributes.reset();                    \
  }                                             \

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

class ParserBase {
public:
  enum NameKind {
    StringName,
    VarName,
    ExprName,
    StaticClassExprName,
    StaticName
  };

public:
  ParserBase(Scanner &scanner, const char *fileName);
  virtual ~ParserBase();

  Scanner &scanner() { return m_scanner;}

  /**
   * Main function to call to start parsing the file. This function is already
   * implemented in hphp.y. Therefore, a subclass only has to declare it.
   */
  virtual bool parse() = 0;

  /**
   * How to decide whether to turn on XHP.
   */
  virtual bool enableXHP() = 0;

  /**
   * Public accessors.
   */
  const char *file() const { return m_fileName;}
  std::string getMessage(bool filename = false) const;
  LocationPtr getLocation() const;
  void getLocation(Location &loc) const {
    loc = *m_loc;
    loc.file = file();
  }

  int line0() const { return m_loc->line0;}
  int char0() const { return m_loc->char0;}
  int line1() const { return m_loc->line1;}
  int char1() const { return m_loc->char1;}

  // called by generated code
  int scan(ScannerToken *token, Location *loc) {
    return m_scanner.getNextToken(*token, *loc);
  }
  void setRuleLocation(Location *loc) {
    m_loc = loc;
  }
  void fatal(Location *loc, ParserBase *parser, const char *msg) {}

  void pushFuncLocation();
  LocationPtr popFuncLocation();

protected:
  Scanner &m_scanner;
  const char *m_fileName;

  Location *m_loc;
  LocationPtrVec m_funcLocs;
};

///////////////////////////////////////////////////////////////////////////////
}

#endif // __HPHP_UTIL_PARSER_PARSER_H__
