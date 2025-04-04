#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>
#include <endian.h>
#include <sched.h>
#include "tree.hpp"
#include "treeNode.hpp"

namespace kiselev
{
  template< typename Key, typename Value, typename Cmp >
  class BinarySearchTree;

  namespace detail
  {
    template< typename Key, typename Value, typename Cmp, bool IsConst >
    class Iterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
    {
    public:
      using value = std::pair< Key, Value >;
      using reference = std::conditional< IsConst, const value&, value&>;
      using pointer = std::conditional< IsConst, const value*, value*>;
      using iterator = Iterator< Key, Value, Cmp, IsConst >;

      Iterator();
      template < bool OtherIsConst, std::enable_if< IsConst && !OtherIsConst, int > = 0 >
      Iterator(const iterator&) noexcept;
      template< bool OtherIsConst, std::enable_if< IsConst && !OtherIsConst, int > = 0 >
      iterator& operator=(const iterator&) noexcept;

      iterator& operator++() noexcept;
      iterator& operator++(int) noexcept;

      iterator& operator--() noexcept;
      iterator& operator--(int) noexcept;

      reference operator*() const noexcept;
      pointer operator->() const noexcept;

      bool operator==(const iterator&) const noexcept;
      bool operator!=(const iterator&) const noexcept;
    private:
      TreeNode< Key, Value>* node_;
      explicit Iterator(TreeNode< Key, Value >*);
      friend class Iterator< Key, Value, Cmp, !IsConst >;
      friend class BinarySearchTree< Key, Value >;
    };

    template< typename Key, typename Value, typename Cmp, bool IsConst >
    Iterator< Key, Value, Cmp, IsConst >::Iterator():
      node_(nullptr)
    {}

    template< typename Key, typename Value, typename Cmp, bool IsConst >
    template< bool OtherIsConst, std::enable_if< IsConst && !OtherIsConst, int > >
    Iterator< Key, Value, Cmp, IsConst >::Iterator(const iterator& other) noexcept:
      node_(other.node_)
    {}

    template< typename Key, typename Value, typename Cmp, bool IsConst >
    Iterator< Key, Value, Cmp, IsConst >::Iterator(TreeNode< Key, Value >* node):
      node_(node)
    {}

    template< typename Key, typename Value, typename Cmp, bool IsConst >
    template< bool OtherIsConst, std::enable_if< IsConst && !OtherIsConst, int > >
    Iterator< Key, Value, Cmp, IsConst >& Iterator< Key, Value, Cmp, IsConst >::operator=(const iterator& other) noexcept
    {
      node_ = other.node_;
      return *this;
    }

    template< typename Key, typename Value, typename Cmp, bool IsConst >
    Iterator< Key, Value, Cmp, IsConst >& Iterator< Key, Value, Cmp, IsConst >::operator++() noexcept
    {
      assert(node_ != nullptr);
      TreeNode< Key, Value >* temp = node_;
      if (temp->right)
      {
        temp = temp->right;
        while (temp->left)
        {
          temp = temp->left;
        }
        return iterator(temp);
      }
      while (temp->parent && temp == temp->parent->right)
      {
        temp = temp->parent;
      }
      return iterator(temp->parent);
    }

    template< typename Key, typename Value, typename Cmp, bool IsConst >
    Iterator< Key, Value, Cmp, IsConst >& Iterator< Key, Value, Cmp, IsConst >::operator++(int) noexcept
    {
      assert(node_ != nullptr);
      iterator result(*this);
      ++(*this);
      return result;
    }

    template< typename Key, typename Value, typename Cmp, bool IsConst >
    Iterator< Key, Value, Cmp, IsConst >& Iterator< Key, Value, Cmp, IsConst >::operator--() noexcept
    {
      assert(node_ != nullptr);
      TreeNode< Key, Value>* temp = node_;
      if (temp->left)
      {
        temp = temp->left;
        while (temp->right)
        {
          temp = temp->right;
        }
        return iterator(temp);
      }
      while (temp->parent && temp == temp->parent->left)
      {
        temp = temp->parent;
      }
      return iterator(temp->parent);
    }

    template< typename Key, typename Value, typename Cmp, bool IsConst >
    Iterator< Key, Value, Cmp, IsConst >& Iterator< Key, Value, Cmp, IsConst >::operator--(int) noexcept
    {
      assert(node_ != nullptr);
      iterator result(*this);
      --(*this);
      return result;
    }

    template< typename Key, typename Value, typename Cmp, bool IsConst >
    typename Iterator< Key, Value, Cmp, IsConst >::reference Iterator< Key, Value, Cmp, IsConst >::operator*() const noexcept
    {
      assert(node_ != nullptr);
      return node_->value;
    }

    template< typename Key, typename Value, typename Cmp, bool IsConst >
    typename Iterator< Key, Value, Cmp, IsConst >::pointer Iterator< Key, Value, Cmp, IsConst >::operator->() const noexcept
    {
      assert(node_ != nullptr);
      return std::addressof(node_->value);
    }

    template< typename Key, typename Value, typename Cmp, bool IsConst >
    bool Iterator< Key, Value, Cmp, IsConst >::operator==(const iterator& other) const noexcept
    {
      return node_ == other.node_;
    }

    template< typename Key, typename Value, typename Cmp, bool IsConst >
    bool Iterator< Key, Value, Cmp, IsConst >::operator!=(const iterator& other) const noexcept
    {
      return !(*this == other);
    }
  }
}
#endif
