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
    alymova::outputProcess(std::cout, list);
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << "Allocate error\n";
  }
  catch (const std::logic_error& e)
  {
    std::cerr << "Incorrect sum\n";
    return 1;
  }
}
