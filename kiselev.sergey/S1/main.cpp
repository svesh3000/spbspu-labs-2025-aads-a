#include <iostream>
#include <stdexcept>
#include "actionsList.hpp"
int main()
{
  list list;
  try
  {
    kiselev::createList(std::cin, list);
    kiselev::output(std::cout, list);
    return 0;
  }
  catch (const std::overflow_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
