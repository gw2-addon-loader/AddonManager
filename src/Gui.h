#pragma once
#include "stdafx.h"

class Gui
{
	struct ToggleButton
	{
		void init();
		void act(Gui& gui);
		ImVec2 pos;
		ImVec2 size;
	} toggleButton;

	struct MainWindow
	{
		bool visible;
		void init();
		void act();
		int activeIndex = -1;
	} mainWindow;

public:
	Gui();

	void init();
	void draw();
	void deinit();
};

