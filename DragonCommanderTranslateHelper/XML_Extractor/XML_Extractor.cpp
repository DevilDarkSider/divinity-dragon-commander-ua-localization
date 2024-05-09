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

		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\Grumio\default_dialog_grumio.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\Grumio\end_turn_grumio.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Subtitles\CombatMoveAround.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_1_elf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_2_aida.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_2_dwarf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_2_lizard_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_3_aida.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_3_dwarf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_3_elf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_4_aida.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_4_dwarf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_4_undead_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_5_1_aida.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_5_1_dwarf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_5_1_elf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_5_2_aida.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_5_2_dwarf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_5_2_elf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_5_aida.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_5_dwarf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_5_undead_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_6_aida.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_6_dwarf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_6_elf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_7_aida.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_7_dwarf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_7_imp_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_8_aida.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_8_dwarf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_8_imp_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_9_1_1_aida.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_9_1_1_dwarf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_9_1_1_undead_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_9_1_2_aida.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_9_1_2_dwarf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_9_1_2_undead_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_9_1_aida.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_9_1_dwarf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_9_1_undead_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_9_2_1_aida.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_9_2_1_dwarf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_9_2_1_undead_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_9_2_2_aida.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_9_2_2_dwarf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_9_2_2_undead_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_9_2_aida.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_9_2_dwarf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_9_2_undead_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_10_1_aida.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_10_1_dwarf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_10_1_lizard_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_10_2_aida.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_10_2_dwarf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_10_2_lizard_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_10_aida.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_10_dwarf_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\aida_10_lizard_council.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\default_dialog_aida.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\mspr02_aida_intro.lsx)",
		//LR"(D:\SteamLibrary\steamapps\common\Divinity Dragon Commander\Data\Mods\Main\Gameplay\Story\Dialogs\_templates_\In Progress\mspr03_aida.lsx)",
	};
	for (auto& path : aPaths)
	{
		GetDialogs(path.c_str());
	}
}