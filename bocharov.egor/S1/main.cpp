#include <iostream>
#include "actions.hpp"

int main()
{
  try
  {
    bocharov::pairs_list_t pairs_list = bocharov::createList(std::cin);
    bocharov::outputList(std::cout, pairs_list);
    bocharov::print_lists_info(std::cout, pairs_list);
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Memory allocation error\n";
    return 1;
  }
  catch (const std::overflow_error &)
  {
    std::cerr << "Overflow error\n";
    return 1;
  }
  std::cout << '\n';
}
