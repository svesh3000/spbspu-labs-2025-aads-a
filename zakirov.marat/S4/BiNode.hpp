#ifndef BINODE_HPP
#define BINODE_HPP

namespace zakirov
{
  template < class K, class T >
  struct BiNode
  {
    BiNode(K key, const T & data);
    BiNode< K, T > left;
    BiNode< K, T > right;
    BiNode< K, T > parent;
    std::pair< K, T > value;
  };
}

#endif
