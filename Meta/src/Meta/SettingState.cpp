#include "pch.h"
#include "SettingState.h"

namespace Meta {

	SettingState::SettingState(sf::RenderWindow* window, std::stack<State*>* states)
		:State(window, states, this->supported_keys)
	{
		this->initBackground();
		this->button.push_back(new Button(125.f, 40.f, (float)(this->window->getSize().x / 4), (float)(this->window->getSize().y / 2),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &this->pixelFont, "Screen Resolution"));
		this->button.push_back(new Button(125.f, 40.f, (float)(this->window->getSize().x / 4), (float)(this->window->getSize().y / 2 + 50),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &this->pixelFont, "Sound"));
		this->button.push_back(new Button(125.f, 40.f, (float)(this->window->getSize().x / 4), (float)(this->window->getSize().y / 2 + 100),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &this->pixelFont, "Back"));
	}

	SettingState::~SettingState()
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

	void SettingState::initBackground()
	{
		if (!this->texture.loadFromFile("Images/Background.jpg")) { MT_CORE_ERROR("Images/Background.jpg missing!"); }

		this->background.setTexture(this->texture);
	}

	void SettingState::endState(std::stack<State*>* states)
	{
		if (this->button[2]->isClicked())
		{
			states->pop();
		}
	}

	void SettingState::update(const float& dt)
	{
		for (auto& b : this->button)
		{
			b->update(this->getMousePos());
		}
		this->endState(this->states);
	}

	void SettingState::render(sf::RenderWindow* window)
	{
		window->draw(this->background);
		for (auto& b : this->button)
		{
			b->render(window);
		}
	}


}
