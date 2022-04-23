#include "pch.h"
#include "Tile.h"

namespace Meta {

	void Tile::initTexture()
	{

		if (!this->tile[0].loadFromFile("Images/Tilemap/Grass.png")) { MT_CORE_ERROR("Images/Tilemap/Grass.png missing!"); }
		if (!this->tile[1].loadFromFile("Images/Tilemap/GrassFlower.png")) { MT_CORE_ERROR("Images/Tilemap/GrassFlower.png missing!"); }
		if (!this->tile[2].loadFromFile("Images/Tilemap/StoneGround.png")) { MT_CORE_ERROR("Images/Tilemap/StoneGround.png missing!"); }
		if (!this->tile[3].loadFromFile("Images/Tilemap/Tree.png")) { MT_CORE_ERROR("Images/Tilemap/Tree.png missing!"); }
	}

	Tile::Tile(const float& posX, const float& posY, const sf::Vector2f& size, const int& tile_code, const int& tile_layer)
	{
		this->initTexture();
		this->tileCode = tile_code;
		this->tileLayer = tile_layer;
		this->sprite.setTexture(this->tile[tile_code]);
		this->sprite.setPosition(posX, posY);
		if (tile_code == 2)
		{
			this->sprite.setScale(1.064, 1.064);
		}
	}

	Tile::~Tile()
	{
	}

	const sf::Vector2f& Tile::getTilePosition()
	{
		return this->sprite.getPosition();
	}

	void Tile::update()
	{

	}

	void Tile::render(sf::RenderTarget* window)
	{
		window->draw(this->sprite);
	}


}