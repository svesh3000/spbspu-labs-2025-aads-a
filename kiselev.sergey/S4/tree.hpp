#ifndef TREE_HPP
#define TREE_HPP
#include <functional>

namespace kiselev
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class BinarySearchTree
  {
  public:
    void push(Key k, Value v);
    Value get(Key k);
    void pop(Key k);
  private:
    enum class Color
    {
      RED,
      BLACK
    };
    struct Node
    {
      Key key;
      Value value;
      Color color;
      Node* left;
      Node* right;
      Node* parent;
    };
    Node* root;
    Compare comp;
  };
}
#endif
