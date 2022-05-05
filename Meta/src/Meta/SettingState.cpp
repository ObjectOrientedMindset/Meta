#include "pch.h"
#include "SettingState.h"


namespace Meta {

	SettingState::SettingState(std::shared_ptr<Window> window, std::stack<std::shared_ptr<State>>* states)
		:State(window, states, supported_keys)
	{
		initBackground();
		buttons.push_back(std::make_shared<Button>(125.f, 40.f, (float)(window->getWindow()->getSize().x / 4), (float)(window->getWindow()->getSize().y / 2),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &pixelFont, "Screen Resolution"));
		buttons.push_back(std::make_shared<Button>(125.f, 40.f, (float)(window->getWindow()->getSize().x / 4), (float)(window->getWindow()->getSize().y / 2 + 50),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &pixelFont, "Sound"));
		buttons.push_back(std::make_shared<Button>(125.f, 40.f, (float)(window->getWindow()->getSize().x / 4), (float)(window->getWindow()->getSize().y / 2 + 100),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &pixelFont, "Back"));
	}

	SettingState::~SettingState()
	{
		buttons.clear();
	}

	void SettingState::initBackground()
	{
		if (!texture.loadFromFile("Images/Background.jpg")) { MT_CORE_ERROR("Images/Background.jpg missing!"); }

		background.setTexture(texture);
	}

	void SettingState::endState()
	{
		if (buttons[2]->isClicked())
		{
			states->pop();
		}
	}

	void SettingState::update(const float& dt)
	{
		for (auto& b : buttons)
		{
			b->update(getMousePos());
		}
		endState();
	}

	void SettingState::render()
	{
		window->getWindow()->draw(background);
		for (auto& b : buttons)
		{
			b->render(window->getWindow());
		}
	}


}
