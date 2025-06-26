#ifndef BINODE_HPP
#define BINODE_HPP

namespace zakirov
{
  template < class K, class T >
  struct BiNode
  {
    BiNode(K key, const T & data);
    BiNode< K, T > left_;
    BiNode< K, T > right_;
    BiNode< K, T > parent_;
    std::pair< K, T > value_;
  };
}

#endif
