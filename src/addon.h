#pragma once
#include "stdafx.h"

struct addon_instance
{
	gw2al_core_vtable* api;
	Main main;
	lib_imgui<Gui> gui;
};

addon_instance& gAddon();

void log_text_fmt(gw2al_log_level level, const wchar_t* source, const wchar_t* fmt, ...);

#define LOG_INFO(m, t, ...) log_text_fmt(LL_INFO, m, t, __VA_ARGS__)
#define LOG_ERROR(m, t, ...) log_text_fmt(LL_ERR, m, t, __VA_ARGS__)
#define LOG_WARNING(m, t, ...) log_text_fmt(LL_WARN, m, t, __VA_ARGS__)
#define LOG_DEBUG(m, t, ...) log_text_fmt(LL_DEBUG, m, t, __VA_ARGS__)