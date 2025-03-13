#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "node.hpp"
#include <memory>

namespace finaev
{
  template < class T >
  struct listIterator
  {
  public:
	  using this_t = listIterator< T >;
	  listIterator();
	  listIterator(Node<T>* node);
	  ~listIterator() = default;
	  T& operator*();
	  Node< T > operator->();
	  this_t& operator++();
	  this_t operator++(int);
	  bool operator==(const listIterator& i);
	  bool operator!=(const listIterator& i);
  private:
	  Node< T >* node_;
  };
}

template < class T >
finaev::listIterator < T >::listIterator():
  node_(nullptr)
{}

template < class T >
finaev::listIterator < T >::listIterator(Node<T>* node) :
  node_(node)
{}

template < class T >
T& finaev::listIterator< T >::operator*()
{
  return node_->data;
}

template < class T >
finaev::Node< T > finaev::listIterator< T >::operator->()
{
  return std::addressof(this->node_);
}

template < class T >
finaev::listIterator< T >& finaev::listIterator< T >::operator++()
{
  node_ = node_->next;
  return *this;
}

template < class T >
finaev::listIterator< T > finaev::listIterator< T >::operator++(int)
{
  this_t res(*this);
  ++(*this);
  return res;
}

template < class T >
bool finaev::listIterator< T > ::operator==(const listIterator& i)
{
  return node_ == i.node_;
}

template < class T >
bool finaev::listIterator< T > ::operator!=(const listIterator& i)
{
  return !(*this == i);
}

#endif