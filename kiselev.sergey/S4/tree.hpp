#ifndef TREE_HPP
#define TREE_HPP
#include <functional>
#include <cstddef>
#include <ios>
#include <utility>
#include "iterator.hpp"
#include "treeNode.hpp"

namespace kiselev
{
  template< typename Key, typename Value, typename Cmp = std::less< Key > >
  class RBTree
  {
  public:
    using value = std::pair< Key, Value >;
    using Iterator = detail::Iterator< Key, Value, Cmp, false >;
    using ConstIterator = detail::Iterator< Key, Value, Cmp, true >;

    RBTree();

    size_t size() const noexcept;
    bool empty() const noexcept;

    Iterator begin() noexcept;
    ConstIterator cbegin() const noexcept;
    Iterator end() noexcept;
    ConstIterator cend() const noexcept;

    template< typename... Args >
    std::pair< Iterator, bool > emplace(Args&&...);
    template< typename... Args >
    Iterator emplaceHint(ConstIterator, Args&&...);

    void swap(RBTree< Key, Value, Cmp >&) noexcept;
    void clear() noexcept;
    Iterator find(const Key&) noexcept;
    ConstIterator find(const Key&) const noexcept;

    void push(Key, Value);
    Value get(Key);
    void pop(Key);
  private:
    using Node = TreeNode< Key, Value>;

    void rotateLeft(Node* node) noexcept;
    void rotateRight(Node* node) noexcept;
    void fixInsert(Node* node) noexcept;
    void fixDelete(Node* node) noexcept;
    Node* root_;
    Cmp cmp_;
    size_t size_;
  };

  template< typename Key, typename Value, typename Cmp >
  RBTree< Key, Value, Cmp >::RBTree():
    root_(nullptr),
    size_(0)
  {}

  template< typename Key, typename Value, typename Cmp >
  void RBTree< Key, Value, Cmp >::rotateLeft(Node* node) noexcept
  {
    Node* child = node->right;
    node->right = child->left;
    if (child->left)
    {
      child->left->parent = node;
    }
    child->parent = node->parent;
    if (!node->parent)
    {
      root_ = child;
    }
    else if (node == node->parent->left)
    {
      node->parent->left = child;
    }
    else
    {
      node->parent->right = child;
    }
    child->left = node;
    node->parent = child;
  }

  template< typename Key, typename Value, typename Cmp >
  void RBTree< Key, Value, Cmp >::rotateRight(Node* node) noexcept
  {
    Node* child = node->left;
    node->left = child->right;
    if (child->right)
    {
      child->right->parent = node;
    }
    child->parent = node->parent;
    if (!node->parent)
    {
      root_ = child;
    }
    else if (node == node->parent->right)
    {
      node->parent->right = child;
    }
    else
    {
      node->parent->left = child;
    }
    child->right = node;
    node->parent = child;
  }

  template< typename Key, typename Value, typename Cmp >
  void RBTree< Key, Value, Cmp >::fixInsert(Node* node) noexcept
  {
    Node* parent = nullptr;
    Node* grandParent = nullptr;
    while (node != root_ && node->color == Color::RED && node->parent->color == Color::RED)
    {
      parent = node->parent;
      grandParent = parent->parent;
      if (parent == grandParent->left)
      {
        Node* uncle = grandParent->right;
        if (uncle && uncle->color == Color::RED)
        {
          grandParent->color = Color::RED;
          parent->color = Color::BLACK;
          uncle->color = Color::BLACK;
          node = grandParent;
        }
        else
        {
          if (node == parent->right)
          {
            rotateLeft(parent);
            node = parent;
            parent = node->parent;
          }
          rotateRight(grandParent);
          std::swap(parent->color, grandParent->color);
          node = parent;
        }
      }
      else
      {
        Node* uncle = grandParent->left;
        if (uncle && uncle->color == Color::RED)
        {
          grandParent->color = Color::RED;
          parent->color = Color::BLACK;
          uncle->color = Color::BLACK;
          node = grandParent;
        }
        else
        {
          if (node == parent->left)
          {
            rotateRight(parent);
            node = parent;
            parent = node->parent;
          }
          rotateLeft(grandParent);
          std::swap(parent->color, grandParent->color);
          node = parent;
        }
      }
    }
    root_->color = Color::BLACK;
  }

  template< typename Key, typename Value, typename Cmp >
  void RBTree< Key, Value, Cmp >::fixDelete(Node* node) noexcept
  {
    while (node && node->color == Color::BLACK)
    {
      if (node == node->parent->left)
      {
        Node* brother = node->parent->right;
        if (brother->color == Color::RED)
        {
          brother->color = Color::BLACK;
          node->parent->color = Color::RED;
          rotateLeft(node->parent);
          brother = node->parent->right;
        }
        if ((!brother->left || brother->left->color == Color::BLACK) && (!brother->right || brother->right == Color::BLACK))
        {
          brother->color = Color::RED;
          node = node->parent;
        }
        else
        {
          if (!brother->right || brother->right->color == Color::BLACK)
          {
            if (brother->left)
            {
              brother->left->color = Color::BLACK;
            }
            brother->color = Color::RED;
            rotateRight(brother);
            brother = node->parent->right;
          }
          brother->color = node->parent->color;
          node->parent->color = Color::BLACK;
          if (brother->right)
          {
            brother->right->color = Color::BLACK;
          }
          rotateLeft(node->parent);
          node = root_;
        }
      }
      else
      {
        Node* brother = node->parent->left;
        if (brother->color == Color::RED)
        {
          brother->color = Color::BLACK;
          node->parent->color = Color::RED;
          rotateRight(node->parent);
          brother = node->parent->left;
        }
        if ((!brother->left || brother->left->color == Color::BLACK) && (!brother->right || brother->right->color == Color::BLACK))
        {
          brother->color = Color::RED;
          node = node->parent;
        }
        else
        {
          if (!brother->left || brother->left->color == Color::BLACK)
          {
            if (brother->right)
            {
              brother->right->color = Color::BLACK;
            }
            brother->color = Color::RED;
            rotateLeft(brother);
            brother = node->parent->left;
          }
          brother->color = node->parent->color;
          node->parent->color = Color::BLACK;
          if (brother->left)
          {
            brother->left->color = Color::BLACK;
          }
          rotateRight(node->parent);
          node = root_;
        }
      }
    }
    node->color = Color::BLACK;
  }

  template< typename Key, typename Value, typename Cmp >
  size_t RBTree< Key, Value, Cmp >::size() const noexcept
  {
    return size_;
  }

  template< typename Key, typename Value, typename Cmp >
  bool RBTree< Key, Value, Cmp >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< typename Key, typename Value, typename Cmp >
  void RBTree< Key, Value, Cmp >::swap(RBTree< Key, Value, Cmp >& tree) noexcept
  {
    std::swap(root_, tree.root_);
    std::swap(size_, tree.size_);
  }

  template< typename Key, typename Value, typename Cmp >
  typename RBTree< Key, Value, Cmp >::Iterator RBTree< Key, Value, Cmp >::begin() noexcept
  {
    if (empty())
    {
      return end();
    }
    Node* temp = root_;
    while (temp->left)
    {
      temp = temp->left;
    }
    return Iterator(temp);
  }

  template< typename Key, typename Value, typename Cmp >
  typename RBTree< Key, Value, Cmp >::ConstIterator RBTree< Key, Value, Cmp >::cbegin() const noexcept
  {
    if (empty())
    {
      return cend();
    }
    Node* temp = root_;
    while (temp->left)
    {
      temp = temp->left;
    }
    return ConstIterator(temp);
  }

  template< typename Key, typename Value, typename Cmp >
  typename RBTree< Key, Value, Cmp >::Iterator RBTree< Key, Value, Cmp >::end() noexcept
  {
    return Iterator(nullptr);
  }

  template< typename Key, typename Value, typename Cmp >
  typename RBTree< Key, Value, Cmp >::ConstIterator RBTree< Key, Value, Cmp >::cend() const noexcept
  {
    return ConstIterator(nullptr);
  }

  template< typename Key, typename Value, typename Cmp >
  typename RBTree< Key, Value, Cmp >::Iterator RBTree< Key, Value, Cmp >::find(const Key& key) noexcept
  {
    Node* temp = root_;
    while (temp)
    {
      if (cmp_(key, temp->data.first))
      {
        temp = temp->left;
      }
      else if (cmp_(temp->data.first, key))
      {
        temp = temp->right;
      }
      else
      {
        return Iterator(temp);
      }
    }
    return end();
  }

  template< typename Key, typename Value, typename Cmp >
  typename RBTree< Key, Value, Cmp >::ConstIterator RBTree< Key, Value, Cmp >::find(const Key& key) const noexcept
  {
    const Node* temp = root_;
    while (temp)
    {
      if (cmp_(key, temp->data.first))
      {
        temp = temp->left;
      }
      else if (cmp_(temp->data.first, key))
      {
        temp = temp->right;
      }
      else
      {
        return ConstIterator(temp);
      }
    }
    return cend();
  }

  template< typename Key, typename Value, typename Cmp >
  template< typename... Args >
  std::pair< typename RBTree< Key, Value, Cmp >::Iterator, bool > RBTree< Key, Value, Cmp >::emplace(Args &&... args)
  {
    value val(std::forward< Args >(args)...);
    const Key& key = val.first;
    Node* temp = root_;
    Node* parent = nullptr;
    while (temp)
    {
      parent = temp;
      if (cmp_(temp->data.first, key))
      {
        temp = temp->left;
      }
      else if (cmp_(key, temp->data.first))
      {
        temp = temp->right;
      }
      else
      {
        return { Iterator(temp), false };
      }
    }

    Node* newNode = new Node(val, Color::RED, nullptr, nullptr, parent);
    if (!parent)
    {
      root_ = newNode;
    }
    else if (cmp_(parent->data.first))
    {
      parent->right = newNode;
    }
    else
    {
      parent->left = newNode;
    }
    fixInsert(newNode);
    size_++;
    return { Iterator(newNode), true };
  }

  template< typename Key, typename Value, typename Cmp >
  template< typename... Args >
  typename RBTree< Key, Value, Cmp >::Iterator RBTree< Key, Value, Cmp >::emplaceHint(ConstIterator hint, Args &&... args)
  {
    if (hint == end() || empty())
    {
      return emplace(std::forward< Args >(args)...).first;
    }
    value val(std::forward< Args >(args)...);
    const Key& key = val.first;
    Node* pos = hint.node_;
    if (cmp_(key, pos->data.first))
    {
      if (!hint->left)
      {
        Node* newNode = new Node(val, Color::RED, nullptr, nullptr, pos);
        pos->left = newNode;
        fixInsert(newNode);
        ++size_;
        return Iterator(newNode);
      }
    }
    else if (cmp_(pos->data.first, key))
    {
      if (!pos->right)
      {
        Node* newNode = new Node(val, Color::RED, nullptr, nullptr, pos);
        pos->right = newNode;
        fixInsert(newNode);
        ++size_;
        return Iterator(newNode);
      }
    }
    else
    {
      return Iterator(pos);
    }
    return emplace(std::forward< Args >(args)...).first;
  }
}
#endif
