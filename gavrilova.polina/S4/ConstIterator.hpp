#ifndef CONST_ITERATOR_TTT_HPP
#define CONST_ITERATOR_TTT_HPP

#include <cassert>
#include <iterator>
#include "TwoThreeTree.hpp"

namespace gavrilova {
  template < class Key, class Value, class Cmp >
  struct ConstIterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > > {
    using this_t = ConstIterator< Key, Value, Cmp >;
    using Node = NodeTwoThreeTree< Key, Value >;
    using value_type = std::pair< Key, Value >;

    ConstIterator();
    ~ConstIterator() = default;
    ConstIterator(const this_t&) = default;
    this_t& operator=(const this_t&) = default;

    this_t& operator++() noexcept;
    this_t operator++(int) noexcept;
    this_t& operator--() noexcept;
    this_t operator--(int) noexcept;

    const value_type& operator*() const;
    const value_type* operator->() const;

    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;

  private:
    const Node* node_;
    int key_pos_;
    friend class TwoThreeTree< Key, Value, Cmp >;
    friend class Iterator< Key, Value, Cmp >;
    explicit ConstIterator(const Node* node);

    const Node* go_min(const Node* start) const;
    const Node* go_max(const Node* start) const;
  };

  template < class Key, class Value, class Cmp >
  ConstIterator< Key, Value, Cmp >::ConstIterator():
    node_(nullptr),
    key_pos_(0)
  {}

  template < class Key, class Value, class Cmp >
  ConstIterator< Key, Value, Cmp >& ConstIterator< Key, Value, Cmp >::operator++() noexcept
  {
    assert(node_);

    if (!node_->is_leaf()) {
      const Node* next = node_->children[key_pos_ + 1];
      node_ = go_min(next);
      key_pos_ = 0;
      return *this;
    }

    const Node* cur = node_;
    const Node* parent = cur->parent;

    while (parent) {
      for (int i = 0; i < (parent->is_3_node ? 2 : 1) + 1; ++i) {
        if (parent->children[i] == cur && i < (parent->is_3_node ? 2 : 1)) {
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
  ConstIterator< Key, Value, Cmp > ConstIterator< Key, Value, Cmp >::operator++(int) noexcept
  {
    ConstIterator< Key, Value, Cmp > result(*this);
    ++(*this);
    return result;
  }

  template < class Key, class Value, class Cmp >
  ConstIterator< Key, Value, Cmp >& ConstIterator< Key, Value, Cmp >::operator--() noexcept
  {
    if (!node_) {
      return *this;
    }

    if (!node_->is_leaf()) {
      const Node* next = node_->children[key_pos_];
      node_ = go_max(next);
      key_pos_ = node_->is_3_node ? 1 : 0;
      return *this;
    }

    const Node* cur = node_;
    const Node* parent = cur->parent;

    while (parent) {
      for (int i = 1; i >= 0; --i) {
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
  ConstIterator< Key, Value, Cmp > ConstIterator< Key, Value, Cmp >::operator--(int) noexcept
  {
    ConstIterator< Key, Value, Cmp > result(*this);
    --(*this);
    return result;
  }

  template < class Key, class Value, class Cmp >
  bool ConstIterator< Key, Value, Cmp >::operator==(const this_t& rhs) const
  {
    return node_ == rhs.node_;
  }

  template < class Key, class Value, class Cmp >
  bool ConstIterator< Key, Value, Cmp >::operator!=(const this_t& rhs) const
  {
    return !(rhs == *this);
  }

  template < class Key, class Value, class Cmp >
  const typename ConstIterator<Key, Value, Cmp>::value_type&
  ConstIterator< Key, Value, Cmp >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template < class Key, class Value, class Cmp >
  const typename ConstIterator<Key, Value, Cmp>::value_type*
  ConstIterator< Key, Value, Cmp >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }


  template < class Key, class Value, class Cmp >
  const typename ConstIterator< Key, Value, Cmp >::Node*
  ConstIterator< Key, Value, Cmp >::go_min(const Node* start) const
  {
    const Node* cur = start;
    while (!cur->is_leaf()) {
      cur = cur->children[0];
    }
    return cur;
  }

  template < class Key, class Value, class Cmp >
  const typename ConstIterator< Key, Value, Cmp >::Node*
  ConstIterator< Key, Value, Cmp >::go_max(const Node* start) const
  {
    const Node* cur = start;
    while (!cur->is_leaf()) {
      cur = cur->children[cur->is_3_node ? 2 : 1];
    }
    return cur;
  }
}

#endif
// namespace gavrilova {
//   template< class Key, class Value, class Cmp >
//   struct ConstIterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
//   {
//     using this_t = ConstIterator< Key, Value, Cmp >;

//     ConstIterator();
//     ~ConstIterator() = default;
//     ConstIterator(const this_t&) = default;
//     // ConstIteratorFwd(IteratorFwd< T >& other);
//     this_t& operator=(const this_t&) = default;

//     this_t& operator++();
//     this_t operator++(int);
//     this_t& operator--();
//     this_t operator--(int);
//     const T& operator*() const;
//     const T* operator->() const;
//     bool operator!=(const this_t&) const;
//     bool operator==(const this_t&) const;

//   private:
//     TwoThreeTree< Key, Value, Cmp >* node_;
//     friend class TwoThreeTree< Key, Value, Cmp >;
//     friend class Iterator< Key, Value, Cmp >;
//     explicit ConstIterator(TwoThreeTree< Key, Value, Cmp >* node): node_(node) {};
//   // };
// }
