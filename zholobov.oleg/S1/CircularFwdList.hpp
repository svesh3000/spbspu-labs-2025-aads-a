#ifndef CIRCULARFWDLIST_HPP
#define CIRCULARFWDLIST_HPP

#include <cstddef>
#include <utility>

#include "CircularFwdListIterators.hpp"
#include "FwdListNode.hpp"

namespace zholobov {

  template < typename T >
  class CircularFwdList {
  public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const reference;
    using iterator = CircularFwdListIterator< T >;
    using const_iterator = CircularFwdListConstIterator< T >;

    CircularFwdList();
    explicit CircularFwdList(size_t n);
    CircularFwdList(size_t n, const value_type& val);

    CircularFwdList(const CircularFwdList& other);
    CircularFwdList(CircularFwdList&& other) noexcept;

    ~CircularFwdList();

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;

    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    bool empty() const noexcept;
    size_t size() const { return size_; }

    void assign(size_t n, const value_type& val);
    void push_front(const value_type& val);
    void push_front(value_type&& val);
    void push_back(const value_type& val);
    void push_back(value_type&& val);

    void pop_front();
    void pop_back();
    void remove(const value_type& val);
    template < class Predicate >
    void remove_if(Predicate pred);

    void splice_after(const_iterator pos, CircularFwdList< T >& other);
    void splice_after(const_iterator pos, CircularFwdList< T >&& other);
    void splice_after(const_iterator pos, CircularFwdList< T >& other, const_iterator it);
    void splice_after(const_iterator pos, CircularFwdList< T >&& other, const_iterator it);
    void splice_after(const_iterator pos, CircularFwdList< T >& other, const_iterator first, const_iterator last);
    void splice_after(const_iterator pos, CircularFwdList< T >&& other, const_iterator first, const_iterator last);

    void swap(CircularFwdList& other) noexcept;
    void clear() noexcept;

  private:
    FwdListNode< value_type >* head_;
    FwdListNode< value_type >* tail_;
    size_t size_;

    friend class CircularFwdListIterator< T >;
    friend class CircularFwdListConstIterator< T >;
  };
}

template < typename T >
zholobov::CircularFwdList< T >::CircularFwdList():
  head_(nullptr), tail_(nullptr), size_(0)
{}

template < typename T >
zholobov::CircularFwdList< T >::CircularFwdList(const CircularFwdList& other):
  head_(nullptr), tail_(nullptr), size_(0)
{
  FwdListNode< value_type >* other_p = other.head_;
  if (other_p != nullptr) {
    head_ = new FwdListNode< value_type >(other_p->value, head_);
    ++size_;
    other_p = other_p->next;
    FwdListNode< value_type >* prev = head_;
    while (other_p != other.head_) {
      auto curr = new FwdListNode< value_type >(other_p->value, head_);
      ++size_;
      prev->next = curr;
    };
    tail_ = prev;
  }
}

template < typename T >
zholobov::CircularFwdList< T >::CircularFwdList(CircularFwdList&& other) noexcept:
  head_(nullptr), tail_(nullptr), size_(0)
{
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template < typename T >
zholobov::CircularFwdList< T >::~CircularFwdList()
{
  if (size_ != 0) {
    FwdListNode< value_type >* curr = head_->next;
    while (curr != head_) {
      FwdListNode< value_type >* temp = curr;
      curr = curr->next;
      delete temp;
    }
    delete head_;
  }
}

template < typename T >
typename zholobov::CircularFwdList< T >::iterator zholobov::CircularFwdList< T >::begin() noexcept
{
  return (size_ == 0) ? iterator(nullptr) : iterator(std::addressof(head_));
}

template < typename T >
typename zholobov::CircularFwdList< T >::const_iterator zholobov::CircularFwdList< T >::begin() const noexcept
{
  return (size_ == 0) ? iterator(nullptr) : const_iterator(std::addressof(head_));
}

template < typename T >
typename zholobov::CircularFwdList< T >::iterator zholobov::CircularFwdList< T >::end() noexcept
{
  return (size_ == 0) ? iterator(nullptr) : iterator(std::addressof(tail_->next));
}

template < typename T >
typename zholobov::CircularFwdList< T >::const_iterator zholobov::CircularFwdList< T >::end() const noexcept
{
  return (size_ == 0) ? iterator(nullptr) : const_iterator(std::addressof(tail_->next));
}

template < typename T >
void zholobov::CircularFwdList< T >::push_front(const value_type& val)
{
  auto new_node = new FwdListNode< value_type >(val, head_);
  head_ = new_node;
  if (size_ == 0) {
    tail_ = head_;
  }
  tail_->next = head_;
  ++size_;
}

template < typename T >
void zholobov::CircularFwdList< T >::push_front(value_type&& val)
{
  auto new_node = new FwdListNode< value_type >(std::move(val), head_);
  head_ = new_node;
  if (size_ == 0) {
    tail_ = head_;
  }
  tail_->next = head_;
  ++size_;
}

template < typename T >
inline void zholobov::CircularFwdList< T >::push_back(const value_type& val)
{
  auto new_node = new FwdListNode< value_type >(val, head_);
  if (size_ == 0) {
    head_ = new_node;
    head_->next = head_;
  } else {
    tail_->next = new_node;
  }
  tail_ = new_node;
  ++size_;
}

template < typename T >
inline void zholobov::CircularFwdList< T >::push_back(value_type&& val)
{
  auto new_node = new FwdListNode< value_type >(std::move(val), head_);
  if (size_ == 0) {
    head_ = new_node;
    head_->next = head_;
  } else {
    tail_->next = new_node;
  }
  tail_ = new_node;
  ++size_;
}

#endif
