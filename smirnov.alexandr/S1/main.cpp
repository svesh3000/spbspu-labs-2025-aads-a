#include <iostream>
#include <stdexcept>
#include "list.hpp"
#include "list"
#include "read_sequences.hpp"
#include "print_results.hpp"

int main()
{
  using namespace smirnov;
  try
  {
    std::list< std::pair< std::string, std::list< size_t > > > sequences;
    readSequences(std::cin, sequences);
    if (sequences.empty())
    {
      std::cout << 0 << "\n";
      return 0;
    }
    printName(std::cout, sequences);
    std::list< std::list< size_t > > resultSequences;
    newSequences(resultSequences, sequences);
    if (!resultSequences.empty())
    {
      printSequences(std::cout, resultSequences);
    }
    printSums(std::cout, resultSequences);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
