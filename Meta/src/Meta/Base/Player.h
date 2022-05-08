#pragma once
#include "Meta/Base/Entities.h"
#include "Meta/Base/AnimationComponent.h"
#include "Meta/Base/Core.h"



namespace Meta {

	class META_API Player
		: public Entities
	{
	private:
		//Variables
		sf::Texture playerTexture;
		sf::Sprite playerSprite;
		float movementSpeed;
		float timer;
		float timerMax;
		float posX;
		float posY;
		AnimationComponent playerAnimations;
		void initPlayerFromFile();

	public:
		Player();
		virtual ~Player();

		void initTextures();
		void playerMovement(std::string direction, float dirX, float dirY, const float& dt);

		const sf::Vector2f& getPlayerPosition();
		void setPlayerPosition(float x, float y);
		void update();
		void render(std::shared_ptr<sf::RenderWindow> target);
	};

}

