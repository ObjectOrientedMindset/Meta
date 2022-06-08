#pragma once
#include "State.h"


namespace Meta {

    class META_API MainMenu :
        public State
    {
    private:
        std::vector<std::shared_ptr<Button>> buttons;

        void initBackground();
        //Background for now
        sf::Texture texture;
        sf::Sprite background;
    public:
        MainMenu(std::shared_ptr<Window> window,
        std::stack<std::shared_ptr<State>>* states);
        virtual ~MainMenu();

        //Functions
        void endState() override;
        void update(const float& dt) override;
        void render() override;

    };

}

