#include "outputList.hpp"
#include <limits>

namespace {
  unsigned long long addition(unsigned long long first, unsigned long long second)
  {
    unsigned long long MAX_OF_ULL = std::numeric_limits< unsigned long long >::max();
    if (first > MAX_OF_ULL - second) {
      throw std::overflow_error("Overflow.\n");
    }
    return first + second;
  }

  template < typename T, typename Selector >
  std::ostream& outputListElements(std::ostream& out, const T& list, Selector select)
  {
    auto ptr = list.begin();
    auto end = list.end();
    if (ptr == end) {
      return out;
    }
    out << select(*ptr);
    ++ptr;
    while (ptr != end) {
      out << " " << select(*ptr);
      ++ptr;
    }
    return out;
  }
}

std::ostream& gavrilova::outNames(std::ostream& out, gavrilova::FLPairs list)
{
  return outputListElements(out, list, [](const auto& pair) { return pair.first; });
}

std::ostream& gavrilova::outFwdListULL(std::ostream& out, const FwdList< ULL >& list)
{
  return outputListElements(out, list, [](const auto& value) { return value; });
}

gavrilova::FwdList< unsigned long long > gavrilova::outNumbers(std::ostream& out, FLPairs list, size_t maxLen, size_t n)
{
  FwdList< IteratorFwd< ULL > > ptr_list;
  FwdList< IteratorFwd< ULL > > ptr_end_list;
  FwdList< ULL > sums;

  auto ptr = list.begin();
  for (size_t i = 0; i < n && ptr != list.end(); ++i, ++ptr) {
    ptr_list.push_front(ptr->second.begin());
    ptr_end_list.push_front(ptr->second.end());
  }
  ptr_list.reverse();
  ptr_end_list.reverse();

  auto sums_tail = sums.begin();

  for (size_t i = 0; i < maxLen; ++i) {
    ULL curSum = 0;
    bool all_empty = true;
    bool first_element = true;

    auto current_ptr = ptr_list.begin();
    auto current_end = ptr_end_list.begin();

    while (current_ptr != ptr_list.end()) {
      if (*current_ptr != *current_end) {
        all_empty = false;
        out << (first_element ? "" : " ") << **current_ptr;
        first_element = false;

        curSum = addition(curSum, **current_ptr);

        ++(*current_ptr);
      }
      ++current_ptr;
      ++current_end;
    }

    if (all_empty) {
      break;
    }

    sums_tail = sums.insert(sums_tail, curSum);
  }

  return sums;  // Теперь суммы уже в правильном порядке
  // auto beginList = list.begin();
  // IteratorFwd< ULL > ptr_arr[1000] = {};
  // IteratorFwd< ULL > ptr_end_arr[1000] = {};
  // FwdList< ULL > sums = {};

  // auto ptr = beginList;
  // for (size_t i = 0; i < n; ++i) {
  //   ptr_arr[i] = ptr->second.begin();
  //   ptr_end_arr[i] = ptr->second.end();
  //   ++ptr;
  // }
  // for (size_t i = 0; i < maxLen; ++i) {
  //   ULL curSum = 0;
  //   size_t ind = 0;
  //   while (ind < n && ptr_arr[ind] == ptr_end_arr[ind]) {
  //     ++ind;
  //   }
  //   if (ind == n) {
  //     break;
  //   }
  //   out << *ptr_arr[ind];
  //   curSum = addition(curSum, *ptr_arr[ind]);
  //   ++ptr_arr[ind];
  //   for (size_t j = ind + 1; j < n; ++j) {
  //     if (ptr_arr[j] == ptr_end_arr[j]) {
  //       continue;
  //     }
  //     out << " " << *ptr_arr[j];
  //     curSum = addition(curSum, *ptr_arr[j]);
  //     ++ptr_arr[j];
  //   }
  //   if (i < maxLen - 1) {
  //     out << "\n";
  //   }
  //   sums.push_front(curSum);
  // }
  // sums.reverse();
  // return sums;
}
