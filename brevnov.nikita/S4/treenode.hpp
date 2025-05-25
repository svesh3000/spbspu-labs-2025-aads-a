#ifndef TREENODE_HPP
#define TREENODE_HPP
#include <utility>

namespace brevnov
{
  template< class Key, class Value >
  struct TreeNode
  {
    TreeNode() = default;

    explicit TreeNode(const std::pair< Key, Value > & k):
      left(nullptr),
      right(nullptr),
      parent(nullptr),
      nodeHeight(1),
      data(k)
    {}

    explicit TreeNode(std::pair< Key, Value > && k):
      left(nullptr),
      right(nullptr),
      parent(nullptr),
      nodeHeight(1),
      data(std::move(k))
    {}
    
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    int nodeHeight;
    std::pair< Key, Value > data;
  };
}
#endif
