#ifndef FWD_ITERATOR_HPP
#define FWD_ITERATOR_HPP
#include <iterator>
#include "fwd_list_node.hpp"

namespace zakirov
{
  template< typename T >
  struct FwdIterator: public std::iterator< std::forward_iterator_tag, T >
  {
    FwdListNode< T > * node_;

    FwdIterator():
      node_(nullptr)
    {};

    FwdIterator(FwdListNode< T > * node):
      node_(node)
    {};

    ~FwdIterator() = default;
    FwdIterator(const FwdIterator< T > &) = default;
    FwdIterator< T > & operator=(const FwdIterator< T > &) = default;

  };
}

#endif
