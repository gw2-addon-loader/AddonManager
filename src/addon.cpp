#include "stdafx.h"

gw2al_addon_dsc gAddonDeps[] = {
	{ L"loader_core", L"whatever", 0, 1, 1, 0 },
	LIB_IMGUI_DEP_ENTRY,
	{ 0,0,0,0,0,0 }
};

gw2al_addon_dsc gAddonDsc = {
	L"addon_manager",
	L"addon_manager ",
	1,
	0,
	1,
	gAddonDeps
};

addon_instance gInst;

addon_instance& gAddon()
{
	return gInst;
}

void log_text_fmt(gw2al_log_level level, const wchar_t* source, const wchar_t* fmt, ...)
{
	static wchar_t buf[4096];

	va_list arg;
	va_start(arg, fmt);

	vswprintf(buf, 4096, fmt, arg);

	va_end(arg);

	gInst.api->log_text(level, (wchar_t*)source, buf);
}

template<>
inline lib_imgui<Gui>& lib_imgui<Gui>::instance()
{
	return gInst.gui;
}


gw2al_addon_dsc* gw2addon_get_description()
{
	return &gAddonDsc;
}

gw2al_api_ret gw2addon_load(gw2al_core_vtable* core_api)
{
	gInst.api = core_api;

	gInst.main.init();
	gInst.gui.init(core_api, gAddonDsc.name);

	return GW2AL_OK;
}

gw2al_api_ret gw2addon_unload(int gameExiting)
{
	gInst.gui.deinit();
	gInst.main.deinit();

	return GW2AL_OK;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    return TRUE;
}
