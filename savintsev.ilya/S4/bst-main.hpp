#ifndef BST_MAIN_HPP
#define BST_MAIN_HPP
#include "bst-node.hpp"

namespace savintsev
{
  template< typename Key, typename Value, typename Compare >
  class BinSearchTree
  {
  public:
    BinSearchTree();
  private:
    Node< Key, Value, Compare > * head_;
    size_t size_;
  };

  template< typename Key, typename Value, typename Compare >
  BinSearchTree< Key, Value, Compare >::BinSearchTree():
    head_(new Node< Key, Value, Compare >{}),
    size_(0)
  {}
}

#endif
