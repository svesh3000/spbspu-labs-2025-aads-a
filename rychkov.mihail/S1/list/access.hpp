#ifndef ACCESS_HPP
#define ACCESS_HPP

#include "decl.hpp"

template< class T >
bool rychkov::List< T >::empty() const noexcept
{
  return size_ == 0;
}
template< class T >
size_t rychkov::List< T >::size() const noexcept
{
  return size_;
}
template< class T >
typename rychkov::List< T >::value_type& rychkov::List< T >::front()
{
  return head_->data;
}
template< class T >
const typename rychkov::List< T >::value_type& rychkov::List< T >::front() const
{
  return head_->data;
}
template< class T >
typename rychkov::List< T >::value_type& rychkov::List< T >::back()
{
  return tail_->data;
}
template< class T >
const typename rychkov::List< T >::value_type& rychkov::List< T >::back() const
{
  return tail_->data;
}


template< class T >
typename rychkov::List< T >::iterator rychkov::List< T >::begin() noexcept
{
  return {head_};
}
template< class T >
typename rychkov::List< T >::const_iterator rychkov::List< T >::begin() const noexcept
{
  return {head_};
}
template< class T >
typename rychkov::List< T >::reverse_iterator rychkov::List< T >::rbegin() noexcept
{
  return {tail_};
}
template< class T >
typename rychkov::List< T >::const_reverse_iterator rychkov::List< T >::rbegin() const noexcept
{
  return {tail_};
}

template< class T >
typename rychkov::List< T >::iterator rychkov::List< T >::end() noexcept
{
  return {};
}
template< class T >
typename rychkov::List< T >::const_iterator rychkov::List< T >::end() const noexcept
{
  return {};
}
template< class T >
typename rychkov::List< T >::reverse_iterator rychkov::List< T >::rend() noexcept
{
  return {};
}
template< class T >
typename rychkov::List< T >::const_reverse_iterator rychkov::List< T >::rend() const noexcept
{
  return {};
}

#endif
