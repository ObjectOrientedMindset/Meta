#pragma once


//Creates a window for windows platform 
namespace Meta {

	class META_API Window
	{
	private:
		sf::Event e;

		struct Event
		{
			sf::Event::EventType eventType = sf::Event::EventType();
			sf::Vector2f mousePosition = sf::Vector2f(0.f, 0.f);
			sf::Vector2f inAppMousePosition = sf::Vector2f(0.f, 0.f);
			char input = '\0';
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
				unsigned int Width = 1920,
				unsigned int Heigth = 1080)
				: title(Title), width(Width), height(Heigth)
			{
			}
		};
	private:
		windowData w_Data;
		sf::Vector2f mousePositionOffset;
		
	public:
		Event currentEvent;
		sf::Font pixelFont;
		std::vector<std::string> characterFilePaths;
		std::vector<std::string> tileFilePaths;
		std::vector<std::string> backgroundFilePaths;
		sf::View view;
		std::shared_ptr<sf::RenderWindow> renderWindow;



		Window(const windowData& data = windowData());
		~Window();

		
	private:
		void shutdown();
		void initWindow();
		void loadFiles();
	
	public:
		void saveCharacterFile(const std::string& filePath);
		void deleteCharacterFile(const int& index);
		void saveTileFile(const std::string& filePath);
		void deleteTileFile(const int& index);
		void saveBackgroundFile(const std::string& filePath);
		void deleteBackgroundFile(const int& index);
		void pollEvents();
		void moveView(const float& x, const float& y);
		sf::Vector2f getAppMousePosition();

	};



	

}

