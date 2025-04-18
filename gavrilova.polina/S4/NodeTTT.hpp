#ifndef NODE_TTT_HPP
#define NODE_TTT_HPP

#include <utility>

namespace gavrilova
{
  template <class Value, class Key>
  struct NodeTwoThreeTree
  {
    size_t busy;
    std::pair< Value, Key > data[2];
    NodeTwoThreeTree< Value , Key >* first;
    NodeTwoThreeTree< Value , Key >* second;
    NodeTwoThreeTree< Value , Key >* third;
  }
}

#endif