#ifndef TTT_ITERATOR_H
#define TTT_ITERATOR_H
#include <iterator>
#include <utility>
#include "ttt-node.hpp"

namespace savintsev
{
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTree;

  template< typename Key, typename Value >
  class BidirectIterator;

  template< typename Key, typename Value >
  class BidirectConstIterator:
    public std::iterator< std::bidirectional_iterator_tag, const std::pair< Key, Value > >
  {
    using value_type = const std::pair< Key, Value >;
    using node_type = node_t< std::pair< Key, Value > >;

    template< typename K, typename V, typename C >
    friend class TwoThreeTree;
  public:
    BidirectConstIterator() = default;
    BidirectConstIterator(const BidirectIterator< Key, Value > & it):
      root_(it.root_),
      node_(it.node_),
      pos_(it.pos_)
    {}

    value_type & operator*() const
    {
      return node_->data_[pos_];
    }

    value_type * operator->() const
    {
      return std::addressof(node_->data_[pos_]);
    }

    BidirectConstIterator & operator++()
    {
      return next();
    }

    BidirectConstIterator operator++(int)
    {
      BidirectConstIterator< Key, Value > result(*this);
      ++(*this);
      return result;
    }

    BidirectConstIterator & operator--()
    {
      if (!node_)
      {
        return rbegin();
      }
      return prev();
    }

    BidirectConstIterator operator--(int)
    {
      BidirectConstIterator< Key, Value > result(*this);
      --(*this);
      return result;
    }

    bool operator!=(const BidirectConstIterator & rhs) const
    {
      return !(*this == rhs);
    }

    bool operator==(const BidirectConstIterator & rhs) const
    {
      return node_ == rhs.node_ && pos_ == rhs.pos_;
    }

  private:
    node_type * root_ = nullptr;
    node_type * node_ = nullptr;
    size_t pos_ = 0;

    node_type * rbegin(node_type * node)
    {
      while (root_->kids_[1] || root_->kids_[2])
      {
        if (root_->kids_[2])
        {
          root_ = root_->kids_[2];
        }
        else if (root_->kids_[1])
        {
          root_ = root_->kids_[1];
        }
      }
      return root_;
    }

    BidirectConstIterator(node_type * root, node_type * node = nullptr, size_t pos = 0):
      root_(root),
      node_(node),
      pos_(pos)
    {}

    BidirectConstIterator & next()
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

    BidirectConstIterator & prev()
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

  template< typename Key, typename Value >
  class BidirectIterator:
    public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
  {
    using value_type = std::pair< Key, Value >;
    using node_type = node_t< value_type >;

    template< typename K, typename V, typename C >
    friend class TwoThreeTree;
    friend class BidirectConstIterator< Key, Value >;
  public:
    BidirectIterator() = default;
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
    BidirectIterator & operator--()
    {
      if (!node_)
      {
        return rbegin();
      }
      return prev();
    }
    BidirectIterator operator--(int)
    {
      BidirectIterator< Key, Value > result(*this);
      --(*this);
      return result;
    }
    bool operator!=(const BidirectIterator & rhs) const
    {
      return !(*this == rhs);
    }
    bool operator==(const BidirectIterator & rhs) const
    {
      return node_ == rhs.node_ && pos_ == rhs.pos_;
    }
  private:
    node_type * root_ = nullptr;
    node_type * node_ = nullptr;
    size_t pos_ = 0;

    node_type * rbegin(node_type * node)
    {
      while (root_->kids_[1] || root_->kids_[2])
      {
        if (root_->kids_[2])
        {
          root_ = root_->kids_[2];
        }
        else if (root_->kids_[1])
        {
          root_ = root_->kids_[1];
        }
      }
      return root_;
    }

    BidirectIterator(node_type * root, node_type * node = nullptr, size_t pos = 0):
      root_(root),
      node_(node),
      pos_(pos)
    {}

    BidirectIterator & next()
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
