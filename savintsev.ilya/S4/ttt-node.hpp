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
    value_type data_[2];

    node_t * left_ = nullptr;
    node_t * midd_ = nullptr;
    node_t * righ_ = nullptr;
    node_t * parent_ = nullptr;

    size_t len_ = 0;
    size_t sons_ = 0;
  };
}

#endif
