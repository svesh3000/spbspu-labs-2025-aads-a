#ifndef TREE_2_3_HPP
#define TREE_2_3_HPP
#include <cstddef>
#include <cassert>
#include <functional>
#include "tree-node.hpp"

namespace alymova
{
  template< class Key, class Value, class Comapartor >
  struct TTTIterator;
  template< class Key, class Value, class Comapartor >
  struct TTTConstIterator;

  template< class Key, class Value, class Comparator >
  class TwoThreeTree
  {
  public:
    using Tree = TwoThreeTree< Key, Value, Comparator >;
    using Iterator = TTTIterator< Key, Value, Comparator >;
    using ConstIterator = TTTConstIterator< Key, Value, Comparator >;
    using Node = typename detail::TTTNode< Key, Value >;
    using NodeType = typename detail::TTTNode< Key, Value >::NodeType;
    using NodePoint = typename TTTConstIterator< Key, Value, Comparator >::NodePoint;

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

    void swap(Tree& other);
    void clear();

    Iterator find(const Key& key);
    ConstIterator find(const Key& key) const;

  private:
    Node* fake_;
    Node* root_;
    size_t size_;
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
    clear();
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
    ConstIterator tmp = cbegin();
    return {const_cast< Node* >(tmp.node_), tmp.point_};
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::begin() const noexcept
  {
    return cbegin();
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::cbegin() const noexcept
  {
    if (root_ = nullptr)
    {
      return {};
    }
    Node* tmp = root_;
    while (tmp->left)
    {
      tmp = tmp->left;
    }
    return {tmp, NodePoint::First};
  }

  template< class Key, class Value, class Comparator >
  TTTIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::end()
  {
    ConstIterator tmp = cend();
    return {const_cast< Node* >(tmp.node_), tmp.point_};
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::end() const noexcept
  {
    return cend();
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::cend() const noexcept
  {
    if (root_ = nullptr)
    {
      return {};
    }
    Node* tmp = root_;
    while (tmp->right)
    {
      tmp = tmp->right;
    }
    auto point = (tmp->type == NodeType::Double) ? NodePoint::First : NodePoint::Second;
    return {tmp, point};
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
  void TwoThreeTree< Key, Value, Comparator >::swap(Tree& other)
  {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
  }

  template< class Key, class Value, class Comparator >
  void TwoThreeTree< Key, Value, Comparator >::clear()
  {
    if (!root_)
    {
      return;
    }
    clear(root_->left);
    clear(root_->mid);
    clear(root_->right);
    delete root_;
  }

  template< class Key, class Value, class Comparator >
  TTTIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::find(const Key& key)
  {
    ConstIterator tmp = find(key);
    return {const_cast< Node* >(tmp.node_), tmp.point_};
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::find(const Key& key) const
  {
    for (auto it = begin(); it != end(); it++)
    {
      if (std::equal_to< Key >()(key, it->first))
      {
        return it;
      }
    }
  }

}

#endif
