#pragma once

#include "model-board.hpp"
#include "model-snake.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "view.hpp"

class Controler
{
    int boardSizeX;
    int boardSizeY;
    int windowSizeX;
    int windowSizeY;
    int snakeStartX;
    int snakeStartY;
    float time;
    int timeP;

    Board* board;
    Snake* snake;
    View* view;
    sf::RenderWindow* window;
    void display_info(std::string);
public:
    Controler();
    ~Controler();
    void play();
};
