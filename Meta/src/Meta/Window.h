#pragma once


//Creates a window for windows platform 
namespace Meta {

	class META_API Window
	{
	private:
		std::shared_ptr<sf::RenderWindow> window;
		sf::Event e;

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

		windowData w_Data;
	public:


		Window(const windowData& data = windowData());
		~Window();


		void shutdown();
		void initWindow();
		void pollEvents();

		std::shared_ptr<sf::RenderWindow> getWindow();
	private:

	};


}

