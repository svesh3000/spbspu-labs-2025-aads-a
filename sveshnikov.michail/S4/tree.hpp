#ifndef TREE_HPP
#define TREE_HPP
#include "tree-iter.hpp"
#include "tree-citer.hpp"

namespace sveshnikov
{
  template< class Key, class T >
  class Iter;

  template< class Key, class T >
  class ConstIter;

  template< class Key, class T, class Cmp >
  class AvlTree
  {
  public:
    explicit AvlTree();
    AvlTree(const AvlTree &x);
    AvlTree(AvlTree &&x);

    Iter begin() noexcept;
    ConstIter begin() const noexcept;
    Iter end() noexcept;
    ConstIter end() const noexcept;

    size_t size() const noexcept;
    bool empty() const noexcept;

    T &operator[](const Key &k);
    T &operator[](Key &&k);
    T &at(const Key &k);
    const T &at(const Key &k) const;

    void clear() noexcept;
    void swap(AvlTree &x);
    std::pair< Iter, bool > insert(const T &val);
    Iter erase(ConstIter position);
    size_t erase(const Key &k);

    Iter find(const Key &k);
    ConstIter find(const Key &k) const;
    pair< ConstIter, ConstIter > equal_range(const Key &k) const;
    pair< Iter, Iter > equal_range(const Key &k);

  private:
    friend class Iter< Key, T >;
    friend class ConstIter< Key, T >;
  };

}

#endif
