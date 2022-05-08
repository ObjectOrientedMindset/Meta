#pragma once


//Creates a window for windows platform 
namespace Meta {

	class META_API Window
	{
	private:
		std::shared_ptr<sf::RenderWindow> window;
		sf::Event e;

		struct Event
		{
			sf::Event::EventType eventType;
			sf::Vector2f mousePosition;
			char input;
			bool mouseClicked = false;
			bool changed = false;
		};
	public:
		struct windowData
		{
			std::string title;
			unsigned int width, height;
			bool vsync = false;
			windowData(const std::string Title = "Meta Engine",
				unsigned int Width = 1024,
				unsigned int Heigth = 960)
				: title(Title), width(Width), height(Heigth)
			{
			}
		};
	private:
		windowData w_Data;

	public:
		Event currentEvent;
		sf::Font pixelFont;
		std::string filePathway[5];

		Window(const windowData& data = windowData());
		~Window();

		void pollEvents();
		std::shared_ptr<sf::RenderWindow> getRenderWindow();
	
	private:
		void shutdown();
		void initWindow();
		void loadFiles();
	};



	

}

