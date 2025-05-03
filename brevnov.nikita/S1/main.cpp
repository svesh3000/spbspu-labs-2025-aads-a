#include <exception>
#include "listact.hpp"
int main()
{
  try
  {
    brevnov::list listpair = brevnov::createList(std::cin);
    if (listpair.empty())
    {
      std::cout << "0\n";
      return 0;
    }
    outputName(std::cout, listpair) << "\n";
    if (listpair.front().second.empty())
    {
      std::cout << "0\n";
      return 0;
    }
    outputNumbers(std::cout, listpair);
    brevnov::numberList sum = calculateSum(listpair);
    outputNumber(std::cout, sum) << "\n";
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
