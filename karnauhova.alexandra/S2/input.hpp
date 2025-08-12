#ifndef INPUT_HPP
#define INPUT_HPP

#include <iostream>
#include <fstream>
#include "calc_post.hpp"
#include "stack.hpp"
#include "queue.hpp"

namespace karnauhova
{
    Queue< std::string > split_str(std::string str);
    Stack< long long int > input_str(std::istream& in);
    Queue< std::string > to_post(Queue< std::string > inf);
}

#endif
