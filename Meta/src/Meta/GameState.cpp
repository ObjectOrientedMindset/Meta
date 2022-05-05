#include "pch.h"
#include "GameState.h"


namespace Meta {

	GameState::GameState(std::shared_ptr<Window> window, std::stack<std::shared_ptr<State>>* states, std::map<std::string, int>* supported_keys)
		:State(window, states, supported_keys), pauseMenu(*window->getWindow(), pixelFont)
	{
		tilemaps.push(std::make_shared<Tilemap>());
		filePathCount = 1;
		filePathCountMax = 5;
		initKeyBinds(supported_keys);
		timerMax = 1000.f;
		timer = timerMax;
		player = std::make_unique<Player>();
		pause = false;
	}
	void GameState::initKeyBinds(std::map<std::string, int>* supported_keys)
	{
		std::ifstream keys_file("Config/gamestate_keys.ini");
		std::string key = "";
		std::string key_digit = "";
		if (!keys_file.is_open()) { MT_CORE_ERROR("Config/gamestate_keys.ini missing!"); };
		while (keys_file >> key >> key_digit)
		{
			keybinds[key] = supported_keys->at(key_digit);
		}
		keys_file.close();
	}

	void GameState::changeMap()
	{
		if (player->getPlayerPosition().x > window->getWindow()->getSize().x)
		{
			if (filePathCount < filePathCountMax)
			{
				tilemaps.push(std::make_shared<Tilemap>(filePathway[filePathCount]));
				++filePathCount;
				player->setPlayerPosition(10.f, player->getPlayerPosition().y);
			}
		}
		if (player->getPlayerPosition().x < 0.f)
		{
			if (filePathCount > 1)
			{
				tilemaps.pop();
				--filePathCount;
				player->setPlayerPosition(window->getWindow()->getSize().x - 10.f, player->getPlayerPosition().y);
			}
		}
	}

	GameState::~GameState()
	{
		while (!tilemaps.empty()) {
			tilemaps.pop();
		}
	}

	void GameState::endState()
	{
		if (timer >= timerMax)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))))
			{
				if (!pause)
				{
					pause = true;
				}
				else
				{
					pause = false;
				}
				timer = 0.f;
			}
		}
		++timer;
	}

	void GameState::updatePlayerInput(const float& dt)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
		{
			player->playerMovement("Left", -1.f, 0.f, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
		{
			player->playerMovement("Right", 1.f, 0.f, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
		{
			player->playerMovement("Up", 0.f, -1.f, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
		{
			player->playerMovement("Down", 0.f, 1.f, dt);
		}

	}

	void GameState::update(const float& dt)
	{
		endState();
		if (!pause) // Unpaused update
		{
			updatePlayerInput(dt);
			player->update();
			changeMap();
		}
		else
		{
			pauseMenu.update(getMousePos(), states);
		}
	}

	void GameState::render()
	{
		tilemaps.top()->render(window->getWindow());
		player->render(window->getWindow());
		if (pause)
		{
			pauseMenu.render(window->getWindow());
		}

	}

}
