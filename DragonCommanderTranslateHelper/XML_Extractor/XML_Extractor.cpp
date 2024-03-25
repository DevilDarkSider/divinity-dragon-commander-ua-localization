#include <iostream>
#include "MsXml6.h"
#include "windows.h"
#include <fstream>
#include <atlbase.h>
#include <variant>

LPCWSTR sPath = L"O:\\SteamLibrary\\steamapps\\common\\Divinity Dragon Commander\\Data\\Mods\\Main\\Gameplay\\Hints\\Hints.lsx";

int main()
{
	HRESULT hr = CoInitialize(nullptr);
	if (FAILED(hr))
		MessageBox(nullptr, L"Failed to CoInitialize", L"Failed", MB_OK);

	CComPtr<IXMLDOMDocument> pXMLDoc;
	hr = pXMLDoc.CoCreateInstance(__uuidof(DOMDocument60));
	if (FAILED(hr))
		MessageBox(nullptr, L"Failed to CoCreateInstance DOMDocument60", L"Failed", MB_OK);

	VARIANT var;
	VariantInit(&var);

	var.bstrVal = CComBSTR(sPath);
	var.vt = VT_BSTR;

	VARIANT_BOOL bSuc = VARIANT_FALSE;
	hr = pXMLDoc->load(var, &bSuc);

	VariantClear(&var);


	CComBSTR sName;
	pXMLDoc->get_nodeName(&sName);
	std::wcout << sName.m_str << std::endl;

	CComPtr<IXMLDOMNodeList> pNodes;
	pXMLDoc->get_childNodes(&pNodes);

	long nCount = 0;
	pNodes->get_length(&nCount);

	std::wcout << L"Count of nodes: " << nCount << std::endl;

	for (long i = 0; i < nCount; i++)
	{
		CComPtr<IXMLDOMNode> pNode;
		pNodes->get_item(i, &pNode);
		pNode->get_nodeName(&sName);
		std::wcout << sName.m_str << std::endl;
	}
}