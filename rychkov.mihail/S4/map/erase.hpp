#ifndef ERASE_HPP
#define ERASE_HPP

#include "declaration.hpp"
#include <type_traits.hpp>

template< class Key, class Value, class Compare, size_t N >
typename rychkov::Map< Key, Value, Compare, N >::iterator
    rychkov::Map< Key, Value, Compare, N >::erase(const_iterator pos)
{
  static_assert(std::is_nothrow_move_constructible< value_type >::value, "use of unready functional");
  size_--;
  iterator result{pos.node_, pos.pointed_};
  if (!pos.node_->isleaf())
  {
    const_iterator erased = pos;
    --pos;
    erased.node_->replace(erased.pointed_, std::move(*pos));
  }
  if (pos.node_->size() > 1)
  {
    if (pos.pointed_ == pos.node_->size() - 1)
    {
      ++result;
    }
    pos.node_->erase(pos.pointed_);
    return result;
  }
  while (true)
  {
    if (pos.node_->parent == fake_root())
    {
      if (pos.node_->isleaf())
      {
        fake_children_[0] = nullptr;
        cached_begin_ = fake_root();
        cached_rbegin_ = cached_begin_;
        delete pos.node_;
        return end();
      }
      fake_children_[0] = pos.node_->children[0];
      fake_children_[0]->parent = fake_root();
      delete pos.node_;
      return result;
    }
    pos.node_->pop_back();
    const_iterator erased = pos;
    pos.move_up();
    const_iterator parent = pos;
    parent.pointed_ -= (parent.pointed_ == 0 ? 0 : 1);
    node_type* src = nullptr;
    node_type* erased_subtree = erased.node_->children[0];
    if (pos.pointed_ != 0)
    {
      src = parent.node_->children[parent.pointed_];
      if (src->size() != 1)
      {
        erased.node_->emplace_back(std::move(parent.node_->operator[](parent.pointed_)));
        parent.node_->replace(parent.pointed_, std::move(src->operator[](src->size() - 1)));
        erased.node_->children[1] = erased_subtree;
        erased.node_->children[0] = src->children[src->size()];
        if (!src->isleaf())
        {
          erased.node_->children[0]->parent = erased.node_;
        }
        src->pop_back();
        return result;
      }
      else
      {
        erased.node_->emplace_back(std::move(src->operator[](0)));
        erased.node_->emplace_back(std::move(parent.node_->operator[](parent.pointed_)));
        erased.node_->children[2] = erased_subtree;
        erased.node_->children[1] = src->children[1];
        erased.node_->children[0] = src->children[0];
        if (!src->isleaf())
        {
          erased.node_->children[1]->parent = erased.node_;
          erased.node_->children[0]->parent = erased.node_;
        }
        src->pop_back();
        if (src == cached_begin_)
        {
          cached_begin_ = erased.node_;
        }
        delete src;
        parent.node_->children[parent.pointed_] = erased.node_;
        pos = parent;
      }
    }
    else
    {
      src = parent.node_->children[pos.pointed_ + 1];
      if (src->size() != 1)
      {
        erased.node_->emplace_back(std::move(parent.node_->operator[](pos.pointed_)));
        parent.node_->replace(pos.pointed_, std::move(src->operator[](0)));
        erased.node_->children[0] = erased_subtree;
        erased.node_->children[1] = src->children[0];
        if (!src->isleaf())
        {
          erased.node_->children[1]->parent = erased.node_;
        }
        src->children[0] = src->children[1];
        src->erase(0);
        return result;
      }
      else
      {
        erased.node_->emplace_back(std::move(parent.node_->operator[](parent.pointed_)));
        erased.node_->emplace_back(std::move(src->operator[](0)));
        erased.node_->children[0] = erased_subtree;
        erased.node_->children[1] = src->children[0];
        erased.node_->children[2] = src->children[1];
        if (!src->isleaf())
        {
          erased.node_->children[1]->parent = erased.node_;
          erased.node_->children[2]->parent = erased.node_;
        }
        src->pop_back();
        if (src == cached_begin_)
        {
          cached_begin_ = erased.node_;
        }
        delete src;
        parent.node_->children[parent.pointed_] = erased.node_;
      }
    }
    if (parent.node_->size() > 1)
    {
      parent.node_->erase(pos.pointed_);
      return result;
    }
  }
  return result;
}

template< class Key, class Value, class Compare, size_t N >
typename rychkov::Map< Key, Value, Compare, N >::size_type
    rychkov::Map< Key, Value, Compare, N >::erase(const key_type& key)
{
  const_iterator iter = find(key);
  if (iter == end())
  {
    return 0;
  }
  erase(iter);
  return 1;
}
template< class Key, class Value, class Compare, size_t N >
template< class K >
typename rychkov::Map< Key, Value, Compare, N >::size_type
    rychkov::Map< Key, Value, Compare, N >::erase(std::enable_if_t< is_transparent_v< key_compare >, const K& > key)
{
  const_iterator iter = find(key);
  if (iter == end())
  {
    return 0;
  }
  erase(iter);
  return 1;
}

#endif
