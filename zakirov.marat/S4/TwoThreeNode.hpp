#ifndef TWOTHREENODE_HPP
#define TWOTHREENODE_HPP
#include <cstddef>

namespace zakirov
{
  template < typename T, typename K >
  class TwoThreeNode
  {
  public:
    TwoThreeNode(const T & data, K key);
    TwoThreeNode< T, K > * top_;
    TwoThreeNode< T, K > * left_;
    TwoThreeNode< T, K > * middle_;
    TwoThreeNode< T, K > * right_;
    T data_;
    K key_;
  };

  template < typename T, typename K >
  TwoThreeNode< T, K >::TwoThreeNode(const T & data, K key):
    top_(nullptr),
    left_(nullptr),
    middle_(nullptr),
    right_(nullptr),
    key_(key),
    data_(data)
  {}
}

#endif
