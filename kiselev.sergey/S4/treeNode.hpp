#ifndef TREENODE_HPP
#define TREENODE_HPP

namespace kiselev
{
  enum class Color
  {
    RED,
    BLACK
  };
  template< class Key, class Value >
  struct TreeNode
  {
    Key key;
    Value value;
    Color color;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
  };
}
#endif
