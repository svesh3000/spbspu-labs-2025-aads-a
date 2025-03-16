#ifndef FWD_LIST_DEFINITION_HPP
#define FWD_LIST_DEFINITION_HPP

#include "declaration.hpp"
#include <utility>

template< typename T >
maslevtsov::FwdList< T >::FwdList() noexcept:
  tail_(nullptr),
  size_(0)
{}

template< typename T >
maslevtsov::FwdList< T >::FwdList(const FwdList& rhs):
  FwdList()
{
  if (rhs.empty()) {
    return;
  }
  push_back(*(rhs.cbegin()));
  for (auto i = ++rhs.cbegin(); i != rhs.cend(); ++i) {
    push_back(*i);
  }
}

template< typename T >
maslevtsov::FwdList< T >::FwdList(FwdList&& rhs) noexcept:
  tail_(std::exchange(rhs.tail_, nullptr)),
  size_(std::exchange(rhs.size_, 0))
{}

template< typename T >
maslevtsov::FwdList< T >::FwdList(std::size_t count, T value):
  FwdList()
{
  if (count == 0) {
    return;
  }
  for (std::size_t i = 0; i != count; ++i) {
    push_front(value);
  }
}

template< typename T >
template< class InputIt >
maslevtsov::FwdList< T >::FwdList(InputIt first, InputIt last):
  FwdList()
{
  if (first == last) {
    return;
  }
  for (; first != last; ++first) {
    push_back(*first);
  }
}

template< typename T >
maslevtsov::FwdList< T >::FwdList(std::initializer_list< T > init):
  FwdList(init.cbegin(), init.cend())
{}

template< typename T >
maslevtsov::FwdList< T >::~FwdList()
{
  clear();
}

template< typename T >
typename maslevtsov::FwdList< T >::FwdList& maslevtsov::FwdList< T >::operator=(const FwdList& rhs) noexcept
{
  FwdList< T > copied_rhs(rhs);
  swap(copied_rhs);
  return *this;
}

template< typename T >
typename maslevtsov::FwdList< T >::FwdList& maslevtsov::FwdList< T >::operator=(FwdList&& rhs) noexcept
{
  FwdList< T > copied_rhs(std::move(rhs));
  swap(copied_rhs);
  return *this;
}

template< typename T >
typename maslevtsov::FwdList< T >::FwdList& maslevtsov::FwdList< T >::operator=(std::initializer_list< T > ilist)
{
  FwdList< T > copied_rhs(std::move(ilist));
  swap(copied_rhs);
  return *this;
}

template< typename T >
void maslevtsov::FwdList< T >::assign(std::size_t count, const T& value)
{
  if (count == 0) {
    return;
  }
  FwdList< T > assigned;
  for (std::size_t i = 0; i != count; ++i) {
    assigned.push_back(value);
  }
  swap(assigned);
}

template< typename T >
template< class InputIt >
void maslevtsov::FwdList< T >::assign(InputIt first, InputIt last)
{
  FwdList< T > assigned;
  for (; first != last; ++first) {
    assigned.push_back(*first);
  }
  swap(assigned);
}

template< typename T >
void maslevtsov::FwdList< T >::assign(std::initializer_list< T > ilist)
{
  FwdList< T > assigned(std::move(ilist));
  swap(assigned);
}

template< typename T >
T& maslevtsov::FwdList< T >::front() noexcept
{
  assert(!empty() && "element access to empty list");
  return tail_->next_->data_;
}

template< typename T >
const T& maslevtsov::FwdList< T >::front() const noexcept
{
  assert(!empty() && "element access to empty list");
  return tail_->next_->data_;
}

template< typename T >
T& maslevtsov::FwdList< T >::back() noexcept
{
  assert(!empty() && "element access to empty list");
  return tail_->data_;
}

template< typename T >
const T& maslevtsov::FwdList< T >::back() const noexcept
{
  assert(!empty() && "element access to empty list");
  return tail_->data_;
}

template< typename T >
typename maslevtsov::FwdList< T >::iterator maslevtsov::FwdList< T >::begin() noexcept
{
  return iterator(tail_->next_);
}

template< typename T >
typename maslevtsov::FwdList< T >::const_iterator maslevtsov::FwdList< T >::begin() const noexcept
{
  return const_iterator(tail_->next_);
}

template< typename T >
typename maslevtsov::FwdList< T >::const_iterator maslevtsov::FwdList< T >::cbegin() const noexcept
{
  return const_iterator(tail_->next_);
}

template< typename T >
typename maslevtsov::FwdList< T >::iterator maslevtsov::FwdList< T >::end() noexcept
{
  return iterator(tail_->next_);
}

template< typename T >
typename maslevtsov::FwdList< T >::const_iterator maslevtsov::FwdList< T >::end() const noexcept
{
  return const_iterator(tail_->next_);
}

template< typename T >
typename maslevtsov::FwdList< T >::const_iterator maslevtsov::FwdList< T >::cend() const noexcept
{
  return const_iterator(tail_->next_);
}

template< typename T >
bool maslevtsov::FwdList< T >::empty() const noexcept
{
  return size_ == 0;
}

template< typename T >
std::size_t maslevtsov::FwdList< T >::size() const noexcept
{
  return size_;
}

template< typename T >
void maslevtsov::FwdList< T >::clear() noexcept
{
  while (!empty()) {
    pop_front();
  }
}

template< typename T >
typename maslevtsov::FwdList< T >::iterator maslevtsov::FwdList< T >::insert_after(const_iterator pos, const T& value)
{
  FwdListNode< T >* new_node = new FwdListNode< T >{value, pos.node_->next_};
  pos.node_->next_ = new_node;
  ++size_;
  return iterator(new_node);
}

template< typename T >
typename maslevtsov::FwdList< T >::iterator maslevtsov::FwdList< T >::insert_after(const_iterator pos, T&& value)
{
  insert_after(pos, value);
}

template< typename T >
typename maslevtsov::FwdList< T >::iterator maslevtsov::FwdList< T >::insert_after(const_iterator pos,
  std::size_t count, const T& value) noexcept
{
  splice_after(pos, FwdList< T >(count, value));
}

template< typename T >
template< class InputIt >
typename maslevtsov::FwdList< T >::iterator maslevtsov::FwdList< T >::insert_after(const_iterator pos, InputIt first,
  InputIt last) noexcept
{
  splice_after(pos, FwdList< T >(first, last));
}

template< typename T >
typename maslevtsov::FwdList< T >::iterator maslevtsov::FwdList< T >::insert_after(const_iterator pos,
  std::initializer_list< T > ilist) noexcept
{
  insert_after(pos, ilist.begin(), ilist.end());
}

template< typename T >
typename maslevtsov::FwdList< T >::iterator maslevtsov::FwdList< T >::erase_after(const_iterator pos) noexcept
{
  assert(!empty() && "empty list erasing");
  FwdListNode< T > to_delete = pos.node_->next_;
  pos.node_->next_ = to_delete->next_;
  delete to_delete;
  if (pos.node_->next_ == nullptr) {
    return iterator();
  }
  return iterator(pos.node_->next_);
}

template< typename T >
typename maslevtsov::FwdList< T >::iterator maslevtsov::FwdList< T >::erase_after(const_iterator first,
  const_iterator last) noexcept
{
  assert(!empty() && "empty list erasing");
  for (; first != last; ++first) {
    erase_after(first);
  }
  return iterator(last);
}

template< typename T >
void maslevtsov::FwdList< T >::push_front(const T& value)
{
  FwdListNode< T >* new_node = new FwdListNode< T >{value, nullptr};
  if (empty()) {
    tail_ = new_node;
    tail_->next_ = tail_;
  } else {
    new_node->next_ = tail_->next_;
    tail_->next_ = new_node;
  }
  ++size_;
}

template< typename T >
void maslevtsov::FwdList< T >::push_front(T&& value)
{
  push_front(value);
}

template< typename T >
void maslevtsov::FwdList< T >::push_back(const T& value)
{
  FwdListNode< T >* new_node = new FwdListNode< T >{value, nullptr};
  if (empty()) {
    tail_ = new_node;
    tail_->next_ = tail_;
  } else {
    new_node->next_ = tail_->next_;
    tail_->next_ = new_node;
    tail_ = new_node;
  }
  ++size_;
}

template< typename T >
void maslevtsov::FwdList< T >::push_back(T&& value)
{
  push_back(value);
}

template< typename T >
void maslevtsov::FwdList< T >::pop_front() noexcept
{
  assert(!empty() && "pop_front() to empty list");
  FwdListNode< T >* to_delete = tail_->next_;
  tail_->next_ = to_delete->next_;
  delete to_delete;
  --size_;
}

template< typename T >
void maslevtsov::FwdList< T >::swap(FwdList& other) noexcept
{
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template< typename T >
void maslevtsov::FwdList< T >::splice_after(const_iterator pos, FwdList& other) noexcept
{
  splice_after(pos, other, other.begin(), other.end());
}

template< typename T >
void maslevtsov::FwdList< T >::splice_after(const_iterator pos, FwdList&& other) noexcept
{
  splice_after(pos, other);
}

template< typename T >
void maslevtsov::FwdList< T >::splice_after(const_iterator pos, FwdList& other, const_iterator it) noexcept
{
  splice_after(pos, other, it, ++const_iterator(it));
}

template< typename T >
void maslevtsov::FwdList< T >::splice_after(const_iterator pos, FwdList& other, const_iterator first,
  const_iterator last) noexcept
{
  if (last == const_iterator(first->node_->next_) || other.empty()) {
    return;
  }
  std::size_t size_increase = 0;
  if (other.begin() == first && other.end() == last) {
    size_increase = other.size_;
  } else {
    for (auto it = ++first; it != last; ++it, ++size_increase)
    {}
  }
  FwdListNode< T >* pos_tmp = pos.node_;
  FwdListNode< T >* first_tmp = first.node_;
  FwdListNode< T >* last_tmp = last.node_;
  if (pos_tmp == tail_) {
    tail_ = last_tmp;
  }
  if (last_tmp == other.tail_->next_) {
    other.tail_ = first_tmp;
  }
  last.node_->next_ = pos.node_->next_;
  pos_tmp->next_ = first.node_->next_;
  first_tmp->next_ = last_tmp->next_;
}

template< typename T >
void maslevtsov::FwdList< T >::remove(const T& value) noexcept
{
  remove_if([&](const T& list_value)
  {
    return list_value == value;
  });
}

template< typename T >
template< class UnaryPredicate >
void maslevtsov::FwdList< T >::remove_if(UnaryPredicate condition)
{
  if (empty()) {
    return;
  }
  auto it = cbegin();
  while (it != const_iterator(tail_)) {
    const_iterator next = ++const_iterator(it);
    if (condition(*next)) {
      erase_after(it);
    }
    ++it;
  }
  if (condition(tail_->next_)) {
    erase_after(tail_);
  }
}

#endif
