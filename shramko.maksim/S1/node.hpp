#ifndef NODE_HPP
#define NODE_HPP

namespace shramko
{
  template< typename T >
  class FwdListNode
  {
  public:
    T data_;
    FwdListNode< T >* next_;
    
    explicit FwdListNode(const T& data);
    explicit FwdListNode(T&& data);
  };

  template< typename T >
  FwdListNode< T >::FwdListNode(const T& data):
    data_(data),
    next_(nullptr)
  {}

  template< typename T >
  FwdListNode< T >::FwdListNode(T&& data):
    data_(std::move(data)),
    next_(nullptr)
  {}
}

#endif
