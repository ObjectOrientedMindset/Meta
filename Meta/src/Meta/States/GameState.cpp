#include "mtpch.h"
#include "GameState.h"


namespace Meta {
	
	GameState::GameState(std::shared_ptr<Window> window, std::stack<std::shared_ptr<State>>* states)
		:State(window, states), pauseMenu(*window->renderWindow, window->pixelFont), gui()
	{
		tilemap = std::make_shared<Tilemap>(window);
		player = tilemap->getPlayerInstance();
		filePathCount = 1;
		filePathCountMax = 5;
		pause = false;
	}
	void GameState::camera()
	{
		if (player->data.position.x < posX)
		{
			window->moveView(-0.136f, 0.f);
			
		}
		else if (player->data.position.x > posX)
		{
			window->moveView(0.136f, 0.f);
			
		}

		if (player->data.position.y < posY)
		{
			window->moveView(0.f, -0.136f);
		
		}
		else if (player->data.position.y > posY)
		{
			window->moveView(0.f, 0.136f);
			
		}	

		posX = player->data.position.x;
		posY = player->data.position.y;
		
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

	bool GameState::updatePlayer(const float& dt)
	{
		bool moved = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			player->update("Left", -1.f, 0.f, dt);
			moved = true;			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			player->update("Right", 1.f, 0.f, dt);
			moved = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			player->update("Up", 0.f, -1.f, dt);
			moved = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			player->update("Down", 0.f, 1.f, dt);
			moved = true;
		}
		return moved;
	}

	void GameState::update(const float& dt)
	{
		//unstable objects update(moving)
		if (!pause)
		{
			if (updatePlayer(dt)) 
			{
				camera();
			}
		}
		//stable objects update
		if (window->currentEvent.changed)
		{
			endState();
		}
		if (pause)
		{
			gui.pauseMenu(window, tilemap, states);
		}
		
	}

	void GameState::render()
	{
		tilemap->render();		
	}

}
