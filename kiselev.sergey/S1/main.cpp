#include <exception>
#include <iostream>
#include <list>
#include <stdexcept>
#include "workFlows.hpp"
int main()
{
  list list;
  try
  {
    kiselev::createList(std::cin, list);
    kiselev::output(std::cout, list);
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << "\n";
    return 1;
  }
}
