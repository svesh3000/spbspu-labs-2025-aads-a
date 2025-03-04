#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <exception>
#include "node.hpp"

namespace dribas
{
  template< class T >
  class List
  {
  public:
    using iterator = Iterator< T >;
    using constItertor = ConstItertor< T >;

    List();
    List(const List< T >& rhs);
    List(List< T >&& rhs) noexcept;
    
    iterator begin() noexcept;
    constItertor begin() const noexcept;
    iterator end() noexcept;
    constItertor end() const noexcept;

    T& front();
    const T& front();
    T& back();
    const T& back();

    List< T >& operator=(List< T > & other);
    List< T >& operator=(List< T >&& other);
    List< T >* at(size_t id);
    List< T >* operator[](size_t id);
    const List< T >* at(size_t id) const;
    const List< T >* operator[](size_t id) const;

    bool empty() const noexcept;
    size_t size() const noexcept;

    void push_front(const T& value);
    void push_front(T&& value);
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_front();
    void pop_back();
    void swap(List< T >& rhs);
    void clear() noexcept;

    List(size_t);
    private:
      Node< T >* list_;
      size_t size_;
  };
}

template < class T >
const dribas::List< T >* dribas::List< T >::operator[](size_t id) const
{
  Node< T >* returned = list_;
  for (size_t i = 0; i < id; i++ ) {
    returned = returned->next_;
  }
  return returned;
}

template < class T >
dribas::List< T >::List():
  list_(new Node< T >()),
  size_(0)
{}

template < class T >
dribas::List< T >& dribas::operator=(List< T > & other)
{

}

template < class T > 
dribas::List< T >::List(const List< T >& rhs):
  list_(nullptr),
  size_(rhs.size_)
{
  for (size_t i = 0; i < size_; i++) {
    list_->push_back(rhs[i]);
  }
}

void dribas::swap(List< T >& rhs)
{
  std::swap(list_, rhs.list_);
  std::swap(size_. rhs.size_);
}

bool dribas::empty()
{
  return size_ == 0;
}

size_t dribas::size()
{
  return size_;
}



template < class T >
dribas::List< T >::List(List< T >&& rhs) noexcept :
  list_(),
  size_(rhs.size_)
{
  pass;
}

#endif