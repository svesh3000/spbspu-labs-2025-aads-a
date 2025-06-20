#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP
#include <initializer_list>
#include <iterator>
#include <dynamic-array.hpp>
#include <boost/hash2/xxhash.hpp>
#include "hash-wrapper.hpp"
//#include "hash-map-iter.hpp"
//#include "hash-map-citer.hpp"

namespace savintsev
{
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  class FwdIter;

  template
  <
    typename Key,
    typename T,
    typename HS1 = std::hash< Key >,
    typename HS2 = Hash< Key, boost::hash2::xxhash_64 >,
    typename EQ = std::equal_to<>
  >
  class HashMap
  {
  public:
    friend FwdConstIterator< Key, T, HS1, HS2, EQ >;

    using iterator = FwdIter< Key, T, HS1, HS2, EQ >;
    using const_iterator = FwdConstIterator< Key, T, HS1, HS2, EQ >;

    HashMap();
    HashMap(size_t size);
    template< class InputIterator >
    HashMap(InputIterator first, InputIterator last);
    HashMap(std::initializer_list< std::pair< Key, T > > il);

    size_t size() const;
    size_t capacity() const;
    bool empty() const noexcept;

    void clear() noexcept;
    void swap(HashMap & rhs);

    T & at(const Key & k);
    const T & at(const Key & k) const;

    T & operator[](const Key & k);
    T & operator[](Key && k );

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    iterator erase(const_iterator position);
    size_t erase(const Key & k);
    iterator erase(const_iterator fst, const_iterator last);

    template< class... Args >
    std::pair< iterator, bool > emplace(Args &&... args);
    template< class... Args >
    iterator emplace_hint(const_iterator hint, Args &&... args);

    std::pair< iterator, bool > insert(const std::pair< Key, T > & val);
    iterator insert(const_iterator hint, const std::pair< Key, T > & val);
    template< class InputIterator >
    void insert(InputIterator first, InputIterator last);

    iterator find(const Key & k);
    const_iterator find(const Key & k) const;

    float load_factor() const noexcept;
    float max_load_factor() const noexcept;
    void max_load_factor(float z);

    void rehash(size_t n);

    class FwdIter
    {
    private:
      size_t pos_ = 0;
      bool first_ = true;

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

      FwdIter & operator++();
      FwdIter operator++(int);

      bool operator!=(const FwdIter & rhs) const;
      bool operator==(const FwdIter & rhs) const;
    };

  private:

    Array< std::pair< std::pair< Key, T >, bool > > t1_;
    Array< std::pair< std::pair< Key, T >, bool > > t2_;

    size_t capacity_;
    size_t size_ = 0;

    static constexpr size_t MAX_ITERATIONS = 100;
    
    double max_load_factor_ = 0.75;

    T & insert_data(const Key & k);
    bool lookup_data(const Key & k) const;
    std::pair< T &, bool > get_data(const Key & k) const;
  };

  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  HashMap< Key, T, HS1, HS2, EQ >::HashMap():
    HashMap(10)
  {}
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  HashMap< Key, T, HS1, HS2, EQ >::HashMap(size_t size):
    t1_(size),
    t2_(size),
    capacity_(size)
  {
    for (size_t i = 0; i < capacity_; ++i)
    {
      t1_[i].second = true;
      t2_[i].second = true;
    }
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  template< class InputIterator >
  HashMap< Key, T, HS1, HS2, EQ >::HashMap(InputIterator first, InputIterator last):
    HashMap(10)
  {
    insert(first, last);
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  HashMap< Key, T, HS1, HS2, EQ >::HashMap(std::initializer_list< std::pair< Key, T > > il):
    HashMap(il.begin(), il.end())
  {}
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  size_t HashMap< Key, T, HS1, HS2, EQ >::size() const
  {
    return size_;
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  size_t HashMap< Key, T, HS1, HS2, EQ >::capacity() const
  {
    return (capacity_ * 2);
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  bool HashMap< Key, T, HS1, HS2, EQ >::empty() const noexcept
  {
    return size_ == 0;
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  void HashMap< Key, T, HS1, HS2, EQ >::clear() noexcept
  {
    for (size_t i = 0; i < capacity_; ++i)
    {
      if (!t1_[i].second)
      {
        t1_[i].second = true;
      }
      if (!t2_[i].second)
      {
        t2_[i].second = true;
      }
    }

    size_ = 0;
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  void HashMap< Key, T, HS1, HS2, EQ >::swap(HashMap< Key, T, HS1, HS2, EQ > & rhs)
  {
    t1_.swap(rhs.t1_);
    t2_.swap(rhs.t2_);
    std::swap(capacity_, rhs.capacity_);
    std::swap(size_, rhs.size_);
    std::swap(max_load_factor_, rhs.max_load_factor_);
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  T & HashMap< Key, T, HS1, HS2, EQ >::at(const Key & k)
  {
    auto data = get_data(k);
    if (data.second)
    {
      return data.first;
    }
    throw std::out_of_range("hashmap: at failed: no such item");
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  const T & HashMap< Key, T, HS1, HS2, EQ >::at(const Key & k) const
  {
    auto data = get_data(k);
    if (data.second)
    {
      return data.first;
    }
    throw std::out_of_range("hashmap: at failed: no such item");
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  T & HashMap< Key, T, HS1, HS2, EQ >::operator[](const Key & k)
  {
    auto data = get_data(k);
    if (data.second)
    {
      return data.first;
    }
    return insert_data(k);
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  T & HashMap< Key, T, HS1, HS2, EQ >::operator[](Key && k)
  {
    auto data = get_data(k);
    if (data.second)
    {
      return data.first;
    }
    return insert_data(k);
  }
  template< typename K, typename T, typename HS1, typename HS2, typename EQ >
  typename HashMap< K, T, HS1, HS2, EQ >::iterator HashMap< K, T, HS1, HS2, EQ >::begin() noexcept
  {
    return iterator(*this, 0, true);
  }
  template< typename K, typename T, typename HS1, typename HS2, typename EQ >
  typename HashMap< K, T, HS1, HS2, EQ >::const_iterator HashMap< K, T, HS1, HS2, EQ >::begin() const noexcept
  {
    return const_iterator(*this, 0, true);
  }
  template< typename K, typename T, typename HS1, typename HS2, typename EQ >
  typename HashMap< K, T, HS1, HS2, EQ >::const_iterator HashMap< K, T, HS1, HS2, EQ >::cbegin() const noexcept
  {
    return const_iterator(*this, 0, true);
  }
  template< typename K, typename T, typename HS1, typename HS2, typename EQ >
  typename HashMap< K, T, HS1, HS2, EQ >::iterator HashMap< K, T, HS1, HS2, EQ >::end() noexcept
  {
    return iterator{capacity_, false};
  }
  template< typename K, typename T, typename HS1, typename HS2, typename EQ >
  typename HashMap< K, T, HS1, HS2, EQ >::const_iterator HashMap< K, T, HS1, HS2, EQ >::end() const noexcept
  {
    return const_iterator();
  }
  template< typename K, typename T, typename HS1, typename HS2, typename EQ >
  typename HashMap< K, T, HS1, HS2, EQ >::const_iterator HashMap< K, T, HS1, HS2, EQ >::cend() const noexcept
  {
    return const_iterator();
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  size_t HashMap< Key, T, HS1, HS2, EQ >::erase(const Key & k)
  {
    Key current_key = k;

    size_t h1 = HS1{}(current_key) % capacity_;
    if (!t1_[h1].second)
    {
      Key old_key = t1_[h1].first.first;
      if (EQ{}(current_key, old_key))
      {
        t1_[h1].second = true;
        --size_;
        return 1ull;
      }
    }

    size_t h2 = HS2{}(current_key) % capacity_;
    if (!t2_[h2].second)
    {
      Key old_key = t2_[h2].first.first;
      if (EQ{}(current_key, old_key))
      {
        t2_[h2].second = true;
        --size_;
        return 1ull;
      }
    }

    return 0ull;
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  typename HashMap< Key, T, HS1, HS2, EQ >::iterator HashMap< Key, T, HS1, HS2, EQ >::erase(const_iterator position)
  {
    if (!position.is_valid())
    {
      return iterator();
    }
    if (position.in_t1_)
    {
      t1_[position.pos_].second = true;
      --size_;
      return iterator(*this, position);
    }
    t2_[position.pos_].second = true;
    --size_;
    return iterator(*this, position, false);
  }
  template< typename K, typename T, typename H, typename N, typename E >
  typename HashMap< K, T, H, N, E >::iterator HashMap< K, T, H, N, E >::erase(const_iterator fst, const_iterator last)
  {
    if (!fst.is_valid())
    {
      return iterator();
    }
    for (auto it = fst; it != last; ++it)
    {
      erase(it);
    }
    return iterator(*this, last);
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  template< class... Args >
  std::pair
  <
    typename HashMap< Key, T, HS1, HS2, EQ >::iterator,
    bool
  >
  HashMap< Key, T, HS1, HS2, EQ >::emplace(Args &&... args)
  {
    std::pair< Key, T > temp(std::forward< Args >(args)...);

    auto it = find(temp.first);
    if (it != end())
    {
      return {it, false};
    }

    T & inserted = insert_data(temp.first);
    inserted = std::move(temp.second);
    return {find(temp.first), true};
  }
  template< typename K, typename T, typename A, typename B, typename E >
  template< class... X >
  typename HashMap< K, T, A, B, E >::iterator HashMap< K, T, A, B, E >::emplace_hint(const_iterator hint, X &&... args)
  {
    std::pair< K, T > temp(std::forward< X >(args)...);

    auto it = find(temp.first);
    if (it != end())
    {
      return {it, false};
    }

    T & inserted = insert_data(temp.first);
    inserted = std::move(temp.second);
    return {find(temp.first), true};
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  std::pair
  <
    typename HashMap< Key, T, HS1, HS2, EQ >::iterator,
    bool
  >
  HashMap< Key, T, HS1, HS2, EQ >::insert(const std::pair< Key, T > & val)
  {
    auto it = find(val.first);
    if (it != end())
    {
      return {it, false};
    }

    insert_data(val.first) = val.second;
    return {find(val.first), true};
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  typename HashMap< Key, T, HS1, HS2, EQ >::iterator HashMap< Key, T, HS1, HS2, EQ >::insert(const_iterator hint,
      const std::pair< Key, T > & val)
  {
    return insert(val);
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  template< class InputIterator >
  void HashMap< Key, T, HS1, HS2, EQ >::insert(InputIterator first, InputIterator last)
  {
    for (auto it = first; it != last; ++it)
    {
      insert(*it);
    }
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  typename HashMap< Key, T, HS1, HS2, EQ >::iterator HashMap< Key, T, HS1, HS2, EQ >::find(const Key & k)
  {
    size_t h1 = HS1{}(k) % capacity_;
    size_t h2 = HS2{}(k) % capacity_;

    if (t1_[h1].second && EQ{}(t1_[h1].first.first, k))
    {
      return iterator(*this, h1, true);
    }

    if (t2_[h2].second && EQ{}(t2_[h2].first.first, k))
    {
      return iterator(*this, h2, false);
    }

    return end();
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  typename HashMap< Key, T, HS1, HS2, EQ >::const_iterator HashMap< Key, T, HS1, HS2, EQ >::find(const Key & k) const
  {
    size_t h1 = HS1{}(k) % capacity_;
    size_t h2 = HS2{}(k) % capacity_;

    if (t1_[h1].second && EQ{}(t1_[h1].first.first, k))
    {
      return const_iterator(*this, h1, true);
    }

    if (t2_[h2].second && EQ{}(t2_[h2].first.first, k))
    {
      return const_iterator(*this, h2, false);
    }

    return cend();
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  float HashMap< Key, T, HS1, HS2, EQ >::load_factor() const noexcept
  {
    return static_cast< double >(size_) / (capacity_ * 2);
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  float HashMap< Key, T, HS1, HS2, EQ >::max_load_factor() const noexcept
  {
    return max_load_factor_;
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  void HashMap< Key, T, HS1, HS2, EQ >::max_load_factor(float z)
  {
    if (z > 0 && z <= 1)
    {
      max_load_factor_ = z;
    }
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  void HashMap< Key, T, HS1, HS2, EQ >::rehash(size_t n)
  {
    HashMap< Key, T, HS1, HS2, EQ > map(n);

    map.max_load_factor_ = max_load_factor_;

    for (size_t i = 0; i < capacity_; ++i)
    {
      if (!t1_[i].second)
      {
        map.insert_data(t1_[i].first.first) = t1_[i].first.second;
      }
      if (!t2_[i].second)
      {
        map.insert_data(t2_[i].first.first) = t2_[i].first.second;
      }
    }
    t1_ = std::move(map.t1_);
    t2_ = std::move(map.t2_);
    capacity_ = map.capacity_;
    size_ = map.size_;
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  T & HashMap< Key, T, HS1, HS2, EQ >::insert_data(const Key & k)
  {
    Key original_key = k;
    T * inserted_value = nullptr;

    Key current_key = k;
    T current_value = T{};
    size_t attempts = 0;

    while (attempts < MAX_ITERATIONS)
    {
      size_t h1 = HS1{}(current_key) % capacity_;
      if (t1_[h1].second)
      {
        t1_[h1] = {{current_key, current_value}, false};
        size_++;
        if (current_key == original_key)
        {
          inserted_value = std::addressof(t1_[h1].first.second);
        }
        break;
      }

      auto displaced = t1_[h1];
      t1_[h1] = {{current_key, current_value}, false};
      if (current_key == original_key)
      {
        inserted_value = std::addressof(t1_[h1].first.second);
      }
      current_key = displaced.first.first;
      current_value = displaced.first.second;
      attempts++;

      size_t h2 = HS2{}(current_key) % capacity_;
      if (t2_[h2].second)
      {
        t2_[h2] = {{current_key, current_value}, false};
        size_++;
        if (current_key == original_key)
        {
          inserted_value = std::addressof(t2_[h2].first.second);
        }
        break;
      }

      displaced = t2_[h2];
      t2_[h2] = {{current_key, current_value}, false};
      if (current_key == original_key)
      {
        inserted_value = std::addressof(t2_[h2].first.second);
      }
      current_key = displaced.first.first;
      current_value = displaced.first.second;
      attempts++;

      if (load_factor() > max_load_factor_)
      {
        rehash(capacity_ * 2);
        return insert_data(original_key);
      }
    }

    if (!inserted_value)
    {
      rehash(capacity_ * 2);
      return insert_data(original_key);
    }

    return *inserted_value;
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  bool HashMap< Key, T, HS1, HS2, EQ >::lookup_data(const Key & k) const
  {
    return get_data(k).second;
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  std::pair< T &, bool > HashMap< Key, T, HS1, HS2, EQ >::get_data(const Key & k) const
  {
    Key current_key = k;

    size_t h1 = HS1{}(current_key) % capacity_;
    if (!t1_[h1].second)
    {
      Key old_key = t1_[h1].first.first;
      if (EQ{}(current_key, old_key))
      {
        return {t1_[h1].first.second, true};
      }
    }

    size_t h2 = HS2{}(current_key) % capacity_;
    if (!t2_[h2].second)
    {
      Key old_key = t2_[h2].first.first;
      if (EQ{}(current_key, old_key))
      {
        return {t2_[h2].first.second, true};
      }
    }
    return {t1_[0].first.second, false};
  }

  template< typename K, typename T, typename H1, typename H2, typename EQ >
  typename HashMap< K, T, H1, H2, EQ >::FwdIter::reference HashMap< K, T, H1, H2, EQ >::FwdIter::operator*()
  {
    assert(is_valid());
    return first_ ? map_->t1_[pos_].first : map_->t2_[pos_].first;
  }
  template< typename K, typename T, typename H1, typename H2, typename EQ >
  typename HashMap< K, T, H1, H2, EQ >::FwdIter::pointer HashMap< K, T, H1, H2, EQ >::FwdIter::operator->()
  {
    assert(is_valid());
    return std::addressof(first_ ? map_->t1_[pos_].first : map_->t2_[pos_].first);
  }
  template< typename K, typename T, typename H1, typename H2, typename EQ >
  typename HashMap< K, T, H1, H2, EQ >::FwdIter::reference HashMap< K, T, H1, H2, EQ >::FwdIter::operator*() const
  {
    assert(is_valid());
    return first_ ? map_->t1_[pos_].first : map_->t2_[pos_].first;
  }
  template< typename K, typename T, typename H1, typename H2, typename EQ >
  typename HashMap< K, T, H1, H2, EQ >::FwdIter::pointer HashMap< K, T, H1, H2, EQ >::FwdIter::operator->() const
  {
    assert(is_valid());
    return std::addressof(first_ ? map_->t1_[pos_].first : map_->t2_[pos_].first);
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  typename HashMap< Key, T, HS1, HS2, EQ >::FwdIter & HashMap< Key, T, HS1, HS2, EQ >::FwdIter::operator++()
  {
    ++pos_;
    skip_empty();
    return *this;
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  typename HashMap< Key, T, HS1, HS2, EQ >::FwdIter HashMap< Key, T, HS1, HS2, EQ >::FwdIter::operator++(int)
  {
    FwdIter< Key, T, HS1, HS2, EQ > result(*this);
    ++(*this);
    return result;
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  bool HashMap< Key, T, HS1, HS2, EQ >::FwdIter::operator!=(const FwdIter & rhs) const
  {
    return !(*this == rhs);
  }
  template< typename Key, typename T, typename HS1, typename HS2, typename EQ >
  bool HashMap< Key, T, HS1, HS2, EQ >::FwdIter::operator==(const FwdIter & rhs) const
  {
    if (map_ || rhs.map_)
    {
      return map_ == rhs.map_ && pos_ == rhs.pos_ && first_ == rhs.first_;
    }
    return true;
  }
  template< typename K, typename T, typename H1, typename H2, typename EQ >
  void HashMap< K, T, H1, H2, EQ >::FwdIter::skip_empty()
  {
    while (first_ && (pos_ < capacity_) && t1_[pos_].second)
    {
      ++pos_;
    }
    if ((pos_ >= capacity_) && first_)
    {
      first_ = false;
      pos_ = 0;
      while (pos_ < capacity_ && t2_[pos_].second)
      {
        ++pos_;
      }
    }
  }
}

#endif
