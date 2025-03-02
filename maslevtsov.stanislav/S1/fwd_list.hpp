#ifndef FWD_LIST_HPP
#define FWD_LIST_HPP

#include <cstddef>
#include "fwd_list_node.hpp"
#include "fwd_iterator.hpp"

namespace maslevtsov {
  template< typename T >
  class FwdList
  {
  public:
    FwdList();
    FwdList(const FwdList& rhs);
    FwdList(FwdList&& rhs);
    ~FwdList();
    FwdList& operator=(const FwdList& rhs);
    FwdList& operator=(FwdList&& rhs);

    FwdIterator< T > begin() const noexcept;
    FwdIterator< T > end() const noexcept;

    T& front() const;
    T& back() const;

    std::size_t size() const noexcept;
    bool empty() const noexcept;

    void push_front(const T& value);
    void push_front(T&& value);
    void pop_front() noexcept;
    void swap(FwdList& other) noexcept;
    void clear() noexcept;

  private:
    FwdListNode< T >* head_;
    FwdListNode< T >* tail_;
    std::size_t size_;
  };
}

template< typename T >
maslevtsov::FwdList< T >::FwdList():
  head_(nullptr),
  tail_(new FwdListNode< T >{T(), nullptr}),
  size_(0)
{
  tail_->next_ = tail_;
}

template< typename T >
maslevtsov::FwdList< T >::FwdList(const FwdList& rhs):
  FwdList()
{
  FwdList< T > reversed;
  for (auto i = rhs.begin(); i != rhs.end(); ++i) {
    reversed.push_front(*i);
  }
  for (auto i = reversed.begin(); i != reversed.end(); ++i) {
    push_front(*i);
  }
}

template< typename T >
maslevtsov::FwdList< T >::FwdList(FwdList&& rhs):
  head_(rhs.head_),
  tail_(rhs.tail_),
  size_(rhs.size_)
{
  rhs.head_ = nullptr;
  rhs.tail_ = nullptr;
}

template< typename T >
maslevtsov::FwdList< T >::~FwdList()
{
  clear();
  delete tail_;
}

template< typename T >
typename maslevtsov::FwdList< T >::FwdList& maslevtsov::FwdList< T >::operator=(const FwdList& rhs)
{
  FwdList< T > copied_rhs(rhs);
  swap(copied_rhs);
  return *this;
}

template< typename T >
typename maslevtsov::FwdList< T >::FwdList& maslevtsov::FwdList< T >::operator=(FwdList&& rhs)
{
  FwdList< T > copied_rhs(std::move(rhs));
  swap(copied_rhs);
  return *this;
}

template< typename T >
maslevtsov::FwdIterator< T > maslevtsov::FwdList< T >::begin() const noexcept
{
  return FwdIterator< T >(head_);
}

template< typename T >
maslevtsov::FwdIterator< T > maslevtsov::FwdList< T >::end() const noexcept
{
  return FwdIterator< T >(tail_);
}

template< typename T >
T& maslevtsov::FwdList< T >::front() const
{
  return head_->data_;
}

template< typename T >
T& maslevtsov::FwdList< T >::back() const
{
  FwdIterator< T > it = begin();
  for (; it != end(); ++it);
  return *it;
}

template< typename T >
std::size_t maslevtsov::FwdList< T >::size() const noexcept
{
  return size_;
}

template< typename T >
bool maslevtsov::FwdList< T >::empty() const noexcept
{
  return size_ == 0;
}

template< typename T >
void maslevtsov::FwdList< T >::push_front(const T& value)
{
  FwdListNode< T >* new_node = new FwdListNode< T >{value, nullptr};
  new_node->next_ = empty() ? tail_ : head_;
  tail_->next_ = new_node;
  head_ = new_node;
  ++size_;
}

template< typename T >
void maslevtsov::FwdList< T >::push_front(T&& value)
{
  FwdListNode< T >* new_node = new FwdListNode< T >{std::move(value), nullptr};
  new_node->next_ = empty() ? tail_ : head_;
  tail_->next_ = new_node;
  head_ = new_node;
  ++size_;
}

template< typename T >
void maslevtsov::FwdList< T >::pop_front() noexcept
{
  FwdListNode< T >* new_head = head_->next_;
  delete head_;
  tail_->next_ = new_head;
  head_ = new_head;
  --size_;
}

template< typename T >
void maslevtsov::FwdList< T >::swap(FwdList& other) noexcept
{
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template< typename T >
void maslevtsov::FwdList< T >::clear() noexcept
{
  while (!empty()) {
    pop_front();
  }
}

#endif
