#ifndef TREENODE_HPP
#define TREENODE_HPP
#include <utility>

namespace brevnov
{
  template< class Key, class Value >
  struct TreeNode
  {
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    std::pair< Key, Value > data;
  };
}
#endif
