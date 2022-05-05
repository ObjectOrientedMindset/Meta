#pragma once
#include "State.h"
#include "Core.h"

namespace Meta {

    class META_API SettingState :
        public State
    {
    private: 
        std::vector<std::shared_ptr<Button>> buttons;
        sf::Texture texture;
        sf::Sprite background;
    public:
        SettingState(std::shared_ptr<Window> window,
            std::stack<std::shared_ptr<State>>* states);
        virtual ~SettingState();


        void initBackground();
        void endState();
        void update(const float& dt);
        void render();

    };

}

