#ifndef LIST_HPP
#define LIST_HPP

namespace maslov
{
  template< typename T >
  struct List
  {
    void push_back(const T &);
  };
}

#endif