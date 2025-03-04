#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <stdexcept>
#include "node.hpp"

namespace dribas
{
  template< class T >
  class List
  {
  public:
    //using iterator = Iterator< T >;
    //using constItertor = ConstItertor< T >;

    List();
    List(const List< T >& rhs);
    List(List< T >&& rhs) noexcept;
    
    //iterator begin() noexcept;
    //constItertor begin() const noexcept;
    //iterator end() noexcept;
    //constItertor end() const noexcept;

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    List< T >& operator=(List< T >& other);
    List< T >& operator=(List< T >&& other) noexcept;
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
    void move(List< T >&& rhs);

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
dribas::List< T >* dribas::List< T >::operator[](size_t id)
{
  return const_cast< List< T >* >(static_cast< const List< T >* >(this)->operator[](id));
}

template < class T >
const dribas::List< T >* dribas::List< T >::at(size_t id) const
{
  if (id > size_) {
    throw std::out_of_range("ID IS OUT OF RANGE");
  }
  return this[id];
}

template < class T >
dribas::List< T >* dribas::List< T >::at(size_t id)
{
  return const_cast< List< T >* >(static_cast< const List< T >* >(this)->at(id)); 
}

template < class T >
dribas::List< T >::List():
  list_(new Node< T >()),
  size_(0)
{}

template < class T > 
dribas::List< T >::List(const List< T >& rhs):
  list_(nullptr),
  size_(rhs.size_)
{
  for (size_t i = 0; i < size_; i++) {
    list_->push_back(rhs[i]);
  }
}

template < class T >
void dribas::List< T >::swap(List< T >& rhs)
{
  std::swap(list_, rhs.list_);
  std::swap(size_, rhs.size_);
}

template < class T >
bool dribas::List< T >::empty() const noexcept
{
  return size_ == 0;
}

template < class T>
size_t dribas::List< T >::size() const noexcept
{
  return size_;
}

template < class T >
dribas::List< T >& dribas::List< T >::operator=(List< T >& other)
{
  List< T > copy(other);
  swap(copy);
  return *this;
}

template < class T >
dribas::List< T >& dribas::List< T >::operator=(List< T >&& other) noexcept
{
  list_ = std::move_if_noexcept(other.list_);
  size_ = std::move_if_noexcept(other.size_);
  return *this;
}

template < class T >
dribas::List< T >::List(List< T >&& rhs) noexcept:
{
  clear();
  size_ = rhs.size_;
  rhs.size_ = 0;
  list_->data_ = rhs.list_->data_;
  list_->next_ = rhs.list_->next_;
  rhs.list_->data_ = T();
  rhs.list_->next_ = nullptr;
}

#endif