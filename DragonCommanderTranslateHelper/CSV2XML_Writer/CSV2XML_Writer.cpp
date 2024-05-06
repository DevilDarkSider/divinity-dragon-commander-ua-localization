#include "MsXml6.h"
#include "windows.h"
#include <fstream>
#include <atlbase.h>
#include <vector>
#include <atlstr.h>

#include <codecvt>
#include <iostream>
#include <string>
#include <iomanip>
#include <memory.h>
#include <string.h>

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
//silence codecvt warnings

struct XmlData
{
	CStringW sData;
	CStringW sHandle;
};
std::wstring sPathToXML = LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Localization\English\ukrainian - Copy.xml)";
std::vector<XmlData> aTranslation;

void MoveTranslationToXML(LPCWSTR sPath2CSV)
{
	aTranslation.clear();

	std::vector<XmlData> aHints;
	std::wifstream in(sPath2CSV, std::ios::binary);
	in.imbue(std::locale(in.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::little_endian>));

	std::wstring str;
	while (std::getline(in, str) && !str.empty())
	{
		auto nPos = str.rfind(L';');
		XmlData data;
		data.sHandle.SetString(str.c_str() + nPos + 1);
		data.sData.SetString(str.c_str(), nPos);
		data.sData.Trim(L'\"');
		aTranslation.push_back(std::move(data));
		
	}
	in.close();

	std::wstring sOut;
	std::wifstream out(sPathToXML, std::ios::binary);
	out.imbue(std::locale(out.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::little_endian>));
	while (std::getline(out, str) && !str.empty())
	{
		for (size_t i = 0; i < aTranslation.size(); i++)
		{
			const auto& data = aTranslation[i];
			size_t nPos = str.find(data.sHandle.GetString());
			if (nPos != (size_t)-1)
			{
				size_t nStart = str.find(L'>') + 1;
				size_t nCount = str.rfind(L'<') - nStart;

				str.erase(nStart, nCount);
				str.insert(nStart, data.sData.GetString());
				aTranslation.erase(aTranslation.begin() + i);
				break;
			}
		}


		sOut.append(str);
	}
	out.close();

	std::wofstream newFile(sPathToXML);
	newFile.imbue(std::locale());

	newFile << sOut.c_str();

	newFile.close();
}

int main()
{
	std::locale::global(std::locale(""));

	std::vector<std::wstring> aPaths
	{
		LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Hints\Hints.txt)",
	};


	for (auto& path : aPaths)
	{
		MoveTranslationToXML(path.c_str());
	}


	return 0;
}
