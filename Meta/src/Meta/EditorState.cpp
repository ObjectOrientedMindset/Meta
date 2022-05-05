#include "pch.h"
#include "EditorState.h"



namespace Meta {

	EditorState::EditorState(std::shared_ptr<Window> window, std::stack<std::shared_ptr<State>>* states, std::map<std::string, int>* supported_keys)
		:State(window, states, supported_keys), pmenu(*window->getWindow(), pixelFont)
	{
		tilemaps.push(std::make_shared<Tilemap>());
		filePathCount = 1;
		filePathCountMax = 10;
		initKeyBinds(supported_keys);
		pause = false;
		timerMax = 1000.f;
		timer = 0.f;
		mouseCoordinatesText_x.setFont(pixelFont);
		mouseCoordinatesText_x.setCharacterSize(20);
		mouseCoordinatesText_y.setFont(pixelFont);
		mouseCoordinatesText_y.setCharacterSize(20);
		tileCollision.setPosition(getMousePos().x - 50.f, getMousePos().y - 50.f);
		tileCollision.setFillColor(sf::Color(0, 255, 0, 75));
		tileCollision.setSize(sf::Vector2f(tilemaps.top()->maxSize));
		tileCode = 1;
		text.setFont(pixelFont);
		text.setPosition(100.f, 100.f);
		text.setFillColor(sf::Color(100, 100, 255, 255));
		initEditMap();
	}


	void EditorState::initKeyBinds(std::map<std::string, int>* supported_keys)
	{
		std::ifstream keys_file("Config/gamestate_keys.ini");
		std::string key = "";
		std::string key_digit = "";
		if (!keys_file.is_open()) { MT_CORE_ERROR("Config/gamestate_keys.ini missing!"); }
		while (keys_file >> key >> key_digit)
		{
			keybinds[key] = supported_keys->at(key_digit);
		}
	}
	void EditorState::initEditMap()
	{   //Invisible map for editing the real tilemap
		for (int x = 0; x < (window->getWindow()->getSize().x / 100) + 1; x++)
		{
			editmap.push_back(std::vector<sf::RectangleShape>());
			for (int y = 0; y < (window->getWindow()->getSize().y / 100) + 1; y++)
			{
				editmap[x].push_back(sf::RectangleShape(sf::Vector2f(tilemaps.top()->maxSize)));
				editmap[x][y].setPosition(x * 100, y * 100);
			}
		}
	}
	void EditorState::addTile(const sf::Vector2f& tile)
	{
		tilemaps.top()->update(tile, tileCode, tileLayer);
	}
	void EditorState::deleteTile(const sf::Vector2f& tile)
	{
		tilemaps.top()->update(tile, tileCode, tileLayer);
	}
	bool EditorState::tileCollisionCheck(const int& tile_layer)
	{
		for (auto& t : tilemaps.top()->tiles[tile_layer])
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
		for (int x = 0; x < (window->getWindow()->getSize().x / 100) + 1; x++)
		{
			for (int y = 0; y < (window->getWindow()->getSize().y / 100) + 1; y++)
			{
				if (editmap[x][y].getGlobalBounds().contains(getMousePos()))
				{
					return editmap[x][y].getPosition();
				}
			}
		}

		return sf::Vector2f(0, 0);
	}
	void EditorState::updateMouseCoordinates()
	{
		mouseCoordinatesText_x.setPosition(getMousePos().x + 10.f, getMousePos().y - 20.f);
		mouseCoordinatesText_x.setString(std::to_string((int)(getMousePos().x)));
		mouseCoordinatesText_y.setPosition(getMousePos().x + 40.f, getMousePos().y - 20.f);
		mouseCoordinatesText_y.setString(std::to_string((int)(getMousePos().y)));
	}

	void EditorState::changetileCode()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			tileCode = 0;
			tileLayer = 1;
			text.setString("ADD MODE(GRASS)");
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			tileCode = 1;
			tileLayer = 1;
			text.setString("ADD MODE(GRASS&FLOWER)");
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			tileCode = 2;
			tileLayer = 1;
			text.setString("ADD MODE(STONEGROUND)");
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			tileCode = 3;
			tileLayer = 0;
			text.setString("ADD MODE(TREE)");
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) //delete tile mode
		{
			tileCode = 4;
			text.setString("DELETE MODE");
		}
	}

	void EditorState::changeMap()
	{   //check for max files and key press for map change
		if (timer >= timerMax)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				if (filePathCount < filePathCountMax)
				{
					tilemaps.push(std::make_shared<Tilemap>
						(filePathway[filePathCount]));
					++filePathCount;
					timer = 0.f;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				if (filePathCount > 1)
				{
					tilemaps.pop();
					--filePathCount;
					timer = 0.f;
				}
			}
		}
	}

	EditorState::~EditorState()
	{
		while (!tilemaps.empty()) {
			tilemaps.pop();
		}
	}

	void EditorState::endState()
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
	}

	void EditorState::update(const float& dt)
	{
		endState();
		if (!pause) // Unpaused update
		{
			// update coordinates and tileCollision
			changeMap();
			updateMouseCoordinates();
			tileCollision.setPosition(getMousePos().x - 50.f, getMousePos().y - 50.f);
			changetileCode();
			// check for mouse click and tile collision addtile
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (timer >= timerMax)
				{
					if (!tileCollisionCheck(tileLayer))
					{  //add tile
						addTile(getEditMapCollisionCheck());
						timer = 0.f;
					}
					else if (tileCode == 4)
					{ //delete tile
						deleteTile(getEditMapCollisionCheck());
						timer = 0.f;
					}
				}
			}
		}
		else
		{    // if pmenu return true savetilemap
			if (pmenu.update(getMousePos(), states))
			{
				tilemaps.top()->saveTileMap(filePathway[filePathCount - 1]);
			}
		}
		++timer;
	}

	void EditorState::render()
	{
		if (pause)
		{
			pmenu.render(window->getWindow());
		}
		else
		{
			tilemaps.top()->render(window->getWindow());
			window->getWindow()->draw(tileCollision);
			window->getWindow()->draw(mouseCoordinatesText_x);
			window->getWindow()->draw(mouseCoordinatesText_y);
			window->getWindow()->draw(text);
		}
	}

}