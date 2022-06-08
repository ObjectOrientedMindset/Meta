#pragma once
#include "Tile.h"
#include "Player.h"

namespace Meta {

	class META_API Tilemap
	{
	private:
		std::string filePath;
		
		void initTilemap(const std::string& filePathway, std::shared_ptr<Window> window);
	public:
		std::vector<int> tile_code;
		std::vector<int> tile_layer;
		std::vector<sf::Vector2f> tilePosition;
		std::map<int, std::vector<std::shared_ptr<Entity>>> entities; //int is for layers
		sf::Vector2u maxSize;

		Tilemap(std::shared_ptr<Window> window);
		Tilemap(const std::string& filePathway, std::shared_ptr<Window> window);
		virtual ~Tilemap();

		void saveTileMap();
		void addTile(const std::string& id, const sf::Vector2f& position,
			const int& code, const int& layer, std::shared_ptr<Window> window);
		void addCharacter(const std::string& id, const sf::Vector2f& position,
		    const int& code, const int& layer, std::shared_ptr<Window> window);
		void deleteEntity(const sf::Vector2f& position);

		Entity* getPlayerInstance();
		void update();
		void render();
	};

}
