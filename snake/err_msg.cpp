#include "err_msg.hpp"

static bool error_status = false;

void error_msg(std::string file, std::string function, std::string message)
{
    if (error_status)
    std::cerr << "> ERROR MESSAGE BEGIN! "
              << std::endl << "      - IN FILE:       " << file
              << std::endl << "      - IN FUNCTION:   " << function
              << std::endl << "      - ERROR MESSAGE: " << message << std::endl
              << "> ERROR MESSAGE END!" << std::endl;
}

void set_on_error_msg()
{
    error_status = true;
}

void set_off_error_msg()
{
    error_status = false;
}

void msg(std::string message)
{
    if (error_status)
        std::cout << "> MESSAGE BEGIN: " << std::endl <<
                     "      MESSAGE:    "  << message << std::endl <<
                     "> MESSAGE END." << std::endl;
}

template <typename T>
void msg_no(T value)
{
    if (error_status)
    std::cout << "> MESSAGE VALUE BEGIN: " << std::endl <<
                 "      - VALUE:    " << value << std::endl <<
                 "> MESSAGE VALUE END." << std::endl;
}
