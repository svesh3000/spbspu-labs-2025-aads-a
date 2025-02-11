#ifndef SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S1_LIST_NODE_HPP
#define SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S1_LIST_NODE_HPP

namespace kizhin {
  namespace detail {
    template < typename T >
    struct Node
    {
      T data;
      Node* prev;
      Node* next;
    };
  }
}

#endif

