#ifndef TREE_HPP
#define TREE_HPP

#include <exception>
#include "constIterator.hpp"
#include "iterator.hpp"

namespace mozhegova
{
  template< typename Key, typename T, typename Cmp >
  class BiTree
  {
  public:
    using iter = TreeConstIterator< Key, T, Cmp >;
    using cIter = TreeIterator< Key, T, Cmp >;

    BiTree();
    BiTree(const BiTree< Key, T, Cmp > &);
    BiTree(BiTree< Key, T, Cmp > &&);
    ~BiTree();

    T & operator[](const Key &);

    cIter cbegin() const noexcept;
    cIter cend() const noexcept;
    iter begin() noexcept;
    iter end() noexcept;

    size_t size() const noexcept;
    bool empty() const noexcept;

    T & at(const Key &);
    const T & at(const Key &) const;

    void clear() noexcept;
    void swap(BiTree< Key, T, Cmp > &) noexcept;

    iter find(const Key &);
    cIter find(const Key &) const;
  private:
    detail::TreeNode< Key, T > * root_;
    size_t size_;
    Cmp cmp_;
    void clearTree(detail::TreeNode< Key, T > *);
  };

  template< typename Key, typename T, typename Cmp >
  BiTree< Key, T, Cmp >::BiTree():
    root_(nullptr),
    size_(0),
    cmp_(Cmp())
  {}

  template< typename Key, typename T, typename Cmp >
  BiTree< Key, T, Cmp >::BiTree(const BiTree< Key, T, Cmp > & other):
    BiTree(),
    cmp_(other.cmp_)
  {
    for (auto it = other.cbegin(); it != other.cend; ++it)
    {
      insert(*it);
    }
  }

  template< typename Key, typename T, typename Cmp >
  BiTree< Key, T, Cmp >::BiTree(BiTree< Key, T, Cmp > && other):
    root_(other.root_),
    size_(other.size_),
    cmp_(other.cmp_)
  {
    other.root_ = nullptr;
    size_ = 0;
  }

  template< typename Key, typename T, typename Cmp >
  BiTree< Key, T, Cmp >::~BiTree()
  {
    clear();
  }

  template< typename Key, typename T, typename Cmp >
  T & BiTree< Key, T, Cmp >::operator[](const Key & key)
  {
    auto it = find(key);
    if (it == end())
    {
      insert(std::make_pair(key, T()));
      it = find(key);
    }
    return it->second;
  }

  template< typename Key, typename T, typename Cmp >
  T & BiTree< Key, T, Cmp >::at(const Key & key)
  {
    auto it = find(key);
    if (it == end())
    {
      throw std::out_of_memory("<INVALID COMMAND>");
    }
    return it->second;
  }

  template< typename Key, typename T, typename Cmp >
  const T & BiTree< Key, T, Cmp >::at(const Key & key) const
  {
    auto it = find(key);
    if (it == end())
    {
      throw std::out_of_memory("<INVALID COMMAND>");
    }
    return it->second;
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
  typename BiTree< Key, T, Cmp >::cIter BiTree< Key, T, Cmp >::cbegin() const noexcept
  {
    detail::TreeNode< Key, T > * temp = root_;
    while (temp->left)
    {
      temp = temp->left;
    }
    return cIter(temp);
  }

  template< typename Key, typename T, typename Cmp >
  typename BiTree< Key, T, Cmp >::cIter BiTree< Key, T, Cmp >::cend() const noexcept
  {
    detail::TreeNode< Key, T > * temp = root_;
    while (temp->right)
    {
      temp = temp->right;
    }
    return cIter(temp->right);
  }

  template< typename Key, typename T, typename Cmp >
  typename BiTree< Key, T, Cmp >::iter BiTree< Key, T, Cmp >::begin() noexcept
  {
    detail::TreeNode< Key, T > * temp = root_;
    while (temp->left)
    {
      temp = temp->left;
    }
    return iter(temp);
  }

  template< typename Key, typename T, typename Cmp >
  typename BiTree< Key, T, Cmp >::iter BiTree< Key, T, Cmp >::end() noexcept
  {
    detail::TreeNode< Key, T > * temp = root_;
    while (temp->right)
    {
      temp = temp->right;
    }
    return iter(temp->right);
  }

  template< typename Key, typename T, typename Cmp >
  void BiTree< Key, T, Cmp >::clear() noexcept
  {
    if (!root_)
    {
      clearTree(root_);
    }
  }

  template< typename Key, typename T, typename Cmp >
  void BiTree< Key, T, Cmp >::clearTree(detail::TreeNode< Key, T > * root)
  {
    if (!root)
    {
      clearTree(root->left);
      clearTree(root->right);
      delete root;
    }
  }

  template< typename Key, typename T, typename Cmp >
  void BiTree< Key, T, Cmp >::swap(BiTree< Key, T, Cmp > & rhs) noexcept
  {
    std::swap(root_, rhs.root_);
    std::swap(size_, rhs.size_);
    std::swap(cmp_, rhs.cmp_);
  }

  template< typename Key, typename T, typename Cmp >
  typename BiTree< Key, T, Cmp >::iter BiTree< Key, T, Cmp >::find(const Key & key)
  {
    detail::TreeNode< Key, T > * temp = root_;
    while (!temp && temp->data.first != key)
    {
      if (cmp_(temp->data.first, key))
      {
        temp = temp->right;
      }
      else if (!cmp_(temp->data.first, key))
      {
        temp = temp->left;
      }
      else
      {
        return iter(temp);
      }
      return end();
    }
  }

  template< typename Key, typename T, typename Cmp >
  typename BiTree< Key, T, Cmp >::cIter BiTree< Key, T, Cmp >::find(const Key & key) const
  {
    detail::TreeNode< Key, T > * temp = root_;
    while (!temp && temp->data.first != key)
    {
      if (cmp_(temp->data.first, key))
      {
        temp = temp->right;
      }
      else if (!cmp_(temp->data.first, key))
      {
        temp = temp->left;
      }
      else
      {
        return cIter(temp);
      }
      return cend();
    }
  }
}

#endif
