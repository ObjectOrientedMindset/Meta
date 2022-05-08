#include "mtpch.h"
#include "Gui.h"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

namespace Meta {


	Gui::Gui()
	{
	}

	Gui::~Gui()
	{

	}

	void Gui::pauseMenu(std::shared_ptr<Window> window, std::shared_ptr<Tilemap> tilemap,
						std::stack<std::shared_ptr<State>>* states)
	{
		//Editor Pause Menu GUI
		if(!ImGui::Begin("PauseMenu")) MT_CORE_ERROR("ImGui::Begin Failed!");

		if (ImGui::Button("Save", ImVec2(120.f, 25.f)))
			tilemap->saveTileMap();
				
		if (ImGui::Button("Quit", ImVec2(120.f, 25.f)))
			states->pop();

		ImGui::End();
	}

	void Gui::pauseMenu(std::shared_ptr<Window> window, std::stack<std::shared_ptr<State>>* states)
	{
		//Game Pause Menu GUI

	}

	void Gui::editorState()
	{
		//Editor State GUI
		bool show = true;
		ImGui::ShowDemoWindow(&show);

	}

}
