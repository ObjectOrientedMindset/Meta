#include "mtpch.h"
#include "GameState.h"


namespace Meta {

	GameState::GameState(std::shared_ptr<Window> window, std::stack<std::shared_ptr<State>>* states)
		:State(window, states), pauseMenu(*window->getRenderWindow(), window->pixelFont)
	{
		tilemap = std::make_shared<Tilemap>();
		filePathCount = 1;
		filePathCountMax = 5;
		player = std::make_unique<Player>();
		pause = false;
	}


	GameState::~GameState()
	{
	}

	void GameState::endState()
	{

		if (static_cast<int>(window->currentEvent.input) == 27)
		{
			pause == false ? pause = true : pause = false;
		}
	}

	void GameState::updatePlayerInput(const float& dt)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			player->playerMovement("Left", -1.f, 0.f, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			player->playerMovement("Right", 1.f, 0.f, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			player->playerMovement("Up", 0.f, -1.f, dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			player->playerMovement("Down", 0.f, 1.f, dt);
		}

	}

	void GameState::update(const float& dt)
	{
		//unstable objects update(moving)
		if (!pause)
		{
			updatePlayerInput(dt);
			player->update();
		}
		//stable objects update
		if (window->currentEvent.changed)
		{
			endState();
			if (!pause) 
			{

			}
			else
			{
				pauseMenu.update(window->currentEvent.mousePosition, states);
			}
		}
	}

	void GameState::render()
	{
		tilemap->render(window->getRenderWindow());
		player->render(window->getRenderWindow());
		if (pause)
		{
			pauseMenu.render(window->getRenderWindow());
		}

	}

}
