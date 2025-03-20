#include "sequencefunctions.h"

int main()
{
  sequence_list_t sequences;
  asafov::getSequences(sequences, std::cin);
  if (sequences.empty())
  {
    std::cout << '0' << '\n';
  }
  else
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
