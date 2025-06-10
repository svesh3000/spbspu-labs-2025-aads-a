#ifndef HASH_VECTOR_HPP
#define HASH_VECTOR_HPP
#include <utility>
#include <cstddef>

namespace alymova
{
  namespace detail
  {
    template< class Key, class Value >
    struct HashNode
    {
      std::pair< Key, Value > data;
      size_t psl;

      const Key& get_key() const noexcept;
      void swap(HashNode< Key, Value >& other);
    };

    template< class Key, class Value >
    const Key& HashNode< Key, Value >::get_key() const noexcept
    {
      return data.first;
    }

    template< class Key, class Value >
    void HashNode< Key, Value >::swap(HashNode< Key, Value >& other)
    {
      std::swap(data, other.data);
      std::swap(psl, other.psl);
    }
  }
}

#endif
