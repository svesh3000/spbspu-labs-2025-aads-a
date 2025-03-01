#ifndef SPLICE_HPP
#define SPLICE_HPP

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

#endif
