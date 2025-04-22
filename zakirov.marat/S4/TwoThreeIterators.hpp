#ifndef TWOTHREEITERATORS_HPP
#define TWOTHREEITERATORS_HPP
#include <iterator>
#include "TwoThreeNode.hpp"

namespace zakirov
{
  template< typename T, typename K >
  class TwoThreeIter: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    TwoThreeIter();
    ~TwoThreeIter() = default;
    T & operator*() const;
    T * operator->() const;
    TwoThreeIter< T, K > & operator++();
    TwoThreeIter< T, K > operator++(int);
    TwoThreeIter< T, K > & operator--();
    TwoThreeIter< T, K > operator--(int);
    bool operator!=(const TwoThreeIter< T, K > &) const;
    bool operator==(const TwoThreeIter< T, K > &) const;
  private:
    TwoThreeNode< T, K > * node_;
    bool first_ptr_;
  };

  template< typename T, typename K >
  TwoThreeIter< T, K >::TwoThreeIter():
    node_(nullptr)
  {}

  template< typename T, typename K >
  T & TwoThreeIter< T, K >::operator*() const
  {}

  template< typename T, typename K >
  T * TwoThreeIter< T, K >::operator->() const
  {}

  template< typename T, typename K >
  TwoThreeIter< T, K > & TwoThreeIter< T, K >::operator++()
  {}

  template< typename T, typename K >
  TwoThreeIter< T, K > TwoThreeIter< T, K >::operator++(int)
  {}

  template< typename T, typename K >
  TwoThreeIter< T, K > & TwoThreeIter< T, K >::operator--()
  {}

  template< typename T, typename K >
  TwoThreeIter< T, K > TwoThreeIter< T, K >::operator--(int)
  {}

  template< typename T, typename K >
  bool TwoThreeIter< T, K >::operator!=(const TwoThreeIter< T, K > &) const
  {}

  template< typename T, typename K >
  bool TwoThreeIter< T, K >::operator==(const TwoThreeIter &) const
  {}
}

#endif
