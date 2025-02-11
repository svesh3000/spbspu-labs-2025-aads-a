#ifndef SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S1_LIST_COMPARISON_HPP
#define SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S1_LIST_COMPARISON_HPP

#include "list_fwd.hpp"

namespace kizhin {

  template < typename T >
  bool operator==(const List< T >& lhs, const List< T >& rhs)
  {
    // TODO: Implement operator==
    return true; // stub for tests running
  }

  template < typename T >
  bool operator!=(const List< T >& lhs, const List< T >& rhs)
  {
    return !(lhs == rhs);
  }

  template < typename T >
  bool operator<(const List< T >& lhs, const List< T >& rhs)
  {
    // TODO: Implement operator<
    return true; // stub for tests running
  }

  template < typename T >
  bool operator>(const List< T >& lhs, const List< T >& rhs)
  {
    return rhs < lhs;
  }

  template < typename T >
  bool operator<=(const List< T >& lhs, const List< T >& rhs)
  {
    return !(lhs > rhs);
  }

  template < typename T >
  bool operator>=(const List< T >& lhs, const List< T >& rhs)
  {
    return !(lhs < rhs);
  }
}

#endif

