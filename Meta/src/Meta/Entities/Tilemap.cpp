#include "mtpch.h"
#include "Tilemap.h"

namespace Meta {

	void Tilemap::initTilemap(const std::string& filePathway, std::shared_ptr<Window> window)
	{ //Load Tilemap from file
		filePath = filePathway;
		maxSize.x = 100;
		maxSize.y = 100;
		sf::Vector2f tilePosition; tilePosition.x = 0; tilePosition.y = 0;
		std::string id;
		int color = 0;
		int layer = 0;
		std::fstream file_tilemap;
		file_tilemap.open(filePathway, std::ios::in);
		if (!file_tilemap.is_open()) { MT_CORE_ERROR("{} missing!", filePathway); }
		while (file_tilemap >> id >> tilePosition.x >> tilePosition.y >> color >> layer)
		{
			if (id == "Tile")
			{
				addTile(id, tilePosition, color, layer, window);
			}
			else if (id == "Character")
			{
				addCharacter(id, tilePosition, color, layer, window);
			}
		}

		file_tilemap.close();
	}

	Tilemap::Tilemap(std::shared_ptr<Window> window)
	{
		initTilemap("Config/maps/map0.ini", window);
	}

	Tilemap::Tilemap(const std::string& filePathway, std::shared_ptr<Window> window)
	{
		initTilemap(filePathway, window);
	}

	Tilemap::~Tilemap()
	{
		entities.clear();
	}


	void Tilemap::saveTileMap()
	{ //Save Tilemap to file
		std::fstream file_tilemap;
		file_tilemap.open(filePath, std::ios::out);
		if (!file_tilemap.is_open()) { MT_CORE_ERROR("{} missing!", filePath); }
		for (size_t i = 0; i < entities[0].size(); i++)
		{
			file_tilemap << entities[0][i]->data.id << std::endl << (int)(entities[0][i]->data.position.x) << std::endl << (int)(entities[0][i]->data.position.y)
				<< std::endl << entities[0][i]->data.code << std::endl << entities[0][i]->data.layer << std::endl;
		}
		for (size_t i = 0; i < entities[1].size(); i++)
		{
			file_tilemap << entities[1][i]->data.id << std::endl << (int)(entities[1][i]->data.position.x) << std::endl << (int)(entities[1][i]->data.position.y)
				<< std::endl << entities[1][i]->data.code << std::endl << entities[1][i]->data.layer << std::endl;
		}
		file_tilemap.close();
	}

	void Tilemap::addTile(const std::string& id, const sf::Vector2f& position,
		const int& code, const int& layer, std::shared_ptr<Window> window)
	{
		entities[layer].push_back(std::make_shared<Tile>(id, position,
			(sf::Vector2f)(maxSize), code, layer, window));
	}

	void Tilemap::addCharacter(const std::string& id, const sf::Vector2f& position,
		const int& code, const int& layer, std::shared_ptr<Window> window)
	{
		entities[layer].push_back(std::make_shared<Player>(id, position, code, layer, window));
	}

	void Tilemap::deleteEntity(const sf::Vector2f& position)
	{
		bool erased = false;
		for (auto t = entities[1].begin();
			t != entities[1].end();)
		{
			if ((*t)->data.position == position)
			{
				t = entities[1].erase(t);
				erased = true;
			}
			else
			{
				++t;
			}
		}
		for (auto t = entities[0].begin();
			t != entities[0].end();)
		{
			if ((*t)->data.position == position && erased == false)
			{
				t = entities[0].erase(t);
				erased = true;
			}
			else
			{
				++t;
			}
		}
	}

	Entity* Tilemap::getPlayerInstance()
	{
		for (auto& t : entities[0])
		{
			if (t->data.id == "Character")
			{
				return t->getInstance();
			}
		}
		for (auto& t : entities[1])
		{
			if (t->data.id == "Character")
			{
				return t->getInstance();
			}
		}
		MT_CORE_ERROR("Player Object Dont Exist!");
		return nullptr;
	}

	void Tilemap::update()
	{   
		
	}


	void Tilemap::render()
	{
		//Render for layer order
		for (auto& t : entities[0])
		{
			t->render();
		}
		for (auto& t : entities[1])
		{
			t->render();
		}
	}

}
