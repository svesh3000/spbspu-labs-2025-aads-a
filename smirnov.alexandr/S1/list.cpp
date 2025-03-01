#include "List.hpp"

template< typename T >
List< T >::List() = default;

template< typename T >
void List< T >::pushBack(const T & value)
{
  data.push_back(value);
}

template< typename T >
bool List< T >::isEmpty() const
{
  return data.empty();
}

template< typename T >
size_t List< T >::getSize() const
{
  return data.size();
}

template< typename T >
typename List< T >::ConstIterator List< T >::begin() const
{
  return data.begin();
}

template< typename T >
typename List< T >::ConstIterator List< T >::end() const
{
  return data.end();
}
