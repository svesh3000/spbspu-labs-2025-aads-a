#ifndef FWD_LIST_NODE
#define FWD_LIST_NODE

namespace maslevtsov {
  template< typename T >
  class FwdList;

  template< typename T >
  class FwdIterator;

  template< typename T >
  class FwdListNode
  {
    friend class FwdList< T >;
    friend class FwdIterator< T >;

    T data_;
    FwdListNode< T >* next_;

    FwdListNode();
    FwdListNode(const T& data, FwdListNode< T >* next);
    ~FwdListNode();
  };
}

template< typename T >
maslevtsov::FwdListNode< T >::FwdListNode():
  data_(T()),
  next_(nullptr)
{}

template< typename T >
maslevtsov::FwdListNode< T >::FwdListNode(const T& data, FwdListNode< T >* next):
  data_(data),
  next_(next)
{}

template< typename T >
maslevtsov::FwdListNode< T >::~FwdListNode()
{
  delete next_;
}

#endif
