#pragma once

#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

#include "model-board.hpp"
#include "model-snake.hpp"

class View
{
    Board* board;
    Snake* snake;
    sf::RenderWindow* window;

    sf::Font font;
    sf::Text text;

    int fieldSizeX;
    int fieldSizeY;

    void drawEmptyField(LocationXY*);
    void drawSnakeField(LocationXY*);
    void drawSnakeHeadField(LocationXY*);
    void drawFoodField(LocationXY*);
    void drawErrorField(LocationXY*);
    void drawWallField(LocationXY*);

    LocationXY convertFieldToView(LocationXY);

public:
    View(Board*, Snake*, sf::RenderWindow*);
    void display();
    void draw_info(std::string, int);
};
