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
    Node< Key, Value > * root_;
    Compare comp_;
    size_t size_;
  };

  template< typename Key, typename Value, typename Compare >
  BinSearchTree< Key, Value, Compare >::BinSearchTree():
    root_(nullptr),
    size_(0)
  {}
}

#endif
