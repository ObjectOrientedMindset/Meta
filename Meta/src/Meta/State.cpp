#include "pch.h"
#include "State.h"


namespace Meta {
	
	State::State(std::shared_ptr<Window> window, std::stack<std::shared_ptr<State>>* states, std::map<std::string, int>* supported_keys)
	{
		//Init window
		this->window = window;
		this->states = states;
		this->supported_keys = supported_keys;
		pixelFont.loadFromFile("Fonts/PixellettersFull.ttf");
		mousePos = sf::Vector2f(sf::Mouse::getPosition(*window->getWindow()));
		filePathway[0] = "Config/maps/map0.ini";
		filePathway[1] = "Config/maps/map1.ini";
		filePathway[2] = "Config/maps/map2.ini";
		filePathway[3] = "Config/maps/map3.ini";
		filePathway[4] = "Config/maps/map4.ini";
		
	}

	State::~State()
	{
	}

	sf::Vector2f& State::getMousePos()
	{
		mousePos = sf::Vector2f(sf::Mouse::getPosition(*window->getWindow()));
		return mousePos;
	}

}