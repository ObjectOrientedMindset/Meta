#include "pch.h"

#include <Meta.h>


class Game : public Meta::Application
{
public:
	Game()
	{
		
	}
	~Game()
	{

	}

};



Meta::Application* Meta::CreateApplication()
{
	return new Game();
}
