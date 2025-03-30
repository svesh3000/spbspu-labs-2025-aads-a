#ifndef TREE_HPP
#define TREE_HPP
#include <functional>
#include "node.hpp"
#include "iterator.hpp"

namespace demehin
{
  template< typename Key, typename T, typename Cmp = std::less< Key > >
  class Tree
  {
  public:
    using Iter = TreeIterator< Key, T, Cmp >;
    using DataPair = std::pair< Key, T >;
    Tree();



    ~Tree();

    std::pair< Iter, bool > insert(const DataPair&);

    T& at(const Key&);
    const T& at(const Key&) const;

    Iter find(const Key& key) const noexcept;

    Iter begin() const noexcept;
    Iter end() const noexcept;

    size_t size() const noexcept;
    bool empty() const noexcept;
    void clear() noexcept;

  private:
    using Node = demehin::TreeNode< Key, T >;

    Node* fakeRoot_;
    Node* root_;
    Cmp cmp_;
    size_t size_;

    int height(Node*) const noexcept;
    Node* rotateRight(Node*) noexcept;
    Node* rotateLeft(Node*) noexcept;
    Node* balance(Node*) noexcept;
    void balanceUpper(Node*) noexcept;
    int getBalanceFactor(Node*) const noexcept;
    void updateHeight(Node*) noexcept;
  };

  template< typename Key, typename T, typename Cmp >
  Tree< Key, T, Cmp >::Tree():
    fakeRoot_(reinterpret_cast< Node* >(new char[sizeof(Node)])),
    root_(nullptr),
    cmp_(Cmp()),
    size_(0)
  {
    fakeRoot_->left = fakeRoot_->right = fakeRoot_;
    root_ = fakeRoot_;
  }

  template< typename Key, typename T, typename Cmp >
  Tree< Key, T, Cmp >::~Tree()
  {
    delete[] reinterpret_cast< char* >(fakeRoot_);
  }

  template< typename Key, typename T, typename Cmp >
  std::pair< TreeIterator< Key, T, Cmp >, bool > Tree< Key, T, Cmp >::insert(const DataPair& value)
  {
    Node* newNode = new Node(value);
    if (root_ == fakeRoot_)
    {
      root_ = newNode;
      root_->parent = fakeRoot_;
      fakeRoot_->right = root_;
      size_++;
      return { Iter(root_), true };
    }
    Node* current = root_;
    Node* parent = fakeRoot_;
    bool isLeft = false;
    while (current != fakeRoot_ && current != nullptr)
    {
      parent = current;
      if (cmp_(value.first, current->data.first))
      {
        current = current->left;
        isLeft = true;
      }
      else if (cmp_(current->data.first, value.first))
      {
        current = current->right;
        isLeft = false;
      }
      else
      {
        delete newNode;
        return { Iter(current), false };
      }

    }

    newNode->parent = parent;
    if (isLeft)
    {
      parent->left = newNode;
    }
    else
    {
      parent->right = newNode;
    }

    balanceUpper(newNode);
    size_++;
    return { Iter(newNode), true };
  }

  template< typename Key, typename T, typename Cmp >
  int Tree< Key, T, Cmp >::height(Node* node) const noexcept
  {
    return (node == fakeRoot_ || node == nullptr) ? -1 : node->height;
  }

  template< typename Key, typename T, typename Cmp >
  void Tree< Key, T, Cmp >::updateHeight(Node* node) noexcept
  {
    if (node != fakeRoot_ && node != nullptr)
    {
      node->height = 1 + std::max(height(node->left), height(node->right));
    }
  }

  template< typename Key, typename T, typename Cmp >
  int Tree< Key, T, Cmp >::getBalanceFactor(Node* node) const noexcept
  {
    if (node == fakeRoot_ || node == nullptr)
    {
      return 0;
    }
    return height(node->left) - height(node->right);
  }

  template< typename Key, typename T, typename Cmp >
  typename Tree< Key, T, Cmp >::Node* Tree< Key, T, Cmp >::rotateRight(Node* node) noexcept
  {
    Node* lt = node->left;
    node->left = lt->right;
    if (lt->right != nullptr)
    {
      lt->right->parent = node;
    }

    lt->right = node;
    lt->parent = node->parent;
    node->parent = lt;

    updateHeight(node);
    updateHeight(lt);

    return lt;
  }

  template< typename Key, typename T, typename Cmp >
  typename Tree< Key, T, Cmp >::Node* Tree< Key, T, Cmp >::rotateLeft(Node* node) noexcept
  {
    Node* rt = node->right;
    node->right = rt->left;
    if (rt->left != nullptr)
    {
      rt->left->parent = node;
    }

    rt->left = node;
    rt->parent = node->parent;
    node->parent = rt;

    updateHeight(node);
    updateHeight(rt);

    return rt;
  }

  template< typename Key, typename T, typename Cmp >
  typename Tree< Key, T, Cmp >::Node* Tree< Key, T, Cmp >::balance(Node* node) noexcept
  {
    updateHeight(node);
    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1)
    {
      if (getBalanceFactor(node->left) < 0)
      {
        node->left = rotateLeft(node->left);
      }
      return rotateRight(node);
    }

    if (balanceFactor < -1)
    {
      if (getBalanceFactor(node->right) > 0)
      {
        node->right = rotateRight(node->right);
      }
      return rotateLeft(node);
    }

    return node;
  }

  template< typename Key, typename T, typename Cmp >
  void Tree< Key, T, Cmp >::balanceUpper(Node* node) noexcept
  {
    while (node != fakeRoot_)
    {
      node = balance(node);
      node = node->parent;
    }
  }

  template< typename Key, typename T, typename Cmp >
  typename Tree< Key, T, Cmp >::Iter Tree< Key, T, Cmp >::begin() const noexcept
  {
    return Iter(root_);
  }

  template< typename Key, typename T, typename Cmp >
  typename Tree< Key, T, Cmp >::Iter Tree< Key, T, Cmp >::end() const noexcept
  {
    return Iter(fakeRoot_);
  }

  template< typename Key, typename T, typename Cmp >
  T& Tree< Key, T, Cmp >::at(const Key& key)
  {
    auto searched = find(key);
    if (searched != end())
    {
      return (*searched).second;
    }
    throw std::out_of_range("undefined key");
  }

  template< typename Key, typename T, typename Cmp >
  typename Tree< Key, T, Cmp >::Iter Tree< Key, T, Cmp >::find(const Key& key) const noexcept
  {
    for (auto it = begin(); it != end(); it++)
    {
      if ((*it).first == key)
      {
        return it;
      }
    }
    return end();
  }

}


#endif
