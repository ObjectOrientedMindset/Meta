#include "pch.h"
#include "PauseMenu.h"


namespace Meta {

	PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	{
		this->background.setPosition(window.getSize().x / 2.f, 0.f);
		this->background.setSize(sf::Vector2f(window.getSize().x / 4.f, window.getSize().y - 50.f));
		this->background.setFillColor(sf::Color(55, 55, 55, 100));
		this->text.setFont(font);
		this->text.setString("PAUSED");
		this->text.setCharacterSize(30);
		this->text.setFillColor(sf::Color(255, 255, 255, 200));
		this->text.setPosition(window.getSize().x / 2.f + 50.f, 100.f);
		this->button.push_back(new Button(125.f, 40.f, (float)(window.getSize().x / 2 + 50), (float)(window.getSize().y / 2 + 50),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &font, "Save"));
		this->button.push_back(new Button(125.f, 40.f, (float)(window.getSize().x / 2 + 50), (float)(window.getSize().y / 2 + 100),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &font, "Quit"));
	}

	PauseMenu::~PauseMenu()
	{
		unsigned int iterationCounter = 0;
		for (auto& b : this->button)
		{
			delete this->button.at(iterationCounter);
			this->button.erase(this->button.begin() + iterationCounter);
			--iterationCounter;
		}
		++iterationCounter;
	}

	bool PauseMenu::update(const sf::Vector2f mousePos, std::stack<State*>* states)
	{
		for (auto& b : this->button)
		{
			b->update(mousePos);
		}
		//Save
		if (this->button[0]->isClicked())
		{
			//Tilemap save
			return true;
		}
		//Quit 
		else if (this->button[1]->isClicked())
		{
			states->pop();
		}
		return false;
	}

	void PauseMenu::render(sf::RenderWindow* window)
	{
		window->draw(this->background);
		window->draw(this->text);
		for (auto& b : this->button)
		{
			b->render(window);
		}
	}


}