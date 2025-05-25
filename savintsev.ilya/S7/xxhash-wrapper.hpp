#ifndef XXHASH_WRAPPER_HPP
#define XXHASH_WRAPPER_HPP
#include <boost/hash2/xxhash.hpp>
#include <boost/hash2/hash_append.hpp>

namespace savintsev
{
  template< typename Key >
  struct XXHash
  {
    size_t operator()(const Key & key) const
    {
      boost::hash2::xxhash_64 hasher;
      std::uint32_t v1 = 0x01020304;
      boost::hash2::hash_append(hasher, {}, v1);

      return hasher.result();
    }
  };
}

#endif
