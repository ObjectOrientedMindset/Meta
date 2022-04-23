#include "pch.h"
#include "Application.h"

namespace Meta {

	void Application::initWindow()
	{
		//Initialize Game window
		this->window = new sf::RenderWindow(sf::VideoMode(1024, 960), "Sanbox", sf::Style::Close | sf::Style::Titlebar);
	}
	void Application::initSupportedKeys()
	{
		std::ifstream keys_file("config/supported_keys.ini");
		std::string key = "";
		int key_digit = 0;

		while (keys_file >> key >> key_digit)
		{
			this->supportedKeys[key] = key_digit;
		}
		keys_file.close();
	}
	Application::Application()
	{
		this->initWindow();
		this->initSupportedKeys();
		this->initStates();
	}
	Application::~Application()
	{
		delete this->window;
	}

	void Application::initStates()
	{
		this->state.push(new MainMenu(this->window, &this->state, &this->supportedKeys));
	}

	void Application::updateDt()
	{
		//Updates the dt variable with the time it takes to update and render one frame

		this->dt = this->dtClock.restart().asSeconds();
	}

	void Application::pollEvents()
	{
		while (this->window->pollEvent(this->e))
		{
			if (this->e.type == sf::Event::Closed)
				this->window->close();

		}
	}

	void Application::update()
	{
		if (this->state.empty() == false)
		{
			this->state.top()->update(this->dt);
		}
		//Application end
		else
		{
			this->window->close();
		}
	}

	void Application::render()
	{
		this->window->clear();

		if (this->state.empty() == false)
		{
			this->state.top()->render(this->window);
		}

		this->window->display();
	}

	void Application::run()
	{
		while (this->window->isOpen())
		{
			this->updateDt();
			this->pollEvents();
			this->update();
			this->render();
		}
		
	}

}
