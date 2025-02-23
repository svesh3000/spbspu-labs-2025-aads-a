#define BIDIRECTIONAL_ITERATOR_HPP
#define BIDIRECTIONAL_ITERATOR_HPP

#include <iterator>
#include <type_traits>

namespace rychkov
{
  template< class T >
  struct List;
  template< class T >
  struct node_t;

  template< class T, bool isConst, bool isReversed >
  class BidirectionalIterator
  {
  public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::bidirectional_iterator_tag;

    BidirectionalIterator() noexcept;

    BidirectionalIterator& operator++() noexcept;
    BidirectionalIterator operator++(int) noexcept;
    BidirectionalIterator& operator--() noexcept;
    BidirectionalIterator operator--(int) noexcept;

    typename std::enable_if< isConst, const reference >::type operator*() noexcept;
    reference operator*() const noexcept;
    typename std::enable_if< isConst, const pointer >::type operator->() noexcept;
    pointer operator->() const noexcept;
  private:
    friend class rychkov::List< T >;
    node_t* node_;
    BidirectionalIterator(node_* node) noexcept;
  };
}

#endif
