#ifndef SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S1_FORWARD_LIST_COMPARISON_HPP
#define SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S1_FORWARD_LIST_COMPARISON_HPP

#include "forward-list-fwd-declaration.hpp"

namespace kizhin {

  template < typename T >
  bool operator==(const ForwardList< T >& lhs, const ForwardList< T >& rhs)
  {
    // TODO: Implement operator==
    return true; // stub for tests running
  }

  template < typename T >
  bool operator!=(const ForwardList< T >& lhs, const ForwardList< T >& rhs)
  {
    return !(lhs == rhs);
  }

  template < typename T >
  bool operator<(const ForwardList< T >& lhs, const ForwardList< T >& rhs)
  {
    // TODO: Implement operator<
    return true; // stub for tests running
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

