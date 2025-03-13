#ifndef LISTITERATORS_HPP
#define LISTITERATORS_HPP
#include "list.hpp"

namespace krylov
{
  template< typename T >
  class List;

  template < typename T >
  class Iterator
  {
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    Iterator();
    Iterator(Node< T >* node);
    Iterator(Node< T >* node, const List< T >* list);
    T& operator*();
    T* operator->();
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    bool operator!=(const Iterator& other) const;
    bool operator==(const Iterator& other) const;
  private:
    Node< T >* current_;
    const List< T >* list_;
    friend class List< T >;
  };

  template < typename T >
  Iterator< T >::Iterator(Node< T >* node):
    current_(node),
    list_(nullptr)
  {}

  template < typename T >
  Iterator< T >::Iterator(Node< T >* node, const List< T >* list):
    current_(node),
    list_(list)
  {}

  template < typename T >
  T& Iterator< T >::operator*()
  {
    return current_->data_;
  }

  template < typename T >
  T* Iterator< T >::operator->()
  {
    return &(current_->data_);
  }

  template < typename T >
  Iterator< T >& Iterator< T >::operator++()
  {
    if (current_ && current_->next_)
    {
      current_ = current_->next_;
    }
    else
    {
      current_ = nullptr;
    }
    return *this;
  }

  template < typename T >
  Iterator< T > Iterator< T >::operator++(int)
  {
    Iterator< T > temp = *this;
    ++(*this);
    return temp;
  }

  template < typename T >
  Iterator< T >& Iterator< T >::operator--()
  {
    if (!current_)
    {
      current_ = list_->tail_;
    }
    else
    {
      current_ = current_->prev_;
    }
    return *this;
  }

  template < typename T >
  Iterator< T > Iterator< T >::operator--(int)
  {
    Iterator< T > temp = *this;
    --(*this);
    return temp;
  }

  template < typename T >
  bool Iterator< T >::operator!=(const Iterator& other) const
  {
    return current_ != other.current_;
  }

  template < typename T >
  bool Iterator < T >::operator==(const Iterator& other) const
  {
    return current_ == other.current_;
  }
}

#endif
