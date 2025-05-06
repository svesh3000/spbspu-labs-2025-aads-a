#ifndef TTT_NODE_H
#define TTT_NODE_H
#include <cstddef>
#include <utility>

namespace savintsev
{
  template< typename Key, typename Value >
  struct node_t
  {
    using value_type = std::pair< Key, Value >;
    value_type data_;

    node_t * left_ = nullptr;
    node_t * right_ = nullptr;
    node_t * parent_ = nullptr;

    size_t height_ = 1;
  };
}

#endif
