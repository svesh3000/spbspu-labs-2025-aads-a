#ifndef READ_SEQUENCES_HPP
#define READ_SEQUENCES_HPP
#include <forward_list>
#include <string>

namespace sveshnikov
{
  std::forward_list < std::pair < std::string, std::forward_list<int> * > > *readSequences(std::istream &in);
}

#endif