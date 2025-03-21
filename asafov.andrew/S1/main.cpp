#include "sequencefunctions.h"

int main()
{
  asafov::sequence_list_t sequences;
  asafov::getSequences(sequences, std::cin);
  if (!sequences.empty())
  {
    try
    {
      asafov::outputSequences(sequences, std::cout);
    }
    catch (const std::overflow_error&)
    {
      std::cerr << "owerlfow!\n";
      return 0;
    }
  }
  return 0;
}
