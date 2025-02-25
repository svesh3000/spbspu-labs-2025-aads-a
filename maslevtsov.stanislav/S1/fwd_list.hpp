#ifndef FWD_LIST
#define FWD_LIST

#include <cstddef>
#include "fwd_list_node.hpp"
#include "fwd_iterator.hpp"

namespace maslevtsov {
  template< typename T >
  class FwdList
  {
  public:
    FwdList();
    ~FwdList();

    FwdIterator< T > begin();
    FwdIterator< T > end();

    T& front() const;
    T& back() const;

    std::size_t size() const;
    bool empty() const;

    void push_front(const T& value);
    void push_front(T&& value);
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_front();
    void swap(FwdList& other);
    void clear();

  private:
    FwdListNode< T >* head_;
    FwdListNode< T >* tail_;
    std::size_t size_;
  };
}

template< typename T >
maslevtsov::FwdList< T >::FwdList():
  head_(nullptr),
  tail_(head_),
  size_(0)
{}

template< typename T >
maslevtsov::FwdList< T >::~FwdList()
{
  clear();
}

template< typename T >
maslevtsov::FwdIterator< T > maslevtsov::FwdList< T >::begin()
{
  return FwdIterator< T >(head_);
}

template< typename T >
maslevtsov::FwdIterator< T > maslevtsov::FwdList< T >::end()
{
  return FwdIterator< T >(tail_->next_);
}

template< typename T >
T& maslevtsov::FwdList< T >::front() const
{
  return head_->data_;
}

template< typename T >
T& maslevtsov::FwdList< T >::back() const
{
  return tail_->data_;
}

template< typename T >
std::size_t maslevtsov::FwdList< T >::size() const
{
  return size_;
}

template< typename T >
bool maslevtsov::FwdList< T >::empty() const
{
  return size_ == 0;
}

template< typename T >
void maslevtsov::FwdList< T >::push_front(const T& value)
{
  FwdListNode< T >* new_node = new FwdListNode< T >(value, head_);
  head_ = new_node;
  tail_->next_ = head_;
  ++size_;
}

template< typename T >
void maslevtsov::FwdList< T >::push_front(T&& value)
{
  FwdListNode< T >* new_node = new FwdListNode< T >(std::move(value), head_);
  head_ = new_node;
  tail_->next_ = head_;
  ++size_;
}

template< typename T >
void maslevtsov::FwdList< T >::push_back(const T& value)
{
  FwdListNode< T >* new_node = new FwdListNode< T >(value, head_);
  tail_ = new_node;
  ++size_;
}

template< typename T >
void maslevtsov::FwdList< T >::push_back(T&& value)
{
  FwdListNode< T >* new_node = new FwdListNode< T >(std::move(value), head_);
  tail_ = new_node;
  ++size_;
}

template< typename T >
void maslevtsov::FwdList< T >::pop_front()
{
  FwdListNode< T >* to_delete = head_;
  head_ = to_delete->next_;
  tail_->next_ = head_;
  delete to_delete;
  --size_;
}

template< typename T >
void maslevtsov::FwdList< T >::swap(FwdList& other)
{
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template< typename T >
void maslevtsov::FwdList< T >::clear()
{
  while (!empty()) {
    pop_front();
  }
}

#endif
