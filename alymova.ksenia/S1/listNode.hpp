#ifndef LIST_NODE_HPP
#define LIST_NODE_HPP

namespace alymova
{
  template< typename T >
  class List;
  template< typename T >
  struct Iterator;
  template< typename T >
  struct ConstIterator;

  template< typename T >
  class ListNode
  {
  public:
    T data_;
    ListNode< T >* next_;
    ListNode< T >* prev_;

    ListNode() = default;
    ListNode(T data, ListNode< T >* next, ListNode< T >* prev);
  };

  template< typename T >
  ListNode< T >::ListNode(T data, ListNode< T >* next, ListNode< T >* prev):
    data_(data),
    next_(next),
    prev_(prev)
  {}
}
#endif
