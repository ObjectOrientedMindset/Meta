#pragma once
#include "Meta/Base/AnimationComponent.h"
#include "Entity.h"

namespace Meta {

	class META_API Player
		: public Entity
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
		

	public:
		

		Player(const std::string& id,
			const sf::Vector2f& position,
			const int& code, const int& layer,
			std::shared_ptr<Window> window);
		virtual ~Player();

		void initTextures();
		void playerMovement(std::string direction, float dirX, float dirY, const float& dt);

		
		Entity* getInstance() override { return this; }
		void update(std::string direction, float dirX, float dirY, const float& dt) override;
		void render() override;
	};

}

