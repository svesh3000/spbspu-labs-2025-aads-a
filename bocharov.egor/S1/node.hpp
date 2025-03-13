#ifndef NODE_HPP
#define NODE_HPP

namespace maslevtsov {
  template< typename T >
  class FwdListNode
  {
  public:
    T data_;
    FwdListNode< T >* next_;
  };
}

#endif
