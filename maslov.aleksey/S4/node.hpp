#ifndef NODE_HPP
#define NODE_HPP

#include <utility>

namespace maslov
{
  template< class Key, class T >
  struct BiTreeNode
  {
    std::pair< const Key, T > data;
    BiTreeNode * left;
    BiTreeNode * right;
    BiTreeNode * parent;
  };
}

#endif
