#pragma once
#include "State.h"
#include "Meta/GUI/Gui.h"
#include "Meta/GUI/PauseMenu.h"
#include "Meta/Tilemap/Tilemap.h"



namespace Meta {


    class META_API EditorState :
        public State
    {
    private:
        //Variables
        Gui gui;
        PauseMenu pmenu;
        std::shared_ptr<Tilemap> tilemap;
        bool pause = false;
        sf::Text mouseCoordinatesText_x;
        sf::Text mouseCoordinatesText_y;
        sf::RectangleShape tileCollision;
        sf::RectangleShape editMapRectangle;
        std::vector<std::vector<sf::RectangleShape>> editmap;
        unsigned int tileCode = 1;
        int tileLayer;
        sf::Text text;
        float mouseX;
        float mouseY;
        sf::Cursor cursorArrow;
        sf::Cursor cursorHand;
        unsigned int timerMax = 100;
        unsigned int timer = timerMax;
        sf::Vector2f tilePosition = sf::Vector2f(0.f,0.f);

        //Functions
        void initEditMap();
        void addTile(sf::Vector2f tile);
        void deleteTile(sf::Vector2f tile);
        void tileCollisionCheck();
        bool editMapCollisionCheck();
        void updateMouseCoordinates();
        void changetileCode();
        void camera();
    public:
        EditorState(std::shared_ptr<Window> window,
        std::stack<std::shared_ptr<State>>* states);
        virtual ~EditorState();

        //Functions
        void endState();
        virtual void update(const float& dt);
        virtual void render();
        
    };

}

