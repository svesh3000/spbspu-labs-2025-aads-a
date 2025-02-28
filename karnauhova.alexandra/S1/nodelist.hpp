#ifndef NODELIST_HPP
#define NODELIST_HPP

template< typename T >
struct NodeList
{
  T data;
  NodeList< T >* next;
  //NodeList(const T& value) : data(value), next(nullptr) {}
};
#endif
