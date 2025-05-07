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
    using value_type = std::pair< Key, Value >;
    using node_type = node_t< value_type >;

    using iterator = BidirectIterator< Key, Value >;

    TwoThreeTree();

    iterator begin() noexcept;
    iterator end() noexcept;

    iterator find(const key_type & k);

    mapped_type & operator[](const key_type & k);
    //mapped_type & operator[](key_type && k);

    std::pair< iterator, bool > insert(const value_type & val);
  private:
    node_type * root_;
    size_t size_;

    std::pair< iterator, bool > lazy_find(const key_type & k);

    node_type * split_node(node_type * node);
    void sort_node(node_type * node)
    {
      if (node->len_ == 2)
      {
        if (!Compare{}(node->data_[0].first, node->data_[1].first))
        {
          std::swap(node->data_[0], node->data_[1]);
        }
      }
      if (node->len_ == 3)
      {
        if (!Compare{}(node->data_[0].first, node->data_[1].first))
        {
          std::swap(node->data_[0], node->data_[1]);
        }
        if (!Compare{}(node->data_[1].first, node->data_[2].first))
        {
          std::swap(node->data_[1], node->data_[2]);
        }
        if (!Compare{}(node->data_[0].first, node->data_[1].first))
        {
          std::swap(node->data_[0], node->data_[1]);
        }
      }
    }

    void insert_data_in_node(node_type * node, const value_type & val)
    {
      node->data_[node->len_] = val;
      node->len_++;
      sort_node(node);
    }
  };

  template< typename Key, typename Value, typename Compare >
  TwoThreeTree< Key, Value, Compare >::TwoThreeTree():
    root_(nullptr),
    size_(0)
  {}

  template< typename K, typename V, typename C >
  typename TwoThreeTree< K, V, C >::iterator TwoThreeTree< K, V, C >::begin() noexcept
  {
    node_type * temp = root_;
    while (temp->kids_[0])
    {
      temp = temp->kids_[0];
    }
    return iterator(temp, 0);
  }

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
    return insert(std::make_pair(k, mapped_type{})).first->second;
  }

  /*
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
*/
  template< typename K, typename V, typename C >
  typename std::pair< typename TwoThreeTree< K, V, C >::iterator, bool >
  TwoThreeTree< K, V, C >::lazy_find(const key_type & k)
  {
    if (!root_)
    {
      return {iterator(), false};
    }

    node_type * node = root_;

    while (true)
    {
      if (node->data_[0].first == k)
      {
        return {iterator(node, 0), true};
      }

      if (node->len_ == 2 && node->data_[1].first == k)
      {
        return {iterator(node, 1), true};
      }

      if (!node->kids_[0] && !node->kids_[1] && !node->kids_[2])
      {
        return {iterator(node, node->len_ == 2 ? 1 : 0), false};
      }

      if (C{}(k, node->data_[0].first))
      {
        node = node->kids_[0];
      }
      else if (node->len_ == 1 || C{}(k, node->data_[1].first))
      {
        node = node->kids_[1];
      }
      else
      {
        node = node->kids_[2];
      }
    }
  }

  template< typename Key, typename Value, typename Compare >
  typename TwoThreeTree< Key, Value, Compare >::node_type * TwoThreeTree< Key, Value, Compare >::split_node(node_type * node)
  {
    if (node->len_ < 3)
    {
      return node;
    }
    node_type * left = new node_type{};
    node_type * right = nullptr;
    try
    {
      right = new node_type{};
    }
    catch (const std::bad_alloc & e)
    {
      delete left;
      throw;
    }
    left->parent_ = node->parent_;
    right->parent_ = node->parent_;
    for (size_t i = 0; i < 2; ++i)
    {
      left->kids_[i] = node->kids_[i];
      if (left->kids_[i])
      {
        left->kids_[i]->parent_ = left;
      }
      right->kids_[i] = node->kids_[i + 2];
      if (right->kids_[i])
      {
        right->kids_[i]->parent_ = right;
      }
    }
    insert_data_in_node(left, node->data_[0]);
    insert_data_in_node(right, node->data_[2]);

    if (node->parent_)
    {
      node_type * parent = node->parent_;

      insert_data_in_node(parent, node->data_[1]);

      if (parent->kids_[0] == node)
      {
        parent->kids_[3] = parent->kids_[2];
        parent->kids_[2] = parent->kids_[1];
        parent->kids_[1] = right;
        parent->kids_[0] = left;
      }
      else if (parent->kids_[1] == node)
      {
        parent->kids_[3] = parent->kids_[2];
        parent->kids_[2] = right;
        parent->kids_[1] = left;
      }
      else
      {
        parent->kids_[3] = right;
        parent->kids_[2] = left;
      }

      delete node;
      return parent;
    }
    else
    {
      left->parent_ = node;
      right->parent_ = node;
      node->data_[0] = node->data_[1];
      node->kids_[0] = left;
      node->kids_[1] = right;
      node->kids_[2] = nullptr;
      node->kids_[3] = nullptr;
      node->len_ = 1;
      return node;
    }
  }

  template< typename K, typename V, typename C >
  std::pair< typename TwoThreeTree< K, V, C >::iterator, bool > TwoThreeTree< K, V, C >::insert(const value_type & val)
  {
    auto result = lazy_find(val.first);

    if (result.second)
    {
      return {result.first, false};
    }
    node_type * current = result.first.node_;

    if (!current)
    {
      root_ = new node_type{};
      insert_data_in_node(root_, val);
      size_++;
      return {iterator(root_), true};
    }

    insert_data_in_node(current, val);

    while (current && current->len_ == 3)
    {
      current = split_node(current);
    }
    while (current->parent_)
    {
      current = current->parent_;
    }

    root_ = current;
    size_++;

    /*
    node_type * node = root_;
    std::cout << "HEAD: " << node->data_[0].first << '|' <<node->data_[0].second << '\n';
    std::cout << '\n' << "kids: ";
    for (size_t i = 0; i < 4; ++i)
    {
      std::cout << i << ") " << ((node->kids_[i]) ? node->kids_[i]->data_[0].first : 0) << "|" << ((node->kids_[i]) ? node->kids_[i]->data_[0].second : 0);
      if (node->kids_[i])
      {
        for (size_t j = 0; j < 4; ++j)
        {
          std::cout << "[ " << ((node->kids_[i]->kids_[j]) ? node->kids_[i]->kids_[j]->data_[0].first : 0) << '|' << ((node->kids_[i]->kids_[j]) ? node->kids_[i]->kids_[j]->data_[0].second : 0) << " ]";
        }
      }
      std::cout << " ";
    }
    std::cout << '\n';
    */
    return {lazy_find(val.first).first, true};
  }
}

#endif
