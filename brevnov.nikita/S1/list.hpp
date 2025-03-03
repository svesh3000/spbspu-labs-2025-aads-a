#ifndef LIST_HPP
#define LIST_HPP
#include <initializer_list>
#include "node.hpp"
namespace brevnov
{
  template< typename T >
  class List
  {
  public:
    List();
    List(size_t n, const T& val);
    List(const List< T > & copy);
    List(List< T > && del);
    template< typename InputIterator >
    List< T >(InputIterator begin, InputIterator end);
    List< T >(initializer_list<value_type> il);

  private:
    Node< T > * head_;
    Node< T > * tail_;
    size_t size;
  }

  template< typename T >
  List::List():
    head_(nullptr),
    tail_(new Node< T >(T())),
    size_(0)
  {}

  template< typename T >
  List::List(size_t n, const T& val):
    List()
  {
    for (size_t i = 0, i < n; i++)
    {
      push_back(val);
    }
  }

  template< typename T >
  List::List(const List< T > & copy)
  {
    for (ConstIterator< T > it = copy.begin(); it != copy.end(); ++it)
    {
      push_back(*it);
    }
  }

  template< typename T >
  List::List(List< T > && del):
    head_(del.head_),
    tail_(del.tail_),
    size_(del.size_)
  {
    del.head_ = nullptr;
    del.tail_ = new Node< T >(T());
    del.size_ = 0;
  }

  template< typename T >
  template< typename InputIterator >
  List::List(InputIterator begin, InputIterator end):
    List()
  {
    for (; begin != end; ++begin)
    {
      push_back(begin);
    }
  }

  template< typename T >
  List::List(initializer_list<value_type> il):
    List(il.begin(), il.end())
  {}
}  
#endif
