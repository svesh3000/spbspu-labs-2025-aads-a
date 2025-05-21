#ifndef TREE_HEAVY_ITERATORS_HPP
#define TREE_HEAVY_ITERATORS_HPP
#include <iterator>
#include <stack.hpp>
#include "tree-node.hpp"

namespace alymova
{
  template< class Key, class Value, class Comparator >
  struct TTTLnrIterator:
    public std::iterator< std::forward_iterator_tag, std::pair< Key, Value > >
  {
  public:
    //using LnrIterator = TTTLnrIterator< Key, Value, Comparator >;
    using Node = typename detail::TTTNode< Key, Value, Comparator >;
    using NodeType = typename Node::NodeType;
    using NodePoint = typename detail::NodePoint;

    TTTLnrIterator();
    TTTLnrIterator& operator++();
    TTTLnrIterator operator++(int);
    TTTLnrIterator& operator--() noexcept;
    TTTLnrIterator operator--(int) noexcept;
    bool operator==(const TTTLnrIterator& other) const noexcept;
    bool operator!=(const TTTLnrIterator& other) const noexcept;
    std::pair< Key, Value >& operator*() noexcept;
    std::pair< Key, Value >* operator->() noexcept;
  private:
    Node const* root_;
    std::pair< Node*, NodePoint > node_;
    std::pair< Node*, NodePoint > tmp_;
    Stack< std::pair< Node*, NodePoint > > nexts_;

    TTTLnrIterator(Node* root, NodePoint point);
    void fallLeft();

    friend class TwoThreeTree< Key, Value, Comparator >;
  };

  template< class Key, class Value, class Comparator >
  TTTLnrIterator< Key, Value, Comparator >::TTTLnrIterator():
    root_(nullptr),
    node_({nullptr, NodePoint::Empty}),
    tmp_({nullptr, NodePoint::Empty}),
    nexts_()
  {}

  template< class Key, class Value, class Comparator >
  TTTLnrIterator< Key, Value, Comparator >::TTTLnrIterator(Node* root, NodePoint point):
    root_(root),
    node_({root, point}),
    tmp_({root, point}),
    nexts_()
  {
    if (point != NodePoint::Fake)
    {
      ++(*this);
    }
  }

  template< class Key, class Value, class Comparator >
  TTTLnrIterator< Key, Value, Comparator >& TTTLnrIterator< Key, Value, Comparator >::operator++()
  {
    assert(node_.second != NodePoint::Fake && "You are trying to access beyond tree's bounds");
    while (tmp_.first)
    {
      nexts_.push(tmp_);
      tmp_.first = tmp_.first->left;
    }
    node_ = nexts_.top();
    nexts_.pop();
    if (node_.first->type == NodeType::Triple && node_.second == NodePoint::First)
    {
      nexts_.push({node_.first, NodePoint::Second});
      tmp_.first = node_.first->mid;
      return *this;
    }
    tmp_.first = node_.first->right;
    if (tmp_.first)
    {
      if (tmp_.first->type == NodeType::Fake)
      {
        tmp_.second = NodePoint::Fake;
      }
    }
    return *this;
  }

  template< class Key, class Value, class Comparator >
  bool TTTLnrIterator< Key, Value, Comparator >::operator==(const TTTLnrIterator& other) const noexcept
  {
    if (node_.second == NodePoint::Fake && other.node_.second == NodePoint::Fake)
    {
      return true;
    }
    return (node_ == other.node_);
  }

  template< class Key, class Value, class Comparator >
  bool TTTLnrIterator< Key, Value, Comparator >::operator!=(const TTTLnrIterator& other) const noexcept
  {
    return !(*this == other);
  }

  template< class Key, class Value, class Comparator >
  std::pair< Key, Value >& TTTLnrIterator< Key, Value, Comparator >::operator*() noexcept
  {
    assert(node_.first != nullptr && "You are trying to access beyond tree's bounds");

    return node_.first->data[node_.second - 1];
  }

  template< class Key, class Value, class Comparator >
  std::pair< Key, Value >* TTTLnrIterator< Key, Value, Comparator >::operator->() noexcept
  {
    assert(node_.first != nullptr && "You are trying to access beyond tree's bounds");

    return std::addressof(node_.first->data[node_.second - 1]);
  }
}

#endif
