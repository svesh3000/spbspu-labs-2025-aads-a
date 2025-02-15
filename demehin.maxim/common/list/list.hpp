#ifndef LIST_HPP
#define LIST_HPP
#include "iterator.hpp"
#include "node.hpp"

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
    using Node = demehin::Node< T >;

    Node* fake_;
    Node* tail_;
    size_t size_;

  };

  template< typename T >
  using Node = demehin::Node< T >;

  template< typename T >
  List< T >::List():
    fake_(reinterpret_cast< Node* >(new char[sizeof(Node)])),
    tail_(nullptr),
    size_(0)
  {
    //fake_ = nullptr;
    new (fake_) Node(T());
  }

  template< typename T >
  List< T >::~List()
  {
    Node* current = fake_->next_;
    while (current != nullptr)
    {
      Node* next = current->next_;
      delete current;
      current = next;
    }
    delete[] reinterpret_cast< char* >(fake_);
  }

  template< typename T >
  List< T >::List(const List< T >& rhs):
    List()
  {
    
  }

  template < typename T >
  List< T >::List(List< T >&& rhs):
    fake_(rhs.fake_),
    tail_(rhs.tail_)
  {
    rhs.fake_ = nullptr;
    rhs.tail_ = nullptr;
  }

  template < typename T >
  ListIterator< T > List< T >::begin()
  {
    return ListIterator< T >(fake_->next_);
  }

  template < typename T >
  ListIterator< T > List< T >::end()
  {
    return ListIterator< T >(tail_);
  }

  template < typename T >
  void List< T >::pop_front()
  {
    
  }

  template < typename T >
  T& List< T >::front()
  {
    return fake_.next_->data_;
  }

  template < typename T >
  size_t List< T >::size() const
  {
    return size_;
  }

}

#endif
