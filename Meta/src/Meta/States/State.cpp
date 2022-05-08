#include "mtpch.h"
#include "State.h"


namespace Meta {
	

	State::State(std::shared_ptr<Window> window, std::stack<std::shared_ptr<State>>* states)
	{
		this->window = window;
		this->states = states;

	}


	State::~State()
	{
	}

}