#include "pch.h"
#include "Tilemap.h"

namespace Meta {

	void Tilemap::initTilemap(const std::string& filePathway)
	{ //Load Tilemap from file
		maxSize.x = 100;
		maxSize.y = 100;
		sf::Vector2f tilePosition; tilePosition.x = 0; tilePosition.y = 0;
		int color = 0;
		int layer = 0;
		std::fstream file_tilemap;
		file_tilemap.open(filePathway, std::ios::in);
		if (!file_tilemap.is_open()) { MT_CORE_ERROR("{} missing!", filePathway); }
		while (file_tilemap >> tilePosition.x >> tilePosition.y >> color >> layer)
		{
			update(tilePosition, color, layer);
		}

		file_tilemap.close();
	}

	Tilemap::Tilemap()
	{
		initTilemap("Config/maps/map0.ini");
	}

	Tilemap::Tilemap(const std::string& filePathway)
	{
		initTilemap(filePathway);
	}

	Tilemap::~Tilemap()
	{
		tiles.clear();
	}


	void Tilemap::saveTileMap(const std::string& filePathway)
	{ //Save Tilemap from file
		std::fstream file_tilemap;
		file_tilemap.open(filePathway, std::ios::out);
		if (!file_tilemap.is_open()) { MT_CORE_ERROR("{} missing!", filePathway); }
		for (int i = 0; i < tiles[0].size(); i++)
		{
			file_tilemap << (int)(tiles[0][i]->getTilePosition().x) << std::endl << (int)(tiles[0][i]->getTilePosition().y)
				<< std::endl << tiles[0][i]->getTileCode() << std::endl << tiles[0][i]->getTileLayer() << std::endl;
		}
		for (int i = 0; i < tiles[1].size(); i++)
		{
			file_tilemap << (int)(tiles[1][i]->getTilePosition().x) << std::endl << (int)(tiles[1][i]->getTilePosition().y)
				<< std::endl << tiles[1][i]->getTileCode() << std::endl << tiles[1][i]->getTileLayer() << std::endl;
		}
		file_tilemap.close();
	}

	void Tilemap::update(const sf::Vector2f& tile_position, const int& tile_code, const int& tile_layer)
	{   //Create new tile
		if (tile_code != 4)
		{
			tiles[tile_layer].push_back(std::make_shared<Tile>(tile_position.x,
				tile_position.y, (sf::Vector2f)(maxSize), tile_code, tile_layer));
		}
		//Delete a tile
		else
		{
			bool erased = false;
			for (auto t = tiles[0].begin();
				t != tiles[0].end();)
			{
				if ((*t)->getTilePosition() == tile_position)
				{
					t = tiles[0].erase(t);
					erased = true;
				}
				else
				{
					++t;
				}
			}
			for (auto t = tiles[1].begin();
				t != tiles[1].end();)
			{
				if ((*t)->getTilePosition() == tile_position && erased == false)
				{
					t = tiles[1].erase(t);
					erased = true;
				}
				else
				{
					++t;
				}
			}
		}
	}


	void Tilemap::render(std::shared_ptr<sf::RenderWindow> window)
	{
		//Render for layer order
		for (auto& t : tiles[1])
		{
			t->render(window);
		}
		for (auto& t : tiles[0])
		{
			t->render(window);
		}
	}

}
