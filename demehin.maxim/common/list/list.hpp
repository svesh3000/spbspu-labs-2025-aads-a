#ifndef LIST_HPP
#define LIST_HPP
#include "iterator.hpp"

namespace demehin
{
  template< typename T >
  struct List
  {
  public:
    using Iter = ListIterator< T >;

    List();

    ~List();

    List(const List< T >&);
    List(List< T >&&);

    Iter begin();
    Iter end();

    size_t size() const;

    void pop_front();

    void push_back(const T&);

    T& front();

  private:
    using Node = Node< T >;

    Node* fake_;
    Node* head_;
    Node* tail_;
    size_t size_;

  };

  template< typename T >
  List< T >::List():
    fake_(static_cast< Node< T >* >(new char[sizeof(Node < T >)])),
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {
    new (fake_) Node< T >(T());
  }
}

#endif
