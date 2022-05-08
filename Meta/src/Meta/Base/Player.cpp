#include "mtpch.h"
#include "Player.h"


namespace Meta {

	Player::Player()
		:Entities(), playerAnimations(playerSprite)
	{
		initTextures();
		timerMax = 500.f;
		timer = timerMax;
		initPlayerFromFile();
		playerSprite.setPosition(posX, posY);
		movementSpeed = 200.f;
		playerAnimations.addAnimation("Down", playerSprite, timer, 0, 0, 3, 0, 64, 60);
		playerAnimations.addAnimation("Left", playerSprite, timer, 4, 0, 7, 0, 64, 60);
		playerAnimations.addAnimation("Right", playerSprite, timer, 8, 0, 11, 0, 64, 60);
		playerAnimations.addAnimation("Up", playerSprite, timer, 12, 0, 15, 0, 64, 60);
	}

	void Player::initPlayerFromFile()
	{
		posX = 0; posY = 0;
		std::fstream file;
		file.open("Config/player.ini", std::ios::in);
		if (!file.is_open()) { MT_CORE_ERROR("Config/Player.ini missing!"); }
		file >> posX >> posY;
		std::cout << posX;
		if (posX == 0 || posY == 0) { MT_CORE_WARN("Config/Player.ini file contents could be missing!"); }
		file.close();
	}

	Player::~Player()
	{
	}
	void Player::initTextures()
	{
		if (!playerTexture.loadFromFile("Images/PLAYER_SHEET2.png")) { MT_CORE_ERROR("Images/PLAYER_SHEET2.png missing!"); }
		playerSprite.setTexture(playerTexture);
	}

	void Player::playerMovement(std::string direction, float dirX, float dirY, const float& dt)
	{
		//Update player input
		playerSprite.move(dirX * dt * movementSpeed, dirY * dt * movementSpeed);
		if (timer >= timerMax)
		{
			playerAnimations.playAnimation(direction, dt);
			timer = 0.f;
			playerSprite.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y);
		}
	}

	const sf::Vector2f& Player::getPlayerPosition()
	{
		return playerSprite.getPosition();
	}
	void Player::setPlayerPosition(float x, float y)
	{
		playerSprite.setPosition(x, y);
	}
	void Player::update()
	{
		++timer;
	}

	void Player::render(std::shared_ptr<sf::RenderWindow> target)
	{
		target->draw(playerSprite);
	}

}
