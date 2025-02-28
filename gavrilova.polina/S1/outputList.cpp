#include "outputList.hpp"
#include <limits>

namespace {
  unsigned long long addition (size_t first, size_t second) {
    unsigned long long MAX_OF_SIZET = std::numeric_limits<unsigned long long>::max();
    if (first > MAX_OF_SIZET - second) {
      throw std::overflow_error("Overflow.\n");
    }
    return first + second;
  }
}
std::ostream& gavrilova::outNames(std::ostream& out, gavrilova::FLPairs list)
{
  auto ptr = list.begin();
  auto end = list.end();
  if (ptr == end) {
    return out;
  }
  out << ptr->first;
  ++ptr;
  while (ptr != end) {
    out << " " << ptr->first;
    ++ptr;
  }
  out << "\n";
  return out;
}
std::forward_list< unsigned long long > gavrilova::outNumbers(std::ostream& out, gavrilova::FLPairs list, size_t maxLen, size_t n)
{
  using fwdlistOfPairs = std::forward_list< std::pair< std::string, std::forward_list< ULL > > >;
  fwdlistOfPairs::iterator beginList = list.begin();
  std::forward_list< ULL >::iterator ptr_arr[1000] = {};
  std::forward_list< ULL >::iterator ptr_end_arr[1000] = {};
  std::forward_list< ULL > sums = {};

  fwdlistOfPairs::iterator ptr = beginList;
  for (size_t i = 0; i < n; ++i) {
    ptr_arr[i] = ptr->second.begin();
    ptr_end_arr[i] = ptr->second.end();
    ++ptr;
  }
  for (size_t i = 0; i < maxLen; ++i) {
    size_t curSum = 0;
    size_t ind = 0;
    while (ptr_arr[ind] == ptr_end_arr[ind]) {
      ++ind;
    }
    out << *ptr_arr[ind];
    curSum = addition(curSum, *ptr_arr[ind]);
    ++ptr_arr[ind];
    for (size_t j = ind + 1; j < n; ++j) {
      if (ptr_arr[j] == ptr_end_arr[j]) {
        continue;
      }
      out << " " << *ptr_arr[j];
      curSum = addition(curSum, *ptr_arr[j]);
      ++ptr_arr[j];
    }
    sums.push_front(curSum);
    out << "\n";
  }
  sums.reverse();
  return sums;
}
std::ostream& gavrilova::outFwdListULL(std::ostream& out, std::forward_list< ULL > list) {
  auto ptr = list.begin();
  auto end = list.end();
  out << *ptr;
  ++ptr;
  while (ptr != end) {
    out << " " << *ptr;
    ++ptr;
  }
  out << "\n";
  return out;
}
