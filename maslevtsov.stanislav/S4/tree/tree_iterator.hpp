#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include <iterator>
#include "tree_node.hpp"

namespace maslevtsov {
  template< class T >
  class TreeIterator final: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    template< class Key, class Type, class Compare >
    friend class Tree;

    TreeIterator();
    TreeIterator(const TreeIterator& rhs) noexcept = default;
    ~TreeIterator() = default;
    TreeIterator& operator=(const TreeIterator& rhs) noexcept = default;

    TreeIterator& operator++();
    TreeIterator& operator++(int);
    TreeIterator& operator--();
    TreeIterator& operator--(int);

    const T& operator*() const;
    const T* operator->() const;

    bool operator==(const TreeIterator& rhs) const;
    bool operator!=(const TreeIterator& rhs) const;

  private:
    TreeNode< T >* node_;
    bool is_first_;

    TreeIterator(TreeIterator< T >* node, bool is_first_);
    TreeIterator< T >* get_min_node(TreeIterator< T >* node);
    TreeIterator< T >* get_max_node(TreeIterator< T >* node);
  };

  template< class T >
  TreeIterator< T >::TreeIterator():
    node_(nullptr)
  {}

  template< class T >
  typename TreeIterator< T >::TreeIterator& TreeIterator< T >::operator++()
  {
    if (!(node_->is_two) && is_first_) {
      TreeNode< T >* min_node = get_min_node(node_->middle_);
      if (!min_node) {
        is_first_ = false;
      } else {
        node_ = min_node;
      }
      return *this;
    }
    TreeNode< T >* min_node = get_min_node(node_->right_);
    if (!min_node) {
      if (node_->parent_) {
        while (node_->parent_ && node_->parent_->right_ == node_) {
          node_ = node_->parent_;
        }
        if (node_->parent_ && node_->parent_->middle_ == node_) {
          node_ = node_->parent_;
          is_first_ = false;
          return *this;
        } else if (node_->parent_) {
          node_ = node_->parent_;
        }
      }
    } else {
      node_ = min_node;
    }
    is_first_ = true;
    return *this;
  }

  template< class T >
  typename TreeIterator< T >::TreeIterator& TreeIterator< T >::operator++(int)
  {
    TreeIterator< T > result(*this);
    ++(*this);
    return result;
  }

  template< class T >
  typename TreeIterator< T >::TreeIterator& TreeIterator< T >::operator--()
  {
    if (!(node_->is_two) && !is_first_) {
      TreeNode< T >* max_node = get_max_node(node_->middle_);
      if (!max_node) {
        is_first_ = true;
      } else {
        node_ = max_node;
      }
      return *this;
    }
    TreeNode< T >* max_node = get_max_node(node_->left_);
    if (!max_node) {
      if (node_->parent_) {
        while (node_->parent_ && node_->parent_->left_ == node_) {
          node_ = node_->parent_;
        }
        if (node_->parent_ && node_->parent_->middle_ == node_) {
          node_ = node_->parent_;
          is_first_ = true;
          return *this;
        } else if (node_->parent_) {
          node_ = node_->parent_;
        }
      }
    } else {
      node_ = max_node;
    }
    is_first_ = false;
    return *this;
  }

  template< class T >
  typename TreeIterator< T >::TreeIterator& TreeIterator< T >::operator--(int)
  {
    TreeIterator< T > result(*this);
    --(*this);
    return result;
  }

  template< class T >
  const T& TreeIterator< T >::operator*() const
  {
    return is_first_ ? node_->data1_ : node_->data2_;
  }

  template< class T >
  const T* TreeIterator< T >::operator->() const
  {
    return is_first_ ? std::addressof(node_->data1_) : std::addressof(node_->data2_);
  }

  template< class T >
  bool TreeIterator< T >::operator==(const TreeIterator& rhs) const
  {
    return node_ == rhs.node_ && (!node_ || is_first_ == rhs.is_first_);
  }

  template< class T >
  bool TreeIterator< T >::operator!=(const TreeIterator& rhs) const
  {
    return !(*this == rhs);
  }

  template< class T >
  TreeIterator< T >::TreeIterator(TreeIterator< T >* node, bool is_first):
    node_(node),
    is_first_(is_first)
  {}

  template< class T >
  TreeIterator< T >* TreeIterator< T >::get_min_node(TreeIterator< T >* node)
  {
    TreeNode< T >* result = node;
    while (result && result->left_) {
      result = result->left_;
    }
    return result;
  }

  template< class T >
  TreeIterator< T >* TreeIterator< T >::get_max_node(TreeIterator< T >* node)
  {
    TreeNode< T >* result = node;
    while (result && result->right_) {
      result = result->right_;
    }
    return result;
  }
}

#endif
