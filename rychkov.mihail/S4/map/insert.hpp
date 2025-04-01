#ifndef INSERT_HPP
#define INSERT_HPP

#include "declaration.hpp"
#include "iterator.hpp"

template< class Key, class Value, class Compare >
typename rychkov::Map< Key, Value, Compare >::const_iterator
    rychkov::Map< Key, Value, Compare >::find_hint(const key_type& key)
{
  /*if (root_ == nullptr)
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
  }*/
}
/*template< class Key, class Value, class Compare >
template< class... Args >
typename rychkov::Map< Key, Value, Compare >::iterator
    rychkov::Map< Key, Value, Compare >::emplace(Args... args)
{
  node_type* newNode = new node_type{{args...}};
  place_node(hint, newNode);
  return {newNode};
}
template< class Key, class Value, class Compare >
void rychkov::Map< Key, Value, Compare >::place_node(const_iterator hint, node_type* node)
{
  if (() || (hint.node_->second_part != nullptr))
}*/

#endif
