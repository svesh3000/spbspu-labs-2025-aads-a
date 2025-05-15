#ifndef MAP_HPP
#define MAP_HPP

#include "map_base.hpp"

namespace rychkov
{
  template< class K, class T, class C = std::less<>, size_t N = 2 >
  class Map: public MapBase< K, T, C, N, false, true >
  {
  private:
    using Base = MapBase< K, T, C, N, false, true >;
  public:
    using key_type = typename Base::key_type;
    using mapped_type = typename Base::mapped_type;
    using value_type = typename Base::value_type;
    using size_type = typename Base::size_type;
    using difference_type = typename Base::difference_type;
    using key_compare = typename Base::key_compare;
    using value_compare = typename Base::value_compare;

    using reference = typename Base::reference;
    using const_reference = typename Base::const_reference;
    using pointer = typename Base::pointer;
    using const_pointer = typename Base::const_pointer;

    using iterator = typename Base::iterator;
    using const_iterator = typename Base::const_iterator;
    using reverse_iterator = typename Base::reverse_iterator;
    using const_reverse_iterator = typename Base::const_reverse_iterator;

    Map() = default;
    Map(std::initializer_list< value_type > init):
      Base(init)
    {}
    template< class InputIt >
    Map(InputIt from, InputIt to):
      Base(from, to)
    {}

  private:
    template< class R, class K1 >
    using transparent_compare_key = details::transparent_compare_key< R, K1, C, const_iterator >;

  public:
    mapped_type& at(const key_type& key);
    const mapped_type& at(const key_type& key) const;
    template< class K1 >
    transparent_compare_key< mapped_type&, K1 > at(const K1& key);
    template< class K1 >
    transparent_compare_key< const mapped_type&, K1 > at(const K1& key) const;

    mapped_type& operator[](const key_type& key);
    mapped_type& operator[](key_type&& key);
    template< class K1 >
    transparent_compare_key< mapped_type&, K1 > operator[](K1&& key);
  };
  template< class K, class T, class C = std::less<>, size_t N = 2 >
  using MultiMap = MapBase< K, T, C, N, false, true >;
}

template< class K, class T, class C, size_t N >
typename rychkov::Map< K, T, C, N >::mapped_type&
    rychkov::Map< K, T, C, N >::at(const key_type& key)
{
  iterator temp = this->find(key);
  if (temp == this->end())
  {
    throw std::out_of_range("at index out of range");
  }
  return temp->second;
}
template< class K, class T, class C, size_t N >
const typename rychkov::Map< K, T, C, N >::mapped_type&
    rychkov::Map< K, T, C, N >::at(const key_type& key) const
{
  const_iterator temp = this->find(key);
  if (temp == this->end())
  {
    throw std::out_of_range("at index out of range");
  }
  return temp->second;
}
template< class K, class T, class C, size_t N >
template< class K1 >
typename rychkov::Map< K, T, C, N >::transparent_compare_key< typename rychkov::Map< K, T, C, N >::mapped_type&, K1 >
    rychkov::Map< K, T, C, N >::at(const K1& key)
{
  iterator temp = this->find(key);
  if (temp == this->end())
  {
    throw std::out_of_range("at index out of range");
  }
  return temp->second;
}
template< class K, class T, class C, size_t N >
template< class K1 >
typename rychkov::Map< K, T, C, N >::transparent_compare_key
    < const typename rychkov::Map< K, T, C, N >::mapped_type&, K1 >
    rychkov::Map< K, T, C, N >::at(const K1& key) const
{
  const_iterator temp = this->find(key);
  if (temp == this->end())
  {
    throw std::out_of_range("at index out of range");
  }
  return temp->second;
}
template< class K, class T, class C, size_t N >
typename rychkov::Map< K, T, C, N >::mapped_type& rychkov::Map< K, T, C, N >::operator[](const key_type& key)
{
  iterator temp = this->find(key);
  if (temp == this->end())
  {
    return this->try_emplace(key).first->second;
  }
  return temp->second;
}
template< class K, class T, class C, size_t N >
typename rychkov::Map< K, T, C, N >::mapped_type& rychkov::Map< K, T, C, N >::operator[](key_type&& key)
{
  iterator temp = this->find(key);
  if (temp == this->end())
  {
    return this->try_emplace(std::move(key)).first->second;
  }
  return temp->second;
}
template< class K, class T, class C, size_t N >
template< class K1 >
typename rychkov::Map< K, T, C, N >::transparent_compare_key< typename rychkov::Map< K, T, C, N >::mapped_type&, K1 >
    rychkov::Map< K, T, C, N >::operator[](K1&& key)
{
  iterator temp = this->find(key);
  if (temp == this->end())
  {
    return this->try_emplace(std::forward< K1 >(key)).first->second;
  }
  return temp->second;
}

#endif
