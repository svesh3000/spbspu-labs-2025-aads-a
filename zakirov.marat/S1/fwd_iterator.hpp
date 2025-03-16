#ifndef FWD_ITERATOR_HPP
#define FWD_ITERATOR_HPP
#include "fwd_list_node.hpp"

namespace zakirov
{
  template< typename T >
  struct FwdIterator: public std::iterator< std::forward_iterator_tag, T >
  {
    FwdListNode< T > * node_;

    FwdIterator();
    FwdIterator(FwdListNode< T > * node);
    ~FwdIterator() = default;
    FwdIterator(const FwdIterator< T > &) = default;
    FwdIterator< T > & operator=(const FwdIterator< T > &) = default;

    template< typename T >
    FwdIterator< T >::FwdIterator():
      node_(nullptr)
    {}

    template< typename T >
    FwdIterator< T >::FwdIterator(FwdListNode< T > * node)
    {
      node_(node)
    };
  };
}

#endif
