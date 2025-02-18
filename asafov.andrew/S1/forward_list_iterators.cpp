#include "forward_list.h"

//const-iterators
template <typename T>
T& asafov::Forward_list<T>::const_iterator::operator*()
{
  return node_->data_;
}

template <typename T>
T* asafov::Forward_list<T>::const_iterator::operator->()
{
  return *node_->data_;
}

template <typename T>
typename asafov::Forward_list<T>::const_iterator& asafov::Forward_list<T>::const_iterator::operator++()
{
  node_ = node_->next_;
  return *this;
  
}

template <typename T>
typename asafov::Forward_list<T>::const_iterator asafov::Forward_list<T>::const_iterator::operator++(int)
{
  asafov::Forward_list<T> result(*this);
  ++(*this);
  return result;
}

template <typename T>
bool asafov::Forward_list<T>::const_iterator::operator==(const const_iterator& rhs) const
{
  return node_ == rhs.node_;
}

template <typename T>
bool asafov::Forward_list<T>::const_iterator::operator!=(const const_iterator& rhs) const
{
  return !(rhs == *this);
}

template <typename T>
typename asafov::Forward_list<T>::const_iterator asafov::Forward_list<T>::cbegin()
{
  return *this;
}

template <typename T>
typename asafov::Forward_list<T>::const_iterator asafov::Forward_list<T>::cend()
{
  asafov::Forward_list<T>::const_iterator it = *this;
  while (it++->next != *this);
  return it;
}

//iterators
template <typename T>
T& asafov::Forward_list<T>::iterator::operator*()
{
  return node_->data_;
}

template <typename T>
T* asafov::Forward_list<T>::iterator::operator->()
{
  return *node_->data_;
}

template <typename T>
typename asafov::Forward_list<T>::iterator& asafov::Forward_list<T>::iterator::operator++()
{
  node_ = node_->next_;
  return *this;
  
}

template <typename T>
typename asafov::Forward_list<T>::iterator asafov::Forward_list<T>::iterator::operator++(int)
{
  asafov::Forward_list<T> result(*this);
  ++(*this);
  return result;
}

template <typename T>
bool asafov::Forward_list<T>::iterator::operator==(const iterator& rhs) const
{
  return node_ == rhs.node_;
}

template <typename T>
bool asafov::Forward_list<T>::iterator::operator!=(const iterator& rhs) const
{
  return !(rhs == *this);
}

template <typename T>
typename asafov::Forward_list<T>::iterator asafov::Forward_list<T>::begin()
{
  return &this;
}

template <typename T>
typename asafov::Forward_list<T>::iterator asafov::Forward_list<T>::end()
{
  asafov::Forward_list<T>::iterator it = *this;
  while (it++->next != *this);
  return it;
}

template <typename T>
typename asafov::Forward_list<T>::iterator asafov::Forward_list<T>::last()
{
  asafov::Forward_list<T>::iterator it = *this;
  while (it++->next != this.end());
  return it;
}
