#include <exception>
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
    if (list.front().second.empty())
    {
      std::cout << "0\n";
      return 0;
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
