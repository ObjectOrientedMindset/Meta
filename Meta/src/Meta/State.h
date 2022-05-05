#pragma once
#include "Button.h"
#include "Core.h"
#include "Window.h"

namespace Meta {

	class META_API State
	{
	protected:
		//Game window
		std::shared_ptr<Window> window;
		//States
		std::stack<std::shared_ptr<State>>* states;
		//Fonts
		sf::Font pixelFont;
		//Mouse
		sf::Vector2f mousePos;
		//Keys
		std::map<std::string, int>* supported_keys;
		//Files
		std::string filePathway[5];
	public:
			State(std::shared_ptr<Window> window,
			std::stack<std::shared_ptr<State>>* states,
			std::map<std::string, int>* supported_keys);
		virtual ~State();

		sf::Vector2f& getMousePos();

		//Functions
		virtual void endState() = 0;
		virtual void update(const float& dt) = 0;
		virtual void render() = 0;


	};

}

