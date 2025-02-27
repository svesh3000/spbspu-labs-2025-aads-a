#include <iostream>
#include <list>
#include <sstream>
#include <cctype>
#include "inputProcess.hpp"
#include "list.hpp"
#include "iterators.hpp"

int main()
{
  list_pair_t list;
  try
  {
    alymova::inputProcess(std::cin, list);
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << "Allocate error\n";
  }

  if (list.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  alymova::outputListString(std::cout, list);
  std::cout << "\n";

  bool overflow = false;
  list_int_t sums;
  alymova::outputProcess(std::cout, list, sums, overflow);
  if (overflow)
  {
    std::cerr << "Summation is incorrect\n";
    return 1;
  }
  if (sums.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  alymova::outputListInt(std::cout, sums);
  std::cout << "\n";
}
