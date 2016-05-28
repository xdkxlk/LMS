#include "stdafx.h"
#include "HtmlGenerator.h"

const CString CHtmlGenerator::c_head(CString("<!DOCTYPE html>")
	+ CString("<html lang=\"zh-CN\">")
	+CString("<head>")
	+ CString("<meta charset=\"utf-8\">")
	+ CString("<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">")
	+ CString("<meta name=\"viewport\" content=\"width=device-width, initial-scale = 1\">")
	+ CString("<link href=\"http://cdn.bootcss.com/bootstrap/3.3.5/css/bootstrap.min.css\" rel=\"stylesheet\">")
	+ CString("</head>")
	);

const CString CHtmlGenerator::c_bodyHead("<body style='background-color:#CCCCFF; '><div class='container'>");
const CString CHtmlGenerator::c_buttom("</div><script src=\"http://cdn.bootcss.com/jquery/1.11.3/jquery.min.js\"></script><script src=\"http://cdn.bootcss.com/bootstrap/3.3.5/js/bootstrap.min.js\"></script></body></html>");

CHtmlGenerator::CHtmlGenerator()
{
	m_htmlBuff = c_head + c_bodyHead;
}


CHtmlGenerator::~CHtmlGenerator()
{
}

void CHtmlGenerator::flush(IHTMLDocument2* document)
{
	document->close();

	VARIANT  *param;
	SAFEARRAY  *sfArray;
	CString str = this->getHtml();
	BSTR  bstr = str.AllocSysString();

	//  Creates  a  new  one-dimensional  array  
	sfArray = SafeArrayCreateVector(VT_VARIANT, 0, 1);

	if (sfArray == NULL || document == NULL)  {
		goto  cleanup;
	}

	SafeArrayAccessData(sfArray, (LPVOID*)&  param);
	param->vt = VT_BSTR;
	param->bstrVal = bstr;
	SafeArrayUnaccessData(sfArray);
	document->write(sfArray);

cleanup:
	SysFreeString(bstr);
	if (sfArray != NULL)  {
		SafeArrayDestroy(sfArray);
	}
}

CString CHtmlGenerator::getHtml()
{
	return m_htmlBuff + c_buttom;
}

void CHtmlGenerator::addMsg(const CString& name, const CString& msg, CHtmlData::HTMLDATATYPE type)
{
	CHtmlData data;
	data.m_message = msg;
	data.m_name = name;
	data.m_type = type;
	m_htmlData.push_back(data);

	if (type == CHtmlData::HTMLDATATYPE::USER)
	{
		m_htmlBuff += "<h5 class='text-right'>";
		m_htmlBuff += name;
		m_htmlBuff += ":</h5><h3><p class='text-right'><span style='background-color:#49e; color:white; padding:3px; border-radius:4px;'>";
		m_htmlBuff += msg;
		m_htmlBuff += "</span></p></h3>";
	}
	else if (type == CHtmlData::HTMLDATATYPE::OTHER)
	{
		m_htmlBuff += "<h5>";
		m_htmlBuff += name;
		m_htmlBuff += ":</h5><h3><p><span style='background-color:white; color:black; padding:3px; border-radius:4px;'>";
		m_htmlBuff += msg;
		m_htmlBuff += "</span></p></h3>";
	}
}