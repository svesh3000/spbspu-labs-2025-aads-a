#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <algorithm>

#include "iterator.hpp"
#include "constIterator.hpp"

namespace dribas
{
  template <class Key, class T, class Compare> class Iterator;
  template <class Key, class T, class Compare> class ConstIterator;

  template< class Key, class T >
  struct Node
  {
    std::pair< Key, T > value;
    Node< Key, T >* left;
    Node< Key, T >* right;
    Node< Key, T >* parent;
    int height;
    bool isFake;
    Node(const std::pair< Key, T >&, Node< Key, T >*);
    Node();
    template< class... Args >
    Node(Node< Key, T >* fakeleaf, Args&&... args);
    ~Node() = default;
  };

  template< class Key, class T >
  template< class... Args >
  Node< Key, T >::Node(Node< Key, T >* fakeleaf, Args&&... args):
    value(std::forward< Args >(args)...),
    left(fakeleaf),
    right(fakeleaf),
    parent(nullptr),
    height(1),
    isFake(false)
  {
    left->parent = this;
    right->parent = this;
  }

  template< class Key, class T >
  Node< Key, T >::Node():
    left(nullptr),
    right(nullptr),
    parent(nullptr),
    height(0),
    isFake(true)
  {}

  template< class Key, class T >
  Node< Key, T >::Node(const std::pair< Key, T >& val, Node< Key, T >* fakeleaf):
    value(val),
    left(fakeleaf),
    right(fakeleaf),
    parent(nullptr),
    height(1),
    isFake(false)
  {
    left->parent = this;
    right->parent = this;
  }

  template< class Key, class T, class Compare = std::less< Key > >
  class AVLTree
  {
    friend class Iterator< Key, T, Compare >;
    friend class ConstIterator< Key, T, Compare >;
    using iterator = Iterator< Key, T, Compare >;
    using const_iterator = ConstIterator< Key, T, Compare >;
    using TreeType = AVLTree< Key, T, Compare >;
    using NodeType = Node< Key, T >;
  public:
    AVLTree();
    // AVLTree(const TreeType&);
    // AVLTree(AVLTree&&);
    ~AVLTree();

    // TreeType& operator=(const TreeType&);
    // TreeType& operator=(TreeType&&);
    // T& at(const Key&);
    // const T& at(const Key&) const;
    // T& operator[](const Key&);

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    template< class... Args >
    std::pair< iterator, bool > emplace(Args&&... args);
    //iterator emplace_hint(const_iterator hint, Args&&... args);


    // std::pair< iterator, bool > insert(const std::pair< Key, T >&);
    // void swap(AVLTree&);
    void clear() noexcept;
    // bool empty() const noexcept;
    // size_t size() const noexcept;
    // iterator find(const Key&);
    // const_iterator find(const Key&) const;

  private:
    NodeType* fakeleaf_;
    NodeType* root_;
    Compare cmp_;
    size_t size_;
    void balanceTree(NodeType*);
    NodeType* balance(NodeType*) noexcept;
    void updateHeight(NodeType*) noexcept;
    int getBalanceFactor(NodeType*) const noexcept;
    NodeType* rightRotate(NodeType*) noexcept;
    NodeType* leftRotate(NodeType*) noexcept;
    // NodeType* findNode(const Key&) const;
    void clearSubtree(NodeType*) noexcept;
  };

  template< class Key, class T, class Cmp >
  void AVLTree< Key, T, Cmp >::balanceTree(NodeType* node)
  {
    while (node) {
      NodeType* parent = node->parent;
      bool isLeft = false;
      if (parent != nullptr) {
        isLeft = (parent->left == node);
      }
      node = balance(node);
      if (parent != nullptr) {
        if (isLeft) {
          parent->left = node;
        } else {
          parent->right = node;
        }
      } else {
        root_ = node;
      }
      node = parent;
    }
  }

  template< class Key, class T, class Cmp >
  ConstIterator< Key, T, Cmp > AVLTree< Key, T, Cmp >::end() const noexcept
  {
    return const_iterator{ fakeleaf_, this};
  }

  template< class Key, class T, class Cmp >
  Iterator< Key, T, Cmp > AVLTree< Key, T, Cmp >::end() noexcept
  {
    return iterator{ fakeleaf_, this };
  }

  template< class Key, class T, class Cmp >
  ConstIterator< Key, T, Cmp > AVLTree< Key, T, Cmp >::begin() const noexcept
  {
    auto current = root_;
    if (current == fakeleaf_) {
      const_iterator{ current, this };
    }
    while (current->left != fakeleaf_) {
      current = current->left;
    }
    return const_iterator{ current, this };
  }

  template< class Key, class T, class Cmp >
  Iterator< Key, T, Cmp > AVLTree< Key, T, Cmp >::begin() noexcept
  {
    auto current = root_;
    if (current == fakeleaf_) {
      iterator{ current, this };
    }
    while (current->left != fakeleaf_) {
      current = current->left;
    }
    return iterator{ current, this };
  }

  template< class Key, class T, class Cmp >
  void AVLTree< Key, T, Cmp >::clearSubtree(NodeType* node) noexcept
  {
    if (node != fakeleaf_) {
      clearSubtree(node->left);
      clearSubtree(node->right);
      delete node;
    }
  }

  template< class Key, class T, class Cmp >
  void AVLTree< Key, T, Cmp >::clear() noexcept
  {
    clearSubtree(root_);
    root_ = fakeleaf_;
    size_ = 0;
  }

  template< class Key, class T, class Cmp >
  AVLTree< Key, T, Cmp >::~AVLTree()
  {
    clearSubtree(root_);
    delete[] reinterpret_cast< char* >(fakeleaf_);
  } 

  template< class Key, class T, class Cmp >
  AVLTree< Key, T, Cmp >::AVLTree():
    fakeleaf_(reinterpret_cast< NodeType* >(new char[sizeof(NodeType)])),
    root_(fakeleaf_),
    cmp_(),
    size_(0)
  {
    root_->left = fakeleaf_;
    root_->right = fakeleaf_;
    root_->isFake = true;
    fakeleaf_->parent = root_;
    root_->height = 0;
  }

  template< class Key, class T, class Cmp >
  template< class... Args >
  std::pair< Iterator< Key, T, Cmp >, bool > AVLTree< Key, T, Cmp >::emplace(Args&&... args)
  {
    NodeType* newNode = new NodeType(fakeleaf_, std::forward< Args >(args)...);
    const Key& key = newNode->value.first;
    newNode->right = fakeleaf_;
    newNode->left = fakeleaf_;
    if (root_ == fakeleaf_) {
      root_ = newNode;
      size_++;
      return { iterator(root_, this), true };
    }
    NodeType* current = root_;
    NodeType* parent = nullptr;
    while (current != fakeleaf_) {
      parent = current;
      if (cmp_(key, current->value.first)) {
        current = current->left;
      } else if (cmp_(current->value.first, key)) {
        current = current->right;
      } else {
        delete newNode;
        return { iterator(current, this), false };
      }
    }
    newNode->parent = parent;
    if (cmp_(key, parent->value.first)) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }
  
    balanceTree(newNode);
    size_++;
    return { iterator(newNode, this), true };
  }

  template< class Key, class T, class Cmp >
  void AVLTree< Key, T, Cmp >::updateHeight(NodeType* node) noexcept
  {
    auto current = node;
    while (node != nullptr || node == fakeleaf_) {
      node->height = std::max(node->right->height, node->left->height) + 1;
      node = node->parent;
    }
    node = current;
  }

  template< class Key, class T, class Cmp >
  int AVLTree< Key, T, Cmp >::getBalanceFactor(NodeType* node) const noexcept
  {
    if (node == fakeleaf_) {
      return 0;
    }
    return node->left->height - node->right->height;
  }

  template< class Key, class T, class Cmp >
  Node< Key, T >* AVLTree< Key, T, Cmp >::rightRotate(NodeType* node) noexcept
  {
    NodeType* leftNode = node->left;
    if (!leftNode->isFake) {
      leftNode->right->parent = node;
    }

    leftNode->parent = node->parent;
    node->parent = leftNode;
    leftNode->right = node;
    if (leftNode->parent != nullptr) {
      if (leftNode->parent->left == node) {
        leftNode->parent->left = leftNode;
      } else {
        leftNode->parent->right = leftNode;
      }
    } else {
      root_ = leftNode;
    }
    updateHeight(node);
    updateHeight(leftNode);

    return leftNode;
  }

  template < class Key, class T, class Cmp >
  Node< Key, T >* AVLTree< Key, T, Cmp >::leftRotate(NodeType* node) noexcept
  {
    NodeType* rightNode = node->right;
    if (!rightNode->isFake) {
      rightNode->left->parent = node;
    }

    rightNode->parent = node->parent;
    node->parent = rightNode;
    rightNode->left = node;
    if (rightNode->parent != nullptr) {
      if (rightNode->parent->right == node) {
        rightNode->parent->right = rightNode;
      } else {
        rightNode->parent->left = rightNode;
      }
    } else {
      root_ = rightNode;
    }
    updateHeight(node);
    updateHeight(rightNode);

    return rightNode;
  }

  template < class Key, class T, class Cmp >
  Node< Key, T >* AVLTree< Key, T, Cmp >::balance(NodeType* node) noexcept
  {
    updateHeight(node);
    int balance = getBalanceFactor(node);
    if (balance > 1) {
      if (getBalanceFactor(node->left) < 0) {
        node->left = leftRotate(node->left);
      }
      return rightRotate(node);
    }
    if (balance < -1) {
      if (getBalanceFactor(node->right) > 0) {
        node->right = rightRotate(node->right);
      }
      return leftRotate(node);
    }
    return node;
  }
}
#endif