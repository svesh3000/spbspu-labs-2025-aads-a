#ifndef BIITERATOR_HPP
#define BIITERATOR_HPP
#include <BiNode.hpp>

namespace zakirov
{
  template< class K, class T >
  class BiIter: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    explicit BiIter() noexcept;

    std::pair< K, T > & operator*() noexcept;
    std::pair< K, T > * operator->() noexcept;
    BiIter< K, T > & operator++() noexcept;
    BiIter< K, T > operator++(int) noexcept;
    BiIter< K, T > & operator--() noexcept;
    BiIter< K, T > operator--(int) noexcept;
    bool operator!=(const BiIter< K, T > &) const noexcept;
    bool operator==(const BiIter< K, T > &) const noexcept;

  private:
    friend class BiTree< K, T >;
    explicit BiIter(BiNode< K, T > * node) noexcept;
    BiNode< K, T > * node_;
  };

  template< class K, class T >
  class CBiIter: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    explicit CBiIter() noexcept;

    std::pair< K, T > & operator*() const noexcept;
    std::pair< K, T > * operator->() const noexcept;
    CBiIter< K, T > & operator++() noexcept;
    CBiIter< K, T > operator++(int) noexcept;
    CBiIter< K, T > & operator--() noexcept;
    CBiIter< K, T > operator--(int) noexcept;
    bool operator!=(const CBiIter< K, T > &) const noexcept;
    bool operator==(const CBiIter< K, T > &) const noexcept;

  private:
    friend class BiTree< K, T >;
    explicit CBiIter(BiNode< K, T > * node) noexcept;
    BiNode< K, T > * node_;
  };
}

#endif
