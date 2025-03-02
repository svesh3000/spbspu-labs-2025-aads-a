#ifndef FWDLISTNODE_HPP
#define FWDLISTNODE_HPP

#include <utility>

namespace zholobov {

  template < typename T >
  struct FwdListNode {
    T value;
    FwdListNode* next;
    FwdListNode(T val, FwdListNode* nextNode):
      value(std::move(val)), next(nextNode) {}
  };

}

#endif
