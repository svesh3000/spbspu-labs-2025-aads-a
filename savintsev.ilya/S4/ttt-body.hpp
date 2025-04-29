#ifndef TTT_BODY_HPP
#define TTT_BODY_HPP
#include <functional>
#include "ttt-node.hpp"
#include "ttt-iterator.hpp"

namespace savintsev
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class TwoThreeTree
  {
  public:
    using key_type = Key;
    using mapped_type = Value;

    using iterator = BidirectIterator< Key, Value >;

    TwoThreeTree();

    iterator begin() noexcept;
    iterator end() noexcept;
    //const_iterator begin() const noexcept;
    //const_iterator end() const noexcept;
    iterator find(const key_type & k);
    //const_iterator find(const key_type & k) const;
    mapped_type & operator[](const key_type & k);
    mapped_type & operator[](key_type && k);
  private:
    node_t< Key, Value > * root_;
    size_t size_;

    iterator lazy_find(const key_type & k);
    iterator create_node(iterator it, const key_type & k);
  };

  template< typename Key, typename Value, typename Compare >
  TwoThreeTree< Key, Value, Compare >::TwoThreeTree():
    root_(nullptr),
    size_(0)
  {}

  template< typename K, typename V, typename C >
  typename TwoThreeTree< K, V, C >::iterator TwoThreeTree< K, V, C >::end() noexcept
  {
    return iterator();
  }

  template< typename K, typename V, typename C >
  typename TwoThreeTree< K, V, C >::iterator TwoThreeTree< K, V, C >::find(const key_type & k)
  {
    iterator temp = lazy_find(k);
    if (!temp || k != temp.node_->data_[temp.pos_].first)
    {
      return end();
    }
    return temp;
  }

  template< typename K, typename V, typename C >
  typename TwoThreeTree< K, V, C >::mapped_type & TwoThreeTree< K, V, C >::operator[](const key_type & k)
  {
    iterator temp = lazy_find(k);
    if (!temp.node_ || k != temp.node_->data_[temp.pos_].first)
    {
      temp = create_node(temp, k);
    }
    return temp.node_->data_[temp.pos_].second;
  }

  template< typename K, typename V, typename C >
  typename TwoThreeTree< K, V, C >::mapped_type & TwoThreeTree< K, V, C >::operator[](key_type && k)
  {
    iterator temp = lazy_find(k);
    if (!temp.node_ || k != temp.node_->data_[temp.pos_].first)
    {
      temp = create_node(temp, k);
    }
    return temp.node_->data_[temp.pos_].second;
  }

  template< typename K, typename V, typename C >
  typename TwoThreeTree< K, V, C >::iterator TwoThreeTree< K, V, C >::lazy_find(const key_type & k)
  {
    if (!root_)
    {
      return iterator{nullptr};
    }
    node_t< K, V > * temp = root_;
    C comp;
    while (temp->data_[0].first != k)
    {
      if (temp->len_ == 2)
      {
        if (temp->data_[1].first == k)
        {
          return iterator{temp, true};
        }

        if (!temp->sons_)
        {
          return iterator{temp, true};
        }

        if (comp(k, temp->data_[0].first))
        {
          temp = temp->left_;
        }
        else if (comp(k, temp->data_[1].first))
        {
          temp = temp->midd_;
        }
        else
        {
          temp = temp->righ_;
        }
      }
      else if (temp->len_ == 1)
      {
        if (!temp->sons_)
        {
          return iterator{temp};
        }

        if (comp(k, temp->data_[0].first))
        {
          temp = temp->left_;
        }
        else
        {
          temp = temp->righ_;
        }
      }
    }
    return iterator{temp};
  }

  template< typename K, typename V, typename C >
  typename TwoThreeTree< K, V, C >::iterator TwoThreeTree< K, V, C >::create_node(iterator it, const key_type & k)
  {
    node_t< K, V > * current = it.node_;
    if (!current)
    {
      root_ = new node_t< K, V >{};
      root_->data_[0] = {k, mapped_type{}};
      root_->len_ = 1;
      size_++;
      return iterator(root_);
    }
    else if (current->len_ == 1)
    {
      if (C{}(k, current->data_[0].first))
      {
        current->data_[1] = current->data_[0];
        current->data_[0] = {k, mapped_type{}};
      }
      else
      {
        current->data_[1] = {k, mapped_type{}};
      }
      current->len_ = 2;
      size_++;
      return iterator(current, 1);
    }
    else
    {
      // zdes probros naverh, poka shto throw =)
      throw std::runtime_error("Node splitting not implemented");
    }
  }
}

#endif
