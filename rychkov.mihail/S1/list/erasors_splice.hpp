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
void rychkov::List< T >::splice(const_iterator pos, List& rhs, const_iterator it)
{
  splice(pos, rhs, it, ++const_iterator(it));
}
template< class T >
void rychkov::List< T >::splice(const_iterator pos, List& rhs, const_iterator from, const_iterator to)
{
  if (from == to)
  {
    return;
  }
  size_type erasedSize = 0;
  if ((from == rhs.begin()) && (to == rhs.end()))
  {
    erasedSize = rhs.size_;
  }
  else
  {
    for (const_iterator i = from; i != to; ++i, ++erasedSize)
    {}
  }

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
typename rychkov::List< T >::iterator rychkov::List< T >::erase(const_iterator pos)
{
  if (pos != end())
  {
    return erase(pos, ++const_iterator(pos));
  }
  return end();
}
template< class T >
typename rychkov::List< T >::iterator rychkov::List< T >::erase(const_iterator from, const_iterator to)
{
  if (from == to)
  {
    return end();
  }
  if (from == begin())
  {
    head_ = to.node_;
    if (head_ != nullptr)
    {
      head_->prev = nullptr;
    }
  }
  else
  {
    from.node_->prev->next = to.node_;
  }
  if (to == end())
  {
    tail_ = from.node_->prev;
    if (tail_ != nullptr)
    {
      tail_->next = nullptr;
    }
  }
  else
  {
    to.node_->prev = from.node_->prev;
  }
  while (from != to)
  {
    const_iterator temp = from++;
    delete temp.node_;
    --size_;
  }
  return {to.node_};
}

template< class T >
typename rychkov::List< T >::size_type rychkov::List< T >::remove(const value_type& value)
{
  size_type result = 0;
  const_iterator i = begin();
  while (i != end())
  {
    const_iterator temp = i++;
    if (*temp == value)
    {
      erase(temp);
      result++;
    }
  }
  return result;
}
template< class T >
template< class C >
typename rychkov::List< T >::size_type rychkov::List< T >::remove_if(C condition)
{
  size_type result = 0;
  const_iterator i = begin();
  while (i != end())
  {
    const_iterator temp = i++;
    if (condition(*temp))
    {
      erase(temp);
      result++;
    }
  }
  return result;
}

#endif
