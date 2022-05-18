#include "mtpch.h"
#include "EditorState.h"
#include "Meta/GUI/Gui.h"


namespace Meta {


	EditorState::EditorState(std::shared_ptr<Window> window, std::stack<std::shared_ptr<State>>* states)
		:State(window, states), pmenu(*window->renderWindow, window->pixelFont), gui()
	{
		tilemap = std::make_shared<Tilemap>();
		mouseCoordinatesText_x.setFont(window->pixelFont);
		mouseCoordinatesText_x.setCharacterSize(20);
		mouseCoordinatesText_y.setFont(window->pixelFont);
		mouseCoordinatesText_y.setCharacterSize(20);
		tileCollision.setPosition(window->currentEvent.mousePosition.x - 50.f, window->currentEvent.mousePosition.y - 50.f);
		tileCollision.setFillColor(sf::Color(0, 255, 0, 75));
		tileCollision.setSize(sf::Vector2f(tilemap->maxSize));
		text.setFont(window->pixelFont);
		text.setPosition(100.f, 100.f);
		text.setFillColor(sf::Color(100, 100, 255, 255));
		initEditMap();
		mouseX = window->currentEvent.mousePosition.x;
		mouseY = window->currentEvent.mousePosition.y;
		cursorHand.loadFromSystem(sf::Cursor::Hand);
		cursorArrow.loadFromSystem(sf::Cursor::Arrow);
	}


	void EditorState::initEditMap()
	{
		unsigned int iteratorX = 0;
		unsigned int iteratorY = 0;
		//Invisible map for editing the real tilemap
		for (int x = static_cast<int>(window->renderWindow->getSize().y) / -10;
			x < static_cast<int>(window->renderWindow->getSize().x) / 10; x++)
		{
			editmap.push_back(std::vector<sf::RectangleShape>());
			for (int y = static_cast<int>(window->renderWindow->getSize().y) / -10;
				y < static_cast<int>(window->renderWindow->getSize().y) / 10; y++)
			{
				editmap[iteratorX].push_back(sf::RectangleShape(sf::Vector2f(tilemap->maxSize)));
				editmap[iteratorX][iteratorY].setPosition(x * 100, y * 100);
				++iteratorY;
			}
			iteratorY = 0;
			++iteratorX;
		}
	}
	void EditorState::addTile(sf::Vector2f tile)
	{
		tilemap->update(tile, tileCode, tileLayer);
	}
	void EditorState::deleteTile(sf::Vector2f tile)
	{
		tilemap->update(tile, tileCode, tileLayer);
	}
	void EditorState::tileCollisionCheck()
	{ //Add and Delete Tiles 
		bool existingTile = false;

		if (tileCode == 4)
		{
			for (auto& t : tilemap->tiles[0])
			{
				if (tilePosition == t->getTilePosition())
				{
					existingTile = true;
				}
			}
			for (auto& t : tilemap->tiles[1])
			{
				if (tilePosition == t->getTilePosition())
				{
					existingTile = true;
				}
			} // if there is a tile delete
			if (existingTile)
			{
				deleteTile(tilePosition);
			}
		}
		else if (tileCode < 4)
		{
			for (auto& t : tilemap->tiles[tileLayer])
			{
				if (tilePosition == t->getTilePosition())
				{
					existingTile = true;
				}
			}   // if there isnt any tile add
			if (!existingTile)
			{
				addTile(tilePosition);
			}
		}
	}
	bool EditorState::editMapCollisionCheck()
	{
		unsigned int iteratorX = 0;
		unsigned int iteratorY = 0;
		// check for any of the edit map tiles contain application mouse position
		for (int x = static_cast<int>(window->renderWindow->getSize().y) / -10;
			x < static_cast<int>(window->renderWindow->getSize().x) / 10; x++)
		{
			for (int y = static_cast<int>(window->renderWindow->getSize().y) / -10;
				y < static_cast<int>(window->renderWindow->getSize().y) / 10; y++)
			{
				if (editmap[iteratorX][iteratorY].getGlobalBounds().contains(window->getAppMousePosition()))
				{
					tilePosition = editmap[iteratorX][iteratorY].getPosition();
					return true;
				}
				++iteratorY;
			}
			iteratorY = 0;
			++iteratorX;
		}

		MT_CORE_ERROR("Edit Map Collision Failed! \nConsider Increasing the Edit Map Size");

		return false;
	}
	void EditorState::updateMouseCoordinates()
	{
		mouseCoordinatesText_x.setPosition(window->getAppMousePosition().x + 10.f, window->getAppMousePosition().y - 20.f);
		mouseCoordinatesText_x.setString(std::to_string(static_cast<int>(window->getAppMousePosition().x)));
		mouseCoordinatesText_y.setPosition(window->getAppMousePosition().x + 40.f, window->getAppMousePosition().y - 20.f);
		mouseCoordinatesText_y.setString(std::to_string(static_cast<int>(window->getAppMousePosition().y)));
	}

	void EditorState::changetileCode()
	{
		switch (window->currentEvent.input)
		{
		case '1':
			tileCode = 0;
			tileLayer = 1;
			text.setString("ADD MODE(GRASS)");
			break;
		case '2':
			tileCode = 1;
			tileLayer = 1;
			text.setString("ADD MODE(GRASS&FLOWER)");
			break;
		case '3':
			tileCode = 2;
			tileLayer = 1;
			text.setString("ADD MODE(STONEGROUND)");
			break;
		case '4':
			tileCode = 3;
			tileLayer = 0;
			text.setString("ADD MODE(TREE)");
			break;
		case '5':
			tileCode = 4;
			text.setString("DELETE MODE");
			break;
		}
	}

	void EditorState::camera()
	{ // check if mouse position changed if so move the view
		if (window->currentEvent.mousePosition.x < mouseX)
		{
			window->moveView(2.5f, 0.f);
		}
		else if (window->currentEvent.mousePosition.x > mouseX)
		{
			window->moveView(-2.5f, 0.f);
		}

		if (window->currentEvent.mousePosition.y < mouseY)
		{
			window->moveView(0.f, 2.5f);
		}
		else if (window->currentEvent.mousePosition.y > mouseY)
		{
			window->moveView(0.f, -2.5f);
		}

		mouseX = window->currentEvent.mousePosition.x;
		mouseY = window->currentEvent.mousePosition.y;
	}

	EditorState::~EditorState()
	{
	}

	void EditorState::endState()
	{
		//Check For Esc Input 
		if (static_cast<int>(window->currentEvent.input) == 27)
		{
			pause == false ? pause = true : pause = false;
		}
	}

	void EditorState::update(const float& dt)
	{
		endState();
		if (!pause) // Unpaused update
		{
			//Camera move
			sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle) == true ?
				window->renderWindow->setMouseCursor(cursorHand), camera() :
				window->renderWindow->setMouseCursor(cursorArrow);

			if (window->currentEvent.changed)
			{
				// update coordinates and tileCollision
				updateMouseCoordinates();
				tileCollision.setPosition(window->getAppMousePosition().x - 50.f, window->getAppMousePosition().y - 50.f);
				changetileCode();

				// check for mouse click and tile collision addtile
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (timer >= timerMax)
					{
						if (editMapCollisionCheck())
						{
							tileCollisionCheck();
						}
						timer = 0;
					}
				}
			}

		}
		// Pause EditorState
		pause == false ? gui.editorState() :
			gui.pauseMenu(window, tilemap, states);


		++timer;
	}

	void EditorState::render()
	{
		if (!pause)
		{
			tilemap->render(window->renderWindow);
			window->renderWindow->draw(tileCollision);
			window->renderWindow->draw(mouseCoordinatesText_x);
			window->renderWindow->draw(mouseCoordinatesText_y);
			window->renderWindow->draw(text);
		}

	}



}