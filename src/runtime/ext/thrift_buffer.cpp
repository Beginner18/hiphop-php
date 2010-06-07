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

#include <runtime/ext/thrift_buffer.h>
#include <runtime/base/array/array_init.h>
#include <runtime/base/externals.h>

#define BUFFER_SIZE 102400
#define INVALID_DATA 1

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

ThriftBuffer::ThriftBuffer() : m_safe(false) {
  m_buf = (char *)malloc(BUFFER_SIZE + 1);
  if (!m_buf) throwOutOfMemory();
  m_pEnd = m_buf + BUFFER_SIZE;
  m_pSafe = m_pEnd - sizeof(int64) - 1;
  m_p = m_buf;
}

ThriftBuffer::ThriftBuffer(int) {
}

ThriftBuffer::~ThriftBuffer() {
  free(m_buf);
}

void ThriftBuffer::reset(bool read) {
  if (read) {
    m_pEnd = m_buf;
    m_safe = false;
  } else {
    m_pEnd = m_buf + BUFFER_SIZE;
  }
  m_pSafe = m_pEnd - sizeof(int64) - 1;
  m_p = m_buf;
}

///////////////////////////////////////////////////////////////////////////////

void ThriftBuffer::write(CStrRef data) {
  int32 len = data.size();
  write(len);

  if (m_p + len > m_pEnd) {
    flush();
  }
  if (len > BUFFER_SIZE) {
    flush(data);
  } else {
    memcpy(m_p, data.data(), len);
    if ((m_p += len) > m_pSafe) flush();
  }
}

void ThriftBuffer::flush() {
  *m_p = '\0';
  String data(m_buf, m_p - m_buf, AttachLiteral);
  m_p = m_buf;
  flush(data);
}

void ThriftBuffer::flush(CStrRef data) {
  m_xout->o_invoke("write", CREATE_VECTOR1(data), -1);
}

///////////////////////////////////////////////////////////////////////////////

void ThriftBuffer::read(char *data, int len) {
  int avail = m_pEnd - m_p;

  // still enough
  if (avail >= len) {
    if (data) memcpy(data, m_p, len);
    if ((m_p += len) > m_pSafe) m_safe = false;
    return;
  }

  if (data) memcpy(data, m_p, avail);
  len -= avail;
  data += avail;

  Array args(CREATE_VECTOR1(BUFFER_SIZE));
  while (true) {
    String ret = m_xin->o_invoke("read", args, -1).toString();
    if (ret.empty()) {
      Object e = create_object("TProtocolException",
                               CREATE_VECTOR2("unable to read enough bytes",
                                              INVALID_DATA));
      throw e;
    }

    const char *rdata = ret.data();
    int rsize = ret.size();

    if (rsize >= len) {
      if (data) memcpy(data, rdata, len);
      rsize -= len;
      if (rsize) {
        memcpy(m_buf, rdata + len, rsize);
        m_pEnd = m_buf + rsize;
      } else {
        m_pEnd = m_buf;
      }
      m_pSafe = m_pEnd - sizeof(int64) - 1;
      m_p = m_buf;
      if (m_p > m_pSafe) m_safe = false;
      return; // done
    }

    if (data) memcpy(data, rdata, rsize);
    len -= rsize;
    data += rsize;
  }
}

void ThriftBuffer::skip(int8 type) {
  switch (type) {
    case T_STOP:
    case T_VOID:
      return;
    case T_STRUCT:
      while (true) {
        int8 ttype; read(ttype); // get field type
        if (ttype == T_STOP) break;
        read(NULL, 2); // skip field number, I16
        skip(ttype); // skip field payload
      }
      return;
    case T_BOOL:
    case T_BYTE:
      read(NULL, 1);
      return;
    case T_I16:
      read(NULL, 2);
      return;
    case T_I32:
      read(NULL, 4);
      return;
    case T_U64:
    case T_I64:
    case T_DOUBLE:
      read(NULL, 8);
      return;
    //case T_UTF7: // aliases T_STRING
    case T_UTF8:
    case T_UTF16:
    case T_STRING: {
      int32 len; read(len);
      read(NULL, len);
      } return;
    case T_MAP: {
      int8 keytype; read(keytype);
      int8 valtype; read(valtype);
      int32 size; read(size);
      for (int32 i = 0; i < size; ++i) {
        skip(keytype);
        skip(valtype);
      }
    } return;
    case T_LIST:
    case T_SET: {
      int8 valtype; read(valtype);
      int32 size; read(size);
      for (int32 i = 0; i < size; ++i) {
        skip(valtype);
      }
    } return;
  };

  char errbuf[128];
  sprintf(errbuf, "Unknown field type: %d", (int)type);
  Object e = create_object("TProtocolException",
                           CREATE_VECTOR2(String(errbuf, CopyString),
                                          INVALID_DATA));
  throw e;
}

void ThriftBuffer::throwOutOfMemory() {
  Object e = create_object("TProtocolException",
                           CREATE_VECTOR1("out of memory"));
  throw e;
}

void ThriftBuffer::throwInvalidStringSize(int size) {
  char errbuf[128];
  sprintf(errbuf, "Negative string size: %d", (int)size);
  Object e = create_object("TProtocolException",
                           CREATE_VECTOR2(String(errbuf, CopyString),
                                          INVALID_DATA));
  throw e;
}

///////////////////////////////////////////////////////////////////////////////
}
