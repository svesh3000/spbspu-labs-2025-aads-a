#ifndef NODE_HPP
#define NODE_HPP

#include <cstddef>
#include <utility>

namespace duhanina
{
  template < typename Key, typename Value >
  struct Node
  {
    std::pair< const Key, Value > data;
    Node* left;
    Node* right;
    Node* parent;
    size_t height;

    Node(const Key& k, const Value& v, Node* p);
  };

  template < typename Key, typename Value >
  Node< Key, Value >::Node(const Key& k, const Value& v, Node* p):
    data(std::make_pair(k, v)),
    parent(p),
    left(nullptr),
    right(nullptr),
    height(1)
  {}
}

#endif
