#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP
#include <utility>

namespace alymova
{
  namespace detail
  {
    template< class Key, class Value >
    struct TTTNode
    {
      using Node = TTTNode< Key, Value >;

      std::pair< Key, Value > data[2];
      enum NodeType {Empty, Double, Triple} type;
      Node* parent;
      Node* left;
      Node* mid;
      Node* right;

      TTTNode();
      TTTNode(const Key& key, const Value& value);
      TTTNode(const Key& key1, const Value& value1, const Key& key2, const Value& value2);
    };

    template< class Key, class Value >
    TTTNode< Key, Value >::TTTNode():
      data{std::pair< Key, Value >(), std::pair< Key, Value >()},
      type(NodeType::Empty),
      parent(nullptr),
      left(nullptr),
      mid(nullptr),
      right(nullptr)
    {}

    template< class Key, class Value >
    TTTNode< Key, Value >::TTTNode(const Key& key, const Value& value):
      data{std::make_pair(key, value), std::pair< Key, Value >()},
      type(NodeType::Double),
      parent(nullptr),
      left(nullptr),
      mid(nullptr),
      right(nullptr)
    {}

    template< class Key, class Value >
    TTTNode< Key, Value >::TTTNode(const Key& key1, const Value& value1, const Key& key2, const Value& value2):
      data{std::make_pair(key1, value1), std::make_pair(key2, value2)},
      type(NodeType::Double),
      parent(nullptr),
      left(nullptr),
      mid(nullptr),
      right(nullptr)
    {}
  }
}

#endif
