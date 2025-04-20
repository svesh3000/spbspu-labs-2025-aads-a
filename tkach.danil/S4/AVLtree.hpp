#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <functional>
#include "node_tree.hpp"
#include "c_iterator.hpp"
#include "iterator.hpp"

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
    TreeNode< Key, Value >* find(const Key& key) const;
    Value& at(const Key& key);
    const Value& at(const Key& key) const;
    Citerator< Key, Value, Cmp > cbegin() const;
    Iterator< Key, Value, Cmp > begin();
    Citerator< Key, Value, Cmp > cend() const;
    Iterator< Key, Value, Cmp > end();
  private:
    TreeNode< Key, Value >* root_;
    size_t size_;
    Cmp cmp_;
    template< class... Args >
    void insertSingle(Args&&... args);
    template< class... Args >
    TreeNode< Key, Value >* insertCmp(TreeNode< Key, Value >* root, Args&&... args);
    void clearFrom(TreeNode< Key, Value >* node);
    TreeNode< Key, Value >* findMin(TreeNode< Key, Value >* node) const;
  };

  template< class Key, class Value, class Cmp >
  AvlTree< Key, Value, Cmp >::AvlTree():
    root_(nullptr),
    size_(0),
    cmp_()
  {}

  template< class Key, class Value, class Cmp >
  Citerator< Key, Value, Cmp > AvlTree< Key, Value, Cmp >::cbegin() const
  {
    return Citerator< Key, Value, Cmp >(findMin(root_));
  }
  
  template< class Key, class Value, class Cmp >
  Iterator< Key, Value, Cmp > AvlTree< Key, Value, Cmp >::begin()
  {
    return Iterator< Key, Value, Cmp >(findMin(root_));
  }
  
  template< class Key, class Value, class Cmp >
  Citerator< Key, Value, Cmp > AvlTree< Key, Value, Cmp >::cend() const
  {
    return Citerator< Key, Value, Cmp >();
  }

  template< class Key, class Value, class Cmp >
  Iterator< Key, Value, Cmp > AvlTree< Key, Value, Cmp >::end()
  {
    return Iterator< Key, Value, Cmp >();
  }

  template< class Key, class Value, class Cmp >
  TreeNode< Key, Value >* AvlTree< Key, Value, Cmp >::findMin(TreeNode< Key, Value >* root) const
  {
    while (root != nullptr && root->left != nullptr)
    {
      root = root->left;
    }
    return root;
  }

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
    const TreeNode< Key, Value >* node = find(key);
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
  void AvlTree< Key, Value, Cmp >::insertSingle(Args&&... args)
  {
    try
    {
      root_ = insertCmp(root_, std::forward< Args >(args)...);
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
  TreeNode< Key, Value >* AvlTree< Key, Value, Cmp >::insertCmp(TreeNode< Key, Value >* root, Args&&... args)
  {
    if (root == nullptr)
    {
      return new TreeNode< Key, Value >(std::forward< Args >(args)...);
    }
    else if (cmp_(std::get<0>(std::forward<Args>(args)...), root->data.first))
    {
      root->left = insertCmp(root->left, std::forward< Args >(args)...);
      if (root->left->parent == nullptr)
      {
        root->left->parent = root;
      }
    }
    else
    {
      root->right = insertCmp(root->right, std::forward< Args >(args)...);
      if (root->right->parent == nullptr)
      {
        root->right->parent = root;
      }
    }
    return root;
  }

  template< class Key, class Value, class Cmp >
  TreeNode< Key, Value >* AvlTree< Key, Value, Cmp >::find(const Key& key) const
  {
    TreeNode< Key, Value >* root = root_;
    while (root_ != nullptr && key != root->data.first)
    {
      if (cmp_(key, root->data.first))
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