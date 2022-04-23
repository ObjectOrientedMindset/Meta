#include "pch.h"
#include "GameState.h"

namespace Meta {

	GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states, std::map<std::string, int>* supported_keys)
		:State(window, states, supported_keys), pauseMenu(*window, this->pixelFont)
	{
		this->tilemaps.push(new Tilemap());
		this->filePathCount = 1;
		this->filePathCountMax = 5;
		this->initKeyBinds(supported_keys);
		this->timerMax = 1000.f;
		this->timer = this->timerMax;
		this->player = new Player();
		this->pause = false;
	}
	void GameState::initKeyBinds(std::map<std::string, int>* supported_keys)
	{
		std::ifstream keys_file("Config/gamestate_keys.ini");
		std::string key = "";
		std::string key_digit = "";
		if (!keys_file.is_open()) { MT_CORE_ERROR("Config/gamestate_keys.ini missing!"); };
		while (keys_file >> key >> key_digit)
		{
			this->keybinds[key] = supported_keys->at(key_digit);
		}
		keys_file.close();
	}

	void GameState::changeMap()
	{
		if (this->player->getPlayerPosition().x > this->window->getSize().x)
		{
			if (this->filePathCount < this->filePathCountMax)
			{
				this->tilemaps.push(new Tilemap(this->filePathway[this->filePathCount]));
				++this->filePathCount;
				this->player->setPlayerPosition(10.f, this->player->getPlayerPosition().y);
			}
		}
		if (this->player->getPlayerPosition().x < 0.f)
		{
			if (this->filePathCount > 1)
			{
				this->tilemaps.pop();
				--this->filePathCount;
				this->player->setPlayerPosition(this->window->getSize().x - 10.f, this->player->getPlayerPosition().y);
			}
		}
	}

	GameState::~GameState()
	{
		delete this->player;
		while (!this->tilemaps.empty()) {
			delete this->tilemaps.top();
			this->tilemaps.pop();
		}
	}

	void GameState::endState(std::stack<State*>* states)
	{
		if (this->timer >= this->timerMax)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
			{
				if (!this->pause)
				{
					this->pause = true;
				}
				else
				{
					this->pause = false;
				}
				this->timer = 0.f;
			}
		}
		++this->timer;
	}

	void GameState::updatePlayerInput(const float& dt)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		{
			this->player->playerMovement("Left", -1.f, 0.f, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		{
			this->player->playerMovement("Right", 1.f, 0.f, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		{
			this->player->playerMovement("Up", 0.f, -1.f, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		{
			this->player->playerMovement("Down", 0.f, 1.f, dt);
		}

	}

	void GameState::update(const float& dt)
	{
		this->endState(this->states);
		if (!this->pause) // Unpaused update
		{
			this->updatePlayerInput(dt);
			this->player->update();
			this->changeMap();
		}
		else
		{
			this->pauseMenu.update(this->getMousePos(), this->states);
		}
	}

	void GameState::render(sf::RenderWindow* window)
	{
		this->tilemaps.top()->render(window);
		this->player->render(window);
		if (this->pause)
		{
			this->pauseMenu.render(window);
		}

	}

}
