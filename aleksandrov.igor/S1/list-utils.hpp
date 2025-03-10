#ifndef LIST_UTILS_HPP
#define LIST_UTILS_HPP

#include "list.hpp"
#include <ios>

namespace aleksandrov
{
  unsigned long long calcSum(List< unsigned long long >&);
  void outputList(List< unsigned long long >&, std::ostream&);

  template< class InputIt1, class InputIt2 >
  bool lexicographicalCompare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
  {
    for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
    {
      if (*first1 < *first2)
      {
        return true;
      }
      if (*first2 < *first1)
      {
        return false;
      }
    }
    return (first1 == last1) && (first2 != last2);
  }
}

#endif

