#ifndef CITERATOR_HPP
#define CITERATOR_HPP

#include <iterator>
#include <cassert>
#include <utility>
#include "node.hpp"

namespace duhanina
{
  template < typename Key, typename Value >
  class ConstIterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< const Key, Value > >
  {
  public:
    ConstIterator();
    explicit ConstIterator(const Node< Key, Value >* node);

    const std::pair< const Key, Value >& operator*() const;
    const std::pair< const Key, Value >* operator->() const;

    ConstIterator& operator++();
    ConstIterator operator++(int);
    ConstIterator& operator--();
    ConstIterator operator--(int);

    bool operator==(const ConstIterator& other) const;
    bool operator!=(const ConstIterator& other) const;

  private:
    const Node< Key, Value >* current_;
    friend class BinarySearchTree;
  };

  template < typename Key, typename Value >
  ConstIterator< Key, Value >::ConstIterator():
    current_(nullptr)
  {}

  template < typename Key, typename Value >
  ConstIterator< Key, Value >::ConstIterator(const Node< Key, Value >* node):
    current_(node)
  {}

  template < typename Key, typename Value >
  const std::pair< const Key, Value >& ConstIterator< Key, Value >::operator*() const
  {
    assert(current_ != nullptr);
    return current_->data;
  }

  template < typename Key, typename Value >
  const std::pair< const Key, Value >* ConstIterator< Key, Value >::operator->() const
  {
    assert(current_ != nullptr);
    return std::addressof(current_->data);
  }

  template < typename Key, typename Value >
  ConstIterator< Key, Value >& ConstIterator< Key, Value >::operator++()
  {
    assert(current_ != nullptr);
    if (current_->right)
    {
      current_ = current_->right;
      while (current_->left)
      {
        current_ = current_->left;
      }
    }
    else
    {
      const Node< Key, Value >* parent = current_->parent;
      while (parent && current_ == parent->right)
      {
        current_ = parent;
        parent = parent->parent;
      }
      current_ = parent;
    }
    return *this;
  }

  template < typename Key, typename Value >
  ConstIterator< Key, Value > ConstIterator< Key, Value >::operator++(int)
  {
    assert(current_ != nullptr);
    ConstIterator temp = *this;
    ++(*this);
    return temp;
  }

  template < typename Key, typename Value >
  ConstIterator< Key, Value >& ConstIterator< Key, Value >::operator--()
  {
    assert(current_ != nullptr);
    if (current_->left)
    {
      current_ = current_->left;
      while (current_->right)
      {
        current_ = current_->right;
      }
    }
    else
    {
      const Node< Key, Value >* parent = current_->parent;
      while (parent && current_ == parent->left)
      {
        current_ = parent;
        parent = parent->parent;
      }
      current_ = parent;
    }
    return *this;
  }

  template < typename Key, typename Value >
  ConstIterator< Key, Value > ConstIterator< Key, Value >::operator--(int)
  {
    assert(current_ != nullptr);
    ConstIterator temp = *this;
    --(*this);
    return temp;
  }

  template < typename Key, typename Value >
  bool ConstIterator< Key, Value >::operator==(const ConstIterator& other) const
  {
    return current_ == other.current_;
  }

  template < typename Key, typename Value >
  bool ConstIterator< Key, Value >::operator!=(const ConstIterator& other) const
  {
    return !(*this == other);
  }
}

#endif
