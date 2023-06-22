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
		renderWindow->close();
	}

	void Window::loadFiles()
	{
		std::string fileLocation;
		std::fstream file_tilemap;
		file_tilemap.open("Config/character_locations.ini", std::ios::in);
		if (!file_tilemap.is_open()) { MT_CORE_ERROR("Config/character_locations.ini missing!"); }
		while (file_tilemap >> fileLocation)
		{
			characterFilePaths.push_back(fileLocation);
		}
		
		file_tilemap.close();

		file_tilemap.open("Config/tile_locations.ini", std::ios::in);
		if (!file_tilemap.is_open()) { MT_CORE_ERROR("Config/tile_locations.ini missing!"); }
		while (file_tilemap >> fileLocation)
		{
			tileFilePaths.push_back(fileLocation);
		}

		file_tilemap.close();

		file_tilemap.open("Config/background_locations.ini", std::ios::in);
		if (!file_tilemap.is_open()) { MT_CORE_ERROR("Config/background_locations.ini missing!"); }
		while (file_tilemap >> fileLocation)
		{
			backgroundFilePaths.push_back(fileLocation);
		}

		file_tilemap.close();


	}
	void Window::saveCharacterFile(const std::string& filePath)
	{
		characterFilePaths.push_back(filePath);
		std::fstream file_tilemap;
		file_tilemap.open("Config/character_locations.ini", std::ios::out);
		if (!file_tilemap.is_open()) { MT_CORE_ERROR("Config/character_locations.ini missing!"); }
		
		for (size_t i = 0; i < characterFilePaths.size(); i++)
		{
			file_tilemap << characterFilePaths[i] << std::endl;
		}


		file_tilemap.close();
	}

	void Window::deleteCharacterFile(const int& index)
	{
		characterFilePaths.erase(characterFilePaths.begin() + index);
		std::fstream file_tilemap;
		file_tilemap.open("Config/character_locations.ini", std::ios::out);
		if (!file_tilemap.is_open()) { MT_CORE_ERROR("Config/character_locations.ini missing!"); }

		for (size_t i = 0; i < characterFilePaths.size(); i++)
		{
			file_tilemap << characterFilePaths[i] << std::endl;
		}


		file_tilemap.close();
	}

	void Window::saveTileFile(const std::string& filePath)
	{
		tileFilePaths.push_back(filePath);
		std::fstream file_tilemap;
		file_tilemap.open("Config/tile_locations.ini", std::ios::out);
		if (!file_tilemap.is_open()) { MT_CORE_ERROR("Config/tile_locations.ini missing!"); }

		for (size_t i = 0; i < tileFilePaths.size(); i++)
		{
			file_tilemap << tileFilePaths[i] << std::endl;
		}


		file_tilemap.close();
	}

	void Window::deleteTileFile(const int& index)
	{
		tileFilePaths.erase(tileFilePaths.begin() + index);
		std::fstream file_tilemap;
		file_tilemap.open("Config/tile_locations.ini", std::ios::out);
		if (!file_tilemap.is_open()) { MT_CORE_ERROR("Config/tile_locations.ini missing!"); }

		for (size_t i = 0; i < tileFilePaths.size(); i++)
		{
			file_tilemap << tileFilePaths[i] << std::endl;
		}


		file_tilemap.close();
	}

	void Window::saveBackgroundFile(const std::string& filePath)
	{
		backgroundFilePaths.push_back(filePath);
		std::fstream file_tilemap;
		file_tilemap.open("Config/background_locations.ini", std::ios::out);
		if (!file_tilemap.is_open()) { MT_CORE_ERROR("Config/background_locations.ini missing!"); }

		for (size_t i = 0; i < backgroundFilePaths.size(); i++)
		{
			file_tilemap << backgroundFilePaths[i] << std::endl;
		}


		file_tilemap.close();

	}

	void Window::deleteBackgroundFile(const int& index)
	{
		backgroundFilePaths.erase(backgroundFilePaths.begin() + index);
		std::fstream file_tilemap;
		file_tilemap.open("Config/background_locations.ini", std::ios::out);
		if (!file_tilemap.is_open()) { MT_CORE_ERROR("Config/background_locations.ini missing!"); }

		for (size_t i = 0; i < backgroundFilePaths.size(); i++)
		{
			file_tilemap << backgroundFilePaths[i] << std::endl;
		}


		file_tilemap.close();
	}
	

	void Window::initWindow()
	{
#ifdef MT_PLATFORM_WINDOWS

		renderWindow = std::make_shared<sf::RenderWindow>(
			sf::VideoMode(w_Data.width, w_Data.height)
			, w_Data.title, sf::Style::Close | sf::Style::Titlebar
			);

		if (renderWindow->isOpen()) MT_CORE_INFO("Window Initialized!");
		else MT_CORE_FATAL("Window Initialization Failed!");

		sf::Image logo = sf::Image();

		if (!logo.loadFromFile("Assets/Logo/M.png")) MT_CORE_ERROR("Logo M.png Loading Failed!");

		renderWindow->setIcon(logo.getSize().x, logo.getSize().y, logo.getPixelsPtr());

		if (!pixelFont.loadFromFile("Fonts/PixellettersFull.ttf")) MT_CORE_ERROR("Fonts/PixellettersFull.ttf Loading Failed!");
		//ImGui Init
		if (!ImGui::SFML::Init(*renderWindow)) MT_CORE_FATAL("ImGui Initialization Failed!");
		//sf View
		view = sf::View(renderWindow->getDefaultView().getCenter(), renderWindow->getDefaultView().getSize());

		mousePositionOffset = sf::Vector2f(0.f, 0.f);
#else
		 MT_CORE_FATAL("Unkown operating system!");
#endif 

	}


	void Window::pollEvents()
	{
		//reset the current event
		currentEvent.eventType = sf::Event::EventType();
		currentEvent.mouseClicked = false;
		currentEvent.mousePosition = sf::Vector2f(sf::Mouse::getPosition(*renderWindow));
		currentEvent.changed = false;
		currentEvent.input = '\0';
		while (renderWindow->pollEvent(e))
		{
			ImGui::SFML::ProcessEvent(*renderWindow, e);
			switch (e.type)
			{
			case sf::Event::Closed:
				renderWindow->close();
				break;
			case sf::Event::MouseButtonPressed:
				currentEvent.eventType = sf::Event::MouseButtonPressed;
				currentEvent.mouseClicked = true;
				currentEvent.changed = true;
				currentEvent.input = '\0';
				break;
			case sf::Event::MouseMoved:
				currentEvent.eventType = sf::Event::MouseMoved;
				currentEvent.mouseClicked = false;
				currentEvent.changed = true;
				currentEvent.input = '\0';
				break;
			case sf::Event::TextEntered:
				if (e.text.unicode < 128) 
				{
					currentEvent.eventType = sf::Event::TextEntered;
					currentEvent.mouseClicked = false;
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


	void Window::moveView(const float& x, const float& y)
	{
		mousePositionOffset.x += x; mousePositionOffset.y += y;

		view.move(x, y);

		renderWindow->setView(view);
	}
	
	sf::Vector2f Window::getAppMousePosition()
	{
		return currentEvent.mousePosition + mousePositionOffset;
	}
}

