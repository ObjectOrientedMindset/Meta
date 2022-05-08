#pragma once
#include "Meta/Base/Core.h"
#include "Meta/GUI/Button.h"
#include "Meta/Base/Window.h"

// State Interface

namespace Meta {

	class META_API State
	{
	protected:
		//Game window
		std::shared_ptr<Window> window;
		//States
		std::stack<std::shared_ptr<State>>* states;
	public:
		State(std::shared_ptr<Window> window,
		std::stack<std::shared_ptr<State>>* states);
		virtual ~State();

		//Functions
		virtual void update(const float& dt) = 0;
		virtual void render() = 0;


	};

}

