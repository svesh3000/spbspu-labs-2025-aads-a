#ifndef SEQUENCEFUNCTIOANS_H
#define SEQUENCEFUNCTIOANS_H
#include "sequenceusings.h"
#include <iostream>
namespace asafov
{
  void getSequences(sequence_list_t& sequences, std::istream& in);
  void outputSequences(sequence_list_t& sequences, std::ostream& out);
}
#endif
