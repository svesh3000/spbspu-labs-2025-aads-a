#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP
#include "iterator.hpp"
namespace brenvov
{
  template< typename T >
  class List;
  template< typename T >
  class ConstIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class List< T >;
  public:
    ConstIterator(): node_(nullptr) {}
    ConstIterator(Node< T > * node): node_(node) {}
    ConstIterator(Iterator< T > it): node_(it.node_) {}
  private:
    Node< T > * node_;
  }
}
#endif
