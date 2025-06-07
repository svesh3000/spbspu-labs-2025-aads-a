#ifndef ITERATOR_TTT_HPP
#define ITERATOR_TTT_HPP

#include <cassert>
#include <iterator>
#include "TwoThreeTree.hpp"

namespace gavrilova {

  template < class Key, class Value, class Cmp >
  struct Iterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > > {
    using this_t = Iterator< Key, Value, Cmp >;
    using Node = NodeTwoThreeTree< Key, Value >;
    using value_type = std::pair< Key, Value >;

    Iterator();
    ~Iterator() = default;
    Iterator(const this_t&) = default;
    this_t& operator=(const this_t&) = default;

    this_t& operator++() noexcept;
    this_t operator++(int) noexcept;
    this_t& operator--() noexcept;
    this_t operator--(int) noexcept;

    value_type& operator*() const;
    value_type* operator->() const;

    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;

  private:
    Node* node_;
    int key_pos_;

    friend class TwoThreeTree< Key, Value, Cmp >;
    friend class ConstIterator< Key, Value, Cmp >;
    explicit Iterator(Node* node, int key_pos = 0);

    Node* go_min(Node* start) const;
    Node* go_max(Node* start) const;
  };

  template < class Key, class Value, class Cmp >
  Iterator< Key, Value, Cmp >::Iterator():
    node_(nullptr),
    key_pos_(0)
  {}

  template < class Key, class Value, class Cmp >
  Iterator< Key, Value, Cmp >::Iterator(Node* node, int key_pos):
    node_(node),
    key_pos_(key_pos)
  {}

  template < class Key, class Value, class Cmp >
  typename Iterator< Key, Value, Cmp >::this_t& Iterator< Key, Value, Cmp >::operator++() noexcept
  {
    assert(node_);

    if (!node_->is_leaf()) {
      Node* next = node_->children[key_pos_ + 1];
      node_ = go_min(next);
      key_pos_ = 0;
      return *this;
    }

    Node* cur = node_;
    Node* parent = cur->parent;

    while (parent) {
      int max_pos = parent->is_3_node ? 2 : 1;
      for (int i = 0; i < max_pos; ++i) {
        if (parent->children[i] == cur && i < max_pos - 1) {
          node_ = parent;
          key_pos_ = i;
          return *this;
        }
      }
      cur = parent;
      parent = parent->parent;
    }

    node_ = nullptr;
    key_pos_ = 0;
    return *this;
  }

  template < class Key, class Value, class Cmp >
  typename Iterator< Key, Value, Cmp >::this_t Iterator< Key, Value, Cmp >::operator++(int) noexcept
  {
    this_t temp(*this);
    ++(*this);
    return temp;
  }

  template < class Key, class Value, class Cmp >
  typename Iterator< Key, Value, Cmp >::this_t& Iterator< Key, Value, Cmp >::operator--() noexcept
  {
    if (!node_) {
      return *this;
    }

    if (!node_->is_leaf()) {
      Node* next = node_->children[key_pos_];
      node_ = go_max(next);
      key_pos_ = node_->is_3_node ? 1 : 0;
      return *this;
    }

    Node* cur = node_;
    Node* parent = cur->parent;

    while (parent) {
      for (int i = (parent->is_3_node ? 1 : 0); i >= 0; --i) {
        if (parent->children[i + 1] == cur) {
          node_ = parent;
          key_pos_ = i;
          return *this;
        }
      }
      cur = parent;
      parent = parent->parent;
    }

    node_ = nullptr;
    key_pos_ = 0;
    return *this;
  }

  template < class Key, class Value, class Cmp >
  typename Iterator< Key, Value, Cmp >::this_t Iterator< Key, Value, Cmp >::operator--(int) noexcept
  {
    this_t temp(*this);
    --(*this);
    return temp;
  }

  template < class Key, class Value, class Cmp >
  typename Iterator< Key, Value, Cmp >::value_type& Iterator< Key, Value, Cmp >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data[key_pos_];
  }

  template < class Key, class Value, class Cmp >
  typename Iterator< Key, Value, Cmp >::value_type* Iterator< Key, Value, Cmp >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data[key_pos_]);
  }

  template < class Key, class Value, class Cmp >
  bool Iterator< Key, Value, Cmp >::operator==(const this_t& rhs) const
  {
    return node_ == rhs.node_ && key_pos_ == rhs.key_pos_;
  }

  template < class Key, class Value, class Cmp >
  bool Iterator< Key, Value, Cmp >::operator!=(const this_t& rhs) const
  {
    return !(*this == rhs);
  }

  template < class Key, class Value, class Cmp >
  typename Iterator< Key, Value, Cmp >::Node* Iterator< Key, Value, Cmp >::go_min(Node* start) const
  {
    Node* cur = start;
    while (!cur->is_leaf()) {
      cur = cur->children[0];
    }
    return cur;
  }

  template < class Key, class Value, class Cmp >
  typename Iterator< Key, Value, Cmp >::Node* Iterator< Key, Value, Cmp >::go_max(Node* start) const
  {
    Node* cur = start;
    while (!cur->is_leaf()) {
      cur = cur->children[cur->is_3_node ? 2 : 1];
    }
    return cur;
  }

}

#endif
