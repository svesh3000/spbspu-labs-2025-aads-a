#ifndef LIST_HPP
#define LIST_HPP
#include <list>

template< typename T >
class List
{
public:
  List() = default;
  void pushBack(const T & value);
  bool isEmpty() const;
  size_t getSize() const;
  using ConstIterator = typename std::list< T >::const_iterator;
  ConstIterator begin() const;
  ConstIterator end() const;
private:
  std::list< T > data;
};

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
