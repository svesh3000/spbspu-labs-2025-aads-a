#ifndef TREE_HPP
#define TREE_HPP
#include "tree-iter.hpp"
#include "tree-citer.hpp"

namespace sveshnikov
{
  template< class Key, class T, class Cmp = std::less< Key > >
  class AvlTree
  {
  public:
    explicit AvlTree(); // ok
    AvlTree(const AvlTree &x);
    AvlTree(AvlTree &&x);
    AvlTree &operator=(const AvlTree &x);
    AvlTree &operator=(AvlTree &&x);

    Iter< Key, T > begin() noexcept;             // ok
    ConstIter< Key, T > begin() const noexcept;  // ok
    ConstIter< Key, T > cbegin() const noexcept; // ok
    Iter< Key, T > end() noexcept;               // ok
    ConstIter< Key, T > end() const noexcept;    // ok
    ConstIter< Key, T > cend() const noexcept;   // ok

    size_t size() const noexcept; // ok
    bool empty() const noexcept;  // ok

    T &operator[](const Key &k);
    T &operator[](Key &&k);
    T &at(const Key &k);
    const T &at(const Key &k) const;

    void clear() noexcept;
    void swap(AvlTree &x);
    std::pair< Iter< Key, T >, bool > insert(const std::pair< Key, T > &val);
    Iter< Key, T > erase(ConstIter< Key, T > position);
    size_t erase(const Key &k);

    Iter< Key, T > find(const Key &k);
    ConstIter< Key, T > find(const Key &k) const;
    pair< ConstIter< Key, T >, ConstIter< Key, T > > equal_range(const Key &k) const;
    pair< Iter< Key, T >, Iter< Key, T > > equal_range(const Key &k);
    size_t count(const Key &k) const;

  private:
    tree_node_t< Key, T > *root_;
    size_t size_;

    tree_node_t< Key, T > *getMinNode();                                // ok
    tree_node_t< Key, T > *getMaxNode();                                // ok
    void updateHeight(tree_node_t< Key, T > *node);                     // ok
    tree_node_t< Key, T > *rotateRight(tree_node_t< Key, T > *node);    // ok
    tree_node_t< Key, T > *rotateLeft(tree_node_t< Key, T > *node);     // ok
    tree_node_t< Key, T > *bigRotateRight(tree_node_t< Key, T > *node); // ok
    tree_node_t< Key, T > *bigRotateLeft(tree_node_t< Key, T > *node);  // ok
  };

  template< class Key, class T, class Cmp >
  AvlTree< Key, T, Cmp >::AvlTree():
    root_(nullptr),
    size_(0)
  {}

  template< class Key, class T, class Cmp >
  tree_node_t< Key, T > *AvlTree< Key, T, Cmp >::getMinNode()
  {
    auto curr = root_;
    while (curr->left_->left)
    {
      curr = curr->left_;
    }
    return curr;
  }

  template< class Key, class T, class Cmp >
  Iter< Key, T > AvlTree< Key, T, Cmp >::begin() noexcept
  {
    return Iter< Key, T >(getMinNode());
  }

  template< class Key, class T, class Cmp >
  ConstIter< Key, T > AvlTree< Key, T, Cmp >::begin() const noexcept
  {
    return cbegin();
  }

  template< class Key, class T, class Cmp >
  ConstIter< Key, T > AvlTree< Key, T, Cmp >::cbegin() const noexcept
  {
    return ConstIter< Key, T >(getMinNode());
  }

  template< class Key, class T, class Cmp >
  tree_node_t< Key, T > *AvlTree< Key, T, Cmp >::getMaxNode()
  {
    auto curr = root_;
    while (curr->right_->right_)
    {
      curr = curr->right_;
    }
    return curr;
  }

  template< class Key, class T, class Cmp >
  Iter< Key, T > AvlTree< Key, T, Cmp >::end() noexcept
  {
    return Iter< Key, T >(getMaxNode()->right_);
  }

  template< class Key, class T, class Cmp >
  ConstIter< Key, T > AvlTree< Key, T, Cmp >::end() const noexcept
  {
    return cend();
  }

  template< class Key, class T, class Cmp >
  ConstIter< Key, T > AvlTree< Key, T, Cmp >::cend() const noexcept
  {
    return ConstIter< Key, T >(getMaxNode()->right_);
  }

  template< class Key, class T, class Cmp >
  size_t AvlTree< Key, T, Cmp >::size() const noexcept
  {
    return size_;
  }

  template< class Key, class T, class Cmp >
  bool AvlTree< Key, T, Cmp >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< class Key, class T, class Cmp >
  std::pair< Iter< Key, T >, bool > AvlTree< Key, T, Cmp >::insert(const std::pair< Key, T > &val)
  {
    Cmp cmp{};
    tree_node_t< Key, T > *curr = root_;
    Iter< Key, T > it = find(val.first);
    if (it != end())
    {
      return std::make_pair(it, false);
    }

    tree_node_t< Key, T > *node = new tree_node_t< Key, T >(val);
    node.right_ = new tree_node_t< Key, T >();
    node.left_ = new tree_node_t< Key, T >();
    node->left_->parent_ = root_;
    node->right_->parent_ = root_;
    size_++;

    if (!root_)
    {
      root_ = node;
    }
    else
    {
      while (curr->height_ != 0)
      {
        curr->height_++;
        if (cmp(val.first, curr->data_.first))
        {
          curr = curr->left_;
        }
        else
        {
          curr = curr->right_;
        }
      }
      node.parent_ = curr.parent_;
      delete curr;
    }
    return std::make_pair(Iter< Key, T >(node), true);
  }

  template< class Key, class T, class Cmp >
  void AvlTree< Key, T, Cmp >::updateHeight(tree_node_t< Key, T > *node)
  {
    if (!node || node->height_ == 0)
    {
      return;
    }
    node->height_ = std::max(node->left_->height_, node->right_->height_) + 1;
  }

  template< class Key, class T, class Cmp >
  tree_node_t< Key, T > *AvlTree< Key, T, Cmp >::rotateRight(tree_node_t< Key, T > *node)
  {
    if (!node || !node->left_ || node->left_->height_ == 0)
    {
      return node;
    }
    tree_node_t< Key, T > *parent = node->parent_;
    tree_node_t< Key, T > *left_son = node->left_;
    tree_node_t< Key, T > *left_right_grand_son = left_son->right_;

    if (parent)
    {
      if (parent->right_ == node)
      {
        parent->right_ = left_son;
      }
      else
      {
        parent->left_ = left_son;
      }
    }
    else
    {
      root_ = left_son;
    }
    node->parent_ = left_son;
    node->left_ = left_right_grand_son;
    left_son->parent_ = parent;
    left_son->right_ = node;
    left_right_grand_son->parent_ = node;
    updateHeight(node);
    updateHeight(left_son);
    return left_son;
  }

  template< class Key, class T, class Cmp >
  tree_node_t< Key, T > *AvlTree< Key, T, Cmp >::rotateLeft(tree_node_t< Key, T > *node)
  {
    if (!node || !node->right_ || node->right_->height_ == 0)
    {
      return node;
    }
    tree_node_t< Key, T > *parent = node->parent_;
    tree_node_t< Key, T > *right_son = node->right_;
    tree_node_t< Key, T > *right_left_grand_son = right_son->left_;

    if (parent)
    {
      if (parent->right_ == node)
      {
        parent->right_ = right_son;
      }
      else
      {
        parent->left_ = right_son;
      }
    }
    else
    {
      root_ = right_son;
    }
    node->parent_ = right_son;
    node->right_ = right_left_grand_son;
    right_son->parent_ = parent;
    right_son->left_ = node;
    right_left_grand_son->parent_ = node;
    updateHeight(node);
    updateHeight(right_son);
    return right_son;
  }

  template< class Key, class T, class Cmp >
  tree_node_t< Key, T > *AvlTree< Key, T, Cmp >::bigRotateRight(tree_node_t< Key, T > *node)
  {
    if (!node || !node->left_)
    {
      return node;
    }
    node->left_ = rotateLeft(node->left_);
    return rotateRight(node);
  }

  template< class Key, class T, class Cmp >
  tree_node_t< Key, T > *AvlTree< Key, T, Cmp >::bigRotateLeft(tree_node_t< Key, T > *node)
  {
    if (!node || !node->right_)
    {
      return node;
    }
    node->right_ = rotateRight(node->right_);
    return rotateLeft(node);
  }
}

#endif
