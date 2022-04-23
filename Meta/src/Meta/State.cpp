#include "pch.h"
#include "State.h"

namespace Meta {
	
	State::State(sf::RenderWindow* window, std::stack<State*>* states, std::map<std::string, int>* supported_keys)
	{
		//Init window
		this->window = window;
		this->states = states;
		this->supported_keys = supported_keys;
		this->pixelFont.loadFromFile("Fonts/PixellettersFull.ttf");
		this->mousePos = sf::Vector2f(sf::Mouse::getPosition(*this->window));
		this->filePathway[0] = "Config/maps/map0.ini";
		this->filePathway[1] = "Config/maps/map1.ini";
		this->filePathway[2] = "Config/maps/map2.ini";
		this->filePathway[3] = "Config/maps/map3.ini";
		this->filePathway[4] = "Config/maps/map4.ini";
	}

	State::~State()
	{
		delete this->states->top();
	}

	sf::Vector2f& State::getMousePos()
	{
		this->mousePos = sf::Vector2f(sf::Mouse::getPosition(*this->window));
		return this->mousePos;
	}

}