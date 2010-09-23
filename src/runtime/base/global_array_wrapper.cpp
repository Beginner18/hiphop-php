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

#include <runtime/base/global_array_wrapper.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

void GlobalArrayWrapper::release() {
}

ssize_t GlobalArrayWrapper::size() const {
  return m_globals->size();
}

Variant GlobalArrayWrapper::getKey(ssize_t pos) const {
  Variant k;
  m_globals->getByIdx(pos, k);
  return k;
}
Variant GlobalArrayWrapper::getValue(ssize_t pos) const {
  Variant k;
  return m_globals->getByIdx(pos, k);
}
CVarRef GlobalArrayWrapper::getValueRef(ssize_t pos) const {
  Variant k;
  return m_globals->getRefByIdx(pos, k);
}
bool GlobalArrayWrapper::supportValueRef() const { return true; }
bool GlobalArrayWrapper::isGlobalArrayWrapper() const { return true; }

bool GlobalArrayWrapper::exists(int64   k) const {
  return exists(Variant(k));
}
bool GlobalArrayWrapper::exists(litstr  k) const {
  return exists(Variant(k));
}
bool GlobalArrayWrapper::exists(CStrRef k) const {
  return exists(Variant(k));
}
bool GlobalArrayWrapper::exists(CVarRef k) const {
  return m_globals->exists(k.toString().data());
}
bool GlobalArrayWrapper::idxExists(ssize_t idx) const {
  return idx < size();
}

Variant GlobalArrayWrapper::get(int64   k, bool error /* = false */) const {
  return get(Variant(k));
}
Variant GlobalArrayWrapper::get(litstr  k, bool error /* = false */) const {
  if (exists(k)) {
    return m_globals->get(k);
  }
  return Variant();
}
Variant GlobalArrayWrapper::get(CStrRef k, bool error /* = false */) const {
  if (exists(k)) {
    return m_globals->get(k);
  }
  return Variant();
}
Variant GlobalArrayWrapper::get(CVarRef k, bool error /* = false */) const {
  if (exists(k)) {
    return m_globals->get(k);
  }
  return Variant();
}

void GlobalArrayWrapper::load(CVarRef k, Variant &v) const {
  ssize_t idx = getIndex(k);
  if (idx >= 0) {
    CVarRef r = getValueRef(idx);
    if (r.isReferenced()) v = ref(r); else v = r;
  }
}

ssize_t GlobalArrayWrapper::getIndex(int64 k) const {
  String s = toString(k);
  return m_globals->getIndex(s.data(), s->hash());
}
ssize_t GlobalArrayWrapper::getIndex(litstr k) const {
  String s(k, AttachLiteral);
  return m_globals->getIndex(k, s->hash());
}
ssize_t GlobalArrayWrapper::getIndex(CStrRef k) const {
  return m_globals->getIndex(k.data(), k->hash());
}

ssize_t GlobalArrayWrapper::getIndex(CVarRef k) const {
  if (k.isInteger()) {
    return ((Array*)m_globals)->get()->getIndex(k.toInt64()) +
      m_globals->size();
  }
  String s = k.toString();
  return m_globals->getIndex(s.data(), s->hash());
}

ArrayData *GlobalArrayWrapper::lval(Variant *&ret, bool copy) {
  ret = &m_globals->lval();
  return NULL;
}
ArrayData *GlobalArrayWrapper::lval(int64   k, Variant *&ret, bool copy,
    bool checkExist /* = false */) {
  return lval(Variant(k), ret, copy);
}
ArrayData *GlobalArrayWrapper::lval(litstr  k, Variant *&ret, bool copy,
    bool checkExist /* = false */) {
  ret = &m_globals->get(k);
  return NULL;
}
ArrayData *GlobalArrayWrapper::lval(CVarRef k, Variant *&ret, bool copy,
    bool checkExist /* = false */) {
  ret = &m_globals->get(k);
  return NULL;
}
ArrayData *GlobalArrayWrapper::lval(CStrRef k, Variant *&ret, bool copy,
    bool checkExist /* = false */) {
  ret = &m_globals->get(k);
  return NULL;
}

ArrayData *GlobalArrayWrapper::set(int64   k, CVarRef v, bool copy) {
  set(Variant(k), v, copy);
  return NULL;
}
ArrayData *GlobalArrayWrapper::set(litstr  k, CVarRef v, bool copy) {
  m_globals->get(k) = v;
  return NULL;
}
ArrayData *GlobalArrayWrapper::set(CStrRef k, CVarRef v, bool copy) {
  m_globals->get(k) = v;
  return NULL;
}
ArrayData *GlobalArrayWrapper::set(CVarRef k, CVarRef v, bool copy) {
  m_globals->get(k) = v;
  return NULL;
}

ArrayData *GlobalArrayWrapper::remove(int64   k, bool copy) {
  return remove(Variant(k), copy);
}
ArrayData *GlobalArrayWrapper::remove(litstr  k, bool copy) {
  unset(m_globals->get(k));
  return NULL;
}
ArrayData *GlobalArrayWrapper::remove(CStrRef k, bool copy) {
  unset(m_globals->get(k));
  return NULL;
}
ArrayData *GlobalArrayWrapper::remove(CVarRef k, bool copy) {
  unset(m_globals->get(k));
  return NULL;
}

ArrayData *GlobalArrayWrapper::copy() const {
  return NULL;
}

ArrayData *GlobalArrayWrapper::append(CVarRef v, bool copy) {
  m_globals->append(v);
  return NULL;
}

ArrayData *GlobalArrayWrapper::append(const ArrayData *elems, ArrayOp op,
                                      bool copy) {
  ((Array*)m_globals)->get()->append(elems, op, false);
  return NULL;
}

ArrayData *GlobalArrayWrapper::pop(Variant &value) {
  throw NotSupportedException(__func__, "manipulating globals array");
}

ArrayData *GlobalArrayWrapper::dequeue(Variant &value) {
  throw NotSupportedException(__func__, "manipulating globals array");
}

ArrayData *GlobalArrayWrapper::prepend(CVarRef v, bool copy) {
  throw NotSupportedException(__func__, "manipulating globals array");
}

ssize_t GlobalArrayWrapper::iter_begin() const {
  return m_globals->iter_begin();
}
ssize_t GlobalArrayWrapper::iter_end() const {
  return m_globals->iter_end();
}
ssize_t GlobalArrayWrapper::iter_advance(ssize_t prev) const {
  return m_globals->iter_advance(prev);
}
ssize_t GlobalArrayWrapper::iter_rewind(ssize_t prev) const {
  return m_globals->iter_rewind(prev);
}

Variant GlobalArrayWrapper::next() {
  m_pos = m_globals->iter_advance(m_pos);
  return value(m_pos);
}

void GlobalArrayWrapper::getFullPos(FullPos &pos) {
  if (m_pos == ArrayData::invalid_index) {
    pos.primary = ArrayData::invalid_index;
  } else if (m_pos < m_globals->staticSize()) {
    pos.primary = m_pos;
    pos.secondary = ArrayData::invalid_index;
  } else {
    m_globals->getFullPos(pos);
  }
}

bool GlobalArrayWrapper::setFullPos(const FullPos &pos) {
  if (pos.primary != ArrayData::invalid_index) {
    if (m_pos < m_globals->staticSize()) return true;
    ArrayData *data = m_globals->getArrayData();
    if (data) {
      data->reset();
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

///////////////////////////////////////////////////////////////////////////////
}
