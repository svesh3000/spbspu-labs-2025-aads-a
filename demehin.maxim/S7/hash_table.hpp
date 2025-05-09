#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include <functional>
//#include <dynamic_array.hpp>
#include <vector>

namespace demehin
{
  template < typename Key, typename T, typename Hash = std::hash< Key >, typename Equal = std::equal_to< Key > >
  class HashTable
  {
  public:
    HashTable() noexcept;
    

  private:
    enum class SlotState
    {
      EMPTY,
      OCCUPIED,
      DELETED
    };

    struct Slot
    {
      std::pair< Key, T > pair;
      SlotState state = SlotState::EMPTY;
    };

    std::vector< Slot > slots_;
    size_t item_cnt_;
    Hash hasher_;
    Equal equal_;
    static constexpr double max_load_factor_ = 0.7;
  };

  template< typename Key, typename T, typename Hash, typename Equal >
  HashTable< Key, T, Hash, Equal >::HashTable() noexcept:
    slots_(16),
    item_cnt_(0)
  {}
}

#endif
