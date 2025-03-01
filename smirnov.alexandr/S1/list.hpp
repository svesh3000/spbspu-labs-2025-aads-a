#ifndef LIST_HPP
#define LIST_HPP
#include <list>

template< typename T >
class List
{
public:
  List();
  void pushBack(const T & value);
  bool isEmpty() const;
  size_t getSize() const;
  using ConstIterator = typename std::list<T>::const_iterator;
  ConstIterator begin() const;
  ConstIterator end() const;
private:
  std::list<T> data;
};
