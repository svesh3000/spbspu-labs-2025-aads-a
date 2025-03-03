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
    ~List();

    List< T > & operator=(const List< T > & copy);
    List< T > & operator=(List< T > && copy);
    List< T > & operator=(initializer_list<value_type> il);

    void clear();
    void swap(List< T > & hl);
  private:
    Node< T > * head_;
    Node< T > * tail_;
    size_t size;
  }

  template< typename T >
  List< T >::List():
    head_(nullptr),
    tail_(new Node< T >(T())),
    size_(0)
  {}

  template< typename T >
  List< T >::List(size_t n, const T& val):
    List()
  {
    for (size_t i = 0, i < n; i++)
    {
      push_back(val);
    }
  }

  template< typename T >
  List< T >::List(const List< T > & copy)
  {
    for (ConstIterator< T > it = copy.cbegin(); it != copy.cend(); ++it)
    {
      push_back(*it);
    }
  }

  template< typename T >
  List< T >::List(List< T > && del):
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
  List< T >::List(InputIterator begin, InputIterator end):
    List()
  {
    for (; begin != end; ++begin)
    {
      push_back(begin);
    }
  }

  template< typename T >
  List< T >::List(initializer_list<value_type> il):
    List(il.begin(), il.end())
  {}

  template< typename T >
  List::~List()
  {
    clear();
    delete tail;
  }

  template< typename T >
  List< T >::clear()
  {
    while (!clear())
    {
      popFront();
    }
  }

  template< typename T >
  List< T > & List< T >::operator=(const List< T > & copy)
  {
    List< T > cpy(copy);
    std::swap(cpy);
    return *this;
  }

  template< typename T >
  void List< T >::swap(List< T > & hl):
  {
    std::swap(head_, hl.head_);
    std::swap(tail_, hl.tail_);
    std::swap(size_, hl.size_);
  }

  template< typename T >
  List< T > & List< T >::operator=(List< T > && copy)
  {
    List< T > cpy(std::move(copy));
    std::swap(cpy);
    return *this;
  }

  template< typename T >
  List< T > & List< T >::operator=(initializer_list<value_type> il)
  {
    List< T > cpy(il);
    std::swap(cpy);
    return *this;
  }
}  
#endif
