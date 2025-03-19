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
    asafov::outputSequences(sequences, std::cout);
  }
  return 0;
}
