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
    ~Node() = default;
  };

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
    using iterator = Iterator< Key, T, Compare >;
    using const_iterator = ConstIterator< Key, T, Compare >;
    using Tree = AVLTree< Key, T, Compare >;
    using NodeType = Node< Key, T >;
  public:
    AVLTree();
    AVLTree(const Tree&);
    AVLTree(Tree&&);
    ~AVLTree();

    Tree& operator=(const Tree&);
    Tree& operator=(Tree&&);
    T& at(const Key&);
    const T& at(const Key&) const;
    T& operator[](const Key&);

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    std::pair< Iterator< Key, T, Compare >, bool > insert(const std::pair< Key, T >&);
    void swap(Tree&);
    void clear() noexcept;
    bool empty() const noexcept;
    size_t size() const noexcept;
    iterator find(const Key&);
    const_iterator find(const Key&) const;

  private:
    NodeType* root_;
    NodeType* fakeleaf_;
    Compare comp;
    NodeType* copyTree(const NodeType*);
    NodeType* balance(NodeType*);
    void updateHeight(NodeType*);
    int getBalanceFactor(NodeType*) const;
    NodeType* rotateRight(NodeType*);
    NodeType* rotateLeft(NodeType*);
    NodeType* findNode(const Key&) const;
    void clearSubtree(NodeType*) noexcept;
  };

  template <class Key, class T, class Compare>
  void AVLTree<Key, T, Compare>::clear() noexcept {
    clearSubtree(root_);
    root_ = fakeleaf_;
  }

  template< class Key, class T, class Compare >
  bool AVLTree< Key, T, Compare >::empty() const noexcept
  {
    return size() == 0;
  }

  template< class Key, class T, class Compare >
  Iterator< Key, T, Compare > AVLTree< Key, T, Compare >::find(const Key& key)
  {
    NodeType* node = findNode(key);
    return iterator(node ? node : nullptr, this);
  }

  template< class Key, class T, class Compare >
  ConstIterator< Key, T, Compare > AVLTree< Key, T, Compare >::find(const Key& key) const
  {
    const NodeType* node = findNode(key);
    return const_iterator(node ? node : nullptr, this);
  }

  template< class Key, class T, class Compare >
  Node< Key, T >* AVLTree< Key, T, Compare >::findNode(const Key& key) const
  {
    Node< Key, T >* current = root_;
    while (current && !current->isFake) {
      if (comp(key, current->value.first)) {
        current = current->left;
      } else if (comp(current->value.first, key)) {
        current = current->right;
      } else {
        return current;
      }
    }
    return nullptr;
  }

  template< class Key, class T, class Compare >
  T& AVLTree< Key, T, Compare >::operator[](const Key& key)
  {
    auto result = insert(std::make_pair(key, T()));
    return result.first->second;
  }

  template< class Key, class T, class Compare >
  T& AVLTree< Key, T, Compare >::at(const Key& key)
  {
    Node< Key, T >* node = findNode(key);
    if (!node || node->isFake) {
      throw std::out_of_range("Key not found in AVLTree");
    }
    return node->value.second;
  }

  template< class Key, class T, class Compare >
  const T& AVLTree< Key, T, Compare >::at(const Key& key) const
  {
    const Node< Key, T >* node = findNode(key);
    if (!node || node->isFake) {
      throw std::out_of_range("Key not found in AVLTree");
    }
    return node->value.second;
  }

  template< class Key, class T, class Compare >
  Iterator< Key, T, Compare > AVLTree< Key, T, Compare >::begin() noexcept
  {
    Node< Key, T >* node = root_;
    while (node && !node->left->isFake) {
      node = node->left;
    }
    return iterator(node, this);
  }

  template< class Key, class T, class Compare >
  ConstIterator< Key, T, Compare> AVLTree<Key, T, Compare >::begin() const noexcept
  {
    const Node< Key, T >* node = root_;
    while (node && !node->left->isFake) {
      node = node->left;
    }
    return ConstIterator<Key, T, Compare>(node, this);
  }

  template< class Key, class T, class Compare >
  Iterator< Key, T, Compare > AVLTree< Key, T, Compare >::end() noexcept
  {
    return iterator(fakeleaf_, this);
  }

  template< class Key, class T, class Compare >
  ConstIterator< Key, T, Compare > AVLTree< Key, T, Compare >::end() const noexcept
  {
    return const_iterator(fakeleaf_, this);
  }

  template< class Key, class T, class Compare >
  ConstIterator< Key, T, Compare > AVLTree< Key, T, Compare >::cbegin() const noexcept
  {
    return begin();
  }

  template< class Key, class T, class Compare >
  ConstIterator< Key, T, Compare > AVLTree< Key, T, Compare >::cend() const noexcept
  {
    return end();
  }

  template < class Key, class T, class Compare >
  size_t AVLTree< Key, T, Compare >::size() const noexcept
  {
    size_t size = 0;
    for (auto i = begin(); i != end(); ++i) {
      size++;
    }
    return size;
  }

  template < class Key, class T, class Compare >
  std::pair< Iterator< Key, T, Compare >, bool > AVLTree< Key, T, Compare >::insert(const std::pair< Key, T >& value)
  {
    if (root_ == fakeleaf_) {
      root_ = new NodeType(value, fakeleaf_);
      root_->left = fakeleaf_;
      root_->right = fakeleaf_;
      return std::make_pair(Iterator< Key, T, Compare >(root_, this), true);
    }

    NodeType* current = root_;
    NodeType* parent = nullptr;

    while (!current->isFake) {
      parent = current;
      if (comp(value.first, current->value.first)) {
        current = current->left;
      } else if (comp(current->value.first, value.first)) {
        current = current->right;
      } else {
        return std::make_pair(Iterator< Key, T, Compare >(current, this), false);
      }
    }

    NodeType* newNode = new NodeType(value, fakeleaf_);
    newNode->parent = parent;
    newNode->left = fakeleaf_;
    newNode->right = fakeleaf_;

    if (comp(value.first, parent->value.first)) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }

    NodeType* node = newNode;
    while (node->parent && !node->parent->isFake) {
      node = node->parent;
      node = balance(node);
      if (node->parent) {
        if (node->parent->left == node->parent->left) {
          node->parent->left = node;
        } else {
          node->parent->right = node;
        }
      }
    }

    if (node == root_) {
      root_ = balance(root_);
    }

    return std::make_pair(Iterator< Key, T, Compare >(newNode, this), true);
  }

  template < class Key, class T, class Compare >
  void AVLTree< Key, T, Compare >::updateHeight(NodeType* node)
  {
    if (node->isFake) return;
    node->height = 1 + std::max(node->left->height, node->right->height);
  }

  template < class Key, class T, class Compare >
  int AVLTree <Key, T, Compare >::getBalanceFactor(NodeType* node) const
  {
    if (node->isFake) return 0;
    return node->left->height - node->right->height;
  }

  template < class Key, class T, class Compare >
  Node< Key, T >* AVLTree< Key, T, Compare >::rotateRight(NodeType* y)
  {
    NodeType* x = y->left;
    NodeType* w = x->right;

    x->right = y;
    y->left = w;

    x->parent = y->parent;
    y->parent = x;
    if (w && !w->isFake) w->parent = y;

    y->height = 1 + std::max(y->left->height, y->right->height);
    x->height = 1 + std::max(x->left->height, x->right->height);

    return x;
  }

  template < class Key, class T, class Compare >
  Node< Key, T >* AVLTree< Key, T, Compare >::rotateLeft(NodeType* x)
  {
    NodeType* y = x->right;
    NodeType* w = y->left;

    y->left = x;
    x->right = w;

    y->parent = x->parent;
    x->parent = y;
    if (w && !w->isFake) w->parent = x;

    x->height = 1 + std::max(x->left->height, x->right->height);
    y->height = 1 + std::max(y->left->height, y->right->height);

    return y;
  }

  template < class Key, class T, class Compare >
  Node< Key, T >* AVLTree< Key, T, Compare >::balance(NodeType* node)
  {
    if (node->isFake) return node;

    updateHeight(node);
    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1) {
      if (getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
      }
      return rotateRight(node);
    }
    if (balanceFactor < -1) {
      if (getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
      }
      return rotateLeft(node);
    }
    return node;
  }

  template< class Key, class T, class Compare >
  void AVLTree< Key, T, Compare >::swap(Tree& other)
  {
    std::swap(other.comp, comp);
    std::swap(other.fakeleaf_, fakeleaf_);
    std::swap(other.root_, root_);
  }

  template< class Key, class T, class Compare >
  AVLTree< Key, T, Compare >::AVLTree()
  {
    fakeleaf_ = new Node< Key, T >();
    fakeleaf_->left = fakeleaf_;
    fakeleaf_->right = fakeleaf_;
    fakeleaf_->parent = nullptr;
    root_ = fakeleaf_;
  }

  template <class Key, class T, class Compare>
  Node< Key, T >* AVLTree< Key, T, Compare >::copyTree(const NodeType* otherNode)
  {
    if (otherNode->isFake) {
      return fakeleaf_;
    }
    NodeType* newNode = new NodeType(otherNode->value, fakeleaf_);
    newNode->left = copyTree(otherNode->left);
    newNode->right = copyTree(otherNode->right);
    newNode->height = otherNode->height;

    if (!newNode->left->isFake) {
      newNode->left->parent = newNode;
    }
    if (!newNode->right->isFake) {
      newNode->right->parent = newNode;
    }
    return newNode;
  }

  template <class Key, class T, class Compare>
  void AVLTree< Key, T, Compare >::clearSubtree(NodeType* node) noexcept
  {
    if (node && !node->isFake) {
      clearSubtree(node->left);
      clearSubtree(node->right);
      delete node;
    }
  }

  template< class Key, class T, class Compare >
  AVLTree< Key, T, Compare >::~AVLTree()
  {
    clearSubtree(root_);
    delete fakeleaf_;
  }

  template< class Key, class T, class Compare >
  AVLTree< Key, T, Compare >::AVLTree(const Tree& other):
    comp(other.comp)
  {
    fakeleaf_ = new NodeType();
    fakeleaf_->left = fakeleaf_->right = fakeleaf_;
    root_ = copyTree(other.root_);
  }

  template< class Key, class T, class Compare >
  AVLTree< Key, T, Compare >& AVLTree< Key, T, Compare >::operator=(const Tree& other)
  {
    if (this != std::addressof(other)) {
      Tree copy(other);
      swap(copy);
    }
    return *this;
  }

  template< class Key, class T, class Compare >
  AVLTree< Key, T, Compare >::AVLTree(Tree&& other):
    root_(other.root_),
    fakeleaf_(other.fakeleaf_),
    comp(std::move(other.comp))
  {
    other.root_ = other.fakeleaf_;
    other.fakeleaf_ = nullptr;
  }

  template< class Key, class T, class Compare >
  AVLTree< Key, T, Compare >& AVLTree< Key, T, Compare >::operator=(Tree&& other)
  {
    if (this != std::addressof(other)) {
      Tree copy(std::move(other));
      swap(copy);
    }
    return *this;
  }
}
#endif