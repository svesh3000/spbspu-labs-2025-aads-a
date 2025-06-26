#ifndef BIITERATOR_HPP
#define BIITERATOR_HPP
#include <iterator>
#include <utility>
#include "BiNode.hpp"

namespace detail
{
  template< class K, class T >
  void next(BiNode< K, T > * node)
  {
    if (!node)
    {
      node = nullptr;
      return;
    }

    if (node->right_)
    {
      node = node->right;
      while (node->left)
      {
        node = node->left;
      }

      return;
    }

    if (!node->parent)
    {
      node = nullptr;
      return;
    }

    while (node->parent_->left_ != node)
    {
      node = node->parent_;
      if (!node->parent_)
      {
        node = nullptr;
        return;
      }
    }
  }

  template< class K, class T >
  BiNode< K, T > * prev(BiNode< K, T > * node)
  {
    if (!node)
    {
      node = nullptr;
      return;
    }

    if (node->left_)
    {
      node = node->left_;
      while (node->right_)
      {
        node = node->right_;
      }

      return;
    }

    if (!node->parent_)
    {
      node = nullptr;
      return;
    }

    while (node->parent_->right_ != node)
    {
      node = node->parent_;
      if (!node->parent_)
      {
        node = nullptr;
        return;
      }
    }

    return node->parent_;
  }
}

namespace zakirov
{
  template< class K, class T, class C >
  class BiTree;

  template< class K, class T, class C >
  class BiIter: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    explicit BiIter() noexcept;

    std::pair< K, T > & operator*() noexcept;
    std::pair< K, T > * operator->() noexcept;
    BiIter< K, T, C > & operator++() noexcept;
    BiIter< K, T, C > & operator++(int) noexcept;
    BiIter< K, T, C > & operator--() noexcept;
    BiIter< K, T, C > & operator--(int) noexcept;
    bool operator!=(const BiIter< K, T, C > & other) const noexcept;
    bool operator==(const BiIter< K, T, C > & other) const noexcept;

  private:
    friend class BiTree< K, T, C >;
    explicit BiIter(BiNode< K, T > * node) noexcept;
    void next();
    void prev();
    BiNode< K, T > * node_;
  };

  template< class K, class T, class C >
  BiIter< K, T, C >::BiIter() noexcept:
    node_(nullptr)
  {}

  template< class K, class T, class C >
  BiIter< K, T, C >::BiIter(BiNode< K, T > * node) noexcept:
    node_(node)
  {}

  template< class K, class T >
  std::pair< K, T > & BiIter< K, T, C >::operator*() noexcept
  {
    return node_->value_;
  }

  template< class K, class T, class C >
  std::pair< K, T > * BiIter< K, T, C >::operator->() noexcept
  {
    return std::addressof(node_->value_);
  }

  template< class K, class T, class C >
  BiIter< K, T, C > & BiIter< K, T, C >::operator++() noexcept
  {
    next();
    return *this;
  }

  template< class K, class T, class C >
  BiIter< K, T, C > BiIter< K, T, C >::operator++(int) noexcept
  {
    BiIter< K, T, C > * start_value = *this;
    next();
    return start_value;
  }

  template< class K, class T, class C >
  BiIter< K, T, C > & BiIter< K, T, C >::operator--() noexcept
  {
    prev();
    return *this;
  }

  template< class K, class T, class C >
  BiIter< K, T, C > BiIter< K, T, C >::operator--(int) noexcept
  {
    BiIter< K, T, C > * start_value = *this;
    prev();
    return start_value;
  }

  template< class K, class T, class C >
  bool BiIter< K, T, C >::operator!=(const BiIter< K, T, C > & other) const noexcept
  {
    return node_ != other.node_;
  }

  template< class K, class T, class C >
  bool BiIter< K, T, C >::operator==(const BiIter< K, T, C > & other) const noexcept
  {
    return node_ != other.node_;
  }

  template< class K, class T, class C >
  void BiIter< K, T, C >::next()
  {
    detail::next(node_);
  }

  template< class K, class T, class C >
  void BiIter< K, T, C >::prev()
  {
    detail::prev(node_);
  }

  template< class K, class T, class C >
  class CBiIter: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    explicit CBiIter() noexcept;

    std::pair< K, T > & operator*() const noexcept;
    std::pair< K, T > * operator->() const noexcept;
    CBiIter< K, T, C > & operator++() noexcept;
    CBiIter< K, T, C > operator++(int) noexcept;
    CBiIter< K, T, C > & operator--() noexcept;
    CBiIter< K, T, C > operator--(int) noexcept;
    bool operator!=(const CBiIter< K, T, C > &) const noexcept;
    bool operator==(const CBiIter< K, T, C > &) const noexcept;

  private:
    friend class BiTree< K, T, C >;
    explicit CBiIter(BiNode< K, T > * node) noexcept;
    void next();
    void prev();
    BiNode< K, T > * node_;
  };

  template< class K, class T, class C >
  CBiIter< K, T, C >::CBiIter() noexcept:
    node_(nullptr)
  {}

  template< class K, class T, class C >
  CBiIter< K, T, C >::CBiIter(BiNode< K, T > * node) noexcept:
    node_(node)
  {}

  template< class K, class T, class C >
  std::pair< K, T > & CBiIter< K, T, C >::operator*() const noexcept
  {
    return node_->data_;
  }

  template< class K, class T, class C >
  std::pair< K, T > * CBiIter< K, T, C >::operator->() const noexcept
  {
    return std::addressof(node_->data_);
  }

  template< class K, class T, class C >
  CBiIter< K, T, C > & CBiIter< K, T, C >::operator++() noexcept
  {
    next();
    return *this;
  }

  template< class K, class T, class C >
  CBiIter< K, T, C > & CBiIter< K, T, C >::operator++(int) noexcept
  {
    BiIter< K, T, C > * start_value = *this;
    next();
    return start_value;
  }

  template< class K, class T, class C >
  CBiIter< K, T, C > & CBiIter< K, T, C >::operator--() noexcept
  {
    prev();
    return *this;
  }

  template< class K, class T, class C >
  CBiIter< K, T, C > & CBiIter< K, T, C >::operator--(int) noexcept
  {
    BiIter< K, T, C > * start_value = *this;
    prev();
    return start_value;
  }

  template< class K, class T, class C >
  bool CBiIter< K, T, C >::operator!=(const CBiIter< K, T, C > & other) const noexcept
  {
    return node_ != other.node_
  }

  template< class K, class T, class C >
  bool CBiIter< K, T, C >::operator==(const CBiIter< K, T, C > & other) const noexcept
  {
    return node_ == other.node_
  }

  template< class K, class T, class C >
  void CBiIter< K, T, C >::next()
  {
    detail::next(node_);
  }

  template< class K, class T, class C >
  void CBiIter< K, T, C >::prev()
  {
    detail::prev(node_);
  }
}

#endif
