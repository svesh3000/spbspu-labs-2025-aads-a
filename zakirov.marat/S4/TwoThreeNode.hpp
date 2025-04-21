#ifndef TWOTHREENODE_HPP
#define TWOTHREENODE_HPP
#include <cstddef>

namespace zakirov
{
  template < typename T>
  class TwoThreeNode
  {
  public:
  TwoThreeNode(const T & data, size_t key);
    TwoThreeNode< T > * top_;
    TwoThreeNode< T > * left_;
    TwoThreeNode< T > * middle_;
    TwoThreeNode< T > * right_;
    T data_;
    size_t key_;
  };

  template < typename T>
  TwoThreeNode< T >::TwoThreeNode(const T & data, size_t key):
    top_(nullptr),
    left_(nullptr),
    middle_(nullptr),
    right_(nullptr),
    key_(key),
    data_(data)
  {}
}

#endif
