#ifndef TREE_CITER_HPP
#define TREE_CITER_HPP
#include <iterator>
#include "tree-node.hpp"

namespace sveshnikov
{
  template< class Key, class T, class Cmp >
  class ConstIter: public std::iterator< bidirectional_iterator_tag, Key, T, Cmp >
  {
  public:
    using value_t = std::pair< Key, T >;
    ConstIter();
    ConstIter(const tree_node_t< Key, T > *node);
    ConstIter(const ConstIter &rhs) = default;
    ~ConstIter() = default;

    ConstIter &operator=(const ConstIter &rhs) = default;
    ConstIter &operator++() noexcept;
    ConstIter operator++(int) noexcept;
    ConstIter &operator--() noexcept;
    ConstIter operator--(int) noexcept;

    const value_t &operator*() const noexcept;
    const value_t *operator->() const noexcept;

    bool operator!=(const ConstIter &rhs) const noexcept;
    bool operator==(const ConstIter &rhs) const noexcept;

  private:
    const tree_node_t< Key, T > *node_;
  };

  template< class Key, class T, class Cmp >
  ConstIter< Key, T, Cmp >::ConstIter():
    node_(nullptr)
  {}

  template< class Key, class T, class Cmp >
  ConstIter< Key, T, Cmp >::ConstIter(const tree_node_t< Key, T > *node):
    node_(node)
  {}
}

#endif
