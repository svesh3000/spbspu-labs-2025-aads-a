#include "IteratorFwd.hpp"

template< typename T >
IteratorFwd< T >& IteratorFwd< T >::operator++()
{
  node = node->next;
  return *this;
}

template< typename T >
IteratorFwd<T> IteratorFwd<T>::operator++(int)
{
  IteratorFwd< T > result(*this);
  ++(*this);
  return result;
}

template< typename T >
bool IteratorFwd<T>::operator==(const this_t& rhs) const
{
  return node == rhs.node;
}

template< typename T >
bool IteratorFwd<T>::operator!=(const this_t& rhs) const
{
  return !(rhs == *this);
}

template< typename T >
T& IteratorFwd<T>::operator*()
{
  return node->data;
}

template< typename T >
T* IteratorFwd<T>::operator->()
{
  return std::addressof(node->data);
}
