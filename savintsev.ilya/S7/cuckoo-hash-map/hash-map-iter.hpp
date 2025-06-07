#ifndef HASH_MAP_ITER_HPP
#define HASH_MAP_ITER_HPP
#include <iterator>
#include <cassert>

namespace savintsev
{
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  class HashMap;

  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  class FwdConstIterator;

  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  class FwdIterator
  {
    friend class HashMap< Key, T, HS1, HS2, EQ >;
    friend class FwdConstIterator< Key, T, HS1, HS2, EQ >;
  private:
    HashMap< Key, T, HS1, HS2, EQ > * map_ = nullptr;
    size_t pos_ = 0;
    bool in_t1_ = true;

    FwdIterator(HashMap< Key, T, HS1, HS2, EQ > & map, size_t pos, bool in_t1);

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

  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  FwdIterator< Key, T, HS1, HS2, EQ >::FwdIterator(HashMap< Key, T, HS1, HS2, EQ > & map, size_t pos, bool in_t):
    map_(std::addressof(map)),
    pos_(pos),
    in_t1_(in_t)
  {
    skip_empty();
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  void FwdIterator< Key, T, HS1, HS2, EQ >::skip_empty()
  {
    while (in_t1_ && (pos_ < map_->capacity_) && (!map_->t1_[pos_].second))
    {
      ++pos_;
    }
    if ((pos_ >= map_->capacity_) && in_t1_)
    {
      in_t1_ = false;
      pos_ = 0;
      while ((pos_ < map_->capacity_) && !map_->t2_[pos_].second)
      {
        ++pos_;
      }
    }
    if (!is_valid())
    {
      map_ = nullptr;
    }
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  bool FwdIterator< Key, T, HS1, HS2, EQ >::is_valid() const
  {
    return map_ && pos_ < map_->capacity_ && (in_t1_ ? map_->t1_[pos_].second : map_->t2_[pos_].second);
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  typename FwdIterator< Key, T, HS1, HS2, EQ >::reference FwdIterator< Key, T, HS1, HS2, EQ >::operator*()
  {
    assert(is_valid());
    return in_t1_ ? map_->t1_[pos_].first : map_->t2_[pos_].first;
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  typename FwdIterator< Key, T, HS1, HS2, EQ >::pointer FwdIterator< Key, T, HS1, HS2, EQ >::operator->()
  {
    assert(is_valid());
    return std::addressof(in_t1_ ? map_->t1_[pos_].first : map_->t2_[pos_].first);
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  typename FwdIterator< Key, T, HS1, HS2, EQ >::reference FwdIterator< Key, T, HS1, HS2, EQ >::operator*() const
  {
    assert(is_valid());
    return in_t1_ ? map_->t1_[pos_].first : map_->t2_[pos_].first;
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  typename FwdIterator< Key, T, HS1, HS2, EQ >::pointer FwdIterator< Key, T, HS1, HS2, EQ >::operator->() const
  {
    assert(is_valid());
    return std::addressof(in_t1_ ? map_->t1_[pos_].first : map_->t2_[pos_].first);
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
      return map_ == rhs.map_ && pos_ == rhs.pos_ && in_t1_ == rhs.in_t1_;
    }
    return true;
  }
}

#endif
