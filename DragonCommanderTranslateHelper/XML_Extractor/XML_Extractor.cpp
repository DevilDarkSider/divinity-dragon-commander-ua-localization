#include <iostream>
#include "MsXml6.h"
#include "windows.h"
#include <fstream>
#include <atlbase.h>
#include <vector>
#include <atlstr.h>

LPCWSTR sPath = LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\aida_1_dwarf_council.lsx)";

struct XmlData
{
	CStringW sData;
	CStringW sHandle;
};

std::vector<XmlData> aHints;

int main()
{
	/*HRESULT hr = CoInitialize(nullptr);
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



	

	CComPtr<IXMLDOMNodeList> pNodes;
	pXMLDoc->get_childNodes(&pNodes);

	CComPtr<IXMLDOMNode> pNode;
	pNodes->get_item(1, &pNode);

	pNodes = nullptr;
	pNode->get_childNodes(&pNodes);

	pNode = nullptr;
	pNodes->get_item(2, &pNode);


	pNodes = nullptr;
	pNode->get_childNodes(&pNodes);

	pNode = nullptr;
	pNodes->get_item(0, &pNode);

	pNodes = nullptr;
	pNode->get_childNodes(&pNodes);

	pNode = nullptr;
	pNodes->get_item(0, &pNode);

	pNodes = nullptr;
	pNode->get_childNodes(&pNodes);

	long nCount = 0;
	pNodes->get_length(&nCount);

	for (long i = 0; i < nCount; i++)
	{
		CComPtr<IXMLDOMNode> pItem;
		pNodes->get_item(i, &pItem);

		CComPtr<IXMLDOMNodeList> pItemNodes;
		pItem->get_childNodes(&pItemNodes);

		CComPtr<IXMLDOMNode> pItemAtributes;
		pItemNodes->get_item(0, &pItemAtributes);

		CComPtr<IXMLDOMNamedNodeMap> pMap;
		pItemAtributes->get_attributes(&pMap);

		VARIANT val;
		VariantInit(&val);

		CComPtr<IXMLDOMNode> pVal;
		pMap->removeNamedItem(CComBSTR(L"value"), &pVal);
		pVal->get_nodeValue(&val);

		hintData data;
		data.sData.SetString(val.bstrVal);

		pVal = nullptr;
		pMap->removeNamedItem(CComBSTR(L"handle"), &pVal);
		pVal->get_nodeValue(&val);

		data.sHandle.SetString(val.bstrVal);

		aHints.push_back(std::move(data));

		VariantClear(&val);
	}

	VariantClear(&var);*/

	std::wifstream file(sPath, std::ios_base::in | std::ios_base::binary);
	
	std::wstring sLine;
	wchar_t ch = 0;
	while (file.get(ch))
	{
		if (ch == L'\n')
		{
			long nFind = sLine.find(L"<attribute id=\"Text\"");
			if (nFind >= 0)
			{
				XmlData data;
				
				long nVal = sLine.find(L"value=");
				nVal += 7;
				long nEnd = sLine.find(L"\"", nVal);

				data.sData.SetString(sLine.c_str() + nVal, nEnd - nVal);

				nVal = sLine.find(L"handle=");
				nVal += 8;
				nEnd = sLine.find(L"\"", nVal);
				data.sHandle.SetString(sLine.c_str() + nVal, nEnd - nVal);

				aHints.push_back(std::move(data));
			}
			sLine.clear();
			continue;
		}

		sLine.append(1, ch);
	}
	
	
	file.close();


	CStringW path(sPath);
	long nPos = path.ReverseFind(L'.');
	path.Delete(nPos, 4);
	path.Append(L".txt");

	std::wfstream newFile(path, std::ios_base::out | std::ios_base::binary);

	for (const auto& item : aHints)
	{
		newFile << L"\"" << item.sData.GetString() << L"\";" << item.sHandle.GetString() << std::endl;
	}
	newFile.close();

}