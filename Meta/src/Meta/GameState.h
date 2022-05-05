#pragma once
#include "State.h"
#include "Player.h"
#include "Tilemap.h"
#include "PauseMenu.h"
#include "Core.h"

namespace Meta {


    class META_API GameState :
        public State
    {
    private:
        //Variables
        std::unique_ptr<Player> player;
        std::stack<std::shared_ptr<Tilemap>> tilemaps;
        PauseMenu pauseMenu;
        bool pause;
        float timer;
        float timerMax;
        int filePathCount, filePathCountMax;
        //Keybind
        std::map<std::string, int> keybinds;

        void initKeyBinds(std::map<std::string, int>* supported_keys);
        void changeMap();
    public:
        GameState(std::shared_ptr<Window> window, std::stack<std::shared_ptr<State>>* states, std::map<std::string, int>* supported_keys);
        virtual ~GameState();



        //Functions
        void endState();
        void updatePlayerInput(const float& dt);
        void update(const float& dt);
        void render();
    };

}

