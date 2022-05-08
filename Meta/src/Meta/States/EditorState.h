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
        bool pause;
        sf::Text mouseCoordinatesText_x;
        sf::Text mouseCoordinatesText_y;
        sf::RectangleShape tileCollision;
        sf::RectangleShape editMapRectangle;
        std::vector<std::vector<sf::RectangleShape>> editmap;
        int tileCode;
        int tileLayer;
        sf::Text text;

        //Functions
        void initEditMap();
        void addTile(const sf::Vector2f& tile);
        void deleteTile(const sf::Vector2f& tile);
        bool tileCollisionCheck(const int& tile_layer);
        const sf::Vector2f& getEditMapCollisionCheck();
        void updateMouseCoordinates();
        void changetileCode();
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

