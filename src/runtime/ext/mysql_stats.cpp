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

#include <runtime/ext/mysql_stats.h>
#include <util/util.h>

using namespace std;

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

bool MySqlStats::s_inited = false;
hphp_string_map<MySqlStats::Verb> MySqlStats::s_verbs;
const char *MySqlStats::s_verb_names[VERB_COUNT];
Mutex MySqlStats::s_mutex;
MySqlStats::StatsMap MySqlStats::s_stats;

void MySqlStats::Init() {
  ASSERT(!s_inited);
  s_verbs["t_begin"   ] = T_BEGIN;
  s_verbs["t_commit"  ] = T_COMMIT;
  s_verbs["t_rollback"] = T_ROLLBACK;
  s_verbs["t_insert"  ] = T_INSERT;
  s_verbs["t_update"  ] = T_UPDATE;
  s_verbs["t_delete"  ] = T_DELETE;
  s_verbs["t_replace" ] = T_REPLACE;
  s_verbs["t_select"  ] = T_SELECT;
  s_verbs["n_insert"  ] = N_INSERT;
  s_verbs["n_update"  ] = N_UPDATE;
  s_verbs["n_delete"  ] = N_DELETE;
  s_verbs["n_replace" ] = N_REPLACE;
  s_verbs["n_select"  ] = N_SELECT;

  s_verb_names[UNKNOWN   ] = "unknown";
  s_verb_names[T_BEGIN   ] = "begin";
  s_verb_names[T_COMMIT  ] = "commit";
  s_verb_names[T_ROLLBACK] = "rollback";
  s_verb_names[T_INSERT  ] = "t_insert";
  s_verb_names[T_UPDATE  ] = "t_update";
  s_verb_names[T_DELETE  ] = "t_delete";
  s_verb_names[T_REPLACE ] = "t_replace";
  s_verb_names[T_SELECT  ] = "t_select";
  s_verb_names[N_INSERT  ] = "n_insert";
  s_verb_names[N_UPDATE  ] = "n_update";
  s_verb_names[N_DELETE  ] = "n_delete";
  s_verb_names[N_REPLACE ] = "n_replace";
  s_verb_names[N_SELECT  ] = "n_select";
}

MySqlStats::Verb MySqlStats::Translate(const std::string &verb,
                                       bool inTransaction) {
  if (!s_inited) Init();
  string composed = inTransaction ? "t_" : "n_";
  composed += Util::toLower(verb);
  hphp_string_map<Verb>::const_iterator iter = s_verbs.find(composed);
  if (iter != s_verbs.end()) {
    return iter->second;
  }
  return UNKNOWN;
}

const char * MySqlStats::Translate(Verb verb) {
  if (!s_inited) Init();
  if (verb >= 0 && verb < VERB_COUNT) {
    return s_verb_names[verb];
  }
  return NULL;
}

void MySqlStats::Record(const std::string &verb,
                        bool inTransaction /* = false */,
                        const std::string &table /* = "" */) {
  Verb v = Translate(verb, inTransaction);
  string ltable = Util::toLower(table);

  Lock lock(s_mutex);
  StatsMap::iterator iter = s_stats.find(ltable);
  if (iter == s_stats.end()) {
    StatsPtr stats(new Stats());
    memset(stats.get(), 0, sizeof(Stats));
    stats->actions[v] = 1;
    s_stats[ltable] = stats;
  } else {
    Stats &stats = *iter->second;
    ++stats.actions[v];
  }
}

std::string MySqlStats::ReportStats() {
  ostringstream out;

  Lock lock(s_mutex);
  for (StatsMap::const_iterator iter = s_stats.begin(); iter != s_stats.end();
       ++iter) {
    string table = iter->first;
    if (table.empty()) {
      table = "x";
    }
    out << "<" << table << ">\n";
    Stats &stats = *iter->second;
    for (int i = 0; i < VERB_COUNT; i++) {
      const char *name = Translate((Verb)i);
      out << "  <" << name << ">";
      out << stats.actions[i];
      out << "</" << name << ">\n";
    }
    out << "</" << table << ">\n";
  }

  return out.str();
}

///////////////////////////////////////////////////////////////////////////////
}
