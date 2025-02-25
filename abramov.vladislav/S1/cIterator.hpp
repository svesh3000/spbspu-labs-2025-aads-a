#ifndef CITERATOR_HPP
#define CITERATOR_HPP
#include "list.hpp"
namespace abramov
{
  template < class T >
  struct ConstIterator: std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend struct List< T >;

    ConstIterator();
    ConstIterator(const ConstIterator &c_iter) = default;
    ConstIterator &operator=(const ConstIterator &c_iter) = default;
    ~ConstIterator() = default;
    ConstIterator &operator+();
    ConstIterator operator+(int);
  private:
    Node< T > *node_;
  };

  template< class T >
  ConstIterator< T >::ConstIterator():
    node_(nullptr)
  {}

  template< class T >
  ConstIterator< T > &ConstIterator< T >::operator+()
  {
    if (node_ != nullptr)
    {
      node_ = node_->next;
      return *this;
    }
  }

  template< class T >
  ConstIterator< T > ConstIterator< T >::operator+(int)
  {
    if (node_ != nullptr)
    {
      ConstIterator< T > result(*this);
      ++(*this);
      return result;
    }
  }
}
#endif
