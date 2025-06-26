#ifndef BINODE_HPP
#define BINODE_HPP
#include <utility>

namespace zakirov
{
  template < class K, class T >
  struct BiNode
  {
    BiNode() = default;
    BiNode(std::pair< K, T > value):
    left_(nullptr),
    right_(nullptr),
    parent_(nullptr),
    value_.first(value.first),
    value_.second(value.second)
  {}

    BiNode< K, T > * left_;
    BiNode< K, T > * right_;
    BiNode< K, T > * parent_;
    std::pair< K, T > value_;
  };

  template < class K, class T >
  BiNode< K, T >::BiNode(std::pair< K, T > value):
    left_(nullptr),
    right_(nullptr),
    parent_(nullptr),
    value_.first(value.first),
    value_.second(value.second)
  {}
}

#endif
