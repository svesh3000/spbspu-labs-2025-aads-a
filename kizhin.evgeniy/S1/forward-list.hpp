#ifndef SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S1_FORWARD_LIST_HPP
#define SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S1_FORWARD_LIST_HPP

#include <initializer_list>
#include <utility>
#include "enable-if-input-iterator.hpp"
#include "forward-list-comparison.hpp"
#include "forward-list-iterator.hpp"
#include "forward-list-swap.hpp"

namespace kizhin {
  template < typename T >
  class ForwardList
  {
  public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    using iterator = detail::ForwardListIterator< value_type, false >;
    using const_iterator = detail::ForwardListIterator< value_type, true >;

    ForwardList() = default;
    ForwardList(const ForwardList&);
    ForwardList(ForwardList&&) noexcept;
    explicit ForwardList(size_type, const_reference = value_type{});
    template < typename InputIt, detail::enable_if_input_iterator< InputIt > = 0 >
    ForwardList(InputIt, InputIt);
    ForwardList(std::initializer_list< value_type > l): ForwardList(l.begin(), l.end()) {}
    ~ForwardList();

    ForwardList& operator=(const ForwardList&);
    ForwardList& operator=(ForwardList&&) noexcept;
    ForwardList& operator=(std::initializer_list< value_type >);

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    reference front();
    reference back();
    const_reference front() const;
    const_reference back() const;
    bool empty() const noexcept;
    size_type size() const noexcept;

    void push_back(const_reference);
    void push_back(value_type&&);
    void push_front(const_reference);
    void push_front(value_type&&);
    void pop_back() noexcept;
    void pop_front() noexcept;
    template < typename... Args >
    void emplace_back(Args&&...);
    template < typename... Args >
    void emplace_front(Args&&...);
    template < typename... Args >
    iterator emplace(const_iterator, Args&&...);

    void assign(size_type, const_reference);
    template < typename InputIt, detail::enable_if_input_iterator< InputIt > = 0 >
    void assign(InputIt, InputIt);
    void assign(std::initializer_list< value_type >);

    iterator insert(const_iterator, const_reference);
    iterator insert(const_iterator, value_type&&);
    iterator insert(const_iterator, size_type, const_reference);
    template < typename InputIt, detail::enable_if_input_iterator< InputIt > = 0 >
    iterator insert(const_iterator, InputIt, InputIt);
    iterator insert(const_iterator, std::initializer_list< value_type >);

    iterator erase(iterator);
    iterator erase(const_iterator);
    iterator erase(iterator, iterator);
    iterator erase(const_iterator, const_iterator);

    void remove(const_reference);
    template < typename UnaryPredicate >
    void remove_if(UnaryPredicate);
// TODO: Define splice
#if 0
    void splice(const_iterator, List&);
    void splice(const_iterator, List&&);
    void splice(const_iterator, List&, const_iterator);
    void splice(const_iterator, List&&, const_iterator);
    void splice(const_iterator, List&, const_iterator, const_iterator);
    void splice(const_iterator, List&&, const_iterator, const_iterator);
#endif

    void reverse() noexcept;
    void unique();
    template < typename BinaryPredicate >
    void unique(BinaryPredicate);
    void sort();
    template < typename Comp >
    void sort(Comp);

    void merge(ForwardList&);
    void merge(ForwardList&&);
    template < typename Comp >
    void merge(ForwardList&, Comp);
    template < typename Comp >
    void merge(ForwardList&&, Comp);

    void clear() noexcept;
    void swap(ForwardList&) noexcept;

  private:
    using Node = detail::Node< value_type >;

    Node* end_ = nullptr;
    size_type size_ = 0;
  };

  template < typename T >
  ForwardList< T >::ForwardList(const ForwardList& rhs)
  {
    for (const_iterator i = rhs.begin(), end = rhs.end(); i != end; ++i) {
      emplace_back(*i);
    }
  }

  template < typename T >
  ForwardList< T >::ForwardList(ForwardList&& rhs) noexcept:
    end_(std::exchange(rhs.end_, nullptr)),
    size_(std::exchange(rhs.size_, 0))
  {
  }

  template < typename T >
  ForwardList< T >::ForwardList(size_type size, const_reference value)
  {
    for (; size; --size) {
      emplace_back(value);
    }
  }

  template < typename T >
  template < typename InputIt, detail::enable_if_input_iterator< InputIt > >
  ForwardList< T >::ForwardList(InputIt first, InputIt last)
  {
    for (; first != last; ++first) {
      emplace_back(*first);
    }
  }

  template < typename T >
  ForwardList< T >::~ForwardList()
  {
    clear();
  }

  template < typename T >
  ForwardList< T >& ForwardList< T >::operator=(const ForwardList& rhs)
  {
    ForwardList tmp(rhs);
    swap(tmp);
    return *this;
  }

  template < typename T >
  ForwardList< T >& ForwardList< T >::operator=(ForwardList&& rhs) noexcept
  {
    clear();
    end_ = std::exchange(rhs.end_, nullptr);
    size_ = std::exchange(rhs.size_, 0);
    return *this;
  }

  template < typename T >
  ForwardList< T >& ForwardList< T >::operator=(std::initializer_list< value_type > init)
  {
    ForwardList tmp(init);
    swap(tmp);
    return *this;
  }

  template < typename T >
  typename ForwardList< T >::iterator ForwardList< T >::begin() noexcept
  {
    return iterator(end_->next);
  }

  template < typename T >
  typename ForwardList< T >::iterator ForwardList< T >::end() noexcept
  {
    return iterator(end_);
  }

  template < typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::begin() const noexcept
  {
    return const_iterator(end_->next);
  }

  template < typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::end() const noexcept
  {
    return const_iterator(end_);
  }

  template < typename T >
  typename ForwardList< T >::reference ForwardList< T >::front()
  {
    return end_->next->data;
  }

  template < typename T >
  typename ForwardList< T >::reference ForwardList< T >::back()
  {
    return end_->prev->data;
  }

  template < typename T >
  typename ForwardList< T >::const_reference ForwardList< T >::front() const
  {
    return end_->next->data;
  }

  template < typename T >
  typename ForwardList< T >::const_reference ForwardList< T >::back() const
  {
    return end_->prev->data;
  }

  template < typename T >
  bool ForwardList< T >::empty() const noexcept
  {
    return size_ == 0;
  }

  template < typename T >
  typename ForwardList< T >::size_type ForwardList< T >::size() const noexcept
  {
    return size_;
  }

  template < typename T >
  void ForwardList< T >::push_back(const_reference value)
  {
    emplace_back(value);
  }

  template < typename T >
  void ForwardList< T >::push_back(value_type&& value)
  {
    emplace_back(std::move(value));
  }

  template < typename T >
  void ForwardList< T >::push_front(const_reference value)
  {
    emplace_front(value);
  }

  template < typename T >
  void ForwardList< T >::push_front(value_type&& value)
  {
    emplace_front(std::move(value));
  }

  template < typename T >
  void ForwardList< T >::pop_back() noexcept
  {
    // TODO: Implement pop
  }

  template < typename T >
  void ForwardList< T >::pop_front() noexcept
  {
    // TODO: Implement pop
  }

  template < typename T >
  template < typename... Args >
  void ForwardList< T >::emplace_back(Args&&...)
  {
    // TODO: Implement emplace
  }

  template < typename T >
  template < typename... Args >
  void ForwardList< T >::emplace_front(Args&&...)
  {
    // TODO: Implement emplace
  }

  template < typename T >
  template < typename... Args >
  typename ForwardList< T >::iterator ForwardList< T >::emplace(const_iterator, Args&&...)
  {
    // TODO: Implement emplace
    return iterator(); // stub for tests running
  }

  template < typename T >
  void ForwardList< T >::assign(size_type, const_reference)
  {
    // TODO: Implement assign
  }

  template < typename T >
  template < typename InputIt, detail::enable_if_input_iterator< InputIt > >
  void ForwardList< T >::assign(InputIt, InputIt)
  {
    // TODO: Implement assign
  }

  template < typename T >
  void ForwardList< T >::assign(std::initializer_list< value_type > l)
  {
    assign(l.begin(), l.end());
  }

  template < typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insert(const_iterator position,
      const_reference value)
  {
    return emplace(position, value);
  }

  template < typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insert(const_iterator position,
      value_type&& value)
  {
    return emplace(position, std::move(value));
  }

  template < typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insert(const_iterator, size_type,
      const_reference)
  {
    // TODO: Implement insert
    return iterator(); // stub for tests running
  }

  template < typename T >
  template < typename InputIt, detail::enable_if_input_iterator< InputIt > >
  typename ForwardList< T >::iterator ForwardList< T >::insert(const_iterator, InputIt,
      InputIt)
  {
    // TODO: Implement insert
    return iterator(); // stub for tests running
  }

  template < typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insert(const_iterator position,
      std::initializer_list< value_type > l)
  {
    return insert(position, l.begin(), l.end());
  }

  template < typename T >
  typename ForwardList< T >::iterator ForwardList< T >::erase(iterator)
  {
    // TODO: Implement erase
    return iterator(); // stub for tests running
  }

  template < typename T >
  typename ForwardList< T >::iterator ForwardList< T >::erase(const_iterator)
  {
    // TODO: Implement erase
    return iterator(); // stub for tests running
  }

  template < typename T >
  typename ForwardList< T >::iterator ForwardList< T >::erase(iterator, iterator)
  {
    // TODO: Implement erase
    return iterator(); // stub for tests running
  }

  template < typename T >
  typename ForwardList< T >::iterator ForwardList< T >::erase(const_iterator,
      const_iterator)
  {
    // TODO: Implement erase
    return iterator(); // stub for tests running
  }

  template < typename T >
  void ForwardList< T >::remove(const_reference value)
  {
    remove_if([&value](const_reference rhs) -> bool { return value == rhs; });
  }

  template < typename T >
  template < typename UnaryPredicate >
  void ForwardList< T >::remove_if(UnaryPredicate)
  {
    // TODO: Implement remove
  }

  template < typename T >
  void ForwardList< T >::reverse() noexcept
  {
    // TODO: Implement reverse
  }

  template < typename T >
  void ForwardList< T >::unique()
  {
    // TODO: Implement unique
  }

  template < typename T >
  template < typename BinaryPredicate >
  void ForwardList< T >::unique(BinaryPredicate)
  {
    // TODO: Implement unique
  }

  template < typename T >
  void ForwardList< T >::sort()
  {
    // TODO: Implement sort
  }

  template < typename T >
  template < typename Comp >
  void ForwardList< T >::sort(Comp)
  {
    // TODO: Implement sort
  }

  template < typename T >
  void ForwardList< T >::merge(ForwardList&)
  {
    // TODO: Implement merge
  }

  template < typename T >
  void ForwardList< T >::merge(ForwardList&&)
  {
    // TODO: Implement merge
  }

  template < typename T >
  template < typename Comp >
  void ForwardList< T >::merge(ForwardList&, Comp)
  {
    // TODO: Implement merge
  }

  template < typename T >
  template < typename Comp >
  void ForwardList< T >::merge(ForwardList&&, Comp)
  {
    // TODO: Implement merge
  }

  template < typename T >
  void ForwardList< T >::clear() noexcept
  {
    // TODO: Implement clear
  }

  template < typename T >
  void ForwardList< T >::swap(ForwardList&) noexcept
  {
    // TODO: Implement swap
  }
}

#endif

