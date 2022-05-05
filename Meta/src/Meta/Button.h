#pragma once
#include "Core.h"

namespace Meta {

	class META_API Button
	{
	private:
		//Button
		sf::RectangleShape button;
		//Font
		sf::Font font;
		sf::Text text;
		//Colour
		int colourState;
		sf::Color idleColour;
		sf::Color hoverColour;
		sf::Color clickColour;
		enum colourState
		{
			IDLE = 0, HOVER, CLICK
		};
	public:
		Button(float width, float height, float x, float y, sf::Color idleColour,
			sf::Color hoverColour, sf::Color clickColour, sf::Font* font, std::string text);
		virtual ~Button();

		//Functions
		const bool isClicked();
		void update(const sf::Vector2f mousePos);
		void render(std::shared_ptr<sf::RenderWindow> window);

	};

}
