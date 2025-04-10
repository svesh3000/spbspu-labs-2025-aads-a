#ifndef TTT_ITERATOR_H
#define TTT_ITERATOR_H
#include <iterator>
#include <utility>
#include "ttt-node.hpp"

namespace savintsev
{
  //template< typename Key, typename Value, typename Compare >
  //class BinSearchTree;

  //template< typename Key, typename Value, typename Compare >
  //class ConstIterator;

  template< typename Key, typename Value >
  class BidirectIterator:
    public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value >>
  {
    using value_type = std::pair< Key, Value >;

    //template< typename Compare >
    //friend class BinSearchTree< Key, Value, Compare >;
    //friend class ConstIterator< T >;
  public:
    BidirectIterator():
      node_(nullptr)
    {}
    value_type & operator*()
    {
      node_->data_[node_->is_righ_];
    }
    value_type * operator->()
    {
      return std::addressof(node_->data_[node_->is_righ_]);
    }
    const value_type & operator*() const
    {
      node_->data_[node_->is_righ_];
    }
    const value_type * operator->() const
    {
      return std::addressof(node_->data_[node_->is_righ_]);
    }
    BidirectIterator & operator++()
    {}
    BidirectIterator operator++(int);
    BidirectIterator & operator--();
    BidirectIterator operator--(int);
    bool operator!=(const BidirectIterator & rhs) const;
    bool operator==(const BidirectIterator & rhs) const;
  private:
    node_t< Key, Value > * node_;
    bool is_righ_ = false;

    BidirectIterator(node_t< Key, Value > * rhs, bool is_right = false):
      node_(rhs),
      is_righ_(is_right)
    {}
  };
/*
  template< typename T >
  class ConstIterator:
    public std:: iterator< std::bidirectional_iterator_tag, T >
  {
    template< typename U >
    friend class List;
  public:
    ConstIterator();
    ConstIterator(Iterator< T > rhs);
    const T & operator*() const;
    const T * operator->() const;
    ConstIterator & operator++();
    ConstIterator operator++(int);
    ConstIterator & operator--();
    ConstIterator operator--(int);
    bool operator!=(const ConstIterator & rhs) const;
    bool operator==(const ConstIterator & rhs) const;
  private:
    ListNode< T > * node;
    ConstIterator(ListNode< T > * rhs);
  };
*/
}

#endif
