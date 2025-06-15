#ifndef NODE_TREE_HPP
#define NODE_TREE_HPP
#include <utility>

namespace smirnov
{
  template < typename Key, typename Value >
  struct NodeTree
  {
    std::pair< const Key, Value > data;
    NodeTree * left;
    NodeTree * right;
    NodeTree * parent;
    int height;

    NodeTree(const Key & key, const Value & value):
      data(key, value),
      left(nullptr),
      right(nullptr),
      parent(nullptr),
      height(1)
    {}
  };
}
#endif
