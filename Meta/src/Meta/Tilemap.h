#pragma once
#include"Tile.h"
#include "Core.h"

namespace Meta {

	class META_API Tilemap
	{
	private:
		void initTilemap(const std::string& filePathway);
	public:
		std::vector<int> tile_code;
		std::vector<int> tile_layer;
		std::vector<sf::Vector2f> tilePosition;
		std::map<int, std::vector<Tile*>> tile; //int is for layers
		sf::Vector2u maxSize;

		Tilemap();
		Tilemap(const std::string& filePathway);
		virtual ~Tilemap();

		void saveTileMap(const std::string& filePathway);
		void update(const sf::Vector2f& tile_position, const int& tile_code, const int& tile_layer);
		void render(sf::RenderTarget* window);
	};

}
