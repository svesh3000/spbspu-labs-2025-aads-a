#ifndef TREE_HPP
#define TREE_HPP

#include "iterator.hpp"

namespace maslov
{
  template< typename Key, typename T, typename Cmp >
  struct BiTree
  {
    using cIterator = TreeConstIterator< Key, T, Cmp >;
    using iterator = TreeIterator< Key, T, Cmp >;

    BiTree();
    BiTree(const BiTree< Key, T, Cmp > & rhs);
    BiTree(BiTree< Key, T, Cmp > && rhs);
    ~BiTree();

    BiTree< Key, T, Cmp > & operator=(const BiTree< Key, T, Cmp > & rhs);
    BiTree< Key, T, Cmp > & operator=(BiTree< Key, T, Cmp > && rhs);

    void push(const Key & key, const T & value);
    T get(const Key & key);
    T pop(const Key & key);

    iterator begin() noexcept;
    cIterator cbegin() const noexcept;
    iterator end() noexcept;
    cIterator cend() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    void clear();
    void swap(BiTree< Key, T, Cmp > & rhs) noexcept;
   private:
    BiTreeNode< Key, T > * fakeRoot_;
    BiTreeNode< Key, T > * fakeLeaf_;
    size_t size_;
    Cmp cmp_;
    void clearTree(BiTreeNode< Key, T > * root);
    void balance(BiTreeNode< Key, T > * node);
    int getBalance(BiTreeNode< Key, T > * node);
    int height(BiTreeNode< Key, T > * node);
    BiTreeNode< Key, T > * rotateLeft(BiTreeNode< Key, T > * root);
    BiTreeNode< Key, T > * rotateRight(BiTreeNode< Key, T > * root);
  };

  template< typename Key, typename T, typename Cmp >
  BiTree< Key, T, Cmp >::BiTree():
    fakeRoot_(new BiTreeNode< Key, T >{std::pair< Key, T >(), nullptr, nullptr, nullptr}),
    fakeLeaf_(new BiTreeNode< Key, T >{std::pair< Key, T >(), nullptr, nullptr, nullptr}),
    size_(0),
    cmp_(Cmp())
  {
    fakeLeaf_->parent = fakeRoot_;
    fakeRoot_->left = fakeLeaf_;
    fakeRoot_->right = fakeLeaf_;
  }

  template< typename Key, typename T, typename Cmp >
  BiTree< Key, T, Cmp >::~BiTree()
  {
    clear();
    delete fakeRoot_;
    delete fakeLeaf_;
  }

  template< typename Key, typename T, typename Cmp >
  BiTree< Key, T, Cmp >::BiTree(const BiTree< Key, T, Cmp > & rhs):
    BiTree()
  {
    for (auto it = rhs.cbegin(); it != rhs.cend(); ++it)
    {
      push(it->first, it->second);
    }
  }

  template< typename Key, typename T, typename Cmp >
  BiTree< Key, T, Cmp >::BiTree(BiTree< Key, T, Cmp > && rhs):
    fakeRoot_(rhs.fakeRoot_),
    fakeLeaf_(rhs.fakeLeaf_),
    size_(rhs.size_),
    cmp_(std::move(rhs.cmp_))
  {
    rhs.fakeRoot_ = new BiTreeNode< Key, T >{std::pair< Key, T >(), nullptr, nullptr, nullptr};
    rhs.fakeLeaf_ = new BiTreeNode< Key, T >{std::pair< Key, T >(), nullptr, nullptr, rhs.fakeRoot_};
    rhs.fakeRoot_->left = rhs.fakeLeaf_;
    rhs.fakeRoot_->right = rhs.fakeLeaf_;
    rhs.size_ = 0;
  }
  template< typename Key, typename T, typename Cmp >
  BiTree< Key, T, Cmp > & BiTree< Key, T, Cmp >::operator=(const BiTree< Key, T, Cmp > & rhs)
  {
    if (this != std::addressof(rhs))
    {
      BiTree temp(rhs);
      swap(temp);
    }
    return *this;
  }
  template< typename Key, typename T, typename Cmp >
  BiTree< Key, T, Cmp > & BiTree< Key, T, Cmp >::operator=(BiTree< Key, T, Cmp > && rhs)
  {
    if (this != &rhs)
    {
      clear();
      delete fakeRoot_;
      delete fakeLeaf_;
      fakeRoot_ = rhs.fakeRoot_;
      fakeLeaf_ = rhs.fakeLeaf_;
      size_ = rhs.size_;
      cmp_ = std::move(rhs.cmp_);
      rhs.fakeRoot_ = new BiTreeNode< Key, T >{std::pair< Key, T >(), nullptr, nullptr, nullptr};
      rhs.fakeLeaf_ = new BiTreeNode< Key, T >{std::pair< Key, T >(), nullptr, nullptr, rhs.fakeRoot_ };
      rhs.fakeRoot_->left = rhs.fakeLeaf_;
      rhs.fakeRoot_->right = rhs.fakeLeaf_;
      rhs.size_ = 0;
    }
    return *this;
  }

  template< typename Key, typename T, typename Cmp >
  void BiTree< Key, T, Cmp >::clear()
  {
    clearTree(fakeRoot_->left);
    clearTree(fakeRoot_->right);
    fakeRoot_->left = fakeLeaf_;
    fakeRoot_->right = fakeLeaf_;
    size_ = 0;
  }

  template< typename Key, typename T, typename Cmp >
  void BiTree< Key, T, Cmp >::clearTree(BiTreeNode< Key, T > * root)
  {
    if (root == fakeLeaf_)
    {
      return;
    }
    clearTree(root->left);
    clearTree(root->right);
    delete root;
  }

  template< typename Key, typename T, typename Cmp >
  size_t BiTree< Key, T, Cmp >::size() const noexcept
  {
    return size_;
  }

  template< typename Key, typename T, typename Cmp >
  bool BiTree< Key, T, Cmp >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< typename Key, typename T, typename Cmp >
  void BiTree< Key, T, Cmp >::swap(BiTree< Key, T, Cmp > & rhs) noexcept
  {
    std::swap(fakeRoot_, rhs.fakeRoot_);
    std::swap(fakeLeaf_, rhs.fakeLeaf_);
    std::swap(size_, rhs.size_);
  }

  template< typename Key, typename T, typename Cmp >
  void BiTree< Key, T, Cmp >::push(const Key & key, const T & value)
  {
    BiTreeNode< Key, T > * current;
    if (empty())
    {
      BiTreeNode< Key, T > * newNode = new BiTreeNode< Key, T >{std::pair< Key, T >(key, value), fakeLeaf_, fakeLeaf_, fakeRoot_};
      fakeRoot_->left = newNode;
      size_++;
      return;
    }
    else
    {
      current = fakeRoot_->left;
    }
    BiTreeNode< Key, T > * parent = nullptr;
    while (current != fakeLeaf_)
    {
      parent = current;
      if (cmp_(key, current->data.first))
      {
        current = current->left;
      }
      else if (cmp_(current->data.first, key))
      {
        current = current->right;
      }
      else
      {
        current->data.second = value;
        return;
      }
    }
    BiTreeNode< Key, T > * newNode = new BiTreeNode< Key, T >{std::pair< Key, T >(key, value), fakeLeaf_, fakeLeaf_, parent};
    if (cmp_(key, parent->data.first))
    {
      parent->left = newNode;
    }
    else
    {
      parent->right = newNode;
    }
    size_++;
    balance(newNode);
  }

  template< typename Key, typename T, typename Cmp >
  T BiTree< Key, T, Cmp >::get(const Key & key)
  {
    BiTreeNode< Key, T > * current = fakeRoot_->left;
    while (current != fakeLeaf_)
    {
      if (cmp_(key, current->data.first))
      {
        current = current->left;
      }
      else if (cmp_(current->data.first, key))
      {
        current = current->right;
      }
      else
      {
        return current->data.second;
      }
    }
    throw std::out_of_range("ERROR: key not found\n");
  }

  template< typename Key, typename T, typename Cmp >
  T BiTree< Key, T, Cmp >::pop(const Key & key)
  {
    BiTreeNode< Key, T > * current = fakeRoot_->left;
    //поиск. возможное дублирование
    while (current != fakeLeaf_)
    {
      if (cmp_(key, current->data.first))
      {
        current = current->left;
      }
      else if (cmp_(current->data.first, key))
      {
        current = current->right;
      }
      else
      {
        break;
      }
    }
    if (current == fakeLeaf_)
    {
      throw std::out_of_range("ERROR: key not found\n");
    }
    T value = current->data.second;
    BiTreeNode< Key, T > * parent = current->parent;
    if (current->left == fakeLeaf_ || current->right == fakeLeaf_)
    {
      BiTreeNode< Key, T > * child = nullptr;
      if (current->left != fakeLeaf_)
      {
        child = current->left;
      }
      else
      {
        child = current->right;
      }
      if (parent->left == current)
      {
        parent->left = child;
      }
      else
      {
        parent->right = child;
      }
      if (child != fakeLeaf_)
      {
        child->parent = parent;
      }
      balance(parent);
      delete current;
    }
    else
    {
      BiTreeNode< Key, T > * minNode = current->right;
      while (minNode->left != fakeLeaf_)
      {
        minNode = minNode->left;
      }
      current->data = minNode->data;
      if (minNode->parent->left == minNode)
      {
        minNode->parent->left = minNode->right;
      }
      else
      {
        minNode->parent->right = minNode->right;
      }
      if (minNode->right != fakeLeaf_)
      {
        minNode->right->parent = minNode->parent;
      }
      balance(current);
      delete minNode;
    }
    size_--;
    return value;
  }

  template< typename Key, typename T, typename Cmp >
  void BiTree< Key, T, Cmp >::balance(BiTreeNode< Key, T > * node)
  {
    BiTreeNode< Key, T > * current = node;
    while (current != fakeRoot_)
    {
      int balanceDifference = getBalance(current);
      if (balanceDifference > 1)
      {
        if (getBalance(current->left) >= 0)
        {
          current = rotateRight(current);
        }
        else
        {
          current->left = rotateLeft(current->left);
          current = rotateRight(current);
        }
      }
      else if (balanceDifference < -1)
      {
        if (getBalance(current->right) >= 0)
        {
          current = rotateLeft(current);
        }
        else
        {
          current->right = rotateRight(current->right);
          current = rotateLeft(current);
        }
      }
      current = current->parent;
    }
  }

  template< typename Key, typename T, typename Cmp >
  int BiTree< Key, T, Cmp >::getBalance(BiTreeNode< Key, T > * node)
  {
    if (node == fakeLeaf_)
    {
      return 0;
    }
    return height(node->left) - height(node->right);
  }

  template< typename Key, typename T, typename Cmp >
  int BiTree< Key, T, Cmp >::height(BiTreeNode< Key, T > * node)
  {
    if (node == fakeLeaf_)
    {
      return 0;
    }
    return 1 + std::max(height(node->left), height(node->right));
  }

  template< typename Key, typename T, typename Cmp >
  BiTreeNode< Key, T > * BiTree< Key, T, Cmp >::rotateRight(BiTreeNode< Key, T > * root)
  {
    if (!root || root->left == fakeLeaf_)
    {
      return root;
    }
    BiTreeNode< Key, T > * rotateNode = root->left;
    BiTreeNode< Key, T > * rightRotateNode = rotateNode->right;
    root->left = rightRotateNode;
    if (rightRotateNode != fakeLeaf_)
    {
      rightRotateNode->parent = root;
    }
    rotateNode->right = root;
    rotateNode->parent = root->parent;
    root->parent = rotateNode;
    if (rotateNode->parent == fakeRoot_)
    {
      fakeRoot_->left = rotateNode;
    }
    else if (rotateNode->parent != nullptr)
    {
      if (rotateNode->parent->left == root)
      {
        rotateNode->parent->left = rotateNode;
      }
      else
      {
        rotateNode->parent->right = rotateNode;
      }
    }
    return rotateNode;
  }

  template< typename Key, typename T, typename Cmp >
  BiTreeNode< Key, T > * BiTree< Key, T, Cmp >::rotateLeft(BiTreeNode< Key, T > * root)
  {
    if (!root || root->right == fakeLeaf_)
    {
      return root;
    }
    BiTreeNode< Key, T > * rotateNode = root->right;
    BiTreeNode< Key, T > * leftRotateNode = rotateNode->left;
    root->right = leftRotateNode;
    if (leftRotateNode != fakeLeaf_)
    {
      leftRotateNode->parent = root;
    }
    rotateNode->left = root;
    rotateNode->parent = root->parent;
    root->parent = rotateNode;
    if (rotateNode->parent == fakeRoot_)
    {
      fakeRoot_->left = rotateNode;
    }
    else if (rotateNode->parent != nullptr)
    {
      if (rotateNode->parent->left == root)
      {
        rotateNode->parent->left = rotateNode;
      }
      else
      {
        rotateNode->parent->right = rotateNode;
      }
    }
    return rotateNode;
  }

  template< typename Key, typename T, typename Cmp >
  typename BiTree< Key, T, Cmp >::iterator BiTree< Key, T, Cmp >::begin() noexcept
  {
    if (empty())
    {
      return end();
    }
    BiTreeNode< Key, T > * current = fakeRoot_->left;
    while (current->left != fakeLeaf_)
    {
      current = current->left;
    }
    return iterator(current, fakeLeaf_);
  }

  template< typename Key, typename T, typename Cmp >
  typename BiTree< Key, T, Cmp >::iterator BiTree< Key, T, Cmp >::end() noexcept
  {
    return iterator(fakeLeaf_, fakeLeaf_);
  }

  template< typename Key, typename T, typename Cmp >
  typename BiTree< Key, T, Cmp >::cIterator BiTree< Key, T, Cmp >::cbegin() const noexcept
  {
    if (empty())
    {
      return cend();
    }
    BiTreeNode< Key, T >* current = fakeRoot_->left;
    while (current->left != fakeLeaf_)
    {
      current = current->left;
    }
    return cIterator(current, fakeLeaf_);
  }

  template< typename Key, typename T, typename Cmp >
  typename BiTree< Key, T, Cmp >::cIterator BiTree< Key, T, Cmp >::cend() const noexcept
  {
    return cIterator(fakeLeaf_, fakeLeaf_);
  }
}

#endif
