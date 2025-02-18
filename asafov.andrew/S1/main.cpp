#include "sequencefunctions.h"

int main(int argc, char* argv[])
{
  sequence_list_t sequences = asafov::getSequences();
  asafov::outputSequences(sequences);
  return 0;    
}
