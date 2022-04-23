#pragma once
#include"Button.h"
#include"State.h"
#include"Player.h"
#include"Tilemap.h"
#include "Core.h"

namespace Meta {

	class META_API PauseMenu
	{
	private:
		//Variables
		sf::RectangleShape background;
		sf::Text text;
		std::vector<Button*> button;
	public:
		PauseMenu(sf::RenderWindow& window, sf::Font& font);
		~PauseMenu();

		//Functions
		bool update(const sf::Vector2f mousePos, std::stack<State*>* states);
		void render(sf::RenderWindow* window);
	};

}

