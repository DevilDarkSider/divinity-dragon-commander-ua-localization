#include <iostream>
#include "MsXml6.h"
#include "windows.h"
#include <fstream>
#include <atlbase.h>
#include <vector>
#include <atlstr.h>


struct XmlData
{
	CStringW sData;
	CStringW sHandle;
};

void GetDialogs(LPCWSTR sPath)
{
	std::vector<XmlData> aHints;
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
	path.Append(L".csv");

	std::wfstream newFile(path, std::ios_base::out | std::ios_base::binary);

	for (const auto& item : aHints)
	{
		newFile << L"\"" << item.sData.GetString() << L"\";" << item.sHandle.GetString() << std::endl;
	}
	newFile.close();
}

int main()
{
	std::vector<std::wstring> aPaths
	{
		LR"(O:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Localization\English\Video\Game_Intro.lsx)",
	};
	for (auto& path : aPaths)
	{
		GetDialogs(path.c_str());
	}
}