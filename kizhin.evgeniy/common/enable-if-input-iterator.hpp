#ifndef SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_COMMON_ENABLE_IF_INPUT_ITERATOR
#define SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_COMMON_ENABLE_IF_INPUT_ITERATOR

#include <iterator>
#include <type_traits>

namespace kizhin {
  namespace detail {
    template < typename... >
    using void_t = void;

    template < typename T, typename = void >
    struct is_input_iterator: std::false_type
    {
    };

    template < typename T >
    using iter_category = typename std::iterator_traits< T >::iterator_category;

    template < typename T >
    struct is_input_iterator< T, void_t< iter_category< T > > >:
      std::is_base_of< std::input_iterator_tag, iter_category< T > >
    {
    };

    template < typename It >
    using enable_if_input_it_impl = std::enable_if< is_input_iterator< It >::value, int >;

    template < typename It >
    using enable_if_input_iterator = typename enable_if_input_it_impl< It >::type;

  }
}

#endif

