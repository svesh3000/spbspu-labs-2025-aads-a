#ifndef TTT_ITERATOR_H
#define TTT_ITERATOR_H
#include <iterator>
#include <utility>
#include <iostream>
#include "ttt-node.hpp"

namespace savintsev
{
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTree;

  template< typename Key, typename Value >
  class BidirectIterator;

  template< typename Key, typename Value >
  class BidirectConstIterator
  {
    template< typename K, typename V, typename C >
    friend class TwoThreeTree;
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::pair< Key, Value >;
    using difference_type = std::ptrdiff_t;
    using pointer = const value_type *;
    using reference = const value_type &;
    using node_type = node_t< value_type >;

    BidirectConstIterator() = default;
    BidirectConstIterator(const BidirectIterator< Key, Value > & it):
      root_(it.root_),
      node_(it.node_),
      pos_(it.pos_)
    {}

    reference operator*() const
    {
      assert(node_ != nullptr);
      assert(pos_ < node_->len_);
      return node_->data_[pos_];
    }

    pointer operator->() const
    {
      assert(node_ != nullptr);
      assert(pos_ < node_->len_);
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
        if (!root_)
        {
          return *this;
        }

        node_ = root_;
        while (node_->kids_[node_->len_])
        {
          node_ = node_->kids_[node_->len_];
        }
        pos_ = node_->len_ - 1;
        return *this;
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
      if (node_ == nullptr && rhs.node_ == nullptr)
      {
        return true;
      }
      return node_ == rhs.node_ && pos_ == rhs.pos_;
    }

  private:
    node_type * root_ = nullptr;
    node_type * node_ = nullptr;
    size_t pos_ = 0;

    BidirectConstIterator & rbegin()
    {
      if (!root_)
      {
        node_ = nullptr;
        return *this;
      }

      node_ = root_;
      while (node_->kids_[node_->len_])
      {
        node_ = node_->kids_[node_->len_];
      }

      pos_ = node_->len_ - 1;
      return *this;
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

      if (node_->kids_[pos_])
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
  class BidirectIterator
  {
    template< typename K, typename V, typename C >
    friend class TwoThreeTree;
    friend class BidirectConstIterator< Key, Value >;
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::pair< Key, Value >;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type &;
    using node_type = node_t< value_type >;

    BidirectIterator() = default;
    reference operator*()
    {
      assert(node_ != nullptr);
      return node_->data_[pos_];
    }
    pointer operator->()
    {
      assert(node_ != nullptr);
      return std::addressof(node_->data_[pos_]);
    }
    reference operator*() const
    {
      assert(node_ != nullptr);
      return node_->data_[pos_];
    }
    pointer operator->() const
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
      std::cout << "tut_nonconst\n";
      if (!node_)
      {
        if (!root_)
        {
          return *this;
        }
        
        node_ = root_;
        while (node_->kids_[node_->len_])
        {
          node_ = node_->kids_[node_->len_];
        }
        pos_ = node_->len_ - 1;
        return *this;
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
      if (node_ == nullptr && rhs.node_ == nullptr)
      {
        return true;
      }
      return node_ == rhs.node_ && pos_ == rhs.pos_;
    }
  private:
    node_type * root_ = nullptr;
    node_type * node_ = nullptr;
    size_t pos_ = 0;

    BidirectIterator & rbegin()
    {
      if (!root_)
      {
        node_ = nullptr;
        return *this;
      }

      node_ = root_;
      while (node_->kids_[node_->len_])
      {
        node_ = node_->kids_[node_->len_];
      }

      pos_ = node_->len_ - 1;
      return *this;
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
