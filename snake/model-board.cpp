#include "model-board.hpp"

Board::Board(int sizeX, int sizeY) :
    board_size_X(sizeX), board_size_Y(sizeY)
{
    for (int x = 0; x < board_size_X; ++x )
        for (int y = 0; y < board_size_Y; ++y)
        {
            Field field = {false, false, false};
            board[x][y] = field;
        }
    for (int x = 0; x < board_size_X; ++x)
        board[x][0].is_wall = true;
    for (int x = 0; x < board_size_X; ++x)
        board[x][board_size_Y-1].is_wall = true;
    for (int y = 0; y < board_size_Y; ++y)
        board[0][y].is_wall = true;
    for (int y = 0; y < board_size_Y; ++y)
        board[board_size_X-1][y].is_wall = true;
}

bool Board::isOnBoard(LocationXY* location) const
{
    int x = location->first;
    int y = location->second;
    if (x >= 0 and y >= 0 and x < board_size_X and y < board_size_Y)
        return true;
    else return false;
}

BoardSizeXY Board::getBoardSize() const
{
    BoardSizeXY sizexy;
    sizexy.first = board_size_X;
    sizexy.second = board_size_Y;
    return sizexy;
}

BoardField Board::getBoardFieldInfo(LocationXY location) const
{
    if (!isOnBoard(&location)) return BoardField::ERROR;
    if (board[location.first][location.second].is_wall) return BoardField::WALL;
    if (board[location.first][location.second].is_food) return BoardField::FOOD;
    if (board[location.first][location.second].is_snake) return BoardField::SNAKE;
    return BoardField::EMPTY;
}

bool Board::set_snake(LocationXY* location)
{
    if(!board[location->first][location->second].is_wall and isOnBoard(location))
    {
        board[location->first][location->second].is_snake = true;
        return true;
    }
    else return false;
}

bool Board::remove_snake(LocationXY * location)
{
    if(isOnBoard(location) and board[location->first][location->second].is_snake)
        board[location->first][location->second].is_snake = false;
    else return false;
    return true;
}

bool Board::is_wall(LocationXY* location) const
{
    if (isOnBoard(location))
        return board[location->first][location->second].is_wall;
    return false;
}

bool Board::is_food(LocationXY* location) const
{
    if (isOnBoard(location))
        return board[location->first][location->second].is_food;
    return false;
}

bool Board::is_snake(LocationXY * location) const
{
    if (isOnBoard(location) and !is_wall(location))
        return board[location->first][location->second].is_snake;
    return false;
}

bool Board::remove_food(LocationXY * location)
{
    if (!isOnBoard(location)) return false;
    if (board[location->first][location->second].is_food){
        board[location->first][location->second].is_food = false;
        msg("FOOD REMOVED");
    }
    else return false;
    return true;
}

bool Board::set_food(LocationXY * location)
{
    if(isOnBoard(location) and !board[location->first][location->second].is_food)
        board[location->first][location->second].is_food = true;
    else return false;
    return true;
}


