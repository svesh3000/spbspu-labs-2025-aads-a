#include "IteratorFwd.hpp"

template< class T >
gavrilova::IteratorFwd< T >& gavrilova::IteratorFwd< T >::operator++()
{
  node = node->next;
  return *this;
}

template< class T >
gavrilova::IteratorFwd<T> gavrilova::IteratorFwd<T>::operator++(int)
{
  IteratorFwd< T > result(*this);
  ++(*this);
  return result;
}

template< class T >
bool gavrilova::IteratorFwd<T>::operator==(const this_t& rhs) const
{
  return node == rhs.node;
}

template< class T >
bool gavrilova::IteratorFwd<T>::operator!=(const this_t& rhs) const
{
  return !(rhs == *this);
}

template< class T >
T& gavrilova::IteratorFwd<T>::operator*()
{
  return node->data;
}

template< class T >
T* gavrilova::IteratorFwd<T>::operator->()
{
  return std::addressof(node->data);
}
