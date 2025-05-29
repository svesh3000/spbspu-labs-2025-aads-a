#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <utility>

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
    AVLTree(const TreeType&);
    AVLTree(TreeType&&) noexcept;
    template< typename InputIt >
    AVLTree(InputIt, InputIt);
    explicit AVLTree(std::initializer_list< std::pair< Key, T > >);
    ~AVLTree();

    TreeType& operator=(const TreeType&);
    TreeType& operator=(TreeType&&) noexcept;
    T& at(const Key&);
    const T& at(const Key&) const;
    T& operator[](const Key&);

    std::pair< iterator, bool > insert(const std::pair< Key, T >& val);
    std::pair< iterator, bool > insert(std::pair< Key, T >&& val);
    template < class InputIterator >
    void insert(InputIterator first, InputIterator last);
    void insert (std::initializer_list< std::pair< Key, T > > il);

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    template< class... Args >
    std::pair< iterator, bool > emplace(Args&&... args);
    //iterator emplace_hint(const_iterator hint, Args&&... args);


    void swap(AVLTree&) noexcept;
    void clear() noexcept;
    bool empty() const noexcept;
    size_t size() const noexcept;
    iterator find(const Key&);
    const_iterator find(const Key&) const;

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
    NodeType* findNode(const Key&) const;
    void clearSubtree(NodeType*) noexcept;
  };

  template< class Key, class T, class Compare >
  AVLTree< Key, T, Compare >::AVLTree(std::initializer_list< std::pair< Key, T > > list):
    AVLTree()
  {
    for (auto it = list.begin(); it != list.end(); it++)
    {
      insert(*it);
    }
  }

  template< class Key, class T, class Compare >
  template< typename InputIt >
  AVLTree< Key, T, Compare >::AVLTree(InputIt first, InputIt last):
    AVLTree()
  {
    for (auto it = first; it != last; it++)
    {
      insert(*it);
    }
  }

  template< class Key, class T, class Compare >
  void AVLTree< Key, T, Compare >::swap(TreeType& other) noexcept
  {
    std::swap(fakeleaf_, other.fakeleaf_);
    std::swap(root_, other.root_);
    std::swap(cmp_, other.cmp_);
    std::swap(size_, other.size_);
  }

  template< class Key, class T, class Compare >
  AVLTree< Key, T, Compare >::AVLTree(const TreeType& other):
    fakeleaf_(new NodeType()),
    root_(fakeleaf_),
    cmp_(other.cmp_),
    size_(0)
  {
    for (const auto& pair: other) {
      this->insert(pair);
    }
  }

  template< class Key, class T, class Compare >
  AVLTree< Key, T, Compare >::AVLTree(TreeType&& other) noexcept:
    fakeleaf_(std::exchange(other.fakeleaf_, nullptr)),
    root_(std::exchange(other.root_, nullptr)),
    cmp_(std::move(other.cmp_)),
    size_(std::exchange(other.size_, 0))
 {}

  template< class Key, class T, class Compare >
  AVLTree< Key, T, Compare >& AVLTree< Key, T, Compare >::operator=(const TreeType& other)
  {
    if (this != std::addressof(other)) {
      AVLTree temp(other);
      swap(temp);
    }
    return *this;
  }

  template< class Key, class T, class Compare >
  AVLTree< Key, T, Compare >& AVLTree< Key, T, Compare >::operator=(TreeType&& other) noexcept
  {
    if (this != std::addressof(other)) {
      AVLTree temp(std::move(other));
      swap(temp);
    }
    return *this;
  }


  template< class Key, class T, class Compare >
  Iterator< Key, T, Compare > AVLTree< Key, T, Compare >::find(const Key& key)
  {
    NodeType* node = findNode(key);
    if (node != fakeleaf_) {
      return iterator{ node, this };
    } else {
      return end();
    }
  }

  template< class Key, class T, class Compare >
  ConstIterator< Key, T, Compare > AVLTree< Key, T, Compare >::find(const Key& key) const
  {
    NodeType* node = findNode(key);
    if (node != fakeleaf_) {
      return const_iterator{ node, this };
    } else {
      return end();
    }
  }

  template< class Key, class T, class Compare >
  Node< Key, T >* AVLTree< Key, T, Compare >::findNode(const Key& key) const
  {
    NodeType* current = root_;
    while (current != fakeleaf_) {
      if (cmp_(key, current->value.first)) {
        current = current->left;
      } else if (cmp_(current->value.first, key)) {
        current = current->right;
      } else {
        return current;
      }
    }
    return fakeleaf_;
  }

  template< class Key, class T, class Cmp >
  T& AVLTree< Key, T, Cmp >::operator[](const Key& key)
  {
    auto result = insert(std::make_pair(key, T()));
    return result.first->second;
  }

  template< class Key, class T, class Cmp >
  const T& AVLTree< Key, T, Cmp >::at(const Key& key) const
  {
    NodeType* node = findNode(key);
    if (node == fakeleaf_) {
      throw std::out_of_range("Key not found in AVLTree");
    }
    return node->value.second;
  }

  template< class Key, class T, class Cmp >
  T& AVLTree< Key, T, Cmp >::at(const Key& key)
  {
    NodeType* node = findNode(key);
    if (node == fakeleaf_) {
      throw std::out_of_range("Key not found in AVLTree");
    }
    return node->value.second;
  }

  template< class Key, class T, class Cmp >
  void AVLTree< Key, T, Cmp >::insert(std::initializer_list< std::pair< Key, T > > il)
  {
    insert(il.begin(), il.end());
  }

  template< class Key, class T, class Cmp >
  template < class InputIterator >
  void AVLTree< Key, T, Cmp >::insert(InputIterator first, InputIterator last)
  {
    for (; first != last; ++first) {
      insert(*first);
    }
  }

  template< class Key, class T, class Cmp >
  std::pair < Iterator< Key, T, Cmp >, bool > AVLTree< Key, T, Cmp >::insert(std::pair< Key, T >&& value)
  {
    return emplace(std::move(value.first), std::move(value.second));
  }

  template< class Key, class T, class Cmp >
  std::pair < Iterator< Key, T, Cmp >, bool > AVLTree< Key, T, Cmp >::insert(const std::pair< Key, T >& value)
  {
    NodeType* current = root_;
    NodeType* parent = nullptr;
    while (current != fakeleaf_) {
      parent = current;
      if (value.first == current->value.first) {
        return {iterator(current, this), false};
      }
      if (cmp_(value.first, current->value.first)) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    NodeType* newNode = new NodeType(value, fakeleaf_);
    newNode->parent = parent;
    if (parent == nullptr) {
      root_ = newNode;
    } else if (cmp_(value.first, parent->value.first)) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    size_++;
    //balanceTree(newNode);
    return {iterator(newNode, this), true};
}

  template< class Key, class T, class Cmp >
  bool AVLTree< Key, T, Cmp >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< class Key, class T, class Cmp >
  size_t AVLTree< Key, T, Cmp >::size() const noexcept
  {
    return size_;
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
      return end();
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
      return end();
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
    delete fakeleaf_;
  }

  template< class Key, class T, class Cmp >
  AVLTree< Key, T, Cmp >::AVLTree():
    fakeleaf_(new NodeType()),
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
    //balanceTree(newNode);
    size_++;
    return { iterator(newNode, this), true };
  }

  template< class Key, class T, class Cmp >
  void AVLTree< Key, T, Cmp >::updateHeight(NodeType* node) noexcept
  {
    auto current = node;
    if (node != nullptr) {
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
}
#endif
