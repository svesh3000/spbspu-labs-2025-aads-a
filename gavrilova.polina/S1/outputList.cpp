#include "outputList.hpp"
std::ostream& gavrilova::outNames(std::ostream& out, std::forward_list< std::pair< std::string, std::forward_list< int > > > list)
{
  auto ptr = list.begin();
  auto end = list.end();
  out << ptr->first;
  ++ptr;
  while (ptr != end) {
    out << " " << ptr->first; 
    ++ptr;
  }
  out << "\n";
  return out;
}
std::forward_list< int > gavrilova::outNumbers(std::ostream& out, std::forward_list< std::pair< std::string, std::forward_list< int > > > list, size_t maxLen, size_t n)
{
  using fwdlistOfPairs = std::forward_list< std::pair< std::string, std::forward_list< int > > >;
  fwdlistOfPairs::iterator beginList = list.begin();
  std::forward_list< int >::iterator ptr_arr[1000] = {};
  std::forward_list< int >::iterator ptr_end_arr[1000] = {};
  std::forward_list< int > sums = {};

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
    curSum += *ptr_arr[ind];
    ++ptr_arr[ind];
    for (size_t j = ind + 1; j < n; ++j) {
      if (ptr_arr[j] == ptr_end_arr[j]) {
        continue;
      }
      out << " " << *ptr_arr[j];
      curSum += *ptr_arr[j];
      ++ptr_arr[j];
    }
    sums.push_front(curSum);
    out << "\n";
  }
  sums.reverse();
  return sums;
}
std::ostream& gavrilova::outFwdListInt(std::ostream& out, std::forward_list< int > list) {
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
