#include "pch.h"
#include "Application.h"
#include "MainMenu.h"




namespace Meta {
	
	void Application::initWindow()
	{
		//Initialize Game window
		window = std::make_shared<Window>();
	}
	void Application::initSupportedKeys()
	{
		std::ifstream keys_file("config/supported_keys.ini");
		std::string key = "";
		int key_digit = 0;

		while (keys_file >> key >> key_digit)
		{
			supportedKeys[key] = key_digit;
		}
		keys_file.close();
	}
	Application::Application()
	{
		initWindow();
		initSupportedKeys();
		initStates();
	}
	Application::~Application()
	{
	}

	void Application::initStates()
	{
		states.push(std::make_shared<MainMenu>(window, &states, &supportedKeys));
	}

	void Application::updateDt()
	{
		//Updates the dt variable with the time it takes to update and render one frame

		dt = dtClock.restart().asSeconds();
	}

	void Application::update()
	{
		if (states.empty() == false)
		{
			states.top()->update(dt);
		}
		//Application end
		else
		{
			window->getWindow()->close();
		}
	}
	
	void Application::render()
	{
		window->getWindow()->clear();
		

		if (states.empty() == false)
		{
			states.top()->render();
		}

		window->getWindow()->display();
	}

	void Application::run()
	{
		while (window->getWindow()->isOpen())
		{
			updateDt();
			window->pollEvents();
			update();
			render();
		}
		
	}

}
