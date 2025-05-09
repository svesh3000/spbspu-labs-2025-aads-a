#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include <functional>
#include <dynamic_array.hpp>


namespace demehin
{
  template < typename Key, typename T, typename Hash = std::hash< Key >, typename Equal = std::equal_to< Key > >
  class HashTable
  {
  public:
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

    DynamicArray< Slot > slots;
    size_t item_cnt;
    Hash hasher;
    Equal equal;
    constexpr double max_load_factor = 0.7;
  }
}

#endif
