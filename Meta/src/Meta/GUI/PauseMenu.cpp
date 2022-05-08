#include "mtpch.h"
#include "PauseMenu.h"

namespace Meta {

	PauseMenu::PauseMenu(const sf::RenderWindow& window, sf::Font& font)
	{
		background.setPosition(window.getSize().x / 2.f, 0.f);
		background.setSize(sf::Vector2f(window.getSize().x / 4.f, window.getSize().y - 50.f));
		background.setFillColor(sf::Color(55, 55, 55, 100));
		text.setFont(font);
		text.setString("PAUSED");
		text.setCharacterSize(30);
		text.setFillColor(sf::Color(255, 255, 255, 200));
		text.setPosition(window.getSize().x / 2.f + 50.f, 100.f);
		buttons.push_back(std::make_shared<Button>(125.f, 40.f, (float)(window.getSize().x / 2 + 50), (float)(window.getSize().y / 2 + 50),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &font, "Save"));
		buttons.push_back(std::make_shared<Button>(125.f, 40.f, (float)(window.getSize().x / 2 + 50), (float)(window.getSize().y / 2 + 100),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &font, "Quit"));
	}

	PauseMenu::~PauseMenu()
	{
		buttons.clear();
	}

	bool PauseMenu::update(const sf::Vector2f mousePos, std::stack<std::shared_ptr<State>>* states)
	{
		for (auto& b : buttons)
		{
			b->update(mousePos);
		}
		//Save
		if (buttons[0]->isClicked())
		{
			//Tilemap save
			return true;
		}
		//Quit 
		else if (buttons[1]->isClicked())
		{
			states->pop();
		}
		return false;
	}

	void PauseMenu::render(std::shared_ptr<sf::RenderWindow> window)
	{
		window->draw(background);
		window->draw(text);
		for (auto& b : buttons)
		{
			b->render(window);
		}
	}


}