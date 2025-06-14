#ifndef TREE_HPP
#define TREE_HPP
#include "tree-iter.hpp"
#include "tree-citer.hpp"

namespace sveshnikov
{
  template< class Key, class T, class Cmp >
  class AvlTree
  {
  public:
    explicit AvlTree(); // ok
    AvlTree(const AvlTree &x);
    AvlTree(AvlTree &&x);
    AvlTree &operator=(const AvlTree &x);
    AvlTree &operator=(AvlTree &&x);

    Iter< Key, T > begin() noexcept;             // ok
    ConstIter< Key, T > begin() const noexcept;  // ok
    ConstIter< Key, T > cbegin() const noexcept; // ok
    Iter< Key, T > end() noexcept;               // ok
    ConstIter< Key, T > end() const noexcept;    // ok
    ConstIter< Key, T > cend() const noexcept;   // ok

    size_t size() const noexcept; // ok
    bool empty() const noexcept;  // ok

    T &operator[](const Key &k);
    T &operator[](Key &&k);
    T &at(const Key &k);
    const T &at(const Key &k) const;

    void clear() noexcept;
    void swap(AvlTree &x);
    std::pair< Iter< Key, T >, bool > insert(const T &val);
    Iter< Key, T > erase(ConstIter< Key, T > position);
    size_t erase(const Key &k);

    Iter< Key, T > find(const Key &k);
    ConstIter< Key, T > find(const Key &k) const;
    pair< ConstIter< Key, T >, ConstIter< Key, T > > equal_range(const Key &k) const;
    pair< Iter< Key, T >, Iter< Key, T > > equal_range(const Key &k);
    size_t count(const Key &k) const;

  private:
    tree_node_t< Key, T > *root_;
    size_t size_;

    tree_node_t< Key, T > *getMinNode();
    tree_node_t< Key, T > *getMaxNode();
  };

  template< class Key, class T, class Cmp >
  AvlTree< Key, T, Cmp >::AvlTree():
    root_(nullptr),
    size_(0)
  {}

  template< class Key, class T, class Cmp >
  tree_node_t< Key, T > *AvlTree< Key, T, Cmp >::getMinNode()
  {
    auto node = root_;
    while (node->left_->left)
    {
      node = node->left_;
    }
    return node;
  }

  template< class Key, class T, class Cmp >
  Iter< Key, T > AvlTree< Key, T, Cmp >::begin() noexcept
  {
    return Iter< Key, T >(getMinNode());
  }

  template< class Key, class T, class Cmp >
  ConstIter< Key, T > AvlTree< Key, T, Cmp >::begin() const noexcept
  {
    return cbegin();
  }

  template< class Key, class T, class Cmp >
  ConstIter< Key, T > AvlTree< Key, T, Cmp >::cbegin() const noexcept
  {
    return ConstIter< Key, T >(getMinNode());
  }

  template< class Key, class T, class Cmp >
  tree_node_t< Key, T > *AvlTree< Key, T, Cmp >::getMaxNode()
  {
    auto node = root_;
    while (node->right_->right_)
    {
      node = node->right_;
    }
    return node;
  }

  template< class Key, class T, class Cmp >
  Iter< Key, T > AvlTree< Key, T, Cmp >::end() noexcept
  {
    return Iter< Key, T >(getMaxNode()->right_);
  }

  template< class Key, class T, class Cmp >
  ConstIter< Key, T > AvlTree< Key, T, Cmp >::end() const noexcept
  {
    return cend();
  }

  template< class Key, class T, class Cmp >
  ConstIter< Key, T > AvlTree< Key, T, Cmp >::cend() const noexcept
  {
    return ConstIter< Key, T >(getMaxNode()->right_);
  }

  template< class Key, class T, class Cmp >
  size_t AvlTree< Key, T, Cmp >::size() const noexcept
  {
    return size_;
  }

  template< class Key, class T, class Cmp >
  bool AvlTree< Key, T, Cmp >::empty() const noexcept
  {
    return size_ == 0;
  }

  std::pair< Iter< Key, T >, bool > insert(const T &val);
}

#endif
