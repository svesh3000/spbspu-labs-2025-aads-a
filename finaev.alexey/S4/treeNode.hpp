#ifndef TREENODE_HPP
#define TREENODE_HPP
#include <utility>

namespace finaev
{
  template < class key, class value >
  struct treeNode
  {
    std::pair< key, value > data;
    treeNode< key, value >* left;
    treeNode< key, value >* right;
    treeNode< key, value >* parent;
    int height;
    treeNode(const key& k, const value& val, treeNode< key, value >* p);
  };

  template < class key, class value >
  treeNode< key, value >::treeNode(const key& k, const value& val, treeNode< key, value >* p):
    data(std::pair< key, value >(k, val)),
    left(nullptr),
    right(nullptr),
    parent(p),
    height(1)
  {}
}

#endif
