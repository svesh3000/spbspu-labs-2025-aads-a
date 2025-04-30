#ifndef TREE_2_3_HPP
#define TREE_2_3_HPP
#include <cstddef>
#include <cassert>
#include <functional>
#include <iostream>
#include "tree-iterators.hpp"
#include "tree-iterator-impl.hpp"
#include "tree-const-iterator-impl.hpp"

namespace alymova
{
  template< class Key, class Value, class Comparator >
  class TwoThreeTree
  {
  public:
    using Tree = TwoThreeTree< Key, Value, Comparator >;
    using Iterator = TTTIterator< Key, Value, Comparator >;
    using ConstIterator = TTTConstIterator< Key, Value, Comparator >;
    using Node = typename detail::TTTNode< Key, Value >;
    using NodeType = typename detail::TTTNode< Key, Value >::NodeType;
    using NodePoint = typename detail::NodePoint;

    using T = std::pair< Key, Value >;

    TwoThreeTree();
    TwoThreeTree(const Tree& other);
    TwoThreeTree(Tree&& other);
    ~TwoThreeTree();

    Tree& operator=(const Tree& other);
    Tree& operator=(Tree&& other);

    Iterator begin();
    ConstIterator begin() const noexcept;
    ConstIterator cbegin() const noexcept;
    Iterator end();
    ConstIterator end() const noexcept;
    ConstIterator cend() const noexcept;

    bool empty() const;
    size_t size() const;

    std::pair< Iterator, bool > insert(const T& value);
    std::pair< Iterator, bool > insert(T&& value);
    template < class InputIterator >
    void insert(InputIterator first, InputIterator last);
    void insert(std::initializer_list< T > il);
    Iterator insert(Iterator hint, const T& value); //hint
    Iterator insert(ConstIterator hint, const T& value); //hint
    void swap(Tree& other);
    void clear();

    Iterator find(const Key& key);
    ConstIterator find(const Key& key) const;

  private:
    Node* fake_;
    Node* root_;
    size_t size_;

    void clear(Node* node);
  };

  template< class Key, class Value, class Comparator >
  TwoThreeTree< Key, Value, Comparator >::TwoThreeTree():
    fake_(new Node{}),
    root_(fake_),
    size_(0)
  {}

  template< class Key, class Value, class Comparator >
  TwoThreeTree< Key, Value, Comparator >::TwoThreeTree(const Tree& other):
    fake_(new Node{}),
    root_(fake_),
    size_(other.size_)
  {}

  template< class Key, class Value, class Comparator >
  TwoThreeTree< Key, Value, Comparator >::TwoThreeTree(Tree&& other):
    fake_(std::exchange(other.fake_, nullptr)),
    root_(std::exchange(other.root_, nullptr)),
    size_(std::exchange(other.size_, 0))
  {}

  template< class Key, class Value, class Comparator >
  TwoThreeTree< Key, Value, Comparator >::~TwoThreeTree()
  {
    if (size_)
    {
      clear(root_);
    }
    delete fake_;
  }

  template< class Key, class Value, class Comparator >
  TwoThreeTree< Key, Value, Comparator >& TwoThreeTree< Key, Value, Comparator >::operator=(const Tree& other)
  {
    assert(this != std::addressof(other) && "Assigning a map to itself");
    Tree copy(other);
    swap(copy);
    return *this;
  }

  template< class Key, class Value, class Comparator >
  TwoThreeTree< Key, Value, Comparator >& TwoThreeTree< Key, Value, Comparator >::operator=(Tree&& other)
  {
    assert(this != std::addressof(other) && "Assigning a map to itself");
    Tree moved(std::move(other));
    swap(moved);
    return *this;
  }

  template< class Key, class Value, class Comparator >
  TTTIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::begin()
  {
    return Iterator(cbegin());
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::begin() const noexcept
  {
    return cbegin();
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::cbegin() const noexcept
  {
    if (root_ == fake_)
    {
      return ConstIterator(fake_, NodePoint::Empty);
    }
    Node* tmp = root_;
    while (tmp->left)
    {
      tmp = tmp->left;
    }
    return ConstIterator(tmp, NodePoint::First);
  }

  template< class Key, class Value, class Comparator >
  TTTIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::end()
  {
    return Iterator(cend());
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::end() const noexcept
  {
    return cend();
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::cend() const noexcept
  {
    return ConstIterator(fake_, NodePoint::Empty);
  }

  template< class Key, class Value, class Comparator >
  size_t TwoThreeTree< Key, Value, Comparator >::size() const
  {
    return size_;
  }

  template< class Key, class Value, class Comparator >
  bool TwoThreeTree< Key, Value, Comparator >::empty() const
  {
    return size_ == 0;
  }

  template< class Key, class Value, class Comparator >
  std::pair< TTTIterator< Key, Value, Comparator >, bool >
    TwoThreeTree< Key, Value, Comparator >::insert(const T& value)
  {
    if (find(value.first) != end())
    {
      return {end(), false};
    }
    if (size_ == 0)
    {
      root_ = new Node{value.first, value.second};
      Iterator tmp(root_, NodePoint::First);
      size_++;
      return {tmp, true};
    }
    return {end(), false};
  }

  template< class Key, class Value, class Comparator >
  void TwoThreeTree< Key, Value, Comparator >::swap(Tree& other)
  {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
  }

  template< class Key, class Value, class Comparator >
  void TwoThreeTree< Key, Value, Comparator >::clear()
  {
    clear(root_);
  }

  template< class Key, class Value, class Comparator >
  TTTIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::find(const Key& key)
  {
    TTTConstIterator< Key, Value, Comparator > tmp = static_cast< const Tree& >(*this).find(key);
    return Iterator(tmp);
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::find(const Key& key) const
  {
    for (ConstIterator it = cbegin(); it != cend(); it++)
    {
      if (std::equal_to< Key >()(key, it->first))
      {
        return it;
      }
    }
    return cend();
  }

  template< class Key, class Value, class Comparator >
  void TwoThreeTree< Key, Value, Comparator >::clear(Node* root)
  {
    if (!root)
    {
      return;
    }
    clear(root->left);
    clear(root->mid);
    clear(root->right);
    delete root;
    root = nullptr;
  }
}

#endif
