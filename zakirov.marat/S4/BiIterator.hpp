#ifndef BIITERATOR_HPP
#define BIITERATOR_HPP
#include <BiNode.hpp>

namespace zakirov
{
  template< class K, class T >
  class BiIter: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    ~BiIter() = default;
    T & operator*() const;
    T * operator->() const;
    BiIter< K, T > & operator++();
    BiIter< K, T > operator++(int);
    BiIter< K, T > & operator--();
    BiIter< K, T > operator--(int);
    bool operator!=(const BiIter< K, T > &) const;
    bool operator==(const BiIter< K, T > &) const;
  private:
    BiIter(BiNode< K, T > * node);
    BiNode< K, T > * node_;
  };

  template< class K, class T >
  class CBiIter: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    ~CBiIter() = default;
    T & operator*() const;
    T * operator->() const;
    CBiIter< K, T > & operator++();
    CBiIter< K, T > operator++(int);
    CBiIter< K, T > & operator--();
    CBiIter< K, T > operator--(int);
    bool operator!=(const CBiIter< K, T > &) const;
    bool operator==(const CBiIter< K, T > &) const;
  private:
    CBiIter(BiNode< K, T > * node);
    BiNode< K, T > * node_;
  };
}

#endif
