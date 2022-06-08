#pragma once
#include "Meta/States/State.h"
#include "Meta/Entities/Tilemap.h"
#include "Meta/Base/Core.h"

namespace Meta {

	class META_API PauseMenu
	{
	private:
		//Variables
		sf::RectangleShape background;
		sf::Text text;
		std::vector<std::shared_ptr<Button>> buttons;
	public:
		PauseMenu(const sf::RenderWindow& window, sf::Font& font);
		~PauseMenu();
		
		//Functions
		bool update(const sf::Vector2f mousePos, std::stack<std::shared_ptr<State>>* states);
		void render(std::shared_ptr<sf::RenderWindow> window);
	};

}

