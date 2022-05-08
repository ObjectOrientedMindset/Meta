#pragma once
#include "State.h"
#include "Meta/Base/Player.h"
#include "Meta/Tilemap/Tilemap.h"
#include "Meta/GUI/PauseMenu.h"

namespace Meta {


    class META_API GameState :
        public State
    {
    private:
        //Variables
        std::unique_ptr<Player> player;
        std::shared_ptr<Tilemap> tilemap;
        PauseMenu pauseMenu;
        bool pause;
        int filePathCount, filePathCountMax;
        //Keybind

    public:
        GameState(std::shared_ptr<Window> window,
        std::stack<std::shared_ptr<State>>* states);
        virtual ~GameState();



        //Functions
        void endState();
        void updatePlayerInput(const float& dt);
        void update(const float& dt);
        void render();
    };

}

