#ifndef LIST_HPP
#define LIST_HPP

#include "listNode.hpp"
#include "iterators.hpp"

namespace shramko
{
  template< typename T >
  class FwdList
  {
  public:
    FwdList();
    ~FwdList();
  
    FwdIterator< T > begin();
    FwdIterator< T > end();

    T& front() const;
  
    std::size_t size() const;
    bool empty() const;
  
    void push_front(const T& value);
    void push_front(T&& value);
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
shramko::FwdList< T >::FwdList():
  head_(nullptr),
  tail_(new FwdListNode< T >(T())),
  size_(0)
{
  tail_->next_ = tail_;
}

template< typename T >
shramko::FwdList< T >::~FwdList()
{
  clear();
  delete tail_;
}

template< typename T >
shramko::FwdIterator< T > shramko::FwdList< T >::begin()
{
  return FwdIterator< T >(head_);
}

template< typename T >
shramko::FwdIterator< T > shramko::FwdList< T >::end()
{
  return FwdIterator< T >(tail_);
}

template< typename T >
T& shramko::FwdList< T >::front() const
{
  return head_->data_;
}

template< typename T >
std::size_t shramko::FwdList< T >::size() const
{
  return size_;
}

template< typename T >
bool shramko::FwdList< T >::empty() const
{
  return size_ == 0;
}

template< typename T >
void shramko::FwdList< T >::push_front(const T& value)
{
  FwdListNode< T >* new_node = new FwdListNode< T >(value);
  new_node->next_ = empty() ? tail_ : head_;
  tail_->next_ = new_node;
  ++size_;
}

template< typename T >
void shramko::FwdList< T >::push_front(T&& value)
{
  FwdListNode< T >* new_node = new FwdListNode< T >(std::move(value));
  new_node->next_ = empty() ? tail_ : head_;
  tail_->next_ = new_node;
  head_ = new_node;
  ++size_;
}

template< typename T >
void shramko::FwdList< T >::pop_front()
{
  FwdListNode< T >* new_head = head_->next_;
  delete head_;
  tail_->next_ = new_head;
  head_ = new_head;
  --size_;
}

template< typename T >
void shramko::FwdList< T >::swap(FwdList& other)
{
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template< typename T >
void shramko::FwdList< T >::clear()
{
  while (!empty()) {
    pop_front();
  }
}

#endif