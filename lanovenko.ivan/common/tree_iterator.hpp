#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include <iterator>
#include "tree_node.hpp"
#include "tree.hpp"

namespace lanovenko
{
  template< typename Key, typename Value, typename Comparator >
  class Tree;

  template< typename Key, typename Value, typename Comparator >
  class TreeIterator final : public std::iterator< std::forward_iterator_tag, Value >
  {
  public:
    using this_t = TreeIterator< Key, Value, Comparator >;
    ~TreeIterator() = default;
    TreeIterator();
    TreeIterator(const this_t&) = default;
    this_t& operator=(const this_t&) = default;
    this_t& operator++();
    this_t operator++(int);
    std::pair< Key, Value >& operator*();
    std::pair< Key, Value >* operator->();
    bool operator!=(const this_t& rhs) const;
    bool operator==(const this_t& rhs) const;
  private:
    TreeNode< Key, Value >* node_;
    explicit TreeIterator(TreeNode< Key, Value >* node);
    friend class Tree< Key, Value, Comparator >;
  };

  template< typename Key, typename Value, typename Comparator >
  TreeIterator< Key, Value, Comparator >::TreeIterator():
    node_(nullptr)
  {}

  template< typename Key, typename Value, typename Comparator >
  TreeIterator< Key, Value, Comparator >& TreeIterator< Key, Value, Comparator >::operator++()
  {
    if (node_->right_)
    {
      node_ = Tree< Key, Value, Comparator >::minValueNode(node_->right_);
      return *this;
    }
    else
    {
      while (node_->parent_ && node_->parent_->left_ != node_)
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
      return *this;
    }
  }

  template< typename Key, typename Value, typename Comparator >
  TreeIterator< Key, Value, Comparator > TreeIterator< Key, Value, Comparator >::operator++(int)
  {
    this_t result(*this);
    ++(*this);
    return result;
  }

  template< class Key, class Value, class Cmp>
  std::pair< Key, Value >& TreeIterator< Key, Value, Cmp >::operator*()
  {
    return node_->data_;
  }

  template< class Key, class Value, class Cmp>
  std::pair< Key, Value >* TreeIterator< Key, Value, Cmp >::operator->()
  {
    return std::addressof(node_->data_);
  }

  template< class Key, class Value, class Cmp>
  bool TreeIterator< Key, Value, Cmp >::operator==(const this_t& rhs) const
  {
    return node_ == rhs.node_;
  }

  template< class Key, class Value, class Cmp>
  bool TreeIterator< Key, Value, Cmp >::operator!=(const this_t& rhs) const
  {
    return !(rhs == *this);
  }

  template< typename Key, typename Value, typename Comparator >
  TreeIterator< Key, Value, Comparator >::TreeIterator(TreeNode< Key, Value >* node):
    node_(node)
  {}
}

#endif
