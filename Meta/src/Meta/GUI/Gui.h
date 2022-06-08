#pragma once
#include "Meta/Entities/Tilemap.h"
#include "Meta/Base/Window.h"
#include "Meta/States/State.h"

namespace Meta
{

	class META_API Gui 
	{
	private:
		sf::Texture image;
		sf::Clock deltaClock;
		std::string assetLocation;
		bool newCharacter = false;
		bool newTile = false;
		bool newBackground = false;
		bool character = false;
		bool tile = false;
		bool background = false;
		struct GuiData
		{
			std::string id = "Tile";
			int code = 0;
			int layer = 0;
			bool deleteMode = false;
			bool addMode = false;
			bool newAssetExplorer = false;
		};
	public:
		GuiData data;

		Gui();
		virtual ~Gui();

		//Editor Pause Menu
		void pauseMenu(std::shared_ptr<Window> window, 
					   std::shared_ptr<Tilemap> tilemap,
					   std::stack<std::shared_ptr<State>>* states);

		void editorState(std::shared_ptr<Window> window);

	private:
		void editorMainMenuBar(std::shared_ptr<Window> window);
		void assetExplorer(std::shared_ptr<Window> window);
	};

}
