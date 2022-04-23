#include "pch.h"
#include "EditorState.h"


namespace Meta {

	EditorState::EditorState(sf::RenderWindow* window, std::stack<State*>* states, std::map<std::string, int>* supported_keys)
		:State(window, states, supported_keys), pmenu(*window, this->pixelFont)
	{
		this->tilemaps.push(new Tilemap());
		this->filePathCount = 1;
		this->filePathCountMax = 10;
		this->initKeyBinds(supported_keys);
		this->pause = false;
		this->timerMax = 1000.f;
		this->timer = 0.f;
		this->mouseCoordinatesText_x.setFont(this->pixelFont);
		this->mouseCoordinatesText_x.setCharacterSize(20);
		this->mouseCoordinatesText_y.setFont(this->pixelFont);
		this->mouseCoordinatesText_y.setCharacterSize(20);
		this->tileCollision.setPosition(this->getMousePos().x - 50.f, this->getMousePos().y - 50.f);
		this->tileCollision.setFillColor(sf::Color(0, 255, 0, 75));
		this->tileCollision.setSize(sf::Vector2f(this->tilemaps.top()->maxSize));
		this->tileCode = 1;
		this->text.setFont(this->pixelFont);
		this->text.setPosition(100.f, 100.f);
		this->text.setFillColor(sf::Color(100, 100, 255, 255));
		this->initEditMap();
	}


	void EditorState::initKeyBinds(std::map<std::string, int>* supported_keys)
	{
		std::ifstream keys_file("Config/gamestate_keys.ini");
		std::string key = "";
		std::string key_digit = "";
		if (!keys_file.is_open()) { MT_CORE_ERROR("Config/gamestate_keys.ini missing!"); }
		while (keys_file >> key >> key_digit)
		{
			this->keybinds[key] = supported_keys->at(key_digit);
		}
	}
	void EditorState::initEditMap()
	{   //Invisible map for editing the real tilemap
		for (int x = 0; x < (this->window->getSize().x / 100) + 1; x++)
		{
			this->editmap.push_back(std::vector<sf::RectangleShape>());
			for (int y = 0; y < (this->window->getSize().y / 100) + 1; y++)
			{
				this->editmap[x].push_back(sf::RectangleShape(sf::Vector2f(this->tilemaps.top()->maxSize)));
				this->editmap[x][y].setPosition(x * 100, y * 100);
			}
		}
	}
	void EditorState::addTile(const sf::Vector2f& tile)
	{
		this->tilemaps.top()->update(tile, this->tileCode, this->tileLayer);
	}
	void EditorState::deleteTile(const sf::Vector2f& tile)
	{
		this->tilemaps.top()->update(tile, this->tileCode, this->tileLayer);
	}
	bool EditorState::tileCollisionCheck(const int& tile_layer)
	{
		for (auto& t : this->tilemaps.top()->tile[tile_layer])
		{    // Check if editmap rectangle position and tile position 
			if (this->getEditMapCollisionCheck() == t->getTilePosition())
			{
				return true;
			}
		}
		return false;
	}
	const sf::Vector2f& EditorState::getEditMapCollisionCheck()
	{ // checking which one of the invisible tiles and return its Vector2f
		for (int x = 0; x < (this->window->getSize().x / 100) + 1; x++)
		{
			for (int y = 0; y < (this->window->getSize().y / 100) + 1; y++)
			{
				if (this->editmap[x][y].getGlobalBounds().contains(this->getMousePos()))
				{
					return this->editmap[x][y].getPosition();
				}
			}
		}

		return sf::Vector2f(0, 0);
	}
	void EditorState::updateMouseCoordinates()
	{
		this->mouseCoordinatesText_x.setPosition(this->getMousePos().x + 10.f, this->getMousePos().y - 20.f);
		this->mouseCoordinatesText_x.setString(std::to_string((int)(this->getMousePos().x)));
		this->mouseCoordinatesText_y.setPosition(this->getMousePos().x + 40.f, this->getMousePos().y - 20.f);
		this->mouseCoordinatesText_y.setString(std::to_string((int)(this->getMousePos().y)));
	}

	void EditorState::changetileCode()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			this->tileCode = 0;
			this->tileLayer = 1;
			this->text.setString("ADD MODE(GRASS)");
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			this->tileCode = 1;
			this->tileLayer = 1;
			this->text.setString("ADD MODE(GRASS&FLOWER)");
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			this->tileCode = 2;
			this->tileLayer = 1;
			this->text.setString("ADD MODE(STONEGROUND)");
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			this->tileCode = 3;
			this->tileLayer = 0;
			this->text.setString("ADD MODE(TREE)");
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) //delete tile mode
		{
			this->tileCode = 4;
			this->text.setString("DELETE MODE");
		}
	}

	void EditorState::changeMap()
	{   //check for max files and key press for map change
		if (this->timer >= this->timerMax)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				if (this->filePathCount < this->filePathCountMax)
				{
					this->tilemaps.push(new Tilemap(this->filePathway[this->filePathCount]));
					++this->filePathCount;
					this->timer = 0.f;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				if (this->filePathCount > 1)
				{
					this->tilemaps.pop();
					--this->filePathCount;
					this->timer = 0.f;
				}
			}
		}
	}

	EditorState::~EditorState()
	{
		while (!this->tilemaps.empty()) {
			delete this->tilemaps.top();
			this->tilemaps.pop();
		}
	}

	void EditorState::endState(std::stack<State*>* states)
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
	}

	void EditorState::update(const float& dt)
	{
		this->endState(this->states);
		if (!this->pause) // Unpaused update
		{
			// update coordinates and tileCollision
			this->changeMap();
			this->updateMouseCoordinates();
			this->tileCollision.setPosition(this->getMousePos().x - 50.f, this->getMousePos().y - 50.f);
			this->changetileCode();
			// check for mouse click and tile collision addtile
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (this->timer >= this->timerMax)
				{
					if (!this->tileCollisionCheck(this->tileLayer))
					{  //add tile
						this->addTile(this->getEditMapCollisionCheck());
						this->timer = 0.f;
					}
					else if (this->tileCode == 4)
					{ //delete tile
						this->deleteTile(this->getEditMapCollisionCheck());
						this->timer = 0.f;
					}
				}
			}
		}
		else
		{    // if pmenu return true savetilemap
			if (this->pmenu.update(this->getMousePos(), this->states))
			{
				this->tilemaps.top()->saveTileMap(this->filePathway[this->filePathCount - 1]);
			}
		}
		++this->timer;
	}

	void EditorState::render(sf::RenderWindow* window)
	{
		if (this->pause)
		{
			this->pmenu.render(window);
		}
		else
		{
			this->tilemaps.top()->render(window);
			window->draw(this->tileCollision);
			window->draw(this->mouseCoordinatesText_x);
			window->draw(this->mouseCoordinatesText_y);
			window->draw(this->text);
		}
	}

}