#include "mtpch.h"
#include "Application.h"
#include "Meta/States/MainMenu.h"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"



namespace Meta {
	
	void Application::initWindow()
	{
		//Initialize Game window
		window = std::make_shared<Window>(Window::windowData());
		
	}

	Application::Application()
	{
		initWindow();
		
		initStates();
	}
	Application::~Application()
	{
	}

	void Application::initStates()
	{
		states.push(std::make_shared<MainMenu>(window, &states));
	}

	void Application::updateDt()
	{
		//Updates the dt variable with the time it takes to update and render one frame

		dt = dtClock.restart().asSeconds();
	}

	void Application::update()
	{
		ImGui::SFML::Update(*window->renderWindow, dtClock.restart());
		

		if (states.empty() == false)
		{
			states.top()->update(dt);
		}
		//Application end
		else
		{
			window->renderWindow->close();
		}
		
	}
	
	void Application::render()
	{
		window->renderWindow->clear();
		

		if (states.empty() == false)
		{
			states.top()->render();
		}


		ImGui::SFML::Render(*window->renderWindow);
		window->renderWindow->display();
	}

	void Application::run()
	{
		while (window->renderWindow->isOpen())
		{
			updateDt();
			window->pollEvents();
			update();
			render();
		}
		
	}

}
