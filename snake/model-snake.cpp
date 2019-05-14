#include "model-snake.hpp"
#include <iostream>
#include <fstream>
Snake::Snake(Board* board, Direction direction, LocationXY head_location)
{
    IsGameRunning = false;

    this->board = board;
    snake.push_back(head_location);
    board->set_snake(&head_location);
    headxy = &snake.front();
    this->direction = direction;

    for (int i = 1; i <= 3; ++i)
    {
        LocationXY locationxy = *headxy;
        switch (direction)
        {
            case Direction::LEFT:
                locationxy.first += i;
                break;
            case Direction::RIGHT:
                locationxy.first -= i;
                break;
            case Direction::UP:
                locationxy.second += i;
                break;
            case Direction::DOWN:
                locationxy.second -= i;
                break;
        }
        snake.push_back(locationxy);
        board->set_snake(&locationxy);
    }
    tailxy = &snake.back();
    score = 0;
    highScore = 0;
    loadHighScore();
}

Snake::~Snake()
{
    if (score >= highScore)
        saveHighScore();
}

bool Snake::set_food()
{
    srand( time( NULL ) );
    bool flag = true;
    do {
        int x = std::rand() % board->getBoardSize().first;
        int y = std::rand() % board->getBoardSize().second;
        LocationXY locationx = {x, y};

        if (     board->isOnBoard(&locationx) and
                !board->is_wall(&locationx)   and
                !board->is_snake(&locationx)  and
                !board->is_food(&locationx)) {
            flag = false;
            food.push(locationx);
            board->set_food(&locationx);
            msg("FOOD SETTED");
            return true;
        }
    } while (flag);
    return true;
}

bool Snake::canTurn(Direction direction) const
{
    switch (this->direction)
    {
        case Direction::LEFT:
            if (direction == Direction::UP) return true;
            if (direction == Direction::DOWN) return true;
            return false;
        case Direction::RIGHT:
            if (direction == Direction::UP) return true;
            if (direction == Direction::DOWN) return true;
            return false;
        case Direction::UP:
            if (direction == Direction::LEFT) return true;
            if (direction == Direction::RIGHT) return true;
            return false;
        case Direction::DOWN:
            if (direction == Direction::LEFT) return true;
            if (direction == Direction::RIGHT) return true;
            return false;
    }
    return false;
}

BoardField Snake::getFieldInfo(LocationXY* location) const
{
    if (!board->isOnBoard(location)) return BoardField::ERROR;
    if (board->is_wall(location)) return BoardField::WALL;
    if (    board->is_snake(location) and
            (headxy->first != location->first or
            headxy->second != location->second)) return BoardField::SNAKE;
    if (board->is_food(location)) return BoardField::FOOD;
    if (headxy->first == location->first and
        headxy->second == location->second) return BoardField::SNAKE_HEAD;
    return BoardField::EMPTY;
}

LocationXY Snake::getFeatureField() const
{
    int newHeadX;
    int newHeadY;
    switch (direction)
    {
        case Direction::LEFT:
            newHeadX = headxy->first-1;
            newHeadY = headxy->second;
            break;
        case Direction::RIGHT:
            newHeadX = headxy->first+1;
            newHeadY = headxy->second;
            break;
        case Direction::UP:
            newHeadX = headxy->first;
            newHeadY = headxy->second-1;
            break;
        case Direction::DOWN:
            newHeadX = headxy->first;
            newHeadY = headxy->second+1;
            break;
    }
    return LocationXY(newHeadX, newHeadY);
}

LocationXY Snake::getHead() const
{
    return *headxy;
}

bool Snake::isGameRunning() const
{
    return IsGameRunning;
}

void Snake::saveHighScore()
{
    std::ofstream out;
    out.open("highScore.txt");
    if (out.is_open())
        out << highScore;
    out.close();
}

void Snake::loadHighScore()
{
    std::ifstream in;
    in.open("highScore.txt");
    int value;
    if (in.is_open())
        while (!in.eof())
            in >> value;
    in.close();

    if (value <= (board->getBoardSize().first-2) * (board->getBoardSize().second-2))
        highScore = value;
    else error_msg("model-snake", "loadHighScore", "Wrong Score");
}

void Snake::moveSnake(LocationXY* newField)
{
    snake.push_front(*newField);
    board->set_snake(newField);
    headxy = &snake.front();
    if (    food.front().first == headxy->first and
            food.front().second == headxy->second) {
        food.pop();
        score++;
    }
    else {
        board->remove_snake(&snake.back());
        snake.pop_back();
        tailxy = &snake.back();
    }

    if (score > highScore)
    {
        highScore = score;
    }
}
bool Snake::move()
{
    return move(direction);
}

void Snake::start()
{
    set_food();
    IsGameRunning = true;
}

bool Snake::move(Direction direct)
{
    if (!isGameRunning()) return false;
    if (canTurn(direct)) direction = direct;
    LocationXY newField = getFeatureField();
    switch (getFieldInfo(&newField))
    {
        case BoardField::EMPTY:
            moveSnake(&newField);
            break;
        case BoardField::WALL:
            IsGameRunning = false;
            return false;
        case BoardField::SNAKE:
            IsGameRunning = false;
            return false;
        case BoardField::FOOD:
            board->remove_food(&newField);
            moveSnake(&newField);
            set_food();
            break;
        case BoardField::ERROR:
            error_msg("model.cpp", "Snake::move", "Error from function move Snake");
            return false;
        case BoardField::SNAKE_HEAD:
            break;
    }
    return true;
}

bool Snake::isWin() const
{
    if (snake.size() == (board->getBoardSize().first-2) * (board->getBoardSize().second-2)){

        std::cout << "YOU WIN" << std::endl;
        return true;
    }
    return false;
}

int Snake::getScore() const
{
    return score;
}

int Snake::getHighScore() const
{
    return highScore;
}
