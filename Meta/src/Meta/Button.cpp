#include "pch.h"
#include "Button.h"

namespace Meta {

	Button::Button(float width, float height, float x, float y, sf::Color idleColour,
		sf::Color hoverColour, sf::Color clickColour, sf::Font* font, std::string text)
	{
		this->colourState = this->IDLE;
		this->idleColour = idleColour;
		this->hoverColour = hoverColour;
		this->clickColour = clickColour;
		this->button.setSize(sf::Vector2f(width, height));
		this->button.setPosition(x, y);
		this->button.setFillColor(this->idleColour);
		this->text.setFont(*font);
		this->text.setString(text);
		this->text.setFillColor(sf::Color::White);
		this->text.setCharacterSize(15);
		this->text.setPosition(this->button.getPosition().x + 5.f,
			this->button.getPosition().y + 5.f);
	}

	Button::~Button()
	{
	}


	const bool Button::isClicked()
	{
		if (this->colourState == this->CLICK)
		{
			return true;
		}
		return false;
	}

	void Button::update(const sf::Vector2f mousePos)
	{
		this->colourState = this->IDLE;
		if (this->button.getGlobalBounds().contains(mousePos))
		{
			this->colourState = this->HOVER;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->colourState = this->CLICK;
			}
		}
		switch (this->colourState)
		{
		case 0:
			this->button.setFillColor(this->idleColour);
			break;
		case 1:
			this->button.setFillColor(this->hoverColour);
			break;
		case 2:
			this->button.setFillColor(this->clickColour);
			break;
		}
	}

	void Button::render(sf::RenderWindow* window)
	{
		window->draw(this->button);
		window->draw(this->text);

	}

}
