#include "view.hpp"

View::View(Board* board, Snake* snake, sf::RenderWindow* window)
{
    this->board = board;
    this->snake = snake;
    this->window = window;
    fieldSizeX = 10;
    fieldSizeY = 10;

    font.loadFromFile("../game_over.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(30);
}

LocationXY View::convertFieldToView(LocationXY location)
{
    int x0 = 10;
    int y0 = 10;
    int x = location.first*fieldSizeX + x0;
    int y = location.second*fieldSizeY + y0;
    return  LocationXY(x, y);
}

void View::drawEmptyField(LocationXY* location)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(fieldSizeX, fieldSizeY));
    rectangle.setPosition(location->first, location->second);
    rectangle.setFillColor(sf::Color(153, 255, 102));
    rectangle.setOutlineThickness(0.5);
    rectangle.setOutlineColor(sf::Color::White);
    window->draw(rectangle);
}
void View::drawSnakeField(LocationXY* location)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(fieldSizeX, fieldSizeY));
    rectangle.setPosition(location->first, location->second);
    rectangle.setFillColor(sf::Color(51, 102, 0));
    rectangle.setOutlineThickness(0.5);
    rectangle.setOutlineColor(sf::Color::White);
    window->draw(rectangle);
}
void View::drawSnakeHeadField(LocationXY* location)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(fieldSizeX, fieldSizeY));
    rectangle.setPosition(location->first, location->second);
    rectangle.setFillColor(sf::Color(0, 51, 0));
    rectangle.setOutlineThickness(0.5);
    rectangle.setOutlineColor(sf::Color::White);
    window->draw(rectangle);
}
void View::drawFoodField(LocationXY* location)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(fieldSizeX, fieldSizeY));
    rectangle.setPosition(location->first, location->second);
    rectangle.setFillColor(sf::Color(255, 51, 0));
    rectangle.setOutlineThickness(0.5);
    rectangle.setOutlineColor(sf::Color::White);
    window->draw(rectangle);
}
void View::drawErrorField(LocationXY* location)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(fieldSizeX, fieldSizeY));
    rectangle.setPosition(location->first, location->second);
    rectangle.setFillColor(sf::Color::White);
    rectangle.setOutlineThickness(0.5);
    rectangle.setOutlineColor(sf::Color::Blue);
    window->draw(rectangle);
}

void View::drawWallField(LocationXY* location)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(fieldSizeX, fieldSizeY));
    rectangle.setPosition(location->first, location->second);
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setOutlineThickness(0.5);
    rectangle.setOutlineColor(sf::Color(96, 64, 31));
    window->draw(rectangle);
}

void View::draw_info(std::string info, int posY)
{
    text.setString(info);
    text.setPosition(board->getBoardSize().first*fieldSizeX+20+40,posY);

    window->draw(text);
}


void View::display()
{
    for (int y = 0; y < board->getBoardSize().second; ++y)
        for (int x = 0; x < board->getBoardSize().first; ++x){
            LocationXY location = {x, y};
            LocationXY viewLocation = convertFieldToView(location);
            switch (snake->getFieldInfo(&location)) {
                case BoardField::EMPTY: drawEmptyField(&viewLocation);
                   break;
                case BoardField::WALL: drawWallField(&viewLocation);
                    break;
                case BoardField::FOOD: drawFoodField(&viewLocation);
                    break;
                case BoardField::SNAKE: drawSnakeField(&viewLocation);
                    break;
                case BoardField::SNAKE_HEAD: drawSnakeHeadField(&viewLocation);
                    break;
                case BoardField::ERROR: drawErrorField(&location);
                    break;
            }
        }
    window->display();
}

