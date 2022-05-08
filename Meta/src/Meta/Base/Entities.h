#pragma once
#include "Core.h"

// Entity Interface

namespace Meta {

	class META_API Entities
	{
	private:

	public:
		Entities();
		virtual ~Entities();

		//Functions

		virtual void update() = 0;
		virtual void render(std::shared_ptr<sf::RenderWindow> target) = 0;
	};

}

