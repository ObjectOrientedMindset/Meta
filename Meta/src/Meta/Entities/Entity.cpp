#include "mtpch.h"
#include "Entity.h"

namespace Meta {

	Entity::Entity(std::shared_ptr<Window> window)
	{
		this->window = window;
	}

	Entity::~Entity()
	{
	}

}
