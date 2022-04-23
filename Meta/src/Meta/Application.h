#pragma once
#include "State.h"
#include "Core.h"
#include "MainMenu.h"


namespace Meta {

	class META_API Application
	{
	private:
		//Delta time
		sf::Clock dtClock;
		float dt;

		//Variables
		sf::RenderWindow* window;
		sf::Event e;
		
		//States
		std::stack<State*> state;
		std::map<std::string, int> supportedKeys;

		void initWindow();
		void initSupportedKeys();

	public:
		Application();
		virtual ~Application();

		//Functions
		void initStates();
		void updateDt();
		void pollEvents();
		void update();
		void render();
		void run();
	};

	Application* CreateApplication();

}
