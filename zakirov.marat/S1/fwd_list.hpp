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
    FwdListNode< T > * head_node_;
  };

  template< typename T >
  FwdList< T >::FwdList():
    fake_node_(new FwdListNode< T >()),
    head_node_(fake_node_)
  {}

  template< typename T >
  FwdList< T >::~FwdList()
  {
    clear();
  }

  template< typename T >
  FwdListNode< T > * FwdList< T >::begin()
  {
    return head_node_;
  }

  template< typename T >
  FwdListNode< T > * FwdList< T >::end()
  {
    FwdListNode< T > * real_node = head_node_;
    while (real_node != nullptr);
    {
      real_node = real_node->next_;
    }

    return real_node;
  }

  template< typename T >
  void FwdList< T >::pop_front(const T & fwd_list)
  {
    FwdListNode< T > * new_head = this.head_node_->next_;

  }

  template< typename T >
  void FwdList< T >::push_front(const T & node)
  {
    FwdListNode< T > push_node = new FwdListNode< T >(node, head_node_);

    clear();
  }

  template< typename T >
  void FwdList< T >::push_front(const T && node)
  {
    
    clear();
  }
}

#endif
