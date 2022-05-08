#include "mtpch.h"
#include "MainMenu.h"
#include "GameState.h"
#include "EditorState.h"

namespace Meta {

	MainMenu::MainMenu(std::shared_ptr<Window> window, std::stack<std::shared_ptr<State>>* states)
		:State(window, states)
	{ //Create button objects
		initBackground();
		buttons.push_back(std::make_shared<Button>(125.f, 40.f, (float)(window->getRenderWindow()->getSize().x / 4), (float)(window->getRenderWindow()->getSize().y / 2),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &window->pixelFont, "New Game"));
		buttons.push_back(std::make_shared<Button>(125.f, 40.f, (float)(window->getRenderWindow()->getSize().x / 4), (float)(window->getRenderWindow()->getSize().y / 2 + 60),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &window->pixelFont, "Editor"));
		buttons.push_back(std::make_shared<Button>(125.f, 40.f, (float)(window->getRenderWindow()->getSize().x / 4), (float)(window->getRenderWindow()->getSize().y / 2 + 300),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &window->pixelFont, "Quit"));
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
			states->push(std::make_shared<GameState>(window, states));
		}
		else if (buttons[1]->isClicked())
		{
			states->push(std::make_shared<EditorState>(window, states));
		}
		else if (buttons[2]->isClicked())
		{
			window->getRenderWindow()->close();
		}
	}

	void MainMenu::update(const float& dt)
	{
		for (auto& b : buttons)
		{
			b->update(window->currentEvent.mousePosition);
		}
		endState();
	}

	void MainMenu::render()
	{
		//Background
		window->getRenderWindow()->draw(background);
		for (auto& b : buttons)
		{
			b->render(window->getRenderWindow());
		}

	}

}