#ifndef TREE_HPP
#define TREE_HPP

#include <cassert>
#include <exception>
#include "tree_node.hpp"
#include "tree_iterator.hpp"

namespace lanovenko
{
  template<typename Key, typename Value, typename Comparator>
  class TreeIterator;

  template< typename Key, typename Value, typename Comparator >
  class Tree
  {
  public:
    ~Tree();
    Tree();
    Tree(const Tree< Key, Value, Comparator >& rhs);
    Tree(Tree< Key, Value, Comparator >&& rhs) noexcept;
    Tree< Key, Value, Comparator >& operator=(const Tree< Key, Value, Comparator >& rhs);
    Tree< Key, Value, Comparator >& operator=(Tree< Key, Value, Comparator >&& rhs) noexcept;
    TreeIterator< Key, Value, Comparator > begin() const noexcept;
    TreeIterator< Key, Value, Comparator > end() const noexcept;
    size_t size() const noexcept;
    bool empty() const noexcept;
    void clear() noexcept;
    void swap(Tree< Key, Value, Comparator >& rhs) noexcept;
    TreeIterator< Key, Value, Comparator > find(const Key& key) const;
    void insert(const std::pair< Key, Value >& value);
    void erase(const std::pair< Key, Value >& value);
    Value& at(const Key& key);
    Value& operator[](const Key& key);
  private:
    TreeNode< Key, Value >* root_;
    size_t size_;
    unsigned short int height(TreeNode< Key, Value >* node) const noexcept;
    short int balanceFactor(TreeNode< Key, Value >* node) const noexcept;
    TreeNode< Key, Value >* rotateRight(TreeNode< Key, Value >* root) const noexcept;
    TreeNode< Key, Value >* rotateLeft(TreeNode< Key, Value >* root) const noexcept;
    TreeNode< Key, Value >* insert(TreeNode< Key, Value >* node, const std::pair< Key, Value >& value, Comparator cmp);
    TreeNode< Key, Value >* minValueNode(TreeNode< Key, Value >* node) const;
    TreeNode< Key, Value >* erase(TreeNode< Key, Value >* node, const std::pair< Key, Value >& value, Comparator cmp);
    TreeIterator< Key, Value, Comparator > find(const Key& key, Comparator cmp) const;
    void clear(TreeNode< Key, Value >* root) noexcept;
  };

  template< typename Key, typename Value, typename Comparator >
  Tree< Key, Value, Comparator >::~Tree()
  {
    clear();
  }

  template< typename Key, typename Value, typename Comparator >
  Tree< Key, Value, Comparator >::Tree() :
    root_(nullptr),
    size_(0)
  {}

  template< typename Key, typename Value, typename Comparator >
  Tree< Key, Value, Comparator >::Tree(const Tree< Key, Value, Comparator >& rhs) :
    root_(nullptr),
    size_(rhs.size_)
  {
    for (TreeIterator< Key, Value, Comparator > it = rhs.begin(); it != rhs.end(); it++)
    {
      insert(*it);
    }
  }

  template<typename Key, typename Value, typename Comparator>
  Tree<Key, Value, Comparator>::Tree(Tree<Key, Value, Comparator>&& rhs) noexcept :
    root_(rhs.root_),
    size_(rhs.size_)
  {}

  template< typename Key, typename Value, typename Comparator >
  Tree< Key, Value, Comparator >& Tree< Key, Value, Comparator >::operator=(const Tree< Key, Value, Comparator >& rhs)
  {
    if (this == std::addressof(rhs))
    {
      return *this;
    }
    Tree< Key, Value, Comparator > temp(rhs);
    swap(temp);
    return *this;
  }

  template<typename Key, typename Value, typename Comparator>
  Tree<Key, Value, Comparator>& Tree<Key, Value, Comparator>::operator=(Tree<Key, Value, Comparator>&& rhs) noexcept
  {
    if (this == std::addressof(rhs))
    {
      return *this;
    }
    Tree< Key, Value, Comparator > temp(std::move(rhs));
    swap(temp);
    return *this;
  }

  template< typename Key, typename Value, typename Comparator >
  inline TreeIterator< Key, Value, Comparator > Tree< Key, Value, Comparator >::begin() const noexcept
  {
    return TreeIterator< Key, Value, Comparator >(minValueNode(root_));
  }

  template< typename Key, typename Value, typename Comparator >
  inline TreeIterator< Key, Value, Comparator > Tree< Key, Value, Comparator >::end() const noexcept
  {
    return TreeIterator< Key, Value, Comparator >();
  }

  template<typename Key, typename Value, typename Comparator>
  inline size_t Tree<Key, Value, Comparator>::size() const noexcept
  {
    return size_;
  }

  template<typename Key, typename Value, typename Comparator>
  inline bool Tree<Key, Value, Comparator>::empty() const noexcept
  {
    return size_ == 0;
  }


  template< typename Key, typename Value, typename Comparator >
  void Tree< Key, Value, Comparator >::clear() noexcept
  {
    clear(root_);
    root_ = nullptr;
  }

  template< typename Key, typename Value, typename Comparator >
  inline void Tree< Key, Value, Comparator >::swap(Tree< Key, Value, Comparator >& rhs) noexcept
  {
    std::swap(root_, rhs.root_);
    std::swap(size_, rhs.size_);
  }

  template<typename Key, typename Value, typename Comparator>
  inline TreeIterator<Key, Value, Comparator> Tree<Key, Value, Comparator>::find(const Key& key) const
  {
    return find(key, Comparator{});
  }

  template<typename Key, typename Value, typename Comparator>
  void Tree< Key, Value, Comparator >::insert(const std::pair< Key, Value >& value)
  {
    root_ = insert(root_, value, Comparator{});
    size_++;
  }

  template< typename Key, typename Value, typename Comparator >
  void Tree< Key, Value, Comparator >::erase(const std::pair< Key, Value >& value)
  {
    root_ = erase(root_, value, Comparator{});
    size_--;
  }

  template<typename Key, typename Value, typename Comparator>
  inline Value& Tree<Key, Value, Comparator>::at(const Key& key)
  {
    TreeIterator< Key, Value, Comparator > node = find(key);
    if (node != end())
    {
      return (*node).second;
    }
    throw std::out_of_range("<INVALID COMMAND>");
  }

  template<typename Key, typename Value, typename Comparator>
  Value& Tree<Key, Value, Comparator>::operator[](const Key& key)
  {
    TreeIterator<Key, Value, Comparator> node = find(key);
    if (node == end())
    {
      insert({ key, Value() });
      node = find(key);
    }
    return node->second;
  }

  template< typename Key, typename Value, typename Comparator >
  inline unsigned short int Tree< Key, Value, Comparator >::height(TreeNode< Key, Value >* node) const noexcept
  {
    return !node ? 0 : node->height_;
  }

  template<typename Key, typename Value, typename Comparator>
  inline short int Tree< Key, Value, Comparator >::balanceFactor(TreeNode< Key, Value >* node) const noexcept
  {
    return !node ? 0 : height(node->left_) - height(node->right_);
  }

  template< typename Key, typename Value, typename Comparator >
  TreeNode< Key, Value >* Tree< Key, Value, Comparator >::rotateRight(TreeNode< Key, Value >* root) const noexcept
  {
    assert(root && root->left_);
    TreeNode< Key, Value  >* newRoot = root->left_;
    if (root->parent_)
    {
      newRoot->parent_ = root->parent_;
      if (root->parent_->right_ == root)
      {
        newRoot->parent_->right_ = newRoot;
      }
      else
      {
        newRoot->parent_->left_ = newRoot;
      }
    }
    else
    {
      newRoot->parent_ = nullptr;
    }
    root->parent_ = newRoot;
    if (newRoot->right_)
    {
      root->left_ = newRoot->right_;
      root->left_->parent_ = root;
    }
    else
    {
      root->left_ = nullptr;
    }
    newRoot->right_ = root;
    root->height_ = std::max(height(root->right_), height(root->left_)) + 1;
    newRoot->height_ = std::max(height(newRoot->right_), height(newRoot->left_)) + 1;
    return newRoot;
  }

  template< typename Key, typename Value, typename Comparator >
  TreeNode< Key, Value >* Tree< Key, Value, Comparator >::rotateLeft(TreeNode < Key, Value >* root) const noexcept
  {
    assert(root && root->right_);
    TreeNode< Key, Value >* newRoot = root->right_;
    if (root->parent_)
    {
      newRoot->parent_ = root->parent_;
      if (root->parent_->right_ == root)
      {
        newRoot->parent_->right_ = newRoot;
      }
      else
      {
        newRoot->parent_->left_ = newRoot;
      }
    }
    else
    {
      newRoot->parent_ = nullptr;
    }
    root->parent_ = newRoot;
    if (newRoot->left_)
    {
      root->right_ = newRoot->left_;
      root->right_->parent_ = root;
    }
    else
    {
      root->right_ = nullptr;
    }
    newRoot->left_ = root;
    root->height_ = std::max(height(root->right_), height(root->left_)) + 1;
    newRoot->height_ = std::max(height(newRoot->right_), height(newRoot->left_)) + 1;
    return newRoot;
  }

  template<typename Key, typename Value, typename Comparator>
  TreeNode<Key, Value>* Tree< Key, Value, Comparator >::insert(
    TreeNode<Key, Value>* node,
    const std::pair<Key, Value>& value,
    Comparator cmp)
  {
    if (!node)
    {
      return new TreeNode<Key, Value>(value);
    }

    if (cmp(value.first, node->data_.first))
    {
      node->left_ = insert(node->left_, value, cmp);
      node->left_->parent_ = node;
    }
    else if (cmp(node->data_.first, value.first))
    {
      node->right_ = insert(node->right_, value, cmp);
      node->right_->parent_ = node;
    }
    else
    {
      node->data_.second = value.second;
      return node;
    }

    node->height_ = std::max(height(node->left_), height(node->right_)) + 1;

    short int balance = balanceFactor(node);

    if (balance > 1 && cmp(value.first, node->left_->data_.first))
    {
      return rotateRight(node);
    }

    if (balance < -1 && cmp(node->right_->data_.first, value.first))
    {
      return rotateLeft(node);
    }

    if (balance > 1 && cmp(node->left_->data_.first, value.first))
    {
      node->left_ = rotateLeft(node->left_);
      return rotateRight(node);
    }

    if (balance < -1 && cmp(value.first, node->right_->data_.first))
    {
      node->right_ = rotateRight(node->right_);
      return rotateLeft(node);
    }

    return node;
  }

  template<typename Key, typename Value, typename Comparator>
  TreeNode<Key, Value>* Tree<Key, Value, Comparator>::minValueNode(TreeNode<Key, Value>* node) const
  {
    TreeNode< Key, Value >* current = node;
    while (current->left_)
    {
      current = current->left_;
    }
    return current;
  }

  template< typename Key, typename Value, typename Comparator >
  TreeNode< Key, Value >* erase(
    TreeNode< Key, Value >* node,
    const std::pair< Key, Value >& value, Comparator cmp
  )
  {
    if (!node)
    {
      return node;
    }

    if (cmp(value.first, node->data_.first))
    {
      node->left_ = erase(node->left_, value, cmp);
    }
    else if (cmp(node->data_.first, value.first))
    {
      node->right_ = erase(node->right_, value, cmp);
    }
    else
    {
      if (!node->left_ || !node->right_)
      {
        TreeNode<Key, Value>* temp = node->left_ ? node->left_ : node->right_;

        if (!temp)
        {
          temp = node;
          node = nullptr;
        }
        else
        {
          node->data_ = temp->data_;
          node->left_ = temp->left_;
          node->right_ = temp->right_;
          if (node->left_) node->left_->parent_ = node;
          if (node->right_) node->right_->parent_ = node;
        }
        delete temp;
      }
      else
      {
        TreeNode<Key, Value>* temp = minValueNode(node->right_);

        node->data_ = temp->data_;

        node->right_ = erase(node->right_, temp->data_, cmp);
      }
    }

    if (!node)
    {
      return node;
    }

    node->height_ = 1 + std::max(height(node->left_), height(node->right_));

    short int balance = balanceFactor(node);

    if (balance > 1 && balanceFactor(node->left_) >= 0)
    {
      return rotateRight(node);
    }

    if (balance > 1 && balanceFactor(node->left_) < 0)
    {
      node->left_ = rotateLeft(node->left_);
      return rotateRight(node);
    }

    if (balance < -1 && balanceFactor(node->right_) <= 0)
    {
      return rotateLeft(node);
    }

    if (balance < -1 && balanceFactor(node->right_) > 0)
    {
      node->right_ = rotateRight(node->right_);
      return rotateLeft(node);
    }

    return node;
  }

  template< typename Key, typename Value, typename Comparator >
  inline TreeIterator< Key, Value, Comparator > Tree< Key, Value, Comparator >::find(
    const Key& key,
    Comparator cmp) const
  {
    TreeNode< Key, Value >* root = root_;
    while (root != nullptr && key != root->data_.first)
    {
      if (cmp(key, root->data_.first))
      {
        root = root->left_;
      }
      else
      {
        root = root->right_;
      }
    }
    return TreeIterator< Key, Value, Comparator >(root);
  }

  template< typename Key, typename Value, typename Comparator >
  void Tree< Key, Value, Comparator >::clear(TreeNode< Key, Value >* root) noexcept
  {
    if (!root)
    {
      return;
    }
    clear(root->left_);
    clear(root->right_);
    delete root;
    size_--;
  }
}


#endif
