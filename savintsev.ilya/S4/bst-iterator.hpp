#ifndef BST_ITERATOR_H
#define BST_ITERATOR_H
#include <iterator>
#include <utility>
#include "bst-node.hpp"

namespace savintsev
{
  template< typename Key, typename Value, typename Compare >
  class BinSearchTree;

  //template< typename Key, typename Value, typename Compare >
  //class ConstIterator;

  template< typename Key, typename Value >
  class Iterator:
    public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value >>
  {
    using value_type = std::pair< Key, Value >;

    //template< typename Compare >
    //friend class BinSearchTree< Key, Value, Compare >;
    //friend class ConstIterator< T >;
  public:
    Iterator():
      node_(nullptr)
    {}
    value_type & operator*()
    {
      node_->data_;
    }
    value_type * operator->()
    {
      return std::addressof(node_->data_);
    }
    const value_type & operator*() const
    {
      node_->data_;
    }
    const value_type * operator->() const
    {
      return std::addressof(node_->data_);
    }
    Iterator & operator++()
    {}
    Iterator operator++(int);
    Iterator & operator--();
    Iterator operator--(int);
    bool operator!=(const Iterator & rhs) const;
    bool operator==(const Iterator & rhs) const;
  private:
    Node< Key, Value > * node_;

    Iterator(Node< Key, Value > * rhs):
      node_(rhs)
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
