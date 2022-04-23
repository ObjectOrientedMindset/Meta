#pragma once
#include "Core.h"

namespace Meta {

	class META_API Entities
	{
	private:

	public:
		Entities();
		virtual ~Entities();

		//Functions

		virtual void update() = 0;
		virtual void render(sf::RenderTarget* target) = 0;
	};

}

