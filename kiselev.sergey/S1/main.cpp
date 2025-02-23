#include <exception>
#include <iostream>
#include <stdexcept>
#include "actionsList.hpp"
int main()
{
  try
  {
    list listPairs = kiselev::createList(std::cin);
    kiselev::output(std::cout, listPairs);
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
