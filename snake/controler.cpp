#include "controler.hpp"

Controler::Controler()
{
     boardSizeX = 41;
     boardSizeY = 41;
     windowSizeX = 760;
     windowSizeY = 430;
     snakeStartX = 30;
     snakeStartY = 20;
    board = new Board (boardSizeX, boardSizeY);
    snake = new Snake (board, Direction::LEFT, LocationXY(snakeStartX,snakeStartY));
    window = new sf::RenderWindow (sf::VideoMode(windowSizeX, windowSizeY), "SNAKE");
}

Controler::~Controler()
{
    delete board;
    delete snake;
}

void Controler::display_info(std::string gameStatus)
{
    std::string info =  "         WELCOME TO SNAKE      \n"
                        "Quick guide: \n"
                        "- to start game press space \n"
                        "- to steer use arrows buttons \n"
                        "- to restart use backspace \n"
                        "STATUS OF YOUR GAME:   \n\n"
                        "SCORE: \n\n"
                        "HIGH SCORE: \n\n"
                        "GAME SPEED: \n\n "
                        "To change Game Speed press: \n"
                        " + PageUp\n"
                        " - PageDown \n"
                        "WARNING! If you change Game Speed: \n"
                        " - be patient \n "
                        "- restart can be needed \n"
                        " - game can work not smoothly \n"
                        " - game works properly between 50% and 150% ";
    std::string author = " Game made by: Szymon Janas 249271";
    int authorPosY = 10;
    int infoPosY = 30;
    int infoLong = 100;
    int statusGamePosY = infoLong+30;
    int scorePosY = infoLong + 62;
    int highScorePosY = infoLong + 95;
    int gameSpeed = highScorePosY + 35;
    view->draw_info(info,infoPosY);
    view->draw_info(author, authorPosY);
    view->draw_info(std::to_string(snake->getScore()), scorePosY);
    view->draw_info(std::to_string(snake->getHighScore()), highScorePosY);
    view->draw_info(std::to_string(timeP) + " %", gameSpeed);
    view->draw_info(gameStatus,statusGamePosY);
}

void Controler::play()
{
   // const unsigned int FPS = 10;
   // window->setFramerateLimit(FPS);
    view = new View (board, snake, window);
    bool wasMoved = true;
    bool start = false;
    bool flagIsLoose = true;
    sf::Clock clock;
    time = 0.07f;
    timeP = 100;

    window->clear();
    display_info("Welcome screen");
    view->display();
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                exit(1);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                if (!snake->isGameRunning()){
                    snake->start();
                    start = true;
                    msg("EVENT START");
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)){
                    delete board;
                    delete snake;
                    board = new Board (boardSizeX, boardSizeY);
                    snake = new Snake (board, Direction::LEFT, LocationXY(snakeStartX,snakeStartY));
                    msg("EVENT RESTART");
                    wasMoved = true;
                    start = false;
                    flagIsLoose = true;
                    delete view;
                    view = new View(board, snake, window);
                    window->clear();
                    display_info("After restart");
                    view->display();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)){
                msg("EVENT GAME FASTER");
                time -= 0.007f;
                timeP+= 10;
                window->clear();
                display_info("Game Speed Faster");
                view->display();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)){
                msg("EVENT GAME SLOWER");
                time += 0.007f;
                timeP-=10;
                window->clear();
                display_info("Game Speed Slower");
                view->display();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                msg("EVENT TURN LEFT");
                snake->move(Direction::LEFT);
                wasMoved = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                msg("EVENT TURN RIGHT");
                snake->move(Direction::RIGHT);
                wasMoved = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                msg("EVENT  TURN UP");
                snake->move(Direction::UP);
                wasMoved = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                msg("EVENT TURN DOWN");
                snake->move(Direction::DOWN);
                wasMoved = false;
            }
        }

        if (wasMoved and snake->isGameRunning()) {
            snake->move();
        }
        while (clock.getElapsedTime().asSeconds() < time)
            if (clock.getElapsedTime().asSeconds() > time)
                clock.restart();

        wasMoved = true;
        if (snake->isGameRunning())
        {
            window->clear();
            display_info("Running");
            view->display();
            clock.restart();
        }
        if (snake->isWin())
        {
            window->clear();
            display_info("You Win");
            view->display();
        }
        if (!snake->isGameRunning() and start and flagIsLoose)
        {
            window->clear();
            display_info("You loose");
            view->display();
            flagIsLoose = false;
        }
    }
    delete view;
}

