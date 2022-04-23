#include "pch.h"
#include "MainMenu.h"

namespace Meta {

	MainMenu::MainMenu(sf::RenderWindow* window, std::stack<State*>* states, std::map<std::string, int>* supported_keys)
		:State(window, states, supported_keys)
	{ //Create button objects
		this->initBackground();
		this->button.push_back(new Button(125.f, 40.f, (float)(this->window->getSize().x / 4), (float)(this->window->getSize().y / 2),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &this->pixelFont, "New Game"));
		this->button.push_back(new Button(125.f, 40.f, (float)(this->window->getSize().x / 4), (float)(this->window->getSize().y / 2 + 50),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &this->pixelFont, "Settings"));
		this->button.push_back(new Button(125.f, 40.f, (float)(this->window->getSize().x / 4), (float)(this->window->getSize().y / 2 + 100),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &this->pixelFont, "Editor"));
		this->button.push_back(new Button(125.f, 40.f, (float)(this->window->getSize().x / 4), (float)(this->window->getSize().y / 2 + 300),
			sf::Color(150, 150, 150, 255), sf::Color(70, 70, 70, 200), sf::Color(20, 20, 20, 200), &this->pixelFont, "Quit"));
	}

	MainMenu::~MainMenu()
	{
		unsigned iteratorCount = 0;
		for (auto& b : this->button)
		{
			delete this->button.at(iteratorCount);
			this->button.erase(this->button.begin() + iteratorCount);
			--iteratorCount;
		}
		++iteratorCount;
	}

	void MainMenu::initBackground()
	{
		if (!this->texture.loadFromFile("Images/Background.jpg")) { MT_CORE_ERROR("Images/Background.jpg missing!"); }

		this->background.setTexture(this->texture);
	}

	void MainMenu::endState(std::stack<State*>* states)
	{   //Check for button click if new Game clicked push gamestate if quit clicked end game
		if (this->button[0]->isClicked())
		{
			this->states->push(new GameState(this->window, this->states, this->supported_keys));
		}
		else if (this->button[1]->isClicked())
		{
			this->states->push(new SettingState(this->window, this->states));
		}
		else if (this->button[2]->isClicked())
		{
			this->states->push(new EditorState(this->window, this->states, this->supported_keys));
		}
		else if (this->button[3]->isClicked())
		{
			this->window->close();
		}
	}

	void MainMenu::update(const float& dt)
	{
		for (auto& b : this->button)
		{
			b->update(this->getMousePos());
		}
		this->endState(this->states);
	}

	void MainMenu::render(sf::RenderWindow* window)
	{
		if (!window)
			window = this->window;
		//Background
		window->draw(this->background);
		for (auto& b : this->button)
		{
			b->render(this->window);
		}

	}

}