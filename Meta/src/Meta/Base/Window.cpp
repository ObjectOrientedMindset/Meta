#include "mtpch.h"
#include "Window.h"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

namespace Meta {
	

	Window::Window(const windowData& data)
	{
		initWindow();
		loadFiles();
	}

	Window::~Window()
	{
		MT_CORE_TRACE("Window Shutdown!");
		
		shutdown();
	}

	void Window::shutdown()
	{
		ImGui::SFML::Shutdown();
		window->close();
	}

	void Window::loadFiles()
	{
		filePathway[0] = "Config/maps/map0.ini";
		filePathway[1] = "Config/maps/map1.ini";
		filePathway[2] = "Config/maps/map2.ini";
		filePathway[3] = "Config/maps/map3.ini";
		filePathway[4] = "Config/maps/map4.ini";
	}

	void Window::initWindow()
	{
		window = std::make_shared<sf::RenderWindow>(
			sf::VideoMode(w_Data.width, w_Data.height)
			, w_Data.title, sf::Style::Close | sf::Style::Titlebar);

		if (window->isOpen()) MT_CORE_INFO("Window initialized!");

		if(!pixelFont.loadFromFile("Fonts/PixellettersFull.ttf")) MT_CORE_ERROR("Fonts/PixellettersFull.ttf Loading Failed!");

		if(!ImGui::SFML::Init(*window)) MT_CORE_FATAL("ImGui Initialization Failed!");
	
	}


	void Window::pollEvents()
	{
		//reset the current event
		currentEvent.eventType = sf::Event::EventType();
		currentEvent.mouseClicked = false;
		currentEvent.mousePosition = sf::Vector2f(sf::Mouse::getPosition(*window));
		currentEvent.changed = false;
		currentEvent.input = '\0';
		while (window->pollEvent(e))
		{
			ImGui::SFML::ProcessEvent(*window, e);
			switch (e.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::MouseButtonPressed:
				currentEvent.eventType = sf::Event::MouseButtonPressed;
				currentEvent.mouseClicked = true;
				currentEvent.mousePosition = sf::Vector2f(sf::Mouse::getPosition(*window));
				currentEvent.changed = true;
				currentEvent.input = '\0';
				break;
			case sf::Event::MouseMoved:
				currentEvent.eventType = sf::Event::MouseMoved;
				currentEvent.mouseClicked = false;
				currentEvent.mousePosition = sf::Vector2f(sf::Mouse::getPosition(*window));
				currentEvent.changed = true;
				currentEvent.input = '\0';
				break;
			case sf::Event::TextEntered:
				if (e.text.unicode < 128) 
				{
					currentEvent.eventType = sf::Event::TextEntered;
					currentEvent.mouseClicked = false;
					currentEvent.mousePosition = sf::Vector2f(sf::Mouse::getPosition(*window));
					currentEvent.changed = true;
					currentEvent.input = static_cast<char>(e.text.unicode);
				}
				else 
				{
					MT_CORE_WARN("Invalid Key Input!");
				}
				break;
			}
		}
	}


	std::shared_ptr<sf::RenderWindow> Window::getRenderWindow()
	{
#ifdef MT_PLATFORM_WINDOWS
		
		return window;
#else
		return MT_CORE_FATAL("Unkown operating system!");
		return nullptr;
#endif 
		
	}


}
