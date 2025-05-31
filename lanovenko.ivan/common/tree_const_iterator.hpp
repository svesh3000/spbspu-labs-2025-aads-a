#ifndef TREE_CONST_ITERATOR_HPP
#define TREE_CONST_ITERATOR_HPP

#include <iterator>
#include "tree_node.hpp"
#include "tree.hpp"

namespace lanovenko
{
  template< typename Key, typename Value, typename Comparator >
  class Tree;

  template< typename Key, typename Value, typename Comparator >
  class TreeConstIterator final : public std::iterator< std::forward_iterator_tag, Value >
  {
  public:
    using this_t = TreeConstIterator< Key, Value, Comparator >;
    ~TreeConstIterator() = default;
    TreeConstIterator();
    TreeConstIterator(const this_t&) = default;
    this_t& operator=(const this_t&) = default;
    this_t& operator++();
    this_t operator++(int);
    const std::pair< Key, Value >& operator*() const;
    const std::pair< Key, Value >* operator->() const;
    bool operator!=(const this_t& rhs) const;
    bool operator==(const this_t& rhs) const;
  private:
    TreeNode< Key, Value >* node_;
    explicit TreeConstIterator(TreeNode< Key, Value >* node);
    friend class Tree< Key, Value, Comparator >;
  };

  template< typename Key, typename Value, typename Comparator >
  TreeConstIterator< Key, Value, Comparator >::TreeConstIterator():
    node_(nullptr)
  {}

  template< typename Key, typename Value, typename Comparator >
  TreeConstIterator< Key, Value, Comparator >& TreeConstIterator< Key, Value, Comparator >::operator++()
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
  TreeConstIterator< Key, Value, Comparator > TreeConstIterator< Key, Value, Comparator >::operator++(int)
  {
    this_t result(*this);
    ++(*this);
    return result;
  }

  template< class Key, class Value, class Cmp>
  const std::pair< Key, Value >& TreeConstIterator< Key, Value, Cmp >::operator*() const
  {
    return node_->data_;
  }

  template< class Key, class Value, class Cmp>
  const std::pair< Key, Value >* TreeConstIterator< Key, Value, Cmp >::operator->() const
  {
    return std::addressof(node_->data_);
  }

  template< class Key, class Value, class Cmp>
  bool TreeConstIterator< Key, Value, Cmp >::operator==(const this_t& rhs) const
  {
    return node_ == rhs.node_;
  }

  template< class Key, class Value, class Cmp>
  bool TreeConstIterator< Key, Value, Cmp >::operator!=(const this_t& rhs) const
  {
    return !(rhs == *this);
  }

  template< typename Key, typename Value, typename Comparator >
  TreeConstIterator< Key, Value, Comparator >::TreeConstIterator(TreeNode< Key, Value >* node):
    node_(node)
  {}
}

#endif
