#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP
#include "node.hpp"
#include <functional>

namespace smirnov
{
  template < typename Key, typename Value, typename Compare >
  class AvlTree;
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class ConstIterator
  {
    friend class AvlTree< Key, Value, Compare >;
  public:
    ConstIterator();
    const std::pair< const Key, Value > & operator*() const;
    const std::pair< const Key, Value > * operator->() const;
    ConstIterator & operator++();
    bool operator==(const ConstIterator & other) const;
    bool operator!=(const ConstIterator & other) const;
  private:
    explicit ConstIterator(Node< Key, Value > * node);
    Node< Key, Value > * current_;
  };
}
#endif
