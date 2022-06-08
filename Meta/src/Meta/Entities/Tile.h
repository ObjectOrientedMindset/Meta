#pragma once
#include "Entity.h"

namespace Meta {

	class META_API Tile
		: public Entity
	{
	private:
		//array accessor
		int tileCode;
		int tileLayer;
		std::vector<sf::Texture> tile;
		sf::Texture texture;
		sf::Sprite sprite;

		void initTexture();
	public:
		Tile(const std::string& id, const sf::Vector2f& position, const sf::Vector2f& size,
			const int& code, const int& layer, std::shared_ptr<Window> window);
		virtual ~Tile();

		
		Entity* getInstance() override { return this; }
		void update(std::string direction, float dirX, float dirY, const float& dt) override;
		void render() override;
	};

}

