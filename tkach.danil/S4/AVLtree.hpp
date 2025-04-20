#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <functional>
#include "node_tree.hpp"

namespace tkach
{
  template< class Key, class Value, class Cmp = std::less< Key > >
  class AvlTree
  {
  public:
    AvlTree();
    void insert(const std::pair< Key, Value > & pair);
    void insert(std::pair< Key, Value > && pair);
    void clear();
    TreeNode< Key, Value >* find(const Key& key);
    Value& at(const Key& key);
    const Value& at(const Key& key) const;
  private:
    TreeNode< Key, Value >* root_;
    size_t size_;
    Cmp cmp_;
    template< class... Args >
    void insertSingle(Args... args);
    template< class... Args >
    TreeNode< Key, Value >* insertCmp(TreeNode< Key, Value >* root, Args... args);
    void clearFrom(TreeNode< Key, Value >* node);
  };

  template< class Key, class Value, class Cmp >
  AvlTree< Key, Value, Cmp >::AvlTree():
    root_(nullptr),
    size_(0),
    cmp_()
  {}

  template< class Key, class Value, class Cmp >
  Value& AvlTree< Key, Value, Cmp >::at(const Key& key)
  {
    TreeNode< Key, Value >* node = find(key);
    if (node)
    {
      return node->data.second;
    }
    throw std::out_of_range("No that element");
  }

  template< class Key, class Value, class Cmp >
  const Value& AvlTree< Key, Value, Cmp >::at(const Key& key) const
  {
    TreeNode< Key, Value >* node = find(key);
    if (node)
    {
      return node->data.second;
    }
    throw std::out_of_range("No that element");
  }

  template< class Key, class Value, class Cmp >
  void AvlTree< Key, Value, Cmp >::insert(const std::pair< Key, Value > & pair)
  {
    insertSingle(pair);
  }

  template< class Key, class Value, class Cmp >
  void AvlTree< Key, Value, Cmp >::insert(std::pair< Key, Value > && pair)
  {
    insertSingle(std::move(pair));
  }

  template< class Key, class Value, class Cmp >
  template< class... Args >
  void AvlTree< Key, Value, Cmp >::insertSingle(Args... args)
  {
    try
    {
      root_ = insertCmp(root_, args);
      size_++;
    }
    catch (...)
    {
      clear();
      throw;
    }
  }

  template< class Key, class Value, class Cmp >
  template< class... Args >
  TreeNode< Key, Value >* AvlTree< Key, Value, Cmp >::insertCmp(TreeNode< Key, Value >* root, Args... args)
  {
    if (root == nullptr)
    {
      return new TreeNode< Key, Value >(std::forward< Args >(args)...);
    }
    else if (cmp(value, root->data))
    {
      root->left = insertCmp(root->left, args);
      if (root->left->parent == nullptr)
      {
        root->left->parent = root;
      }
    }
    else
    {
      root->right = insertCmp(root->right, args);
      if (root->right->parent == nullptr)
      {
        root->right->parent = root;
      }
    }
    return root;
  }

  template< class Key, class Value, class Cmp >
  TreeNode< Key, Value >* AvlTree< Key, Value, Cmp >::find(const Key& key)
  {
    TreeNode< Key, Value >* root = root_;
    while (root_ != nullptr && key != root->data.first)
    {
      if (cmp(key, root->data.first))
      {
        root = root->left;
      }
      else
      {
        root = root->right;
      }
    }
    return root;
  }

  template< class Key, class Value, class Cmp >
  void AvlTree< Key, Value, Cmp >::clear()
  {
    clearFrom(root_);
    root_ = nullptr;
  }

  template< class Key, class Value, class Cmp >
  void AvlTree< Key, Value, Cmp >::clearFrom(TreeNode< Key, Value >* root)
  {
    if (root)
    {
      size_--;
      clearFrom(root->left);
      clearFrom(root->right);
      delete root;
    }
  }
}


#endif