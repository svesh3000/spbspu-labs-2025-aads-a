#ifndef NODE_TTT_HPP
#define NODE_TTT_HPP

#include <cstddef>
#include <utility>

namespace gavrilova {
  template < class Key, class Value >
  struct NodeTwoThreeTree {
    using this_t = NodeTwoThreeTree< Key, Value >;

    std::pair< Key, Value > data[2];
    this_t* children[3];
    this_t* parent;
    bool is_3_node;
    bool is_fake;

    NodeTwoThreeTree():
      parent(nullptr),
      is_3_node(false),
      is_fake(false)
    {
      children[0] = children[1] = children[2] = nullptr;
      data[0] = data[1] = std::pair< Key, Value >();
    }

    bool is_leaf()
    {
      return children[0]->is_fake;
    }
  };
}

#endif
