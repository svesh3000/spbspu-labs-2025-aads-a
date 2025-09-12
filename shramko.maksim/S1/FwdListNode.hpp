#ifndef FORWARDLISTNODE_HPP
#define FORWARDLISTNODE_HPP

namespace shramko
{
  template< typename T >
  struct ListNode
  {
    T dataValue;
    ListNode< T >* nextPtr;

    explicit ListNode(const T& val):
      dataValue(val),
      nextPtr(nullptr)
    {}

    explicit ListNode(T&& val):
      dataValue(std::move(val)),
      nextPtr(nullptr)
    {}
  };
}

#endif
