#include "sequencefunctions.h"

int main()
{
  sequence_list_t sequences = asafov::getSequences();
  asafov::outputSequences(sequences);
  return 0;
}
