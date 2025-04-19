#ifndef TWO_THREE_ITERATOR_HPP
#define TWO_THREE_ITERATOR_HPP

#include <iterator>
#include "two_three_tree_node.hpp"

namespace maslevtsov {
  template< class Key, class T, class Compare = std::less< Key > >
  class TwoThreeTree;

  template< class T >
  class TwoThreeIterator final: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    friend class TwoThreeTree;

    TwoThreeIterator();
    TwoThreeIterator(const TwoThreeIterator& rhs) noexcept = default;
    ~TwoThreeIterator() = default;
    TwoThreeIterator& operator=(const TwoThreeIterator& rhs) noexcept = default;

    TwoThreeIterator& operator++();
    TwoThreeIterator& operator++(int);
    TwoThreeIterator& operator--();
    TwoThreeIterator& operator--(int);

    const T& operator*() const;
    const T* operator->() const;

    bool operator==(const TwoThreeIterator& rhs) const;
    bool operator!=(const TwoThreeIterator& rhs) const;

  private:
    TwoThreeTreeNode< T >* node_;
    bool is_first_;

    TwoThreeIterator(TwoThreeTreeNode< T >* node, bool is_first_);
    TwoThreeTreeNode< T >* get_min_node(TwoThreeTreeNode< T >* node);
    TwoThreeTreeNode< T >* get_max_node(TwoThreeTreeNode< T >* node);
  };

  template< class T >
  TwoThreeIterator< T >::TwoThreeIterator():
    node_(nullptr)
  {}

  template< class T >
  typename TwoThreeIterator< T >::TwoThreeIterator& TwoThreeIterator< T >::operator++()
  {
    if (!(node_->is_two) && is_first_) {
      TwoThreeTreeNode< T >* min_node = get_min_node(node_->middle_);
      if (!min_node) {
        is_first_ = false;
      } else {
        node_ = min_node;
      }
      return *this;
    }
    TwoThreeTreeNode< T >* min_node = get_min_node(node_->right_);
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
  typename TwoThreeIterator< T >::TwoThreeIterator& TwoThreeIterator< T >::operator++(int)
  {
    TwoThreeIterator< T > result(*this);
    ++(*this);
    return result;
  }

  template< class T >
  typename TwoThreeIterator< T >::TwoThreeIterator& TwoThreeIterator< T >::operator--()
  {
    if (!(node_->is_two) && !is_first_) {
      TwoThreeTreeNode< T >* max_node = get_max_node(node_->middle_);
      if (!max_node) {
        is_first_ = true;
      } else {
        node_ = max_node;
      }
      return *this;
    }
    TwoThreeTreeNode< T >* max_node = get_max_node(node_->left_);
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
  typename TwoThreeIterator< T >::TwoThreeIterator& TwoThreeIterator< T >::operator--(int)
  {
    TwoThreeIterator< T > result(*this);
    --(*this);
    return result;
  }

  template< class T >
  const T& TwoThreeIterator< T >::operator*() const
  {
    return (is_first_) ? node_->data1_ : node_->data2_;
  }

  template< class T >
  const T* TwoThreeIterator< T >::operator->() const
  {
    return (is_first_) ? std::addressof(node_->data1_) : std::addressof(node_->data2_);
  }

  template< class T >
  bool TwoThreeIterator< T >::operator==(const TwoThreeIterator& rhs) const
  {
    return node_ == other.node_ && (node_ == nullptr || is_first_ == other.is_first_);
  }

  template< class T >
  bool TwoThreeIterator< T >::operator!=(const TwoThreeIterator& rhs) const
  {
    return !(*this == rhs);
  }

  template< class T >
  TwoThreeIterator< T >::TwoThreeIterator(TwoThreeTreeNode< T >* node, bool is_first):
    node_(node),
    is_first_(is_first)
  {}

  template< class T >
  TwoThreeTreeNode< T >* TwoThreeIterator< T >::get_min_node(TwoThreeTreeNode< T >* node)
  {
    TwoThreeTreeNode< T >* result = node;
    while (result && result->left_) {
      result = result->left_;
    }
    return result;
  }

  template< class T >
  TwoThreeTreeNode< T >* TwoThreeIterator< T >::get_max_node(TwoThreeTreeNode< T >* node)
  {
    TwoThreeTreeNode< T >* result = node;
    while (result && result->right_) {
      result = result->right_;
    }
    return result;
  }
}

#endif
