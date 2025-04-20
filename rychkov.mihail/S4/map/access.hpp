#ifndef ACCESS_HPP
#define ACCESS_HPP

#include "declaration.hpp"
#include <memory>

template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::node_type*
    rychkov::Map< Key, Mapped, Compare, N >::fake_root() noexcept
{
  return getFakePointer(fake_parent_, &node_type::parent_);
}
template< class Key, class Mapped, class Compare, size_t N >
const typename rychkov::Map< Key, Mapped, Compare, N >::node_type*
    rychkov::Map< Key, Mapped, Compare, N >::fake_root() const noexcept
{
  return getFakePointer(fake_parent_, &node_type::parent_);
}

#endif
