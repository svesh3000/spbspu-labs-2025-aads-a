#ifndef ERASORS_SPLICE_HPP
#define ERASORS_SPLICE_HPP

#include "decl.hpp"

template< class T >
void rychkov::List< T >::splice(const_iterator pos, List& rhs)
{
  splice(pos, rhs, rhs.begin(), rhs.end());
}
template< class T >
void rychkov::List< T >::splice(const_iterator pos, List&& rhs)
{
  splice(pos, rhs);
}
template< class T >
void rychkov::List< T >::splice(const_iterator pos, List& rhs, const_iterator from, const_iterator to)
{
  if (from == to)
  {
    return;
  }
  size_type erasedSize = 0;
  for (const_iterator i = from; i != to; ++i, ++erasedSize)
  {}

  if (from == rhs.begin())
  {
    rhs.head_ = to.node_;
  }
  else
  {
    from.node_->prev->next = to.node_;
  }
  const_iterator insertedTail;
  if (to == rhs.end())
  {
    insertedTail = rhs.tail_;
    rhs.tail_ = from.node_->prev;
  }
  else
  {
    insertedTail = to.node_->prev;
    to.node_->prev = from.node_->prev;
  }

  if (pos == begin())
  {
    head_ = from.node_;
    from.node_->prev = nullptr;
  }
  else
  {
    pos.node_->prev->next = from.node_;
    from.node_->prev = pos.node_->prev;
  }
  if (pos == end())
  {
    tail_ = insertedTail.node_;
    insertedTail.node_->next = nullptr;
  }
  else
  {
    pos.node_->prev = insertedTail.node_;
    insertedTail.node_->next = pos.node_;
  }

  rhs.size_ -= erasedSize;
  size_ += erasedSize;
}

template< class T >
void rychkov::List< T >::erase(const_iterator pos)
{
  if (pos == end())
  {
    return;
  }
  size_--;
  if (pos == begin())
  {
    head_ = head_->next;
    head_->prev = nullptr;
  }
  else
  {
    pos.node_->prev->next = pos.node_->next;
  }
  if (pos == const_iterator{tail_})
  {
    tail_ = tail_->prev;
    tail_->next = nullptr;
  }
  else
  {
    pos.node_->next->prev = pos.node_->prev;
  }
  delete pos.node_;
}

#endif
