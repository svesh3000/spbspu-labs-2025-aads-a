#ifndef SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_COMMON_FORWARD_LIST_COMPARISON_HPP
#define SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_COMMON_FORWARD_LIST_COMPARISON_HPP

#include <algorithm>
#include "forward-list-fwd-declaration.hpp"

namespace kizhin {
  template < typename T >
  bool operator==(const ForwardList< T >& lhs, const ForwardList< T >& rhs)
  {
    return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
  }

  template < typename T >
  bool operator!=(const ForwardList< T >& lhs, const ForwardList< T >& rhs)
  {
    return !(lhs == rhs);
  }

  template < typename T >
  bool operator<(const ForwardList< T >& lhs, const ForwardList< T >& rhs)
  {
    auto first1 = lhs.begin();
    auto first2 = rhs.begin();
    auto last1 = lhs.end();
    auto last2 = rhs.end();
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
      if (*first1 < *first2) {
        return true;
      }
      if (*first2 < *first1) {
        return false;
      }
    }
    return (first1 == last1) && (first2 != last2);
  }

  template < typename T >
  bool operator>(const ForwardList< T >& lhs, const ForwardList< T >& rhs)
  {
    return rhs < lhs;
  }

  template < typename T >
  bool operator<=(const ForwardList< T >& lhs, const ForwardList< T >& rhs)
  {
    return !(lhs > rhs);
  }

  template < typename T >
  bool operator>=(const ForwardList< T >& lhs, const ForwardList< T >& rhs)
  {
    return !(lhs < rhs);
  }
}

#endif

