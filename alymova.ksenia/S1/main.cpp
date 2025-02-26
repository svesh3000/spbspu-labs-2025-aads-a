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
  alymova::inputProcess(std::cin, list);
  alymova::outputProcess(std::cout, list);
}
