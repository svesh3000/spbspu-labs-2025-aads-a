#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <iostream>
#include <functional>
#include <cstddef>
#include <iterator>
#include <cassert>

namespace petrov
{
  template< typename K, typename T >
  struct AVLTreeNode
  {
    std::pair< const K, T > data;
    AVLTreeNode< K, T > * left;
    AVLTreeNode< K, T > * right;
    AVLTreeNode< K, T > * parent;
    size_t height;
    void setHeight();
  };

  template< typename K, typename T, typename Cmp = std::less< K > >
  struct ConstAVLTreeIterator: std::iterator< std::bidirectional_iterator_tag, T >
  {
    template< typename A, typename B, typename C >
    friend struct AVLTree;
  public:
    using node_t = AVLTreeNode< K, T >;
    using this_t = ConstAVLTreeIterator< K, T, Cmp >;
    ConstAVLTreeIterator():
      node_(nullptr)
    {}
    ConstAVLTreeIterator(const this_t & rhs) = default;
    ~ConstAVLTreeIterator() = default;
    this_t & operator=(const this_t & rhs) = default;
    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);
    const T & operator*() const;
    const T * operator->() const;
    bool operator==(const this_t & rhs) const;
    bool operator!=(const this_t & rhs) const;
  private:
    const node_t * node_;
    explicit ConstAVLTreeIterator(const node_t * node):
      node_(node)
    {}
  };

  template< typename K, typename T, typename Cmp >
  struct AVLTreeIterator: std::iterator< std::bidirectional_iterator_tag, T >
  {
    template< typename A, typename B, typename C >
    friend struct AVLTree;
  public:
    using node_t = AVLTreeNode< K, T >;
    using this_t = AVLTreeIterator< K, T, Cmp >;
    AVLTreeIterator():
      node_(nullptr)
    {}
    AVLTreeIterator(const this_t & rhs) = default;
    ~AVLTreeIterator() = default;
    this_t & operator=(const this_t & rhs) = default;
    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);
    T & operator*();
    T * operator->();
    bool operator==(const this_t & rhs) const;
    bool operator!=(const this_t & rhs) const;
  private:
    node_t * node_;
    explicit AVLTreeIterator(node_t * node):
      node_(node)
    {}
  };

  template< typename K, typename T, typename Cmp = std::less< K > >
  struct AVLTree
  {
  public:
    using this_t = AVLTree< K, T, Cmp >;
    using node_t = AVLTreeNode< K, T >;
    using const_it_t = ConstAVLTreeIterator< K, T, Cmp >;
    using it_t = AVLTreeIterator< K, T, Cmp >;
    AVLTree():
      root_(nullptr),
      size_(0)
    {}
    AVLTree(const this_t & rhs);
    AVLTree(this_t && rhs);
    ~AVLTree();
    this_t & operator=(const this_t & rhs);
    this_t & operator=(this_t && rhs);
    T & operator[](const K & key);
    const T & operator[](const K & key) const;
    const_it_t cbegin() const;
    const_it_t cend() const;
    it_t begin();
    it_t end();
    bool empty() const noexcept;
    size_t size() const noexcept;
    std::pair< const_it_t, bool > insert(const std::pair< K, T > & val);
    std::pair< const_it_t, bool > insert(std::pair< K, T > && val);
    it_t find(const K & key);
    const_it_t find(const K & key) const;
    T & at(const K & key);
    const T & at(const K & key) const;
    void clear() noexcept;
    void swap(this_t & rhs) noexcept;
  private:
    node_t * root_;
    size_t size_;
    void balance();
    void clearBiTree(node_t * node) noexcept;
  };

  template< typename K, typename T >
  void AVLTreeNode< K, T >::setHeight()
  {
    if (left && right)
    {
      height = std::max(left->height, right->height) + 1;
    }
    else if (!left && !right)
    {
      height = 1;
    }
    else
    {
      if (!left)
      {
        height = right->height + 1;
      }
      else
      {
        height = left->height + 1;
      }
    }
  }

  template< typename K, typename T, typename Cmp >
  typename ConstAVLTreeIterator< K, T, Cmp >::this_t & ConstAVLTreeIterator< K, T, Cmp >::operator++()
  {
    if (!node_->parent || Cmp{}(node_->data.first, node_->parent->data.first))
    {
      if (node_->right)
      {
        node_ = node_->right;
        while (node_->left)
        {
          node_ = node_->left;
        }
      }
      else
      {
        node_ = node_->parent;
      }
    }
    else
    {
      if (node_->right)
      {
        node_ = node_->right;
        while (node_->left)
        {
          node_ = node_->left;
        }
      }
      else
      {
        while (node_->parent && Cmp{}(node_->parent->data.first, node_->data.first))
        {
          node_ = node_->parent;
        }
        node_ = node_->parent;
      }
    }
    return *this;
  }

  template< typename K, typename T, typename Cmp >
  const T & ConstAVLTreeIterator< K, T, Cmp >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data.second;
  }

  template< typename K, typename T, typename Cmp >
  const T * ConstAVLTreeIterator< K, T, Cmp >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data.second);
  }

  template< typename K, typename T, typename Cmp >
  bool ConstAVLTreeIterator< K, T, Cmp >::operator==(const this_t & rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename K, typename T, typename Cmp >
  bool ConstAVLTreeIterator< K, T, Cmp >::operator!=(const this_t & rhs) const
  {
    return !(*this == rhs);
  }

  template< typename K, typename T, typename Cmp >
  typename AVLTreeIterator< K, T, Cmp >::this_t & AVLTreeIterator< K, T, Cmp >::operator++()
  {
    if (!node_->parent || Cmp{}(node_->data.first, node_->parent->data.first))
    {
      if (node_->right)
      {
        node_ = node_->right;
        while (node_->left)
        {
          node_ = node_->left;
        }
      }
      else
      {
        node_ = node_->parent;
      }
    }
    else
    {
      if (node_->right)
      {
        node_ = node_->right;
        while (node_->left)
        {
          node_ = node_->left;
        }
      }
      else
      {
        while (node_->parent && Cmp{}(node_->parent->data.first, node_->data.first))
        {
          node_ = node_->parent;
        }
        node_ = node_->parent;
      }
    }
    return *this;
  }

  template< typename K, typename T, typename Cmp >
  T & AVLTreeIterator< K, T, Cmp >::operator*()
  {
    assert(node_ != nullptr);
    return node_->data.second;
  }

  template< typename K, typename T, typename Cmp >
  T * AVLTreeIterator< K, T, Cmp >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data.second);
  }

  template< typename K, typename T, typename Cmp >
  bool AVLTreeIterator< K, T, Cmp >::operator==(const this_t & rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename K, typename T, typename Cmp >
  bool AVLTreeIterator< K, T, Cmp >::operator!=(const this_t & rhs) const
  {
    return !(*this == rhs);
  }

  template< typename K, typename T, typename Cmp >
  AVLTree< K, T, Cmp >::~AVLTree()
  {
    clear();
  }

  template< typename K, typename T, typename Cmp >
  T & AVLTree< K, T, Cmp >::operator[](const K & key)
  {
    auto temp = root_;
    while (temp)
    {
      if (Cmp{}(key, temp->data.first))
      {
        temp = temp->left;
      }
      else if (Cmp{}(temp->data.first, key))
      {
        temp = temp->right;
      }
      else if (!(Cmp{}(key, temp->data.first) && Cmp{}(temp->data.first, key)))
      {
        break;
      }
    }
    return temp->data.second;
  }

  template< typename K, typename T, typename Cmp >
  const T & AVLTree< K, T, Cmp >::operator[](const K & key) const
  {
    auto temp = root_;
    while (temp)
    {
      if (Cmp{}(key, temp->data.first))
      {
        temp = temp->left;
      }
      else if (Cmp{}(temp->data.first, key))
      {
        temp = temp->right;
      }
      else if (!(Cmp{}(key, temp->data.first) && Cmp{}(temp->data.first, key)))
      {
        break;
      }
    }
    return temp->data.second;
  }

  template< typename K, typename T, typename Cmp >
  typename AVLTree< K, T, Cmp >::const_it_t AVLTree< K, T, Cmp >::cbegin() const
  {
    auto temp = root_;
    while (temp->left)
    {
      temp = temp->left;
    }
    return const_it_t(temp);
  }
  
  template< typename K, typename T, typename Cmp >
  typename AVLTree< K, T, Cmp >::const_it_t AVLTree< K, T, Cmp >::cend() const  
  {
    return const_it_t();
  }

  template< typename K, typename T, typename Cmp >
  typename AVLTree< K, T, Cmp >::it_t AVLTree< K, T, Cmp >::begin()
  {
    auto temp = root_;
    while (temp->left)
    {
      temp = temp->left;
    }
    return it_t(temp);
  }
  
  template< typename K, typename T, typename Cmp >
  typename AVLTree< K, T, Cmp >::it_t AVLTree< K, T, Cmp >::end()  
  {
    return it_t();
  }

  template< typename K, typename T, typename Cmp >
  bool AVLTree< K, T, Cmp >::empty() const noexcept
  {
    if (!size_)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  template< typename K, typename T, typename Cmp >
  size_t AVLTree< K, T, Cmp >::size() const noexcept
  {
    return size_;
  }

  template< typename K, typename T, typename Cmp >
  std::pair< ConstAVLTreeIterator< K, T, Cmp >, bool > AVLTree< K, T, Cmp >::insert(const std::pair< K, T > & val)
  {
    if (empty())
    {
      root_ = new node_t{ val, nullptr, nullptr, nullptr, 1 };
      size_++;
    }
    else
    {
      auto temp = root_;
      while (temp->left || temp->right)
      {
        if (temp->left && Cmp{}(val.first, temp->left->data.first))
        {
          temp = temp->left;
        }
        else if (temp->right && Cmp{}(temp->right->data.first, val.first))
        {
          temp = temp->right;
        }
        else if (!Cmp{}(val.first, temp->data.first) && !Cmp{}(temp->data.first, val.first))
        {
          return std::pair< const_it_t, bool >{ const_it_t(temp), false };
        }
        else
        {
          break;
        }
      }
      if (Cmp{}(val.first, temp->data.first))
      {
        temp->left = new node_t{ val, nullptr, nullptr, temp, 1 };
        temp = temp->left;
      }
      else if (Cmp{}(temp->data.first, val.first))
      {
        temp->right = new node_t{ val, nullptr, nullptr, temp, 1 };
        temp = temp->right;
      }
      else if (!Cmp{}(val.first, temp->data.first) && !Cmp{}(temp->data.first, val.first))
      {
        return std::pair< const_it_t, bool >{ const_it_t(temp), false };
      }
      size_++;
      while (temp->parent)
      {
        temp = temp->parent;
        temp->setHeight();
      }
      /* 
      if (std::abs(root_->left->height - root_->right_height) > 1)
      {
        balancing
      }
      */
      return std::pair< const_it_t, bool >{ const_it_t(temp), true };
    }
    return std::pair< const_it_t, bool >{ const_it_t(root_), true };
  }

  template< typename K, typename T, typename Cmp >
  std::pair< ConstAVLTreeIterator< K, T, Cmp >, bool > AVLTree< K, T, Cmp >::insert(std::pair< K, T > && val)
  {
    if (empty())
    {
      root_ = new node_t{ val, nullptr, nullptr, nullptr, 1 };
      size_++;
    }
    else
    {
      auto temp = root_;
      while (temp->left || temp->right)
      {
        if (temp->left && Cmp{}(val.first, temp->data.first))
        {
          temp = temp->left;
        }
        else if (temp->right && Cmp{}(temp->data.first, val.first))
        {
          temp = temp->right;
        }
        else if (!Cmp{}(val.first, temp->data.first) && !Cmp{}(temp->data.first, val.first))
        {
          return std::pair< const_it_t, bool >{ const_it_t(temp), false };
        }
        else
        {
          break;
        }
      }
      if (Cmp{}(val.first, temp->data.first))
      {
        temp->left = new node_t{ val, nullptr, nullptr, temp, 1 };
        temp = temp->left;
      }
      else if (Cmp{}(temp->data.first, val.first))
      {
        temp->right = new node_t{ val, nullptr, nullptr, temp, 1 };
        temp = temp->right;
      }
      else if (!Cmp{}(val.first, temp->data.first) && !Cmp{}(temp->data.first, val.first))
      {
        return std::pair< const_it_t, bool >{ const_it_t(temp), false };
      }
      size_++;
      while (temp->parent)
      {
        temp = temp->parent;
        temp->setHeight();
      }
      /* 
      if (std::abs(root_->left->height - root_->right_height) > 1)
      {
        balancing
      }
      */
      return std::pair< const_it_t, bool >{ const_it_t(temp), true };
    }
    return std::pair< const_it_t, bool >{ const_it_t(root_), true };
  }

  template< typename K, typename T, typename Cmp >
  typename AVLTree< K, T, Cmp >::it_t AVLTree< K, T, Cmp >::find(const K & key)
  {
    auto temp = root_;
    while (temp)
    {
      if (Cmp{}(key, temp->data.first))
      {
        temp = temp->left;
      }
      else if (Cmp{}(temp->data.first, key))
      {
        temp = temp->right;
      }
      else if (!(Cmp{}(key, temp->data.first), Cmp{}(temp->data.first, key)))
      {
        return it_t(temp);
      }
    }
    return end();
  }

  template< typename K, typename T, typename Cmp >
  typename AVLTree< K, T, Cmp  >::const_it_t AVLTree< K, T, Cmp >::find(const K & key) const
  {
    auto temp = root_;
    while (temp)
    {
      if (Cmp{}(key, temp->data.first))
      {
        temp = temp->left;
      }
      else if (Cmp{}(temp->data.first, key))
      {
        temp = temp->right;
      }
      else if (!(Cmp{}(key, temp->data.first), Cmp{}(temp->data.first, key)))
      {
        return const_it_t(temp);
      }
    }
    return cend();
  }

  template< typename K, typename T, typename Cmp >
  T & AVLTree< K, T, Cmp >::at(const K & key)
  {
    return const_cast< T & >(static_cast< const T & >(this->at(key)));
  }

  template< typename K, typename T, typename Cmp >
  const T & AVLTree< K, T, Cmp >::at(const K & key) const
  {
    auto temp = root_;
    while (temp)
    {
      if (Cmp{}(key, temp->data.first))
      {
        temp = temp->left;
      }
      else if (Cmp{}(temp->data.first, key))
      {
        temp = temp->right;
      }
      else if (!(Cmp{}(key, temp->data.first), Cmp{}(temp->data.first, key)))
      {
        break;
      }
    }
    if (temp)
    {
      return temp->data->second;
    }
    else
    {
      throw std::out_of_range();
    }
  }

  template< typename K, typename T, typename Cmp >
  void AVLTree< K, T, Cmp >::clear() noexcept
  {
    clearBiTree(root_);
    root_ = nullptr;
  }

  template< typename K, typename T, typename Cmp >
  void AVLTree< K, T, Cmp >::clearBiTree(node_t * root) noexcept
  {
    if (root)
    {
      clearBiTree(root->left);
      clearBiTree(root->right);
      delete root;
      root = nullptr;
      size_--;
    }
  }
}

#endif