#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include <cstddef>
#include <functional>
#include <utility>
#include <type_traits.hpp>

namespace rychkov
{
  template< class Member, class Base >
  size_t offsetOf(Member Base::* member)
  {
    return reinterpret_cast< char* >(std::addressof(static_cast< Base* >(nullptr)->*member))
        - static_cast< char* >(nullptr);
  }
  template< class Member, class Base >
  Base* getFakePointer(Member& fakeMember, Member Base::* member)
  {
    static size_t offset = offsetOf(member);
    return reinterpret_cast< Base* >(reinterpret_cast< char* >(std::addressof(fakeMember)) - offset);
  }

  template< class Key, class Value >
  struct MapNode
  {
    std::pair< Key, Value > data;
    MapNode* left = nullptr;
    MapNode* right = nullptr;
    MapNode* parent = nullptr;
    MapNode* second_part = nullptr;
  };

  template< class Key, class Value, bool isConst, bool isReversed >
  class MapIterator;

  template< class Key, class Value, class Compare = std::less<> >
  class Map
  {
  public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair< const Key, Value >;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using key_compare = Compare;

    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    using iterator = MapIterator< Key, Value, false, false >;
    using const_iterator = MapIterator< Key, Value, false, false >;
    using reverse_iterator = MapIterator< Key, Value, false, false >;
    using const_reverse_iterator = MapIterator< Key, Value, false, false >;

    struct value_compare
    {
      key_compare comp;
      bool operator()(const value_type& lhs, const value_type& rhs) const
      {
        return comp(lhs.first, rhs.first);
      }
    };

    Map() noexcept(std::is_nothrow_default_constructible< value_compare >::value);
    Map(const Map& rhs);
    Map(Map&& rhs) noexcept(std::is_nothrow_move_constructible< value_compare >::value);
    ~Map();
    Map& operator=(const Map& rhs);
    Map& operator=(Map&& rhs) noexcept(noexcept(swap(std::declval< Map >())));

    bool empty() const noexcept;
    size_type size() const noexcept;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;

    void clear();
    void swap(Map& rhs) noexcept(is_nothrow_swappable_v< value_type >);

    template< class... Args >
    std::pair< iterator, bool > emplace(Args... args);
    template< class... Args >
    iterator emplace_hint(const_iterator hint, Args... args);

    key_compare key_comp() const;
    value_compare value_comp() const;
    MapNode< Key, Value >* fake_root() noexcept;
    const MapNode< Key, Value >* fake_root() const noexcept;
  private:
    using node_type = MapNode< Key, Value >;
    node_type* fake_left_;
    node_type* fake_right_;
    node_type* fake_parent_;
    node_type* fake_second_part_;
    size_t size_;
    value_compare comp_;

    const_iterator find_hint(const key_type& key);
    void place_node(const_iterator hint, node_type* node);
  };
}

#endif
