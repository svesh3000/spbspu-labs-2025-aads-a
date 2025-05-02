#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include <functional>
#include <memory>
#include <initializer_list>
#include <type_traits.hpp>
#include "node.hpp"
#include "iterator.hpp"

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
  template< class Cmp, class = void >
  struct is_transparent: std::false_type
  {};
  template< class Cmp >
  struct is_transparent< Cmp, void_t< typename Cmp::is_transparent > >: std::true_type
  {};
  template< class Cmp >
  constexpr bool is_transparent_v = is_transparent< Cmp >::value;

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

    using iterator = MapIterator< value_type, N, false, false >;
    using const_iterator = MapIterator< value_type, N, true, false >;
    using reverse_iterator = MapIterator< value_type, N, false, true >;
    using const_reverse_iterator = MapIterator< value_type, N, true, true >;

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
    Map(std::initializer_list< value_type > init);
    template< class InputIt >
    Map(InputIt from, InputIt to);
    ~Map();
    Map& operator=(const Map& rhs);
    Map& operator=(Map&& rhs) noexcept(noexcept(swap(std::declval< Map >())));

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type maxsize() const noexcept;

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

    mapped_type& at(const key_type& key);
    const mapped_type& at(const key_type& key) const;
    template< class K >
    mapped_type& at(std::enable_if_t< is_transparent_v< key_compare >, const K& > key);
    template< class K >
    const mapped_type& at(std::enable_if_t< is_transparent_v< key_compare >, const K& > key) const;
    mapped_type& operator[](const key_type& key);
    mapped_type& operator[](key_type&& key);

    iterator lower_bound(const key_type& key);
    const_iterator lower_bound(const key_type& key) const;
    iterator upper_bound(const key_type& key);
    const_iterator upper_bound(const key_type& key) const;
    iterator find(const key_type& key);
    const_iterator find(const key_type& key) const;
    bool contains(const key_type& key) const;
    std::pair< iterator, iterator > equal_range(const key_type& key);
    std::pair< const_iterator, const_iterator > equal_range(const key_type& key) const;
    size_type count(const key_type& key) const;

    template< class K >
    iterator lower_bound(std::enable_if_t< is_transparent_v< key_compare >, const K& > key);
    template< class K >
    const_iterator lower_bound(std::enable_if_t< is_transparent_v< key_compare >, const K& > key) const;
    template< class K >
    iterator upper_bound(std::enable_if_t< is_transparent_v< key_compare >, const K& > key);
    template< class K >
    const_iterator upper_bound(std::enable_if_t< is_transparent_v< key_compare >, const K& > key) const;
    template< class K >
    iterator find(std::enable_if_t< is_transparent_v< key_compare >, const K& > key);
    template< class K >
    const_iterator find(std::enable_if_t< is_transparent_v< key_compare >, const K& > key) const;
    template< class K >
    bool contains(std::enable_if_t< is_transparent_v< key_compare >, const K& > key) const;
    template< class K >
    std::pair< iterator, iterator > equal_range(std::enable_if_t< is_transparent_v< key_compare >, const K& > key);
    template< class K >
    std::pair< const_iterator, const_iterator > equal_range
        (std::enable_if_t< is_transparent_v< key_compare >, const K& > key) const;
    template< class K >
    size_type count(std::enable_if_t< is_transparent_v< key_compare >, const K& > key) const;

    void clear();
    void swap(Map& rhs) noexcept(is_nothrow_swappable_v< value_compare >);

    iterator erase(const_iterator pos);
    iterator erase(const_iterator from, const_iterator to);
    size_type erase(const key_type& key);
    template< class K >
    size_type erase(const K& key);

    template< class... Args >
    std::pair< iterator, bool > emplace(Args&&... args);
    template< class... Args >
    iterator emplace_hint(const_iterator hint, Args&&... args);

    key_compare key_comp() const;
    value_compare value_comp() const;
  private:
    static constexpr size_t node_capacity = N;
    static constexpr size_t node_middle = (node_capacity + 1) / 2;
    using node_type = MapNode< value_type, node_capacity >;
    using node_size_type = typename node_type::size_type;

    value_compare comp_;
    node_type* cached_begin_ = nullptr;
    node_type* cached_rbegin_ = nullptr;
    size_t size_;

    node_type*const fake_parent_ = nullptr;
    node_type* fake_children_[node_capacity + 1];
    const node_size_type fake_size_;

    node_type* fake_root() const noexcept;
    void devide(node_type& left, node_type& right, node_size_type ins_point, node_type& to_insert);
    void correct_emplace_result(node_type& left, node_type& right, node_size_type ins_point, const_iterator& hint);
    void destroy_subtree(node_type* node);
    template< class K >
    const_iterator lower_bound_impl(const K& key) const;
    template< class K >
    const_iterator upper_bound_impl(const K& key) const;
  };
}

#endif
