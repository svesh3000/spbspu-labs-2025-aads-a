#ifndef FWD_LIST_NODE_HPP
#define FWD_LIST_NODE_HPP

namespace maslevtsov {
  template< typename T >
  class FwdList;

  template< typename T >
  class FwdIterator;

  template< typename T >
  class FwdListNode
  {
  public:
    friend class FwdList< T >;
    friend class FwdIterator< T >;

    FwdListNode();
    FwdListNode(const T& data);

  private:
    T data_;
    FwdListNode< T >* next_;
  };
}

template< typename T >
maslevtsov::FwdListNode< T >::FwdListNode():
  data_(T()),
  next_(nullptr)
{}

template< typename T >
maslevtsov::FwdListNode< T >::FwdListNode(const T& data):
  data_(data),
  next_(nullptr)
{}

#endif
