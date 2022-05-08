#pragma once
#include "Meta/Tilemap/Tilemap.h"
#include "Meta/Base/Window.h"
#include "Meta/States/State.h"

namespace Meta
{

	class META_API Gui 
	{
	private:
		sf::Clock deltaClock;
	public:
		Gui();
		virtual ~Gui();

		//Editor Pause Menu
		void pauseMenu(std::shared_ptr<Window> window, 
					   std::shared_ptr<Tilemap> tilemap,
					   std::stack<std::shared_ptr<State>>* states);
		//Game Pause Menu
		void pauseMenu(std::shared_ptr<Window> window,
					   std::stack<std::shared_ptr<State>>* states);
		void editorState();

	};

}
