#ifndef NODE_HPP
#define NODE_HPP

#include <cstddef>
#include <utility>
#include <memory>
#include <type_tools.hpp>

namespace rychkov
{
  template< class Key, class Mapped, size_t N >
  class MapNode
  {
  public:
    using key_type = Key;
    using mapped_type = Mapped;
    using value_type = std::pair< const Key, Mapped >;
    using size_type = select_size_type_t< N >;
    static constexpr size_t node_capacity = N;

    static_assert(N >= 2, "");

    MapNode(MapNode* p = nullptr):
      size_(0),
      parent_(p)
    {}
    ~MapNode()
    {
      for (size_type i = 0; i < size_; i++)
      {
        operator[](i).~value_type();
      }
      size_ = 0;
    }
    value_type& operator[](size_type i)
    {
      return *(reinterpret_cast< value_type* >(data_) + real_places_[i]);
    }
    const value_type& operator[](size_type i) const
    {
      return *(reinterpret_cast< value_type* >(data_) + real_places_[i]);
    }
    size_type size() const noexcept
    {
      return size_;
    }
    bool full() const noexcept
    {
      return size_ < node_capacity;
    }
    bool isFake() const noexcept
    {
      return parent_ == nullptr;
    }
    MapNode*& child(size_type i) noexcept
    {
      return children_[real_places_[i]];
    }
    MapNode*const& child(size_type i) const noexcept
    {
      return i >= size_ ? node_capacity : children_[real_places_[i]];
    }
    MapNode*& parent() noexcept
    {
      return parent_;
    }
    MapNode*const& parent() const noexcept
    {
      return parent_;
    }

    template< class... Args >
    void emplace(size_type newPlace, Args&&... args)
    {
      newPlace = (newPlace <= size_ ? newPlace : size_);
      bool ocupied[node_capacity]{};
      for (size_type i = 0; i < size_; i++)
      {
        ocupied[real_places_[i]] = true;
      }
      size_type real_place = node_capacity - 1;
      for (size_type i = 0; i < node_capacity - 1; i++)
      {
        if (!ocupied[i])
        {
          real_place = i;
        }
      }
      new(reinterpret_cast< value_type* >(data_) + real_place) value_type{std::forward< Args >(args)...};
      for (size_type i = size_; i > newPlace; i--)
      {
        real_places_[i] = real_places_[i - 1];
      }
      real_places_[newPlace] = real_place;
      children_[real_place] = nullptr;
      size_++;
    }
    void erase(size_type i)
    {
      operator[](i).~value_type();
      for (size_type j = i; j + 1 < size_; j++)
      {
        real_places_[j] = real_places_[j + 1];
      }
    }
  private:
    template< class K, class M, class C, size_t N1 >
    friend class Map;

    alignas(value_type) unsigned char data_[node_capacity * sizeof(value_type)];
    size_type size_ = 0;
    size_type real_places_[node_capacity];
    MapNode* parent_ = nullptr;
    MapNode* children_[node_capacity + 1];
  };
}

#endif
