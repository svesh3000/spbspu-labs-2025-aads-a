#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <algorithm>
#include "iterator.hpp"
#include "nodelist.hpp"

template< typename T >
class List
{
public:
  using Node = NodeList< T >;
  using Iterator = ListIterator< T >;
  List();
  ~List();
  bool empty() const noexcept;
  size_t size() const noexcept;
  Iterator begin() const;
  Iterator end() const;
  T& front();
  T& back();
  void clear();
  void swap(List< T >& other);
  void push_front(const T& data);
  void pop_front();
private:
  Node* fake_;
  size_t size_;
};

template< typename T >
List< T >::List():
  fake_(reinterpret_cast< NodeList< T >* >(new char[sizeof(NodeList< T >)])),
  size_(0)
{
  fake_->next = fake_;
}

template< typename T >
void List< T >::swap(List< T >& other)
{
  std::swap(fake_, other.fake_);
  std::swap(size_, other.size_);
}

template< typename T >
void List< T >::pop_front()
{
  fake_->next = fake_->next->next;
  if (fake_->next == fake_)
  {
    return;
  }
  delete fake_->next;
  size_--;
}

template< typename T >
void List< T >::push_front(const T& data)
{
  Node* new_element = new Node{data, fake_->next};
  fake_->next = new_element;
  size_++;
}

template< typename T >
void List< T >::clear()
{
  NodeList< T >* last = fake_->next;
  while (!size_)
  {
    NodeList< T >* now = last->next;
    delete last;
    last = now;
  }
}

template< typename T >
List< T >::~List()
{
  clear();
  delete[] reinterpret_cast<char*>(fake_);
}

template< typename T >
T& List< T >::front()
{
  return fake_->next->data;
}

template< typename T >
T& List< T >::back()
{
  NodeList< T >* now = fake_;
  while (now->next != fake_)
  {
    now = now->next;
  }
  return now->data;
}

template< typename T >
ListIterator< T > List< T >::begin() const
{
  return ListIterator< T >{fake_->next};
}

template< typename T >
ListIterator< T > List< T >::end() const
{
  NodeList< T >* now = fake_;
  while (now->next != fake_)
  {
    now = now->next;
  }
  return ListIterator< T >{now};
}

template< typename T >
bool List< T >::empty() const noexcept
{
  return size_ == 0;
}

template< typename T >
size_t List< T >::size() const noexcept
{
  return size_;
}

#endif
