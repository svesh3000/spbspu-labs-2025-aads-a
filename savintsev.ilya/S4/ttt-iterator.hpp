#ifndef TTT_ITERATOR_H
#define TTT_ITERATOR_H
#include <iterator>
#include <utility>
#include "ttt-node.hpp"

namespace savintsev
{
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTree;

  //template< typename Key, typename Value, typename Compare >
  //class ConstIterator;

  template< typename Key, typename Value >
  class BidirectIterator:
    public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
  {
    using value_type = std::pair< Key, Value >;
    using node_type = node_t< value_type >;

    template< typename K, typename V, typename C >
    friend class TwoThreeTree;
    //friend class ConstIterator< T >;
  public:
    BidirectIterator():
      node_(nullptr)
    {}
    value_type & operator*()
    {
      return node_->data_[pos_];
    }
    value_type * operator->()
    {
      return std::addressof(node_->data_[pos_]);
    }
    const value_type & operator*() const
    {
      return node_->data_[pos_];
    }
    const value_type * operator->() const
    {
      return std::addressof(node_->data_[pos_]);
    }
    BidirectIterator & operator++()
    {
      return next();
    }
    BidirectIterator operator++(int)
    {
      BidirectIterator< Key, Value > result(*this);
      ++(*this);
      return result;
    }
    BidirectIterator & operator--();
    BidirectIterator operator--(int);
    bool operator!=(const BidirectIterator & rhs) const
    {
      return !(*this == rhs);
    }
    bool operator==(const BidirectIterator & rhs) const
    {
      return node_ == rhs.node_ && pos_ == rhs.pos_;
    }
  private:
    node_type * node_;
    size_t pos_ = 0;

    BidirectIterator(node_type * node, size_t pos = 0):
      node_(node),
      pos_(pos)
    {}

    BidirectIterator& next()
    {
      if (!node_)
      {
        return *this;
      }

      if (pos_ < node_->len_ && node_->kids_[pos_ + 1])
      {
        node_ = node_->kids_[pos_ + 1];
        while (node_->kids_[0])
        {
          node_ = node_->kids_[0];
        }
        pos_ = 0;
        return *this;
      }

      if (pos_ < node_->len_ - 1)
      {
        ++pos_;
        return *this;
      }

      while (node_->parent_)
      {
        size_t parent_pos = 0;
        while (parent_pos <= node_->parent_->len_ && node_->parent_->kids_[parent_pos] != node_)
        {
          ++parent_pos;
        }
        node_ = node_->parent_;
        if (parent_pos < node_->len_)
        {
          pos_ = parent_pos;
          return *this;
        }
      }
      node_ = nullptr;
      return *this;
    }
    BidirectIterator & prev()
    {
      if (!node_)
      {
        return *this;
      }

      if (pos_ > 0 && node_->kids_[pos_])
      {
        node_ = node_->kids_[pos_];
        while (node_->kids_[node_->len_])
        {
          node_ = node_->kids_[node_->len_];
        }
        pos_ = node_->len_ - 1;
        return *this;
      }

      if (pos_ > 0)
      {
        --pos_;
        return *this;
      }

      while (node_->parent_)
      {
        size_t parent_pos = 0;
        while (parent_pos <= node_->parent_->len_ && node_->parent_->kids_[parent_pos] != node_)
        {
          ++parent_pos;
        }

        node_ = node_->parent_;
        if (parent_pos > 0)
        {
          pos_ = parent_pos - 1;
          return *this;
        }
      }

      node_ = nullptr;
      return *this;
    }
  };
}

#endif
