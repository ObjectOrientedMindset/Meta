#pragma once
#include"Button.h"
#include "Core.h"

namespace Meta {

	class META_API State
	{
	protected:
		//Game window
		sf::RenderWindow* window;
		//States
		std::stack<State*>* states;
		//Fonts
		sf::Font pixelFont;
		//Mouse
		sf::Vector2f mousePos;
		//Keys
		std::map<std::string, int>* supported_keys;
		//Files
		std::string filePathway[5];
	public:
		State(sf::RenderWindow* window, std::stack<State*>* states, std::map<std::string, int>* supported_keys);
		virtual ~State();

		sf::Vector2f& getMousePos();

		//Functions
		virtual void endState(std::stack<State*>* states) = 0;
		virtual void update(const float& dt) = 0;
		virtual void render(sf::RenderWindow* window) = 0;


	};

}

