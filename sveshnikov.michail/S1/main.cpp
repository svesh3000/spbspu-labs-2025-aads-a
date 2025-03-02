#include <iostream>
#include "io-sequences.hpp"

int main()
{
  using namespace sveshnikov;
  list_pair_t list;
  try
  {
    inputLists(std::cin, list);
  }
  catch (const std::bad_alloc &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  if (list.empty())
  {
    std::cerr << "ERROR: Input is empty!\n";
    return 1;
  }
  outputNamesLists(std::cout, list) << '\n';
  outputNewLists(std::cout, list) << '\n';
  try
  {
    outputSumsNewLists(std::cout, list) << '\n';
  }
  catch(const std::overflow_error& e)
  {
    std::cerr << e.what() << '\n';
  }
  return 0;
}
