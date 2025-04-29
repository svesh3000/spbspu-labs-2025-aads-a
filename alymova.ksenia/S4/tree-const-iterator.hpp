#ifndef TREE_CONST_ITERATOR_HPP
#define TREE_CONST_ITERATOR_HPP
#include <cassert>
#include <iterator>
#include "tree-2-3.hpp"
#include "tree-node.hpp"

namespace alymova
{
  template< class Key, class Value, class Comparator >
  struct TTTConstIterator:
    public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
  {
  public:
    using ConstIterator = TTTConstIterator< Key, Value, Comparator >;
    using Node = typename detail::TTTNode< Key, Value >;
    using NodeType = typename detail::TTTNode< Key, Value >::NodeType;

    TTTConstIterator();
    ConstIterator& operator++() noexcept;
    ConstIterator& operator++(int) noexcept;
    ConstIterator& operator--() noexcept;
    ConstIterator& operator--(int) noexcept;
    bool operator==(const ConstIterator& other) const noexcept;
    bool operator!=(const ConstIterator& other) const noexcept;
    const std::pair< Key, Value >& operator*() const noexcept;
    const std::pair< Key, Value >* operator->() const noexcept;
  private:
    const Node* node_;
    enum NodePoint {Empty, First, Second} point_;

    TTTConstIterator(Node* node, NodePoint point);

    friend class TwoThreeTree< Key, Value, Comparator >;
  };

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator >::TTTConstIterator():
    node_(nullptr),
    point_(NodePoint::Empty)
  {}

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator >::TTTConstIterator(Node* node, NodePoint point):
    node_(node),
    point_(point)
  {}

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator>& TTTConstIterator< Key, Value, Comparator >::operator++() noexcept
  {
    assert(node_ != nullptr && "You are trying to access beyond list's bounds");
    assert(node_->type != NodeType::Empty && "Incorrect node index");
    assert(point_ != NodePoint::Empty && "Incorrect node index");

    if (node_->type == NodeType::Double)
    {
      if (node_->right)
      {
        node_ = node_->right;
        while (node_->left)
        {
          node_ = node_->left;
        }
        point_ = NodePoint::First;
        return *this;
      }
    }
    else if (node_->type == NodeType::Triple)
    {
      if (point_ == NodePoint::First)
      {
        if (node_->mid)
        {
          node_ = node_->mid;
          while (node_->left)
          {
            node_ = node_->left;
          }
          return *this;
        }
        point_ = NodePoint::Second;
        return *this;
      }
      else if (point_ == NodePoint::Second)
      {
        if (node_->right)
        {
          node_ = node_->right;
          while (node_->left)
          {
            node_ = node_->left;
          }
          point_ = NodePoint::First;
          return *this;
        }
      }
    }
    while (node_->parent)
    {
      if (node_->parent->left == node_)
      {
        node_ = node_->parent;
        point_ = NodeType::First;
        return *this;
      }
      if (node_->parent->mid == node_)
      {
        node_ = node_->parent;
        point_ = NodePoint::Second;
        return *this;
      }
      node_ = node_->parent;
    }
    node_ = nullptr;
    point_ = NodePoint::Empty;
    return *this;
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator>& TTTConstIterator< Key, Value, Comparator >::operator++(int) noexcept
  {
    ConstIterator old = *this;
    ++(*this);
    return old;
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator>& TTTConstIterator< Key, Value, Comparator >::operator--() noexcept
  {
    if (node_->type == NodeType::Double)
    {
      if (node_->left)
      {
        node_ = node_->left;
        while (node_->right)
        {
          node_ = node_->right;
        }
        point_ = (node_->type == NodeType::Double) ? NodePoint::First : NodePoint::Second;
        return *this;
      }
    }
    else if (node_->type == NodeType::Triple)
    {
      if (point_ == NodePoint::First)
      {
        if (node_->left)
        {
          node_ = node_->left;
          while (node_->right)
          {
            node_ = node_->right;
          }
          point_ = (node_->type == NodeType::Double) ? NodePoint::First : NodePoint::Second;
          return *this;
        }
      }
      else if (point_ == NodePoint::Second)
      {
        if (node_->mid)
        {
          node_ = node_->mid;
          while (node_->right)
          {
            node_ = node_->right;
          }
          point_ = (node_->type == NodeType::Double) ? NodePoint::First : NodePoint::Second;
          return *this;
        }
        point_ = NodePoint::First;
        return *this;
      }
    }
    while (node_->parent)
    {
      if (node_->parent->right == node_)
      {
        node_ = node_->parent;
        point_ = (node_->type == NodeType::Double) ? NodePoint::First : NodePoint::Second;
        return *this;
      }
      if (node_->parent->mid == node_)
      {
        node_ = node_->parent;
        point_ = NodePoint::First;
        return *this;
      }
      node_ = node_->parent;
    }
    node_ = nullptr;
    point_ = NodePoint::Empty;
    return *this;
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator>& TTTConstIterator< Key, Value, Comparator >::operator--(int) noexcept
  {
    ConstIterator old = *this;
    --(*this);
    return old;
  }

  template< class Key, class Value, class Comparator >
  bool TTTConstIterator< Key, Value, Comparator >::operator==(const ConstIterator& other) const noexcept
  {
    return node_ == other.node_;
  }

  template< class Key, class Value, class Comparator >
  bool TTTConstIterator< Key, Value, Comparator >::operator!=(const ConstIterator& other) const noexcept
  {
    return node_ != other.node_;
  }

  template< class Key, class Value, class Comparator >
  const std::pair< Key, Value >& TTTConstIterator< Key, Value, Comparator >::operator*() const noexcept
  {
    assert(node_ != nullptr && "You are trying to access beyond list's bounds");
    assert(point_ != NodePoint::Empty && "Incorrect node index");

    return node_->data[point_ - 1];
  }

  template< class Key, class Value, class Comparator >
  const std::pair< Key, Value >* TTTConstIterator< Key, Value, Comparator >::operator->() const noexcept
  {
    assert(node_ != nullptr && "You are trying to access beyond list's bounds");
    assert(point_ != NodePoint::Empty && "Incorrect node index");

    return std::addressof(node_->data[point_ - 1]);
  }
}
#endif
