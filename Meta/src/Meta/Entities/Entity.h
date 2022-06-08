#pragma once
#include "Meta/Base/Core.h"
#include "Meta/Base/Window.h"

// Entity Interface

namespace Meta {

	class META_API Entity
	{
	private:
		struct EntityData
		{
			std::string id;
			int code;
			int layer;
			sf::Vector2f position;
		};
	protected:
		std::shared_ptr<Window> window;
	public:
		EntityData data;
	public:
		Entity(std::shared_ptr<Window> window);
		virtual ~Entity();
		
		
		//Functions


		virtual Entity* getInstance() = 0;
		virtual void update(std::string direction, float dirX, float dirY, const float& dt) = 0;
		virtual void render() = 0;
	};

}

