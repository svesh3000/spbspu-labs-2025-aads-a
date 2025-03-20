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
      return 1;
    }
  }
  return 0;
}
