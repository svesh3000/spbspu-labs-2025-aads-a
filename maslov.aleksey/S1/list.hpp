#ifndef LIST_HPP
#define LIST_HPP

namespace maslov
{
  template< typename T >
  struct Iterator
  {
    T & operator*();
    T * operator->();
    Iterator & operator++();
    Iterator operator++(int);
    Iterator & operator--();
    Iterator operator--(int);
  };
  template< typename T >
  struct List
  {
    void push_front(const T &);
    Iterator< T > begin() const;
    Iterator< T > end() const;
  };
}

#endif