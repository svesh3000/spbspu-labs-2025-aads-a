#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include "union_base.hpp"
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
  class Variant: private details::VariantBaseAlias< Types... >
  {
  public:
    Variant() = default;
    Variant(const Variant& rhs) = default;
    Variant(Variant&& rhs) = default;
    template< class T >
    Variant(T&& value);
    template< class T, class... Args >
    Variant(in_place_type_t< T >, Args&&... args);
    template< size_t N, class... Args >
    Variant(in_place_index_t< N >, Args&&... args);
    ~Variant() = default;

    Variant& operator=(const Variant& rhs) = default;
    Variant& operator=(Variant&& rhs) = default;

    template< class T, class... Args >
    T& emplace(Args&&... args);
    template< size_t N, class... Args >
    variant_alternative_t< N, Types... >& emplace(Args&&... args);

    size_t index() const noexcept;
    bool valueless_by_exception() const noexcept;
  private:
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
}

#endif
