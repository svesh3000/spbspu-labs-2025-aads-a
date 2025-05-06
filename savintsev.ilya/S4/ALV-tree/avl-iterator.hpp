#ifndef AVL_ITERATOR_H
#define AVL_ITERATOR_H
#include <utility>
#include "avl-node.hpp"

namespace savintsev
{
  template< typename Key, typename Value >
  class BidirectIterator
  {
  public:
    using node_type = node_t< Key, Value >;
    using value_type = typename node_type::value_type;

    BidirectIterator() = default;

    explicit BidirectIterator(node_type * node):
      node_(node)
    {}

    value_type & operator*() const
    {
      return node_->data_;
    }

    value_type* operator->() const
    {
      return & node_->data_;
    }

    BidirectIterator & operator++()
    {
      node_ = next(node_);
      return *this;
    }

    BidirectIterator operator++(int)
    {
      BidirectIterator tmp = * this;
      ++(*this);
      return tmp;
    }

    bool operator==(const BidirectIterator & other) const
    {
      return node_ == other.node_;
    }

    bool operator!=(const BidirectIterator & other) const
    {
      return node_ != other.node_;
    }

  private:
    node_type * node_ = nullptr;

    node_type * next(node_type * node)
    {
      if (!node) return nullptr;

      if (node->right_)
      {
        node = node->right_;
        while (node->left_)
          node = node->left_;
        return node;
      }

      node_type * parent = node->parent_;
      while (parent && node == parent->right_)
      {
        node = parent;
        parent = parent->parent_;
      }

      return parent;
    }
    template< typename, typename, typename >
    friend class AVLTree;
  };
}

#endif
