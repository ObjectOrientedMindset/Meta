#include "pch.h"
#include "Window.h"



namespace Meta {


	Window::Window(const windowData& data)
	{
		initWindow();
	}

	Window::~Window()
	{
		MT_CORE_TRACE("Window Shutdown!");

		shutdown();
	}

	void Window::shutdown()
	{
		window->close();
	}

	void Window::initWindow()
	{
		window = std::make_shared<sf::RenderWindow>(
			sf::VideoMode(w_Data.width, w_Data.height)
			, w_Data.title, sf::Style::Default);

	}


	void Window::pollEvents()
	{
		while (window->pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				window->close();
			}			
		}
	}

	std::shared_ptr<sf::RenderWindow> Window::getWindow()
	{
#ifdef MT_PLATFORM_WINDOWS
		
		return window;
#else
		return MT_CORE_FATAL("Unkown operating system!");
		return nullptr;
#endif 
		
	}


}

