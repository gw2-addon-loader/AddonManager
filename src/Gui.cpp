#include "stdafx.h"

Gui::Gui()
{
}

void Gui::init()
{
	toggleButton.init();
	mainWindow.init();
}

void Gui::draw()
{
	toggleButton.act(*this);
	mainWindow.act();
}

void Gui::deinit()
{
	//CHANGE ME
}

//main toggle button that should open up addon manager main menu
//should be blended with game ui
//and also maybe triggerable via hotkey

void Gui::ToggleButton::init()
{
	//TODO: calculate from smth to fit into game UI
	size = ImVec2(10, 10);
	pos = ImVec2(0, 0);
	//TODO: load image (maybe via imgui_lib?)
}

void Gui::ToggleButton::act(Gui & gui)
{
	ImGui::Begin("main menu toggle button", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowPos(pos);
	ImGui::SetWindowSize(size);
	//TODO: use image
	if (ImGui::Button("AM", size))
		gui.mainWindow.visible = !gui.mainWindow.visible;
	ImGui::End();
}

////////////////////

//Main window with addon listing/actions/etc
//

void Gui::MainWindow::init()
{
	visible = false;
}

void Gui::MainWindow::act()
{
	if (!visible)
		return;

	gAddon().main.ensureActualAddonData();

	ImGui::Begin("GW2 addon manager");

	for (const auto& i : gAddon().main.GetAddonList())
	{
		ImGui::Text("%S", i.name);

		if (i.status == GW2AL_OK)
		{
			ImGui::SameLine();
			if (!i.dsc)
			{				
				ImGui::Text("E: [no description found]");
				continue;
			} 

			ImGui::Text("v%u.%u build %u", i.dsc->majorVer, i.dsc->minorVer, i.dsc->revision);
			//TODO: make it a hover popup
			ImGui::Text("%S", i.dsc->description);
		}
		else {
			ImGui::SameLine();
			switch (i.status)
			{
			case GW2AL_BAD_DLL:
				ImGui::Text("E: [missing one of export functions]");
				break;
			case GW2AL_NOT_FOUND:
				ImGui::Text("E: [dll not found]");
				break;
			case GW2AL_DEP_NOT_LOADED:
				ImGui::Text("E: [dependency missing]");
				break;
			case GW2AL_DEP_OUTDATED:
				ImGui::Text("E: [dependency outdated]");
				break;
			default:
				ImGui::Text("E: [general failure]");
				break;
			}
		}

		//TODO: make this work
		ImGui::Button("Update");
		ImGui::SameLine();
		ImGui::Button("Reload");
		ImGui::SameLine();
		ImGui::Button("Disable");
		ImGui::SameLine();
		ImGui::Button("Open config menu");
	}
	
	ImGui::End();
}
