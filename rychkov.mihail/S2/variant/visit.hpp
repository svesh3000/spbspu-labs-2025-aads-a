#ifndef VISIT_HPP
#define VISIT_HPP

#include "declaration.hpp"

#include <utility>
#include <functional.hpp>

namespace rychkov
{
  namespace details
  {
    template< class R, size_t... Actives, class F, class... Variants >
    R invoke_visit(F&& func, Variants&&... args)
    {
      return invoke_r< R >(func, get< Actives >(args)...);
    }
    template< class T, size_t... Lens >
    struct multidimensional_array
    {
      T data;
      constexpr T operator()() const
      {
        return data;
      }
    };
    template< class T, size_t Len, size_t... Lens >
    struct multidimensional_array< T, Len, Lens... >
    {
      multidimensional_array< T, Lens... > data[Len];
      template< class... Sizes >
      constexpr T operator()(size_t i, Sizes... sizes) const
      {
        return data[i](sizes...);
      }
    };

    template< class R, class F, class... Variants, size_t... Actives, size_t... GenSequence >
    constexpr multidimensional_array< R(*)(F, Variants...), sizeof...(GenSequence) >
      generate_visit_vtable(std::index_sequence< Actives... >,
          std::index_sequence< GenSequence... >, std::index_sequence<>)
    {
      return {{ {&invoke_visit< R, Actives..., GenSequence >}... }};
    }
    template< class R, class F, class... Variants, size_t... Actives, size_t... GenSequence,
          size_t NextSize, size_t... Sizes >
    constexpr multidimensional_array< R(*)(F, Variants...), sizeof...(GenSequence), NextSize, Sizes... >
      generate_visit_vtable(std::index_sequence< Actives... >, std::index_sequence< GenSequence... >,
          std::index_sequence< NextSize, Sizes... >)
    {
      return {{generate_visit_vtable< R, F, Variants... >(std::index_sequence< Actives..., GenSequence >(),
                std::make_index_sequence< NextSize >(), std::index_sequence< Sizes... >())...}};
    }
  }
}

template< class R, class F, class First, class... Variants >
R rychkov::visit(F&& func, First&& first, Variants&&... args)
{
  using array_type = details::multidimensional_array< R(*)(F&&, First, Variants...),
        variant_size_v< remove_cvref_t< First > >,
        variant_size_v< remove_cvref_t< Variants > >... >;
  static constexpr array_type vtable =
      details::generate_visit_vtable< R, F&&, First, Variants... >(std::index_sequence<>(),
        std::make_index_sequence< variant_size_v< remove_cvref_t< First > > >(),
        std::index_sequence< variant_size_v< remove_cvref_t< Variants > >... >());
  return vtable(first.index(), args.index()...)(std::forward< F >(func),
        std::forward< First >(first), std::forward< Variants >(args)...);
}
template< class R, class F >
R rychkov::visit(F&& func)
{
  return invoke_r< R >(std::forward< F >(func));
}

template< class F, class... Variants >
rychkov::invoke_result_t< F, rychkov::variant_alternative_t< 0, rychkov::remove_cvref_t< Variants > >... >
    rychkov::visit(F&& func, Variants&&... args)
{
  using return_type = rychkov::invoke_result_t< F,
        rychkov::variant_alternative_t< 0, remove_cvref_t< Variants > >... >;
  return visit< return_type >(std::forward< F >(func), std::forward< Variants >(args)...);
}

#endif
