#ifndef SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S1_LIST_SWAP_HPP
#define SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S1_LIST_SWAP_HPP

#include "list_fwd.hpp"

namespace kizhin {
  template < typename T >
  void swap(List< T >& lhs, List< T >& rhs) noexcept
  {
    lhs.swap(rhs);
  }
}

#endif

