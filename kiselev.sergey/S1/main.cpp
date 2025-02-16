#include <exception>
#include <iostream>
#include <list>
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
    std::cerr << e.what() << "\n";
    return 1;
  }
}
