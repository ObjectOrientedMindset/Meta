#pragma once
#include "State.h"
#include "Meta/Entities/Player.h"
#include "Meta/Entities/Tilemap.h"
#include "Meta/GUI/PauseMenu.h"
#include "Meta/GUI/Gui.h"

namespace Meta {


    class META_API GameState :
        public State
    {
    private:
        //Variables
        std::shared_ptr<Tilemap> tilemap;
        Entity* player;
        PauseMenu pauseMenu;
        Gui gui;
        bool pause;
        int filePathCount, filePathCountMax;
        float posX;
        float posY;

        void camera();
    public:
        GameState(std::shared_ptr<Window> window,
        std::stack<std::shared_ptr<State>>* states);
        virtual ~GameState();



        //Functions
        bool updatePlayer(const float& dt);
        void endState() override;
        void update(const float& dt) override;
        void render() override;
    };

}

