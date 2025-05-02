#ifndef ERASE_HPP
#define ERASE_HPP

#include "declaration.hpp"
#include <type_traits.hpp>

template< class Key, class Value, class Compare, size_t N >
typename rychkov::Map< Key, Value, Compare, N >::iterator
    rychkov::Map< Key, Value, Compare, N >::erase(const_iterator pos)
{
  static_assert(std::is_nothrow_move_constructible< value_type >::value, "use of unready functional");
  iterator result{pos.node_, pos.pointed_};
  if (pos.node_->isleaf())
  {
    if (pos.node_->size() > 1)
    {
      if (pos.pointed_ == pos.node_->size() - 1)
      {
        ++result;
      }
      pos.node_->erase(pos.pointed_);
    }
    else
    {
      if (pos.node_->parent->isfake())
      {
        delete pos.node_;
        fake_children_[0] = nullptr;
        return end();
      }
      const_iterator erased = pos;
      pos.move_up();
      const_iterator parent = pos;
      parent.pointed_ -= (parent.pointed_ == 0 ? 0 : 1);
      for (node_size_type i = parent.pointed_ - 1; i != -1; i--)
      {

      }
    }
  }
  return result;
}

#endif
