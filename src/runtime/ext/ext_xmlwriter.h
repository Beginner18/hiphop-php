/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
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

#ifndef __EXT_XMLWRITER_H__
#define __EXT_XMLWRITER_H__

// >>>>>> Generated by idl.php. Do NOT modify. <<<<<<

#include <runtime/base/base_includes.h>
#include <libxml/tree.h>
#include <libxml/xmlwriter.h>
#include <libxml/uri.h>
#include <runtime/base/file/file.h>
namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

Variant f_xmlwriter_open_memory();
Object f_xmlwriter_open_uri(CStrRef uri);
bool f_xmlwriter_set_indent_string(CObjRef xmlwriter, CStrRef indentstring);
bool f_xmlwriter_set_indent(CObjRef xmlwriter, bool indent);
bool f_xmlwriter_start_document(CObjRef xmlwriter, CStrRef version = "1.0", CStrRef encoding = null_string, CStrRef standalone = null_string);
bool f_xmlwriter_start_element(CObjRef xmlwriter, CStrRef name);
bool f_xmlwriter_start_element_ns(CObjRef xmlwriter, CStrRef prefix, CStrRef name, CStrRef uri);
bool f_xmlwriter_write_element_ns(CObjRef xmlwriter, CStrRef prefix, CStrRef name, CStrRef uri, CStrRef content = null_string);
bool f_xmlwriter_write_element(CObjRef xmlwriter, CStrRef name, CStrRef content = null_string);
bool f_xmlwriter_end_element(CObjRef xmlwriter);
bool f_xmlwriter_full_end_element(CObjRef xmlwriter);
bool f_xmlwriter_start_attribute_ns(CObjRef xmlwriter, CStrRef prefix, CStrRef name, CStrRef uri);
bool f_xmlwriter_start_attribute(CObjRef xmlwriter, CStrRef name);
bool f_xmlwriter_write_attribute_ns(CObjRef xmlwriter, CStrRef prefix, CStrRef name, CStrRef uri, CStrRef content);
bool f_xmlwriter_write_attribute(CObjRef xmlwriter, CStrRef name, CStrRef value);
bool f_xmlwriter_end_attribute(CObjRef xmlwriter);
bool f_xmlwriter_start_cdata(CObjRef xmlwriter);
bool f_xmlwriter_write_cdata(CObjRef xmlwriter, CStrRef content);
bool f_xmlwriter_end_cdata(CObjRef xmlwriter);
bool f_xmlwriter_start_comment(CObjRef xmlwriter);
bool f_xmlwriter_write_comment(CObjRef xmlwriter, CStrRef content);
bool f_xmlwriter_end_comment(CObjRef xmlwriter);
bool f_xmlwriter_end_document(CObjRef xmlwriter);
bool f_xmlwriter_start_pi(CObjRef xmlwriter, CStrRef target);
bool f_xmlwriter_write_pi(CObjRef xmlwriter, CStrRef target, CStrRef content);
bool f_xmlwriter_end_pi(CObjRef xmlwriter);
bool f_xmlwriter_text(CObjRef xmlwriter, CStrRef content);
bool f_xmlwriter_write_raw(CObjRef xmlwriter, CStrRef content);
bool f_xmlwriter_start_dtd(CObjRef xmlwriter, CStrRef qualifiedname, CStrRef publicid = null_string, CStrRef systemid = null_string);
bool f_xmlwriter_write_dtd(CObjRef xmlwriter, CStrRef name, CStrRef publicid = null_string, CStrRef systemid = null_string, CStrRef subset = null_string);
bool f_xmlwriter_start_dtd_element(CObjRef xmlwriter, CStrRef qualifiedname);
bool f_xmlwriter_write_dtd_element(CObjRef xmlwriter, CStrRef name, CStrRef content);
bool f_xmlwriter_end_dtd_element(CObjRef xmlwriter);
bool f_xmlwriter_start_dtd_attlist(CObjRef xmlwriter, CStrRef name);
bool f_xmlwriter_write_dtd_attlist(CObjRef xmlwriter, CStrRef name, CStrRef content);
bool f_xmlwriter_end_dtd_attlist(CObjRef xmlwriter);
bool f_xmlwriter_start_dtd_entity(CObjRef xmlwriter, CStrRef name, bool isparam);
bool f_xmlwriter_write_dtd_entity(CObjRef xmlwriter, CStrRef name, CStrRef content, bool pe = false, CStrRef publicid = null_string, CStrRef systemid = null_string, CStrRef ndataid = null_string);
bool f_xmlwriter_end_dtd_entity(CObjRef xmlwriter);
bool f_xmlwriter_end_dtd(CObjRef xmlwriter);
Variant f_xmlwriter_flush(CObjRef xmlwriter, bool empty = true);
String f_xmlwriter_output_memory(CObjRef xmlwriter, bool flush = true);

///////////////////////////////////////////////////////////////////////////////
// class XMLWriter

FORWARD_DECLARE_CLASS_BUILTIN(XMLWriter);
class c_XMLWriter : public ExtObjectData, public Sweepable {
 public:
  DECLARE_CLASS(XMLWriter, XMLWriter, ObjectData)

  // need to implement
  public: c_XMLWriter(const ObjectStaticCallbacks *cb = &cw_XMLWriter);
  public: ~c_XMLWriter();
  public: void t___construct();
  DECLARE_METHOD_INVOKE_HELPERS(__construct);
  public: bool t_openmemory();
  DECLARE_METHOD_INVOKE_HELPERS(openmemory);
  public: bool t_openuri(CStrRef uri);
  DECLARE_METHOD_INVOKE_HELPERS(openuri);
  public: bool t_setindentstring(CStrRef indentstring);
  DECLARE_METHOD_INVOKE_HELPERS(setindentstring);
  public: bool t_setindent(bool indent);
  DECLARE_METHOD_INVOKE_HELPERS(setindent);
  public: bool t_startdocument(CStrRef version = "1.0", CStrRef encoding = null_string, CStrRef standalone = null_string);
  DECLARE_METHOD_INVOKE_HELPERS(startdocument);
  public: bool t_startelement(CStrRef name);
  DECLARE_METHOD_INVOKE_HELPERS(startelement);
  public: bool t_startelementns(CStrRef prefix, CStrRef name, CStrRef uri);
  DECLARE_METHOD_INVOKE_HELPERS(startelementns);
  public: bool t_writeelementns(CStrRef prefix, CStrRef name, CStrRef uri, CStrRef content = null_string);
  DECLARE_METHOD_INVOKE_HELPERS(writeelementns);
  public: bool t_writeelement(CStrRef name, CStrRef content = null_string);
  DECLARE_METHOD_INVOKE_HELPERS(writeelement);
  public: bool t_endelement();
  DECLARE_METHOD_INVOKE_HELPERS(endelement);
  public: bool t_fullendelement();
  DECLARE_METHOD_INVOKE_HELPERS(fullendelement);
  public: bool t_startattributens(CStrRef prefix, CStrRef name, CStrRef uri);
  DECLARE_METHOD_INVOKE_HELPERS(startattributens);
  public: bool t_startattribute(CStrRef name);
  DECLARE_METHOD_INVOKE_HELPERS(startattribute);
  public: bool t_writeattributens(CStrRef prefix, CStrRef name, CStrRef uri, CStrRef content);
  DECLARE_METHOD_INVOKE_HELPERS(writeattributens);
  public: bool t_writeattribute(CStrRef name, CStrRef value);
  DECLARE_METHOD_INVOKE_HELPERS(writeattribute);
  public: bool t_endattribute();
  DECLARE_METHOD_INVOKE_HELPERS(endattribute);
  public: bool t_startcdata();
  DECLARE_METHOD_INVOKE_HELPERS(startcdata);
  public: bool t_writecdata(CStrRef content);
  DECLARE_METHOD_INVOKE_HELPERS(writecdata);
  public: bool t_endcdata();
  DECLARE_METHOD_INVOKE_HELPERS(endcdata);
  public: bool t_startcomment();
  DECLARE_METHOD_INVOKE_HELPERS(startcomment);
  public: bool t_writecomment(CStrRef content);
  DECLARE_METHOD_INVOKE_HELPERS(writecomment);
  public: bool t_endcomment();
  DECLARE_METHOD_INVOKE_HELPERS(endcomment);
  public: bool t_enddocument();
  DECLARE_METHOD_INVOKE_HELPERS(enddocument);
  public: bool t_startpi(CStrRef target);
  DECLARE_METHOD_INVOKE_HELPERS(startpi);
  public: bool t_writepi(CStrRef target, CStrRef content);
  DECLARE_METHOD_INVOKE_HELPERS(writepi);
  public: bool t_endpi();
  DECLARE_METHOD_INVOKE_HELPERS(endpi);
  public: bool t_text(CStrRef content);
  DECLARE_METHOD_INVOKE_HELPERS(text);
  public: bool t_writeraw(CStrRef content);
  DECLARE_METHOD_INVOKE_HELPERS(writeraw);
  public: bool t_startdtd(CStrRef qualifiedname, CStrRef publicid = null_string, CStrRef systemid = null_string);
  DECLARE_METHOD_INVOKE_HELPERS(startdtd);
  public: bool t_writedtd(CStrRef name, CStrRef publicid = null_string, CStrRef systemid = null_string, CStrRef subset = null_string);
  DECLARE_METHOD_INVOKE_HELPERS(writedtd);
  public: bool t_startdtdelement(CStrRef qualifiedname);
  DECLARE_METHOD_INVOKE_HELPERS(startdtdelement);
  public: bool t_writedtdelement(CStrRef name, CStrRef content);
  DECLARE_METHOD_INVOKE_HELPERS(writedtdelement);
  public: bool t_enddtdelement();
  DECLARE_METHOD_INVOKE_HELPERS(enddtdelement);
  public: bool t_startdtdattlist(CStrRef name);
  DECLARE_METHOD_INVOKE_HELPERS(startdtdattlist);
  public: bool t_writedtdattlist(CStrRef name, CStrRef content);
  DECLARE_METHOD_INVOKE_HELPERS(writedtdattlist);
  public: bool t_enddtdattlist();
  DECLARE_METHOD_INVOKE_HELPERS(enddtdattlist);
  public: bool t_startdtdentity(CStrRef name, bool isparam);
  DECLARE_METHOD_INVOKE_HELPERS(startdtdentity);
  public: bool t_writedtdentity(CStrRef name, CStrRef content, bool pe = false, CStrRef publicid = null_string, CStrRef systemid = null_string, CStrRef ndataid = null_string);
  DECLARE_METHOD_INVOKE_HELPERS(writedtdentity);
  public: bool t_enddtdentity();
  DECLARE_METHOD_INVOKE_HELPERS(enddtdentity);
  public: bool t_enddtd();
  DECLARE_METHOD_INVOKE_HELPERS(enddtd);
  public: Variant t_flush(bool empty = true);
  DECLARE_METHOD_INVOKE_HELPERS(flush);
  public: String t_outputmemory(bool flush = true);
  DECLARE_METHOD_INVOKE_HELPERS(outputmemory);
  public: Variant t___destruct();
  DECLARE_METHOD_INVOKE_HELPERS(__destruct);

  // implemented by HPHP
  public: c_XMLWriter *create();


 public:
  SmartObject<File>  m_uri;
 private:
  xmlTextWriterPtr   m_ptr;
  xmlBufferPtr       m_output;
  xmlOutputBufferPtr m_uri_output;
};

///////////////////////////////////////////////////////////////////////////////
}

#endif // __EXT_XMLWRITER_H__
