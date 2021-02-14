#pragma once
#include "stdafx.h"

typedef void(*ExternalMenuShowProcType)();

class Main
{
public:

	struct AddonListEntry
	{
		wchar_t* name;
		gw2al_api_ret status;
		gw2al_hashed_name hashedName;
		ExternalMenuShowProcType menuShowProc;
		bool showConfigPage;
		const gw2al_addon_dsc* dsc;
	};
	const std::vector<AddonListEntry>& GetAddonList() { return addonList; }

private:

	void clearAddonList();
	void updateAddonList();
	void updateAddonStatuses();

	std::vector<AddonListEntry> addonList;
	bool shouldUpdateAddons;

public:


	void ensureActualAddonData();
	void init();
	void deinit();
};

