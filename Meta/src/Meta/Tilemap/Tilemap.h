#pragma once
#include "Tile.h"
#include "Meta/Base/Core.h"

namespace Meta {

	class META_API Tilemap
	{
	private:
		std::string filePath;

		void initTilemap(const std::string& filePathway);
	public:
		std::vector<int> tile_code;
		std::vector<int> tile_layer;
		std::vector<sf::Vector2f> tilePosition;
		std::map<int, std::vector<std::shared_ptr<Tile>>> tiles; //int is for layers
		sf::Vector2u maxSize;

		Tilemap();
		Tilemap(const std::string& filePathway);
		virtual ~Tilemap();

		void saveTileMap();
		void update(const sf::Vector2f& tile_position, const int& tile_code, const int& tile_layer);
		void render(std::shared_ptr<sf::RenderWindow> window);
	};

}
