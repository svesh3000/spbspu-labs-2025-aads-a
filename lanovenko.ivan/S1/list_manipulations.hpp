#ifndef LIST_MANIPULATIONS_HPP
#define LIST_MANIPULATIONS_HPP

#include <list>
#include <string>
#include <ostream>
#include <limits>
namespace lanovenko
{
  void printSequencesName(const std::list<std::pair<std::string, std::list<unsigned long long>>> temporary, std::ostream& out);
  bool isSumLimit(size_t a, size_t b);
  void printSumList(const std::list<int>& sumList, bool sumLimit, std::ostream& out);
  void printSequences(const std::list < std::pair < std::string, std::list<unsigned long long>>> temporary, size_t maxSize, bool& sumLimit, std::ostream& out);
}

#endif
