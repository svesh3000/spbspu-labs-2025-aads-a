#ifndef NODE_HPP
#define NODE_HPP

#include <utility>

namespace zholobov {

  template < typename Key, typename T >
  struct Node {
    template < typename... Args >
    Node(Args&&... args) noexcept:
      data(std::forward< Args >(args)...),
      parent(nullptr),
      left(nullptr),
      right(nullptr),
      height(1)
    {}

    std::pair< Key, T > data;
    Node* parent;
    Node* left;
    Node* right;
    int height;
  };

}

#endif
