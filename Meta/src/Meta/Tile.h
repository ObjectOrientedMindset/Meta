#pragma once
#include "Core.h"


namespace Meta {

	class META_API Tile
	{
	private:
		//array accessor
		int tileCode;
		int tileLayer;
		sf::Texture tile[4];
		sf::Sprite sprite;

		void initTexture();
	public:
		Tile(const float& posX, const float& posY, const sf::Vector2f& size, const int& tile_code, const int& tile_layer);
		virtual ~Tile();

		const sf::Vector2f& getTilePosition();
		const int getTileCode();
		const int getTileLayer();
		void update();
		void render(sf::RenderTarget* window);
	};

}

