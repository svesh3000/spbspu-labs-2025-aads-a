#ifndef NODE_HPP
#define NODE_HPP
#include <utility>

namespace abramov
{
  template< class Key, class Value >
  struct Node
  {
    Node(const std::pair< Key, Value > &p, const Node< Key, Value > *parent);
  private:
    std::pair< Key, Value > data_;
    Node< Key, Value > *parent_;
    Node< Key, Value > *left_;
    Node< Key, Value > *rigth_;
    size_t heigth_;
  };

  template< class Key, class Value >
  Node::Node(const std::pair< Key, Value > &p, const Node< Key, Value > *parent):
    data_(p),
    parent_(parent),
    left_(parent->left_),
    rigth_(parent->right_)
    heigth_(parent->heigth + 1)
  {}
}
#endif
