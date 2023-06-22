#include "mtpch.h"
#include "Button.h"

namespace Meta {

	Button::Button(float width, float height, float x, float y, sf::Color idleColour,
		sf::Color hoverColour, sf::Color clickColour, sf::Font* font, std::string text)
	{
		colourState = IDLE;
		this->idleColour = idleColour;
		this->hoverColour = hoverColour;
		this->clickColour = clickColour;
		button.setSize(sf::Vector2f(width, height));
		button.setPosition(x, y);
		button.setFillColor(idleColour);
		this->text.setFont(*font);
		this->text.setString(text);
		this->text.setFillColor(sf::Color::White);
		this->text.setCharacterSize(15);
		this->text.setPosition(button.getPosition().x + 5.f,
			button.getPosition().y + 5.f);
	}

	Button::~Button()
	{
	}


	const bool Button::isClicked()
	{
		if (colourState == CLICK)
		{
			return true;
		}
		return false;
	}

	void Button::update(const sf::Vector2f mousePos)
	{
		colourState = IDLE;
		if (button.getGlobalBounds().contains(mousePos))
		{
			colourState = HOVER;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				colourState = CLICK;
			}
		}
		switch (colourState)
		{
		case 0:
			button.setFillColor(idleColour);
			break;
		case 1:
			button.setFillColor(hoverColour);
			break;
		case 2:
			button.setFillColor(clickColour);
			break;
		}
	}

	void Button::render(std::shared_ptr<sf::RenderWindow> window)
	{
		window->draw(button);
		window->draw(text);

	}

}
