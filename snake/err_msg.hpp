#pragma once
#include <iostream>

void error_msg(std::string file, std::string function, std::string message);
void set_on_error_msg();
void set_off_error_msg();
void msg(std::string message);

template<class T>
void msg_no(T value);
