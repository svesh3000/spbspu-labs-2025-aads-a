#ifndef TWO_THREE_ITERATOR_HPP
#define TWO_THREE_ITERATOR_HPP

#include <iterator>
#include "two_three_tree_node.hpp"

namespace maslevtsov {
  template< class Key, class T, class Compare = std::less< Key > >
  class TwoThreeTree;

  template< class T >
  class TwoThreeIterator final: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    TwoThreeIterator();
    TwoThreeIterator(const TwoThreeIterator& rhs) noexcept = default;
    ~TwoThreeIterator() = default;
    TwoThreeIterator& operator=(const TwoThreeIterator& rhs) noexcept = default;

    TwoThreeIterator& operator++();
    TwoThreeIterator& operator++(int);
    TwoThreeIterator& operator--();
    TwoThreeIterator& operator--(int);

    const T& operator*() const;
    const T* operator->() const;

    bool operator==(const TwoThreeIterator& rhs) const;
    bool operator!=(const TwoThreeIterator& rhs) const;

  private:
    TwoThreeTreeNode< T >* node_;
  };
}

#endif
