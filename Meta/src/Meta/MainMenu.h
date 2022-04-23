#pragma once
#include "State.h"
#include"GameState.h"
#include"SettingState.h"
#include"EditorState.h"
#include "Core.h"

namespace Meta {

    class META_API MainMenu :
        public State
    {
    private:
        std::vector<Button*> button;

        void initBackground();
        //Background for now
        sf::Texture texture;
        sf::Sprite background;
    public:
        MainMenu(sf::RenderWindow* window, std::stack<State*>* states, std::map<std::string, int>* supported_keys);
        virtual ~MainMenu();

        //Functions
        void endState(std::stack<State*>* states);
        void update(const float& dt);
        void render(sf::RenderWindow* window);

    };

}

