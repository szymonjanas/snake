#pragma once

#include <queue>
#include <deque>
#include <ctime>
#include "err_msg.hpp"

#include "model-board.hpp"

class Snake
{
    Board* board;
    LocationXY* headxy;
    LocationXY* tailxy;
    Direction direction;

    std::deque<LocationXY> snake;
    std::queue<LocationXY> food;

    bool IsGameRunning;
    int score;
    int highScore;
    void saveHighScore();
    void loadHighScore();

    bool canTurn(Direction direction) const;
    LocationXY getFeatureField() const;
    void moveSnake(LocationXY* newField);
    bool set_food();
public:
    Snake(Board*, Direction, LocationXY);
    ~Snake();
    LocationXY getHead() const;
    bool isGameRunning() const;
    bool move(Direction);
    bool move();
    void start();
    BoardField getFieldInfo(LocationXY*) const;
    bool isWin() const;
    int getScore() const;
    int getHighScore() const;

};
