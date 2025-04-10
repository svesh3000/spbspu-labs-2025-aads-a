#ifndef TTT_BODY_HPP
#define TTT_BODY_HPP
#include <functional>
#include "ttt-node.hpp"
#include "ttt-iterator.hpp"

namespace savintsev
{
  template< typename Key, typename Value, typename Compare >
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
    Compare comp_ = std::less< key_type >();
    size_t size_;

    iterator lazy_find(const key_type & k);
    void create_node();
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
    if (k != temp.node_->data_[temp.is_righ_])
    {
      return end();
    }
    return temp;
  }

  template< typename K, typename V, typename C >
  typename TwoThreeTree< K, V, C >::mapped_type & TwoThreeTree< K, V, C >::operator[](const key_type & k)
  {
    iterator temp = lazy_find(k);
    if (k != temp.node_->data_[temp.is_righ_])
    {
      create_node();
    }
    return temp.node_->data_[temp.is_righ_];
  }

  template< typename K, typename V, typename C >
  typename TwoThreeTree< K, V, C >::iterator TwoThreeTree< K, V, C >::lazy_find(const key_type & k)
  {
    node_t< K, V > * temp = root_;
    while (temp->data_[0]->first != k)
    {
      if (temp->len_ == 2)
      {
        if (temp->data_[1]->first == k)
        {
          return iterator(temp, true);
        }

        if (!temp->sons_)
        {
          return iterator(temp, true);
        }

        if (comp_(k, temp->data_[0]->first))
        {
          temp = temp->left_;
        }
        else if (comp_(k, temp->data_[1]->first))
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
          return iterator(temp);
        }

        if (comp_(k, temp->data_[0]->first))
        {
          temp = temp->left_;
        }
        else
        {
          temp = temp->righ_;
        }
      }
    }
    return iterator(temp);
  }
}

#endif
