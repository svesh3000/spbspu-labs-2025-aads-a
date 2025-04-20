#ifndef NODE_HPP
#define NODE_HPP
#include <utility>

template< class Key, class Value >
struct Node
{
  std::pair< const Key, Value > data;
  Node* left;
  Node* right;
  Node* parent;

  Node(const Key& k, const Value& v, Node* p);
};

template < class Key, class Value >
Node< Key, Value >::Node(const Key& k, const Value& v, Node* p):
  data(std::make_pair(k, v)),
  left(nullptr),
  right(nullptr),
  parent(p)
{
}

#endif
