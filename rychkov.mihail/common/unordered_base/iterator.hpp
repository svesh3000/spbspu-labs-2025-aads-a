#ifndef UNORDERED_BASE_ITERATOR_HPP
#define UNORDERED_BASE_ITERATOR_HPP

#include <iterator>

namespace rychkov
{
  template< class V, bool IsConst >
  class UnorderedBaseIterator
  {
  public:
    using value_type = V;
    using pointer = value_type*;
    using reference = value_type&;
    using difference_type = ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
  };
}

#endif
