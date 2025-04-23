#ifndef INSERT_HPP
#define INSERT_HPP

#include "declaration.hpp"
#include "iterator.hpp"
#include <utility>

/*template< class Key, class Value, class Compare >
typename rychkov::Map< Key, Value, Compare >::const_iterator
    rychkov::Map< Key, Value, Compare >::find_hint(const key_type& key)
{
  if (root_ == nullptr)
  {
    return {};
  }
  node_type* node = root_;
  while (true)
  {
    if (comp_(key, node->data))
    {
      if (node->left == nullptr)
      {
        return {node, nullptr, true};
      }
      node = node->left;
    }
    else if (!comp_(node->data, key))
    {
      return {node, nullptr, true};
    }
    else if (node->second_part != nullptr)
    {
      if (comp_(key, node->second_part->data))
      {
        if (node->right == nullptr)
        {
          return {node, nullptr, false};
        }
        node = node->right;
      }
      else
      {
        if (node->second_part->right == nullptr)
        {
          return {node->second_part, nullptr, false};
        }
        node = node->second_part->right;
      }
    }
    else
    {
      if (node->right == nullptr)
      {
        return {node, nullptr, false};
      }
      node = node->right;
    }
  }
}*/
template< class Key, class Value, class Compare, size_t N >
template< class... Args >
typename rychkov::Map< Key, Value, Compare, N >::iterator
    rychkov::Map< Key, Value, Compare, N >::emplace_hint(const_iterator hint, Args&&... args)
{
  if (hint.node_->isFake())
  {
    if (size_ == 0)
    {
      fake_children_[0] = new node_type{fake_root()};
      cached_begin_ = fake_children_[0];
      cached_rbegin_ = fake_children_[0];
      cached_begin_->emplace(0, std::forward< Args >(args)...);
      size_++;
      return begin();
    }
    hint = {cached_rbegin_, cached_rbegin_->size()};
  }
  return begin();
  /*node_type* fake = fake_root();
  node_type* newNode = new node_type;
  try
  {
    newNode->emplace(0, std::forward< Args >(node)...);
    while (hint.node_ != fake)
    {
      if (!hint.node_->full())
      {
        hint.node_->emplace(hint.pointed_, std::move((*newNode)[0]));
        delete newNode;
        return hint;
      }
      else
      {
        constexpr size_t left_half_len = (node_capacity + 1) / 2;
        if (hint.pointed_ < left_half_len)
        {
          for (node_size_type i = 0; i < hint.pointed_; i++)
          {
            newNode->emplace(i, std::move((*hint.node_)[0]));
            // child =
            hint->node->erase(0);
          }
          for (node_size_type i = hint.pointed_ + 1; i < left_half_len; i++)
          {
            newNode->emplace(i, std::move((*hint.node_)[0]));
            // child =
            hint->node->erase(0);
          }
        }
        else
        {
          for (node_size_type i = 0; i < left_half_len; i++)
          {
            newNode->emplace(i, std::move((*hint.node_)[0]));
            // child =
            hint->node->erase(0);
          }
        }
        for ()

        node_type* prev = hint.node_;
        hint.node_ = hint.node_->parent_;
        for (node_size_type i = 0; i <= node_capacity; i++)
        {
          if ((*hint.node_)[i] == prev)
          {
            hint.pointed_ = i;
            break;
          }
        }
      }
    }
    fake_parent_ = newNode;
    if (size_ == 0)
    {
      fake_children_[0] = newNode;
      fake_children_[1] = newNode;
    }
    size_++;
  }
  catch (...)
  {
    delete newNode;
    throw;
  }*/
}

#endif
