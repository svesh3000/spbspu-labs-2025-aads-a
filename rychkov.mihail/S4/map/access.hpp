#ifndef ACCESS_HPP
#define ACCESS_HPP

#include "declaration.hpp"
#include <memory>

template< class Key, class Value, class Compare >
typename rychkov::Map< Key, Value, Compare >::node_type*
    rychkov::Map< Key, Value, Compare >::fake_root() noexcept
{
  return getFakePointer(fake_left_, &node_type::left);
}

#endif
