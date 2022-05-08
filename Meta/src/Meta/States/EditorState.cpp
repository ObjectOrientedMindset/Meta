#include "mtpch.h"
#include "EditorState.h"
#include "Meta/GUI/Gui.h"


namespace Meta {


	EditorState::EditorState(std::shared_ptr<Window> window, std::stack<std::shared_ptr<State>>* states)
		:State(window, states), pmenu(*window->getRenderWindow(), window->pixelFont), gui()
	{
		tilemap = std::make_shared<Tilemap>();
		pause = false;
		mouseCoordinatesText_x.setFont(window->pixelFont);
		mouseCoordinatesText_x.setCharacterSize(20);
		mouseCoordinatesText_y.setFont(window->pixelFont);
		mouseCoordinatesText_y.setCharacterSize(20);
		tileCollision.setPosition(window->currentEvent.mousePosition.x - 50.f, window->currentEvent.mousePosition.y - 50.f);
		tileCollision.setFillColor(sf::Color(0, 255, 0, 75));
		tileCollision.setSize(sf::Vector2f(tilemap->maxSize));
		tileCode = 1;
		text.setFont(window->pixelFont);
		text.setPosition(100.f, 100.f);
		text.setFillColor(sf::Color(100, 100, 255, 255));
		initEditMap();
	}


	void EditorState::initEditMap()
	{   //Invisible map for editing the real tilemap
		for (int x = 0; x < (window->getRenderWindow()->getSize().x / 100) + 1; x++)
		{
			editmap.push_back(std::vector<sf::RectangleShape>());
			for (int y = 0; y < (window->getRenderWindow()->getSize().y / 100) + 1; y++)
			{
				editmap[x].push_back(sf::RectangleShape(sf::Vector2f(tilemap->maxSize)));
				editmap[x][y].setPosition(x * 100, y * 100);
			}
		}
	}
	void EditorState::addTile(const sf::Vector2f& tile)
	{
		tilemap->update(tile, tileCode, tileLayer);
	}
	void EditorState::deleteTile(const sf::Vector2f& tile)
	{
		tilemap->update(tile, tileCode, tileLayer);
	}
	bool EditorState::tileCollisionCheck(const int& tile_layer)
	{
		for (auto& t : tilemap->tiles[tile_layer])
		{    // Check if editmap rectangle position and tile position 
			if (getEditMapCollisionCheck() == t->getTilePosition())
			{
				return true;
			}
		}
		return false;
	}
	const sf::Vector2f& EditorState::getEditMapCollisionCheck()
	{ // checking which one of the invisible tiles and return its Vector2f
		for (int x = 0; x < (window->getRenderWindow()->getSize().x / 100) + 1; x++)
		{
			for (int y = 0; y < (window->getRenderWindow()->getSize().y / 100) + 1; y++)
			{
				if (editmap[x][y].getGlobalBounds().contains(window->currentEvent.mousePosition))
				{
					return editmap[x][y].getPosition();
				}
			}
		}

		return sf::Vector2f(0, 0);
	}
	void EditorState::updateMouseCoordinates()
	{
		mouseCoordinatesText_x.setPosition(window->currentEvent.mousePosition.x + 10.f, window->currentEvent.mousePosition.y - 20.f);
		mouseCoordinatesText_x.setString(std::to_string((int)(window->currentEvent.mousePosition.x)));
		mouseCoordinatesText_y.setPosition(window->currentEvent.mousePosition.x + 40.f, window->currentEvent.mousePosition.y - 20.f);
		mouseCoordinatesText_y.setString(std::to_string((int)(window->currentEvent.mousePosition.y)));
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
		if (window->currentEvent.changed)
		{	
			if (!pause) // Unpaused update
			{
				// update coordinates and tileCollision
				updateMouseCoordinates();
				tileCollision.setPosition(window->currentEvent.mousePosition.x - 50.f, window->currentEvent.mousePosition.y - 50.f);
				changetileCode();
				// check for mouse click and tile collision addtile
				if (window->currentEvent.mouseClicked)
				{
					if (!tileCollisionCheck(tileLayer))
					{  //add tile
						addTile(getEditMapCollisionCheck());

					}
					else if (tileCode == 4)
					{ //delete tile
						deleteTile(getEditMapCollisionCheck());

					}
				}
			}
		}
		pause == false ? gui.editorState() : gui.pauseMenu(window, tilemap, states);
	}

	void EditorState::render()
	{
		if (!pause)
		{
			tilemap->render(window->getRenderWindow());
			window->getRenderWindow()->draw(tileCollision);
			window->getRenderWindow()->draw(mouseCoordinatesText_x);
			window->getRenderWindow()->draw(mouseCoordinatesText_y);
			window->getRenderWindow()->draw(text);
		}

	}



}