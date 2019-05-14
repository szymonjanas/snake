#include <iostream>
#include "controler.hpp"
#include "view.hpp"
#include "model-board.hpp"
#include "model-snake.hpp"
#include "err_msg.hpp"

int main ()
{
    //set_on_error_msg();
    error_msg("MAIN", "MAIN", "TEST ERROR MESSAGE");
    Controler ctrl;
    ctrl.play();

    return 0;
}
