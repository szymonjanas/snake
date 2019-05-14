#pragma once

#include <queue>
#include <deque>
#include <ctime>
#include "err_msg.hpp"

using LocationXY = std::pair<int, int>;
using BoardSizeXY = std::pair<int, int>;

struct Field
{
    bool is_wall;
    bool is_food;
    bool is_snake;
};

enum class Direction {LEFT, RIGHT, UP, DOWN};
enum class BoardField{SNAKE_HEAD, FOOD, SNAKE, WALL, EMPTY, ERROR};
class Board
{
    const int board_size_X;
    const int board_size_Y;
    Field board[100][100];
    std::vector<Field*> snake;
    bool moveSnake();
public:
    Board(int,int);
    bool isOnBoard(LocationXY*) const;
    BoardField getBoardFieldInfo(LocationXY) const;
    BoardSizeXY getBoardSize() const;
    bool is_wall (LocationXY*) const;
    bool is_food (LocationXY*) const;
    bool is_snake(LocationXY*) const;
    bool set_snake(LocationXY*);
    bool remove_snake(LocationXY*);
    bool set_food(LocationXY*);
    bool remove_food(LocationXY*);
    void clear_snake();
};
