#ifndef HASH_NODE_HPP
#define HASH_NODE_HPP

namespace maslov
{
  template< class Key, class T >
  struct HashNode
  {
    Key key;
    T value;
    bool occupied = false;
    bool deleted = false;
  };
}

#endif
