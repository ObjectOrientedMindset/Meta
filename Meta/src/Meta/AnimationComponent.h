#pragma once
#include "Core.h"

class META_API AnimationComponent
{
private:

	class Animation
	{
	public:
		sf::Sprite& sprite;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;
		int startFrameX, startFrameY, width, height;


		Animation(sf::Sprite& sprite, int start_frameX, int start_frameY, int end_frameX
			, int end_frameY, int width, int height)
			: sprite(sprite), startRect(start_frameX* width, start_frameY* height, width, height),
			currentRect(startRect), endRect(end_frameX* width, end_frameY* height, width, height),
			startFrameX(start_frameX), startFrameY(start_frameY), width(width), height(height)
		{
			this->sprite.setTextureRect(startRect);
		}

		void play(const float& dt)
		{

			if (this->currentRect == this->endRect)
			{
				this->currentRect = this->startRect;
			}
			else
			{
				this->currentRect.left += this->width;
			}
			this->sprite.setTextureRect(this->currentRect);

		}
	};
	sf::Sprite& sprite;
	std::map<std::string, Animation*> animations;
public:
	AnimationComponent(sf::Sprite& sprite_)
		: sprite(sprite_)
	{
	}
	virtual ~AnimationComponent()
	{
		for (auto& i : this->animations)
		{
			delete i.second;
		}
	}
	void addAnimation(const std::string key, sf::Sprite& sprite, float animation_timer
		, int start_frame_x, int start_frame_y, int end_frames_x, int end_frames_y, int width, int height)
	{
		this->animations[key] = new Animation(sprite, start_frame_x, start_frame_y, end_frames_x, end_frames_y, width, height);
	}

	void playAnimation(std::string key, const float& dt)
	{
		this->animations[key]->play(dt);
	}
};

