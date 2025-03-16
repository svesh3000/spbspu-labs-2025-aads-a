#ifndef MY_LIST_HPP
#define MY_LIST_HPP
#include "fwd_list_node.hpp"

namespace zakirov
{
  template< typename T >
  class FwdList
  {
  public:
    FwdList();
    ~FwdList();
    FwdListNode< T > * begin();
    FwdListNode< T > * end();
    void pop_front(const T & fwd_list);
    void push_front(const T & fwd_list);
    void push_front(const T && fwd_list);
  private:
    FwdListNode< T > * fake_node_;
    size_t node_quantity_;
  };

  template< typename T >
  FwdList< T >::FwdList():
    fake_node_(reinterpret_cast< FwdListNode< T >* >(new char[sizeof(FwdListNode< T >)])),
    node_quantity_(0)
  {
    fake->next = fake;
  }

  template< typename T >
  FwdList< T >::~FwdList()
  {
    
  }

}

#endif
