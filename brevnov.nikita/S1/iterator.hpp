#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "node.hpp"
namespace brevnov
{
  template< typename T >
  class List;
  template< typename T >
  class ConstIterator;
  template< typename T >
  class Iterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class List< T >;
    friend class ConstIterator< T >;
  public:
    Iterator(): node_(nullptr) {};
    Iterator(Node< T > * node): node_(node) {};
  private:
    Node< T > * node_;
  }
}

#endif
