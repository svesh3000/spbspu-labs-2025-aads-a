#ifndef BST_NODE_H
#define BST_NODE_H
#include <cstddef>

namespace savintsev
{
  template< typename Key, typename Value, typename Compare >
  struct Node
  {
    Key keys_[2];
    Value vals_[2];
    Compare comp_;

    Node * left_ = nullptr;
    Node * midd_ = nullptr;
    Node * righ_ = nullptr;
    Node * parent_ = nullptr;

    size_t hold_ = 0;
  };
}

#endif
