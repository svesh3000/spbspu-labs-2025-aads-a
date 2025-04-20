#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include <cassert>
#include <utility>
#include "node.hpp"

namespace duhanina
{
  template < typename Key, typename Value >
  class Iterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< const Key, Value > >
  {
  public:
    Iterator();
    explicit Iterator(Node< Key, Value >* node);

    std::pair< const Key, Value >& operator*() const;
    std::pair< const Key, Value >* operator->() const;

    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);

    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

  private:
    Node< Key, Value >* current_;
    friend class BinarySearchTree;
  };

  template < typename Key, typename Value >
  Iterator< Key, Value >::Iterator():
    current_(nullptr)
  {}

  template < typename Key, typename Value >
  Iterator< Key, Value >::Iterator(Node< Key, Value >* node):
    current_(node)
  {}

  template < typename Key, typename Value >
  std::pair< const Key, Value >& Iterator< Key, Value >::operator*() const
  {
    assert(current_ != nullptr);
    return current_->data;
  }

  template < typename Key, typename Value >
  std::pair< const Key, Value >* Iterator< Key, Value >::operator->() const
  {
    assert(current_ != nullptr);
    return std::addressof(current_->data);
  }

  template < typename Key, typename Value >
  Iterator< Key, Value >& Iterator< Key, Value >::operator++()
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
      Node< Key, Value >* parent = current_->parent;
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
  Iterator< Key, Value > Iterator< Key, Value >::operator++(int)
  {
    assert(current_ != nullptr);
    Iterator< Key, Value > temp = *this;
    ++(*this);
    return temp;
  }

  template < typename Key, typename Value >
  Iterator< Key, Value >& Iterator< Key, Value >::operator--()
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
      Node< Key, Value >* parent = current_->parent;
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
  Iterator< Key, Value > Iterator< Key, Value >::operator--(int)
  {
    assert(current_ != nullptr);
    Iterator< Key, Value > temp = *this;
    --(*this);
    return temp;
  }

  template < typename Key, typename Value >
  bool Iterator< Key, Value >::operator==(const Iterator& other) const
  {
    return current_ == other.current_;
  }

  template < typename Key, typename Value >
  bool Iterator< Key, Value >::operator!=(const Iterator& other) const
  {
    return !(*this == other);
  }
}

#endif
