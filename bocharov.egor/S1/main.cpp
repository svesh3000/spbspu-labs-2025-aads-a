#include <iostream>
#include "actions.hpp"

int main()
{
  bocharov::pairs_list_t pairs_list = bocharov::createList(std::cin);
  if (pairs_list.empty())
  {
    std::cout << 0 << '\n';
    return 0;
  }
  bocharov::outputList(std::cout, pairs_list);
  try
  {
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
