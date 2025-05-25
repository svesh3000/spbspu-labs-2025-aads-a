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

    explicit TreeNode(const std::pair< Key, Value > && k):
      left(nullptr),
      right(nullptr),
      parent(nullptr),
      nodeHeight(1),
      data(std::move(k))
    {}

    int getHeight(const TreeNode* node)
    {
      if (node == nullptr)
      {
        return 0;
      }
      return node->height;
    }

    int balanceFactor(const TreeNode* node)
    {
      if (node == nullptr)
      {
        return 0;
      }
      return getHeight(node->left) - getHeight(node->right);
    }
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    int nodeHeight;
    std::pair< Key, Value > data;
  };
}
#endif
