#ifndef INPUT_PROCESS_HPP
#define INPUT_PROCESS_HPP
#include <list>
#include <sstream>
#include <cctype>
#include "inputProcess.hpp"
#include "list.hpp"
#include "iterators.hpp"

using pair_t = std::pair< std::string, alymova::List< int > >;
using list_pair_t = alymova::List< pair_t >;
using list_pair_citer_t = alymova::ConstIterator< pair_t >;
using list_int_t = alymova::List< int >;
using list_int_iter_t = alymova::Iterator< int >;
using list_int_citer_t = alymova::ConstIterator< int >;

namespace alymova
{
  void inputProcess(std::istream& in, list_pair_t& list);
  void outputProcess(std::ostream& out, const list_pair_t& list);
  size_t findMaxListSize(const list_pair_t& list);
  bool isOverflowSumInt(int a, int b);
}
#endif
