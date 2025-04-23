#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include <functional>
#include <memory>
#include <type_traits.hpp>
#include "node.hpp"

namespace rychkov
{
  template< class Member, class Base >
  size_t offsetOf(const Member Base::* member)
  {
    return reinterpret_cast< const char* >(std::addressof(static_cast< Base* >(nullptr)->*member))
        - static_cast< const char* >(nullptr);
  }
  template< class Member, class Base >
  Base* getFakePointer(const Member& fakeMember, const Member Base::* member)
  {
    static size_t offset = offsetOf(member);
    auto clear_p = const_cast< Member* >(std::addressof(fakeMember));
    return reinterpret_cast< Base* >(reinterpret_cast< char* >(clear_p) - offset);
  }

  template< class Key, class Mapped, size_t N, bool isConst, bool isReversed >
  class MapIterator;

  template< class Key, class Mapped, class Compare = std::less<>, size_t N = 2 >
  class Map
  {
  public:
    using key_type = Key;
    using mapped_type = Mapped;
    using value_type = std::pair< const Key, Mapped >;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using key_compare = Compare;

    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    using iterator = MapIterator< key_type, mapped_type, N, false, false >;
    using const_iterator = MapIterator< key_type, mapped_type, N, true, false >;
    using reverse_iterator = MapIterator< key_type, mapped_type, N, false, true >;
    using const_reverse_iterator = MapIterator< key_type, mapped_type, N, true, true >;

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
    void swap(Map& rhs) noexcept(is_nothrow_swappable_v< value_compare >);

    template< class... Args >
    std::pair< iterator, bool > emplace(Args... args);
    template< class... Args >
    iterator emplace_hint(const_iterator hint, Args&&... args);

    key_compare key_comp() const;
    value_compare value_comp() const;
    static constexpr size_t node_capacity = N;
    using node_type = MapNode< key_type, mapped_type, node_capacity >;
    using node_size_type = typename node_type::size_type;
    node_type* fake_root() const noexcept;
  private:
    const node_size_type fake_size_;
    const node_size_type fake_real_places_[node_capacity];
    node_type* fake_parent_ = nullptr;
    node_type* fake_children_[node_capacity + 1];

    node_type* cached_begin_ = nullptr;
    node_type* cached_rbegin_ = nullptr;
    size_t size_;
    value_compare comp_;

    const_iterator find_hint(const key_type& key);
    void destroy_subtree(node_type* node);
  };
}

#endif
