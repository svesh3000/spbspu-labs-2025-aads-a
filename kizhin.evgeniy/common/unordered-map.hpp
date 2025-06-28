#ifndef SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_COMMON_UNORDERED_MAP_HPP
#define SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_COMMON_UNORDERED_MAP_HPP

#include <algorithm>
#include <cassert>
#include <functional>
#include <stdexcept>
#include <utility>

namespace kizhin {
  template < typename Key, typename T, typename Hash = std::hash< Key >,
      typename KeyEqual = std::equal_to< Key > >
  class UnorderedMap
  {
  public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair< Key, T >;
    using hasher = Hash;
    using key_equal = KeyEqual;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using size_type = std::size_t;

  private:
    template < bool isConst >
    class Iterator;

  public:
    using iterator = Iterator< false >;
    using const_iterator = Iterator< true >;

    UnorderedMap() noexcept = default;
    UnorderedMap(const UnorderedMap&);
    UnorderedMap(UnorderedMap&&) noexcept;
    template < typename InputIt >
    UnorderedMap(InputIt, InputIt);
    UnorderedMap(std::initializer_list< value_type >);
    ~UnorderedMap();

    UnorderedMap& operator=(const UnorderedMap&);
    UnorderedMap& operator=(UnorderedMap&&) noexcept;

    bool empty() const noexcept;
    size_type size() const noexcept;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    mapped_type& operator[](const key_type&);
    mapped_type& at(const key_type&);
    const mapped_type& at(const key_type&) const;

    iterator find(const key_type&);
    const_iterator find(const key_type&) const;
    size_type count(const key_type&) const;

    std::pair< iterator, bool > insert(const value_type&);
    template < typename InputIt >
    void insert(InputIt, InputIt);
    iterator erase(const_iterator);

    void clear() noexcept;
    void swap(UnorderedMap&) noexcept;

    void rehash(size_type);
    void reserve(size_type);

    hasher hashFunc() const;
    key_equal keyEq() const;

  private:
    struct Node;

    constexpr static const double maxLoadFactor = 0.75;

    Node* begin_ = nullptr;
    size_type size_ = 0;
    size_type capacity_ = 0;

    void resize(size_type);
  };

  template < typename K, typename T, typename H, typename E >
  struct UnorderedMap< K, T, H, E >::Node
  {
    value_type value{};
    enum {
      empty,
      occupied,
      deleted,
    } state = empty;
  };

  template < typename K, typename T, typename H, typename E >
  template < bool IsConst >
  class UnorderedMap< K, T, H, E >::Iterator
  {
  private:
    template < typename T1, typename T2 >
    using cond_t = std::conditional_t< IsConst, T1, T2 >;

  public:
    using value_type = UnorderedMap::value_type;
    using difference_type = std::ptrdiff_t;
    using pointer = cond_t< UnorderedMap::const_pointer, UnorderedMap::pointer >;
    using reference = cond_t< UnorderedMap::const_reference, UnorderedMap::reference >;
    using iterator_category = std::forward_iterator_tag;

    Iterator() noexcept = default;
    template < bool RhsConst, std::enable_if_t< IsConst && !RhsConst, int > = 0 >
    Iterator(const Iterator< RhsConst >&) noexcept;

    pointer operator->() const noexcept;
    reference operator*() const noexcept;

    Iterator& operator++();
    Iterator operator++(int);

    friend bool operator==(const Iterator& lhs, const Iterator& rhs) noexcept
    {
      return lhs.node_ == rhs.node_ && lhs.end_ == rhs.end_;
    }

    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) noexcept
    {
      return !(lhs == rhs);
    }

  private:
    friend class UnorderedMap;

    Node* node_ = nullptr;
    const Node* end_ = nullptr;

    Iterator(Node*, const Node*) noexcept;
  };

  template < typename K, typename T, typename H, typename E >
  template < bool IsConst >
  UnorderedMap< K, T, H, E >::Iterator< IsConst >::Iterator(Node* node,
      const Node* end) noexcept:
    node_(node),
    end_(end)
  {
    while (node_ != end_ && node_->state != Node::occupied) {
      ++node_;
    }
  }

  template < typename K, typename T, typename H, typename E >
  template < bool IsConst >
  template < bool IsRhsConst, std::enable_if_t< IsConst && !IsRhsConst, int > >
  UnorderedMap< K, T, H, E >::Iterator< IsConst >::Iterator(
      const Iterator< IsRhsConst >& rhs) noexcept:
    node_(rhs.node_),
    end_(rhs.end_)
  {}

  template < typename K, typename T, typename H, typename E >
  template < bool IsConst >
  auto UnorderedMap< K, T, H, E >::Iterator< IsConst >::operator->() const noexcept
      -> pointer
  {
    assert(node_ && "Dereferencing empty iterator");
    assert(node_ != end_ && "Dereferencing end iterator");
    return std::addressof(**this);
  }

  template < typename K, typename T, typename H, typename E >
  template < bool IsConst >
  auto UnorderedMap< K, T, H, E >::Iterator< IsConst >::operator*() const noexcept
      -> reference
  {
    assert(node_ && "Dereferencing empty iterator");
    assert(node_ != end_ && "Dereferencing end iterator");
    return node_->value;
  }

  template < typename K, typename T, typename H, typename E >
  template < bool IsConst >
  auto UnorderedMap< K, T, H, E >::Iterator< IsConst >::operator++() -> Iterator&
  {
    assert(node_ && "Incrementing empty iterator");
    assert(node_ != end_ && "Incrementing end iterator");
    do {
      ++node_;
    } while (node_ != end_ && node_->state != Node::occupied);
    return *this;
  }

  template < typename K, typename T, typename H, typename E >
  template < bool IsConst >
  auto UnorderedMap< K, T, H, E >::Iterator< IsConst >::operator++(int) -> Iterator
  {
    Iterator result(*this);
    ++(*this);
    return result;
  }

  template < typename K, typename T, typename H, typename E >
  UnorderedMap< K, T, H, E >::UnorderedMap(const UnorderedMap& rhs):
    UnorderedMap(rhs.begin(), rhs.end())
  {}

  template < typename K, typename T, typename H, typename E >
  UnorderedMap< K, T, H, E >::UnorderedMap(UnorderedMap&& rhs) noexcept:
    begin_(std::exchange(rhs.begin_, nullptr)),
    size_(std::exchange(rhs.size_, 0)),
    capacity_(std::exchange(rhs.capacity_, 0))
  {}

  template < typename K, typename T, typename H, typename E >
  template < typename InputIt >
  UnorderedMap< K, T, H, E >::UnorderedMap(const InputIt first, const InputIt last)
  {
    insert(first, last);
  }

  template < typename K, typename T, typename H, typename E >
  UnorderedMap< K, T, H, E >::UnorderedMap(std::initializer_list< value_type > list):
    UnorderedMap(list.begin(), list.end())
  {}

  template < typename K, typename T, typename H, typename E >
  UnorderedMap< K, T, H, E >::~UnorderedMap()
  {
    clear();
  }

  template < typename K, typename T, typename H, typename E >
  UnorderedMap< K, T, H, E >& UnorderedMap< K, T, H, E >::operator=(
      const UnorderedMap& rhs)
  {
    UnorderedMap(rhs).swap(*this);
    return *this;
  }

  template < typename K, typename T, typename H, typename E >
  UnorderedMap< K, T, H, E >& UnorderedMap< K, T, H, E >::operator=(
      UnorderedMap&& rhs) noexcept
  {
    UnorderedMap(std::move(rhs)).swap(*this);
    return *this;
  }

  template < typename K, typename T, typename H, typename E >
  bool UnorderedMap< K, T, H, E >::empty() const noexcept
  {
    return size() == 0;
  }

  template < typename K, typename T, typename H, typename E >
  typename UnorderedMap< K, T, H, E >::size_type UnorderedMap< K, T, H, E >::size()
      const noexcept
  {
    return size_;
  }

  template < typename K, typename T, typename H, typename E >
  typename UnorderedMap< K, T, H, E >::iterator UnorderedMap< K, T, H,
      E >::begin() noexcept
  {
    return iterator{ begin_, begin_ + capacity_ };
  }

  template < typename K, typename T, typename H, typename E >
  typename UnorderedMap< K, T, H, E >::iterator UnorderedMap< K, T, H, E >::end() noexcept
  {
    return iterator{ begin_ + capacity_, begin_ + capacity_ };
  }

  template < typename K, typename T, typename H, typename E >
  typename UnorderedMap< K, T, H, E >::const_iterator UnorderedMap< K, T, H, E >::begin()
      const noexcept
  {
    return const_iterator{ begin_, begin_ + capacity_ };
  }

  template < typename K, typename T, typename H, typename E >
  typename UnorderedMap< K, T, H, E >::const_iterator UnorderedMap< K, T, H, E >::end()
      const noexcept
  {
    return const_iterator{ begin_ + capacity_, begin_ + capacity_ };
  }

  template < typename K, typename T, typename H, typename E >
  typename UnorderedMap< K, T, H, E >::mapped_type& UnorderedMap< K, T, H,
      E >::operator[](const key_type& key)
  {
    return insert({ key, {} }).first->second;
  }

  template < typename K, typename T, typename H, typename E >
  typename UnorderedMap< K, T, H, E >::mapped_type& UnorderedMap< K, T, H, E >::at(
      const key_type& key)
  {
    const UnorderedMap* constThis = this;
    return const_cast< mapped_type& >(constThis->at(key));
  }

  template < typename K, typename T, typename H, typename E >
  const typename UnorderedMap< K, T, H, E >::mapped_type& UnorderedMap< K, T, H, E >::at(
      const key_type& key) const
  {
    const_iterator pos = find(key);
    if (pos == end()) {
      throw std::out_of_range("UnorderedMap::at");
    }
    return pos->second;
  }

  template < typename K, typename T, typename H, typename E >
  typename UnorderedMap< K, T, H, E >::iterator UnorderedMap< K, T, H, E >::find(
      const key_type& key)
  {
    const UnorderedMap* constThis = this;
    const_iterator result = constThis->find(key);
    return iterator{ result.node_, result.end_ };
  }

  template < typename K, typename T, typename H, typename E >
  typename UnorderedMap< K, T, H, E >::const_iterator UnorderedMap< K, T, H, E >::find(
      const key_type& key) const
  {
    if (empty()) {
      return end();
    }
    Node* curr = begin_ + hashFunc()(key) % capacity_;
    const Node* const stop = curr == begin_ ? begin_ + capacity_ : curr - 1;
    while (curr != stop) {
      if (curr->state == Node::occupied && keyEq()(curr->value.first, key)) {
        return const_iterator{ curr, begin_ + capacity_ };
      }
      const size_type nextIndex = (curr - begin_ + 1) % capacity_;
      curr = begin_ + nextIndex;
    }
    return end();
  }

  template < typename K, typename T, typename H, typename E >
  typename UnorderedMap< K, T, H, E >::size_type UnorderedMap< K, T, H, E >::count(
      const key_type& key) const
  {
    return static_cast< size_type >(find(key) != end());
  }

  template < typename K, typename T, typename H, typename E >
  std::pair< typename UnorderedMap< K, T, H, E >::iterator, bool > UnorderedMap< K, T, H,
      E >::insert(const value_type& value)
  {
    if (size() + 1 > static_cast< size_type >(capacity_ * maxLoadFactor)) {
      resize(capacity_ + std::max(capacity_, 4ul));
    }
    Node* curr = begin_ + hashFunc()(value.first) % capacity_;
    Node* firstDeleted = nullptr;
    while (curr->state != Node::empty) {
      if (curr->state == Node::occupied && keyEq()(curr->value.first, value.first)) {
        return std::make_pair(iterator{ curr, begin_ + capacity_ }, false);
      }
      if (curr->state == Node::deleted && !firstDeleted) {
        firstDeleted = curr;
      }
      const size_type nextIndex = (curr - begin_ + 1) % capacity_;
      curr = begin_ + nextIndex;
    }
    curr = firstDeleted ? firstDeleted : curr;
    curr->value = value;
    curr->state = Node::occupied;
    ++size_;
    return std::make_pair(iterator{ curr, begin_ + capacity_ }, true);
  }

  template < typename K, typename T, typename H, typename E >
  template < typename InputIt >
  void UnorderedMap< K, T, H, E >::insert(InputIt first, const InputIt last)
  {
    for (; first != last; ++first) {
      insert(*first);
    }
  }

  template < typename K, typename T, typename H, typename E >
  typename UnorderedMap< K, T, H, E >::iterator UnorderedMap< K, T, H, E >::erase(
      const_iterator position)
  {
    position.node_->state = Node::deleted;
    ++position;
    --size_;
    return iterator{ position.node_, position.end_ };
  }

  template < typename K, typename T, typename H, typename E >
  void UnorderedMap< K, T, H, E >::clear() noexcept
  {
    delete[] std::exchange(begin_, nullptr);
    size_ = 0;
    capacity_ = 0;
  }

  template < typename K, typename T, typename H, typename E >
  void UnorderedMap< K, T, H, E >::swap(UnorderedMap& rhs) noexcept
  {
    using std::swap;
    swap(begin_, rhs.begin_);
    swap(size_, rhs.size_);
    swap(capacity_, rhs.capacity_);
  }

  template < typename K, typename T, typename H, typename E >
  typename UnorderedMap< K, T, H, E >::hasher UnorderedMap< K, T, H, E >::hashFunc() const
  {
    return hasher{};
  }

  template < typename K, typename T, typename H, typename E >
  typename UnorderedMap< K, T, H, E >::key_equal UnorderedMap< K, T, H, E >::keyEq() const
  {
    return key_equal{};
  }

  template < typename K, typename T, typename H, typename E >
  void UnorderedMap< K, T, H, E >::resize(const size_type newSize)
  {
    if (newSize < capacity_) {
      return;
    }
    UnorderedMap resized{};
    resized.begin_ = new Node[newSize];
    resized.capacity_ = newSize;
    for (const_reference value: *this) {
      resized.insert(value);
    }
    swap(resized);
  }

  template < typename K, typename T, typename H, typename E >
  void swap(UnorderedMap< K, T, H, E >& lhs, UnorderedMap< K, T, H, E >& rhs) noexcept(
      noexcept(lhs.swap(rhs)))
  {
    lhs.swap(rhs);
  }

  template < typename K, typename T, typename H, typename E >
  bool operator==(const UnorderedMap< K, T, H, E >& lhs,
      const UnorderedMap< K, T, H, E >& rhs)
  {
    if (lhs.size() != rhs.size()) {
      return false;
    }
    return std::is_permutation(lhs.begin(), lhs.end(), rhs.begin() /*, lhs.keyEq()*/);
  }

  template < typename K, typename T, typename H, typename E >
  bool operator!=(const UnorderedMap< K, T, H, E >& lhs,
      const UnorderedMap< K, T, H, E >& rhs)
  {
    return !(lhs == rhs);
  }
}

#endif

