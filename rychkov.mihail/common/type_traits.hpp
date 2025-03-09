#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace rychkov
{
  template< bool Logic1, bool... Logics >
  struct conjunction
  {
    enum: bool
    {
      value = Logic1 && conjunction< Logics... >::value
    };
  };
  template< bool Logic1 >
  struct conjunction< Logic1 >
  {
    enum: bool
    {
      value = Logic1
    };
  };
  template< bool... Logics >
  constexpr bool conjunction_v = conjunction< Logics... >::value;

  template< class T >
  using remove_cvref_t = std::remove_cv_t< std::remove_reference_t< T > >;
}

#endif
