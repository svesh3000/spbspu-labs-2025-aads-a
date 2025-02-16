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
    if (list.front().second.empty() || list.empty())
    {
      std::cout << "0\n";
      return 0;
    }
    kiselev::output(std::cout, list);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
