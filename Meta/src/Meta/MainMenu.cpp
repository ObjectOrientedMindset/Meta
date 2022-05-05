#include "pch.h"
#include "MainMenu.h"
#include "GameState.h"
#include "SettingState.h"
#include "EditorState.h"

namespace Meta {

	MainMenu::MainMenu(std::shared_ptr<Window> window, std::stack<std::shared_ptr<State>>* states, std::map<std::string, int>* supported_keys)
		:State(window, states, supported_keys)
	{ //Create button objects
		initBackground();
		buttons.push_back(std::make_shared<Button>(125.f, 40.f, (float)(window->getWindow()->getSize().x / 4), (float)(window->getWindow()->getSize().y / 2),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &pixelFont, "New Game"));
		buttons.push_back(std::make_shared<Button>(125.f, 40.f, (float)(window->getWindow()->getSize().x / 4), (float)(window->getWindow()->getSize().y / 2 + 50),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &pixelFont, "Settings"));
		buttons.push_back(std::make_shared<Button>(125.f, 40.f, (float)(window->getWindow()->getSize().x / 4), (float)(window->getWindow()->getSize().y / 2 + 100),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &pixelFont, "Editor"));
		buttons.push_back(std::make_shared<Button>(125.f, 40.f, (float)(window->getWindow()->getSize().x / 4), (float)(window->getWindow()->getSize().y / 2 + 300),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &pixelFont, "Quit"));
	}

	MainMenu::~MainMenu()
	{
		buttons.clear();
	}

	void MainMenu::initBackground()
	{
		if (!texture.loadFromFile("Images/Background.jpg")) { MT_CORE_ERROR("Images/Background.jpg missing!"); }

		background.setTexture(texture);
	}

	void MainMenu::endState()
	{   //Check for button click if new Game clicked push gamestate if quit clicked end game
		if (buttons[0]->isClicked())
		{
			states->push(std::make_shared<GameState>(window, states, supported_keys));
		}
		else if (buttons[1]->isClicked())
		{
			states->push(std::make_shared<SettingState>(window, states));
		}
		else if (buttons[2]->isClicked())
		{
			states->push(std::make_shared<EditorState>(window, states, supported_keys));
		}
		else if (buttons[3]->isClicked())
		{
			window->getWindow()->close();
		}
	}

	void MainMenu::update(const float& dt)
	{
		for (auto& b : buttons)
		{
			b->update(getMousePos());
		}
		endState();
	}

	void MainMenu::render()
	{
		//Background
		window->getWindow()->draw(background);
		for (auto& b : buttons)
		{
			b->render(window->getWindow());
		}

	}

}