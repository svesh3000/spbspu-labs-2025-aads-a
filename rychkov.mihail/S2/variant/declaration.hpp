#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include <algorithm>
#include "tools.hpp"

namespace rychkov
{
  template< class... Types >
  class Variant;

  template< class T, class... Types >
  T* get_if(Variant< Types... >* variant) noexcept;
  template< class T, class... Types >
  const T* get_if(const Variant< Types... >* variant) noexcept;
  template< size_t N, class... Types >
  variant_alternative_t< N, Types... >* get_if(Variant< Types... >* variant) noexcept;
  template< size_t N, class... Types >
  const variant_alternative_t< N, Types... >* get_if(const Variant< Types... >* variant) noexcept;

  template< class... Types >
  class Variant
  {
  public:
    template< class T0 = variant_alternative_t< 0, Types... > >
    Variant() noexcept(std::is_nothrow_default_constructible< T0 >::value);
    Variant(const Variant& rhs);
    Variant(Variant&& rhs) noexcept(is_nothrow_move_constructible_v);
    template< class T >
    Variant(T&& value);
    template< class T, class... Args >
    Variant(in_place_type_t< T >, Args&&... args);
    template< size_t N, class... Args >
    Variant(in_place_index_t< N >, Args&&... args);
    ~Variant();

    Variant& operator=(const Variant& rhs);
    Variant& operator=(Variant&& rhs) noexcept(is_nothrow_move_constructible_v);

    template< class T, class... Args >
    T& emplace(Args&&... args);
    template< size_t N, class... Args >
    variant_alternative_t< N, Types... >& emplace(Args&&... args);

    size_t index() const noexcept;
    bool valueless_by_exception() const noexcept;
  private:
    static constexpr bool is_nothrow_move_constructible_v = conjunction_v< std::is_trivially_move_constructible< Types >::value... >;
    static constexpr size_t size_ = std::max({sizeof(Types)...});

    using size_type = std::conditional_t< (size_ < 255), byte, size_t >;

    size_type active_;
    byte data_[size_];

    void copy(const Variant& rhs);
    void move(Variant&& rhs) noexcept(is_nothrow_move_constructible_v);
    void destruct();

    template< class T, class... Ts >
    friend T* rychkov::get_if(Variant< Ts... >* variant) noexcept;
    template< class T, class... Ts >
    friend const T* rychkov::get_if(const Variant* variant) noexcept;
    template< size_t N, class... Ts >
    friend variant_alternative_t< N, Ts... >* rychkov::get_if(Variant< Ts... >* variant) noexcept;
    template< size_t N, class... Ts >
    friend const variant_alternative_t< N, Ts... >* rychkov::get_if(const Variant* variant) noexcept;
  };

  class bad_variant_access;

  template< class T, class... Types >
  T& get(Variant< Types... >& variant);
  template< class T, class... Types >
  const T& get(const Variant< Types... >& variant);
  template< class T, class... Types >
  T&& get(Variant< Types... >&& variant);
  template< class T, class... Types >
  const T&& get(const Variant< Types... >&& variant);

  template< size_t N, class... Types >
  variant_alternative_t< N, Types... >& get(Variant< Types... >& variant);
  template< size_t N, class... Types >
  const variant_alternative_t< N, Types... >& get(const Variant< Types... >& variant);
  template< size_t N, class... Types >
  variant_alternative_t< N, Types... >&& get(Variant< Types... >&& variant);
  template< size_t N, class... Types >
  const variant_alternative_t< N, Types... >&& get(const Variant< Types... >&& variant);

  template< class T, class... Types >
  bool holds_alternative(const Variant< Types... >& variant) noexcept;
  constexpr size_t variant_npos = -1U;
}

#endif
