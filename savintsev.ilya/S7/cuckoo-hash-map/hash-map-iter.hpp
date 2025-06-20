#ifndef HASH_MAP_ITER_HPP
#define HASH_MAP_ITER_HPP
#include <iterator>
#include <cassert>
#include <dynamic-array.hpp>

namespace savintsev
{
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  class HashMap;

  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  class FwdConstIterator;

  template< typename Key, typename T >
  class FwdIterator
  {
    friend class HashMap< Key, T, HS1, HS2, EQ >;
    friend class FwdConstIterator< Key, T, HS1, HS2, EQ >;
  private:
    Array< std::pair< std::pair< Key, T >, bool > > * tab1_ = nullptr;
    Array< std::pair< std::pair< Key, T >, bool > > * tab2_ = nullptr;
    size_t pos_ = 0;
    size_t capacity_ = 0;
    bool first_ = true;

    template< typename HS1, typename HS2, typename EQ >
    FwdIterator(HashMap< Key, T, HS1, HS2, EQ > * map, size_t pos, bool in_first_table);
    //FwdIterator(const FwdConstIterator< Key, T, HS1, HS2, EQ > & it);

    void skip_empty();
    bool is_valid() const;

  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::pair< Key, T >;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type &;

    FwdIterator() = default;

    reference operator*();
    pointer operator->();
    reference operator*() const;
    pointer operator->() const;

    FwdIterator & operator++();
    FwdIterator operator++(int);

    bool operator!=(const FwdIterator & rhs) const;
    bool operator==(const FwdIterator & rhs) const;
  };

  template< typename Key, typename T >
  template< typename HS1, typename HS2, typename EQ >
  FwdIterator< Key, T >::FwdIterator(HashMap< Key, T, HS1, HS2, EQ > * map, size_t pos, bool in_first_table):
    tab1_(nullptr),
    tab2_(nullptr),
    pos_(pos),
    capacity_(0),
    first_(in_first_table)
  {
    if (map)
    {
      tab1_ = std::addressof(map->t1_);
      tab2_ = std::addressof(map->t1_);
      skip_empty();
    }
  }
  template< typename Key, typename T >
  void FwdIterator< Key, T >::skip_empty()
  {
    while (first_ && (pos_ < capacity_) && (tab1_->[]))
    {
      ++pos_;
    }
    if ((pos_ >= capacity_) && first_)
    {
      first_ = false;
      pos_ = 0;
      while (pos_ < capacity_ && tab2_[pos_].second)
      {
        ++pos_;
      }
    }
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  FwdIterator< Key, T, HS1, HS2, EQ >::FwdIterator(const FwdConstIterator< Key, T, HS1, HS2, EQ > & it):
    tab1_(it.tab1_),
    tab2_(map.t2_),
    pos_(pos),
    capacity_(map.capacity_),
    first_(in_t1)
  {
    skip_empty();
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  bool FwdIterator< Key, T, HS1, HS2, EQ >::is_valid() const
  {
    return map_ && pos_ < map_->capacity_ && (first_ ? map_->t1_[pos_].second : map_->t2_[pos_].second);
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  typename FwdIterator< Key, T, HS1, HS2, EQ >::reference FwdIterator< Key, T, HS1, HS2, EQ >::operator*()
  {
    assert(is_valid());
    return first_ ? map_->t1_[pos_].first : map_->t2_[pos_].first;
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  typename FwdIterator< Key, T, HS1, HS2, EQ >::pointer FwdIterator< Key, T, HS1, HS2, EQ >::operator->()
  {
    assert(is_valid());
    return std::addressof(first_ ? map_->t1_[pos_].first : map_->t2_[pos_].first);
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  typename FwdIterator< Key, T, HS1, HS2, EQ >::reference FwdIterator< Key, T, HS1, HS2, EQ >::operator*() const
  {
    assert(is_valid());
    return first_ ? map_->t1_[pos_].first : map_->t2_[pos_].first;
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  typename FwdIterator< Key, T, HS1, HS2, EQ >::pointer FwdIterator< Key, T, HS1, HS2, EQ >::operator->() const
  {
    assert(is_valid());
    return std::addressof(first_ ? map_->t1_[pos_].first : map_->t2_[pos_].first);
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  FwdIterator< Key, T, HS1, HS2, EQ > & FwdIterator< Key, T, HS1, HS2, EQ >::operator++()
  {
    ++pos_;
    skip_empty();
    return *this;
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  FwdIterator< Key, T, HS1, HS2, EQ > FwdIterator< Key, T, HS1, HS2, EQ >::operator++(int)
  {
    FwdIterator< Key, T, HS1, HS2, EQ > result(*this);
    ++(*this);
    return result;
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  bool FwdIterator< Key, T, HS1, HS2, EQ >::operator!=(const FwdIterator & rhs) const
  {
    return !(*this == rhs);
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  bool FwdIterator< Key, T, HS1, HS2, EQ >::operator==(const FwdIterator & rhs) const
  {
    if (map_ || rhs.map_)
    {
      return map_ == rhs.map_ && pos_ == rhs.pos_ && first_ == rhs.first_;
    }
    return true;
  }
}

#endif
