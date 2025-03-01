#ifndef SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S1_ENABLE_IF_INPUT_ITERATOR
#define SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S1_ENABLE_IF_INPUT_ITERATOR

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
    struct is_input_iterator< T,
        void_t< typename std::iterator_traits< T >::iterator_category > >:
      std::is_base_of< std::input_iterator_tag,
          typename std::iterator_traits< T >::iterator_category >
    {
    };

    template < typename It >
    using enable_if_input_iterator =
        typename std::enable_if< is_input_iterator< It >::value, int >::type;
  }
}

#endif

