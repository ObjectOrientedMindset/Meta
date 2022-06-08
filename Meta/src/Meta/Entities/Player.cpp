#include "mtpch.h"
#include "Player.h"


namespace Meta {

	Player::Player(const std::string& id, 
		const sf::Vector2f& position,
		const int& code, const int& layer,
		std::shared_ptr<Window> window)
		:Entity(window), playerAnimations(playerSprite)
	{
		data.id = id;
		data.position = position;
		data.code = code;
		data.layer = layer;
		initTextures();
		timerMax = 500.f;
		timer = timerMax;
		playerSprite.setPosition(position.x, position.y);
		movementSpeed = 200.f;
		playerAnimations.addAnimation("Down", playerSprite, timer, 0, 0, 3, 0, 64, 60);
		playerAnimations.addAnimation("Left", playerSprite, timer, 4, 0, 7, 0, 64, 60);
		playerAnimations.addAnimation("Right", playerSprite, timer, 8, 0, 11, 0, 64, 60);
		playerAnimations.addAnimation("Up", playerSprite, timer, 12, 0, 15, 0, 64, 60);
	}

	Player::~Player()
	{
	}
	void Player::initTextures()
	{
		playerTexture.loadFromFile(window->characterFilePaths[0]) == true ?
			playerSprite.setTexture(playerTexture) : MT_CORE_ERROR("Player::initTexture() failed!");

	}

	void Player::playerMovement(std::string direction, float dirX, float dirY, const float& dt)
	{
		//Update player input
		playerSprite.move(dirX * dt * movementSpeed, dirY * dt * movementSpeed);
		if (timer >= timerMax)
		{
			playerAnimations.playAnimation(direction, dt);
			timer = 0.f;			
		}
		data.position = playerSprite.getPosition();
	}

	void Player::update(std::string direction, float dirX, float dirY, const float& dt)
	{
		playerMovement(direction, dirX, dirY, dt);
		++timer;
	}

	void Player::render()
	{
		window->renderWindow->draw(playerSprite);
	}

}
