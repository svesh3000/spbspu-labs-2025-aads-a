#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <functional>
#include <boost/hash2/xxhash.hpp>

namespace maslov
{
  template< class Key, class T, class Hash1 = std::hash< Key >, class Hash2 = boost::hash2::xxhash_64, class Equal = std::equal_to< Key > >
  struct HashTable
  {};
}

#endif
