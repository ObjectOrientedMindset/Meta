#include "mtpch.h"
#include "Tile.h"

namespace Meta {

	void Tile::initTexture()
	{
		for (int i = 0; i < window->tileFilePaths.size(); i++)
		{
			if (!texture.loadFromFile(window->tileFilePaths[i])) { MT_CORE_ERROR("Tile::initTexture() failed!"); }
			tile.push_back(texture);
		}
	}

	Tile::Tile(const std::string& id, const sf::Vector2f& position, const sf::Vector2f& size,
		const int& code, const int& layer, std::shared_ptr<Window> window) : Entity(window)
	{
		initTexture();
		data.id = id;
		data.position = position;
		data.code = code;
		data.layer = layer;
		sprite.setTexture(tile[code]);
		sprite.setPosition(position.x, position.y);
		if (code == 2)
		{
			sprite.setScale(1.064, 1.064);
		}
	}

	Tile::~Tile()
	{
	}

	void Tile::update(std::string direction, float dirX, float dirY, const float& dt)
	{

	}

	void Tile::render()
	{
		window->renderWindow->draw(sprite);
	}


}