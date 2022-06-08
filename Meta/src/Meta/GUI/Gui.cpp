#include "mtpch.h"
#include "Gui.h"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include "imgui/imgui_stdlib.h"

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
		if (!ImGui::Begin("PauseMenu")) MT_CORE_ERROR("PauseMenu ImGui::Begin Failed!");

		if (ImGui::Button("Save", ImVec2(120.f, 25.f)))
			tilemap->saveTileMap();

		if (ImGui::Button("Quit", ImVec2(120.f, 25.f)))
		{
			window->renderWindow->setView(window->renderWindow->getDefaultView());
			states->pop();
		}

		ImGui::End();
	}

	void Gui::editorState(std::shared_ptr<Window> window)
	{
		//Editor State GUI

		//Main menu bar
		editorMainMenuBar(window);
		

	}

	void Gui::editorMainMenuBar(std::shared_ptr<Window> window)
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::MenuItem("asset menu", NULL, false, false);
				if (ImGui::BeginMenu("New"))
				{
					if (ImGui::MenuItem("Character Asset"))
					{
						newCharacter = true;
					}
					if (ImGui::MenuItem("Tile Asset"))
					{
						newTile = true;
					}

					if (ImGui::MenuItem("Background Asset"))
					{
						newBackground = true;
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Delete"))
				{
					if (ImGui::BeginMenu("Character Assets"))
					{

						for (int i = 0; i < window->characterFilePaths.size(); i++)
						{
							const char* str = window->characterFilePaths[i].c_str();
							if (ImGui::MenuItem(str))
							{
								window->deleteCharacterFile(i);
							}
						}

						ImGui::EndMenu();
					}

					if (ImGui::BeginMenu("Tile Assets"))
					{

						for (int i = 0; i < window->tileFilePaths.size(); i++)
						{
							const char* str = window->tileFilePaths[i].c_str();
							if (ImGui::MenuItem(str))
							{
								window->deleteTileFile(i);
							}
						}

						ImGui::EndMenu();
					}
					if (ImGui::BeginMenu("Background Assets"))
					{

						for (int i = 0; i < window->backgroundFilePaths.size(); i++)
						{
							const char* str = window->backgroundFilePaths[i].c_str();
							if (ImGui::MenuItem(str))
							{
								window->deleteBackgroundFile(i);
							}
						}

						ImGui::EndMenu();
					}


					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Asset"))
			{
				data.newAssetExplorer = true;

				ImGui::EndMenu();
			}


			ImGui::EndMainMenuBar();
		}
		if (newCharacter)
		{
			ImGui::Begin("Add Asset", &newCharacter);

			ImGui::InputText("asset location", &assetLocation);
			if (ImGui::Button("Save", ImVec2(120.f, 25.f)))
			{

				window->saveCharacterFile(assetLocation);
				assetLocation.clear();
			}

			ImGui::End();
		}
		if (newTile)
		{
			ImGui::Begin("Add Asset", &newTile);

			ImGui::InputText("asset location", &assetLocation);
			if (ImGui::Button("Save", ImVec2(120.f, 25.f)))
			{

				window->saveTileFile(assetLocation);
				assetLocation.clear();
			}

			ImGui::End();
		}
		if (newBackground)
		{
			ImGui::Begin("Add Asset", &newBackground);

			ImGui::InputText("asset location", &assetLocation);
			if (ImGui::Button("Save", ImVec2(120.f, 25.f)))
			{

				window->saveBackgroundFile(assetLocation);
				assetLocation.clear();
			}

			ImGui::End();
		}
		if (data.newAssetExplorer)
		{
			assetExplorer(window);
		}

	}

	void Gui::assetExplorer(std::shared_ptr<Window> window)
	{
		ImGui::Begin("Asset Explorer", &data.newAssetExplorer);

		if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
		{
			if (ImGui::BeginTabItem("Characters"))
			{
				background = false; tile = false; character = true;
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Tiles"))
			{
				background = false; tile = true; character = false;
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Backgrounds"))
			{
				background = true; tile = false; character = false;
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		//Left
		{
			ImGui::BeginChild("left pane", ImVec2(260, 0), true);
			if (character)
			{
				data.id = "Character";
				for (int i = 0; i < window->characterFilePaths.size(); i++)
				{
					const char* str = window->characterFilePaths[i].c_str();

					if (ImGui::Selectable(str, data.code == i))
					{						
						data.code = i;
					}

				}
			}
			if (tile)
			{
				data.id = "Tile";
				for (int i = 0; i < window->tileFilePaths.size(); i++)
				{
					const char* str = window->tileFilePaths[i].c_str();

					if (ImGui::Selectable(str, data.code == i))
					{
						data.code = i;
					}


				}
			}
			if (background)
			{
				data.id = "Background";
				for (int i = 0; i < window->backgroundFilePaths.size(); i++)
				{
					const char* str = window->backgroundFilePaths[i].c_str();

					if (ImGui::Selectable(str, data.code == i))
					{
						data.code = i;
					}

				}
			}
			ImGui::EndChild();
		}
		ImGui::SameLine();

		//Right
		{
			ImGui::BeginGroup();
			ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));
			if (character)
			{
				if (data.code >= window->characterFilePaths.size())
				{
					data.code = 0;
				}
				const char* str = window->characterFilePaths[data.code].c_str();
				ImGui::Text("Asset: %s", str);
				ImGui::Separator();
				if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
				{
					if (ImGui::BeginTabItem("Description"))
					{
						image.loadFromFile(window->characterFilePaths[data.code]);
						ImGui::Image(image);
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("Details"))
					{
						const char* str = data.id.c_str();
						ImGui::Text("ID: %s", str);
						ImGui::Text("Code: %d", data.code);
						ImGui::SliderInt("Layer", &data.layer, 0, 1);
						ImGui::EndTabItem();
					}
					ImGui::EndTabBar();
				}
			}
			if (tile)
			{
				if (data.code >= window->tileFilePaths.size())
				{
					data.code = 0;
				}
				const char* str = window->tileFilePaths[data.code].c_str();
				ImGui::Text("Asset: %s", str);
				ImGui::Separator();
				if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
				{
					if (ImGui::BeginTabItem("Description"))
					{
						image.loadFromFile(window->tileFilePaths[data.code]);
						ImGui::Image(image);
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("Details"))
					{
						const char* str = data.id.c_str();
						ImGui::Text("ID: %s", str);
						ImGui::Text("Code: %d", data.code);
						ImGui::SliderInt("Layer", &data.layer, 0, 1);
						ImGui::EndTabItem();
					}
					ImGui::EndTabBar();
				}
			}
			if (background)
			{
				if (data.code >= window->backgroundFilePaths.size())
				{
					data.code = 0;
				}
				const char* str = window->backgroundFilePaths[data.code].c_str();
				ImGui::Text("Asset: %s", str);
				ImGui::Separator();
				if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
				{
					if (ImGui::BeginTabItem("Description"))
					{
						image.loadFromFile(window->backgroundFilePaths[data.code]);
						ImGui::Image(image);
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("Details"))
					{
						const char* str = data.id.c_str();
						ImGui::Text("ID: %s", str);
						ImGui::Text("Code: %d", data.code);
						ImGui::SliderInt("Layer", &data.layer, 0, 1);
						ImGui::EndTabItem();
					}
					ImGui::EndTabBar();
				}
			}

			ImGui::EndChild();
			if (ImGui::Button("Add Mode")) 
			{
				data.addMode = true;
				data.deleteMode = false;
				data.newAssetExplorer = false;
			}
			ImGui::SameLine();
			if (ImGui::Button("Delete Mode")) 
			{
				data.deleteMode = true;
				data.addMode = false;
				data.newAssetExplorer = false;
			}

			ImGui::EndGroup();
		}

		ImGui::End();

	}

}
