#include "stdafx.h"
#include "Main.h"

void Main::clearAddonList()
{
	for (auto& i : addonList)
		free(i.name);
	addonList.clear();
}

void Main::updateAddonList()
{
	clearAddonList();

	const wchar_t* dir = L"addons";

	WIN32_FIND_DATA fdFile;
	HANDLE hFind = NULL;

	wchar_t sPath[2048];
	wsprintf(sPath, L"%s\\*.*", dir);

	LOG_INFO(L"addon_manager", L"Reading addons from \"./%s\" path", dir);

	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
		return;

	do
	{
		if (wcscmp(fdFile.cFileName, L".") != 0
			&& wcscmp(fdFile.cFileName, L"..") != 0)
		{
			if (fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				AddonListEntry item;
				item.name = _wcsdup(fdFile.cFileName);
				item.status = GW2AL_FAIL;
				item.hashedName = gAddon().api->hash_name(item.name);
				item.dsc = nullptr;
				item.showConfigPage = false;
				item.menuShowProc = nullptr;

				/*
				constexpr size_t mbstrSz = 4096;
				item.nameA = new char[mbstrSz];
				size_t unused;
				wcstombs_s(&unused, item.nameA, mbstrSz, item.name, mbstrSz - 1);
				*/

				addonList.push_back(item);
			}
		}
	} while (FindNextFile(hFind, &fdFile));

	FindClose(hFind);

	LOG_INFO(L"addon_manager", L"Found %u possible addons", addonList.size());
}

void Main::updateAddonStatuses()
{
	for (AddonListEntry& i : addonList)
	{
		i.dsc = gAddon().api->query_addon(i.hashedName);

		//if it is properly loaded just set status OK
		if (i.dsc)
			i.status = GW2AL_OK;
		else //otherwise try to load it again and store load error in status
			i.status = gAddon().api->load_addon(i.name);

		wchar_t sMenuProc[2048];
		wsprintf(sMenuProc, L"%s_ExternalShowMenu", i.name);
		auto sMenuHa = gAddon().api->hash_name(sMenuProc);
		i.menuShowProc = (ExternalMenuShowProcType)gAddon().api->query_function(sMenuHa);
	}
}

void Main::ensureActualAddonData()
{
	if (!shouldUpdateAddons)
		return;

	updateAddonList();
	updateAddonStatuses();

	shouldUpdateAddons = false;
}

void Main::init()
{
	shouldUpdateAddons = true;
}

void Main::deinit()
{
	clearAddonList();
}
