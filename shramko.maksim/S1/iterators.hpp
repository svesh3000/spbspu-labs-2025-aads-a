#ifndef ITERATOR
#define ITERATOR

#include <iterator>
#include "list.hpp"

namespace shramko
{
  template< typename T >
  class FwdIterator final: public std::iterator< std::forward_iterator_tag, int >
  {
    public:
    using this_t = FwdIterator< T >;
  
    FwdIterator();
    FwdIterator(const this_t& rhs) = default;
    ~FwdIterator() = default;
  
    this_t& operator=(const FwdIterator& rhs) = default;
    this_t& operator++();
    this_t& operator++(int);
    T& operator*();
    T* operator->();
    bool operator==(const this_t& rhs) const;
    bool operator!=(const this_t& rhs) const;
  
  private:
    FwdListNode< T >* node_;
  };
}
  
template< typename T >
shramko::FwdIterator< T >::FwdIterator():
  node_(nullptr, nullptr)
{}
  
template< typename T >
typename shramko::FwdIterator< T >::this_t& shramko::FwdIterator< T >::operator++()
{
  node_ = node_->next_;
  return *this;
}
  
template< typename T >
typename shramko::FwdIterator< T >::this_t& shramko::FwdIterator< T >::operator++(int)
{
  FwdIterator< T > result(*this);
  ++(*this);
  return result;
}
  
template< typename T >
T& shramko::FwdIterator< T >::operator*()
{}
  
template< typename T >
T* shramko::FwdIterator< T >::operator->()
{}
  
template< typename T >
bool shramko::FwdIterator< T >::operator==(const this_t& rhs) const
{
  return node_ == rhs.node_;
}
  
template< typename T >
bool shramko::FwdIterator< T >::operator!=(const this_t& rhs) const
{
  return !(*this == rhs);
}

#endif