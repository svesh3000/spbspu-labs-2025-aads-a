#ifndef TREENODE_HPP
#define TREENODE_HPP
#include <utility>

namespace brevnov
{
  template< class Key, class Value >
  struct TreeNode
  {
    TreeNode() = default;
    TreeNode(std::pair< Key, Value > k):
      data(k),
      left(nullptr),
      right(nullptr),
      height(1)
    {}

    int height(TreeNode<T>* node)
    {
      if (node == nullptr)
      {
        return 0;
      }
      return node->height;
    }

      int balanceFactor(TreeNode<T>* node)
    {
      if (node == nullptr)
      {
        return 0;
      }
      return height(node->left) - height(node->right);
    }
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    int height;
    std::pair< Key, Value > data;
  };
}
#endif
