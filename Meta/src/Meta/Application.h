#pragma once
#include "State.h"
#include "Window.h"
#include "Core.h"

namespace Meta {

	class META_API Application
	{
	private:
		//Delta time
		sf::Clock dtClock;
		float dt;

		//Variables
		std::shared_ptr<Window> window;
		//States
		std::stack<std::shared_ptr<State>> states;
		std::map<std::string, int> supportedKeys;

		void initWindow();
		void initSupportedKeys();

	public:
		Application();
		virtual ~Application();

		//Functions
		void initStates();
		void updateDt();
		void update();
		void render();
		void run();
	};

	Application* CreateApplication();

}
