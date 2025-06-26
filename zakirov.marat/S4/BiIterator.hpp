#ifndef BIITERATOR_HPP
#define BIITERATOR_HPP
#include <iterator>
#include <utility>
#include "BiNode.hpp"

namespace zakirov
{
  template< class K, class T >
  class BiTree;

  template< class K, class T >
  class BiIter: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    explicit BiIter() noexcept;

    std::pair< K, T > & operator*() noexcept;
    std::pair< K, T > * operator->() noexcept;
    BiIter< K, T > & operator++() noexcept;
    BiIter< K, T > operator++(int) noexcept;
    BiIter< K, T > & operator--() noexcept;
    BiIter< K, T > operator--(int) noexcept;
    bool operator!=(const BiIter< K, T > & other) const noexcept;
    bool operator==(const BiIter< K, T > & other) const noexcept;

  private:
    friend class BiTree< K, T >;
    explicit BiIter(BiNode< K, T > * node) noexcept;
    BiNode< K, T > * next(BiNode< K, T > * node);
    BiNode< K, T > * prev(BiNode< K, T > * node);
    BiNode< K, T > * to_left(BiNode< K, T > * node);
    BiNode< K, T > * to_right(BiNode< K, T > * node);
    BiNode< K, T > * node_;
  };

  template< class K, class T >
  BiIter< K, T >::BiIter() noexcept:
    node_(nullptr)
  {}

  template< class K, class T >
  BiIter< K, T >::BiIter(BiNode< K, T > * node) noexcept:
    node_(node)
  {}

  template< class K, class T >
  std::pair< K, T > & BiIter< K, T >::operator*() noexcept
  {
    return node_->value;
  }

  template< class K, class T >
  std::pair< K, T > * BiIter< K, T >::operator->() noexcept
  {
    return std::addressof(node_->value_);
  }

  template< class K, class T >
  BiIter< K, T > & BiIter< K, T >::operator++() noexcept
  {
    next(node_);
    return *this;
  }

  template< class K, class T >
  BiIter< K, T > BiIter< K, T >::operator++(int) noexcept
  {
    BiIter< K, T > * start_value = *this;
    next(node_);
    return start_value;
  }

  template< class K, class T >
  BiIter< K, T > & BiIter< K, T >::operator--() noexcept
  {
    prev(node_);
    return *this;
  }

  template< class K, class T >
  BiIter< K, T > BiIter< K, T >::operator--(int) noexcept
  {
    BiIter< K, T > * start_value = *this;
    prev(node_);
    return start_value;
  }

  template< class K, class T >
  bool BiIter< K, T >::operator!=(const BiIter< K, T > & other) const noexcept
  {
    return node_ != other.node_;
  }

  template< class K, class T >
  bool BiIter< K, T >::operator==(const BiIter< K, T > & other) const noexcept
  {
    return node_ != other.node_;
  }

  template< class K, class T >
  class CBiIter: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    explicit CBiIter() noexcept;

    std::pair< K, T > & operator*() const noexcept;
    std::pair< K, T > * operator->() const noexcept;
    CBiIter< K, T > & operator++() noexcept;
    CBiIter< K, T > operator++(int) noexcept;
    CBiIter< K, T > & operator--() noexcept;
    CBiIter< K, T > operator--(int) noexcept;
    bool operator!=(const CBiIter< K, T > &) const noexcept;
    bool operator==(const CBiIter< K, T > &) const noexcept;

  private:
    friend class BiTree< K, T >;
    explicit CBiIter(BiNode< K, T > * node) noexcept;
    BiNode< K, T > * node_;
  };

  template< class K, class T >
  CBiIter< K, T >::CBiIter() noexcept:
    node_(nullptr)
  {}

  template< class K, class T >
  CBiIter< K, T >::CBiIter(BiNode< K, T > * node) noexcept:
    node_(node)
  {}

  template< class K, class T >
  std::pair< K, T > & CBiIter< K, T >::operator*() const noexcept
  {
    return node_->data_;
  }

  template< class K, class T >
  std::pair< K, T > * CBiIter< K, T >::operator->() const noexcept
  {
    return std::addressof(node_->data_);
  }

  template< class K, class T >
  CBiIter< K, T > & CBiIter< K, T >::operator++() noexcept
  {
    next(node_);
    return *this;
  }

  template< class K, class T >
  CBiIter< K, T > CBiIter< K, T >::operator++(int) noexcept
  {
    BiIter< K, T > * start_value = *this;
    next(node_);
    return start_value;
  }

  template< class K, class T >
  CBiIter< K, T > & CBiIter< K, T >::operator--() noexcept
  {
    prev(node_);
    return *this;
  }

  template< class K, class T >
  CBiIter< K, T > CBiIter< K, T >::operator--(int) noexcept
  {
    BiIter< K, T > * start_value = *this;
    prev(node_);
    return start_value;
  }

  template< class K, class T >
  bool CBiIter< K, T >::operator!=(const CBiIter< K, T > & other) const noexcept
  {
    return node_ != other.node_
  }

  template< class K, class T >
  bool CBiIter< K, T >::operator==(const CBiIter< K, T > & other) const noexcept
  {
    return node_ == other.node_
  }

  template< class K, class T >
  BiNode< K, T > * next(BiNode< K, T > * node)
  {
    if (!node)
    {
      return nullptr;
    }

    if (node->right_)
    {
      node = node->right;
      while (node->left)
      {
        node = node->left;
      }

      return node;
    }

    if (!node->parent)
    {
      return nullptr;
    }

    while (node->parent_->left_ != node)
    {
      node = node->parent_;
      if (!node->parent_)
      {
        return nullptr;
      }
    }

    return node->parent_;
  }


  template< class K, class T >
  BiNode< K, T > * prev(BiNode< K, T > * node)
  {
    if (!node)
    {
      return nullptr;
    }

    if (node->left_)
    {
      node = node->left_;
      while (node->right_)
      {
        node = node->right_;
      }

      return node;
    }

    if (!node->parent_)
    {
      return nullptr;
    }

    while (node->parent_->right_ != node)
    {
      node = node->parent_;
      if (!node->parent_)
      {
        return nullptr;
      }
    }

    return node->parent_;
  }
}

#endif
