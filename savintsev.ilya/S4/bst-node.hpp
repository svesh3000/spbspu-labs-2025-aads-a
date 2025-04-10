#ifndef BST_NODE_H
#define BST_NODE_H
#include <cstddef>
#include <utility>

namespace savintsev
{
  template< typename Key, typename Value >
  struct Node
  {
    using value_type = std::pair< Key, Value >;
    value_type data_[2];

    Node * sons_[3] = nullptr;
    //Node * midd_ = nullptr;
    //Node * righ_ = nullptr;
    Node * parent_ = nullptr;

    size_t hold_ = 0;
  };
}

#endif
