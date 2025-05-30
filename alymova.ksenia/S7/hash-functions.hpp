#ifndef HASH_FUNCTIONS_HPP
#define HASH_FUNCTIONS_HPP

#include <boost/container_hash/hash.hpp>
#include <boost/hash2/siphash.hpp>
#include <boost/hash2/hash_append.hpp>
#include <boost/hash2/get_integral_result.hpp>

#include <cstddef>

namespace alymova
{
  template< class T, class H = boost::hash2::siphash_64 >
  struct Hasher
  {
    size_t operator()(const T& value) const
    {
      H hasher{};
      boost::hash2::hash_append(hasher, {}, value);
      return boost::hash2::get_integral_result< size_t >(hasher);
    }
  };

  struct PairHasher
  {
    std::size_t operator()(const std::pair< std::string, std::string >& s) const
    {
      size_t hash = Hasher< std::string >{}(s.first);
      boost::hash_combine(hash, s.second);
      return hash;
    }
  };
}

#endif
