#include "mtpch.h"
#include "Tile.h"

namespace Meta {

	void Tile::initTexture()
	{

		if (!tile[0].loadFromFile("Images/Tilemap/Grass.png")) { MT_CORE_ERROR("Images/Tilemap/Grass.png missing!"); }
		if (!tile[1].loadFromFile("Images/Tilemap/GrassFlower.png")) { MT_CORE_ERROR("Images/Tilemap/GrassFlower.png missing!"); }
		if (!tile[2].loadFromFile("Images/Tilemap/StoneGround.png")) { MT_CORE_ERROR("Images/Tilemap/StoneGround.png missing!"); }
		if (!tile[3].loadFromFile("Images/Tilemap/Tree.png")) { MT_CORE_ERROR("Images/Tilemap/Tree.png missing!"); }
	}

	Tile::Tile(const float& posX, const float& posY, const sf::Vector2f& size, const int& tile_code, const int& tile_layer)
	{
		initTexture();
		tileCode = tile_code;
		tileLayer = tile_layer;
		sprite.setTexture(tile[tile_code]);
		sprite.setPosition(posX, posY);
		if (tile_code == 2)
		{
			sprite.setScale(1.064, 1.064);
		}
	}

	Tile::~Tile()
	{
	}

	sf::Vector2f Tile::getTilePosition()
	{
		return sprite.getPosition();
	}

	const int Tile::getTileCode()
	{
		return tileCode;
	}

	const int Tile::getTileLayer()
	{
		return tileLayer;
	}

	void Tile::update()
	{

	}

	void Tile::render(std::shared_ptr<sf::RenderWindow> window)
	{
		window->draw(sprite);
	}


}