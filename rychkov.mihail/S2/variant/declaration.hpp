#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include <functional.hpp>
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
  nth_type_t< N, Types... >* get_if(Variant< Types... >* variant) noexcept;
  template< size_t N, class... Types >
  const nth_type_t< N, Types... >* get_if(const Variant< Types... >* variant) noexcept;

  template< class... Types >
  class Variant: private details::VariantBaseAlias< Types... >
  {
  public:
    Variant() = default;
    Variant(const Variant& rhs) = default;
    Variant(Variant&& rhs) = default;
    template< class T, class... Args >
    explicit Variant(in_place_type_t< T >, Args&&... args);
    template< size_t N, class... Args >
    explicit Variant(in_place_index_t< N >, Args&&... args);
    template< class T,
          size_t RealTypeId = resolve_overloaded_construct_v< T, Types... >,
          class = std::enable_if_t< RealTypeId != sizeof...(Types) >,
          class RealType = nth_type_t< RealTypeId, Types... >,
          class = std::enable_if_t< exactly_once< RealType, Types... > > >
    Variant(T&& value);
    ~Variant() = default;

    Variant& operator=(const Variant& rhs) = default;
    Variant& operator=(Variant&& rhs) = default;
    template< class T,
          size_t RealTypeId = resolve_overloaded_construct_v< T, Types... >,
          class = std::enable_if_t< RealTypeId != sizeof...(Types) >,
          class RealType = nth_type_t< RealTypeId, Types... >,
          class = std::enable_if_t< exactly_once< RealType, Types... > > >
    Variant& operator=(T&& rhs) noexcept(std::is_nothrow_constructible< RealType, T >::value
          && std::is_nothrow_assignable< RealType, T >::value);

    template< class T, class... Args >
    T& emplace(Args&&... args);
    template< size_t N, class... Args >
    nth_type_t< N, Types... >& emplace(Args&&... args);

    size_t index() const noexcept;
    bool valueless_by_exception() const noexcept;
  private:
    template< size_t N, class... Ts >
    friend nth_type_t< N, Ts... >* rychkov::get_if(Variant< Ts... >* variant) noexcept;
    template< size_t N, class... Ts >
    friend const nth_type_t< N, Ts... >* rychkov::get_if(const Variant* variant) noexcept;
  };

  template< class T, class... Types >
  T& get(Variant< Types... >& variant);
  template< class T, class... Types >
  const T& get(const Variant< Types... >& variant);
  template< class T, class... Types >
  T&& get(Variant< Types... >&& variant);
  template< class T, class... Types >
  const T&& get(const Variant< Types... >&& variant);

  template< size_t N, class... Types >
  nth_type_t< N, Types... >& get(Variant< Types... >& variant);
  template< size_t N, class... Types >
  const nth_type_t< N, Types... >& get(const Variant< Types... >& variant);
  template< size_t N, class... Types >
  nth_type_t< N, Types... >&& get(Variant< Types... >&& variant);
  template< size_t N, class... Types >
  const nth_type_t< N, Types... >&& get(const Variant< Types... >&& variant);

  template< class T, class... Types >
  bool holds_alternative(const Variant< Types... >& variant) noexcept;

  class bad_variant_access;
  namespace details
  {
    void throw_bad_variant_access(const char* message);
    void throw_bad_variant_access(bool valueless);
  }

  template< class R, class F, class First, class... Variants >
  R visit(F&& func, First&& first, Variants&&... args);
  template< class R, class F >
  R visit(F&& func);
  template< class F, class... Variants >
  invoke_result_t< F, variant_alternative_t< 0, Variants >... > visit(F&& func, Variants&&... args);
}

#endif
