#ifndef SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S1_LIST_HPP
#define SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S1_LIST_HPP

#include <initializer_list>
#include "enable_if_input_iterator.hpp"
#include "list_comparison.hpp"
#include "list_iterator.hpp"
#include "list_swap.hpp"

namespace kizhin {
  template < typename T >
  class List
  {
  public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    using iterator = detail::ListIterator< value_type, false >;
    using const_iterator = detail::ListIterator< value_type, true >;
    using reverse_iterator = std::reverse_iterator< iterator >;
    using const_reverse_iterator = std::reverse_iterator< const_iterator >;

    List() = default;
    List(const List&);
    List(List&&) noexcept;
    explicit List(size_type, const_reference = value_type{});
    template < typename InputIt, detail::enable_if_input_iterator< InputIt > = 0 >
    List(InputIt, InputIt);
    List(std::initializer_list< value_type > l): List(l.begin(), l.end()) {}
    ~List();

    List& operator=(const List&);
    List& operator=(List&&) noexcept;
    List& operator=(std::initializer_list< value_type >);

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    reverse_iterator rbegin() noexcept; // TODO: remove reverse iterators
    reverse_iterator rend() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator rend() const noexcept;

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

    void splice(const_iterator, List&); // TODO: Define splice
    void splice(const_iterator, List&&);
    void splice(const_iterator, List&, const_iterator);
    void splice(const_iterator, List&&, const_iterator);
    void splice(const_iterator, List&, const_iterator, const_iterator);
    void splice(const_iterator, List&&, const_iterator, const_iterator);

    void reverse() noexcept;
    void unique();
    template < typename BinaryPredicate >
    void unique(BinaryPredicate);
    void sort();
    template < typename Comp >
    void sort(Comp);

    void merge(List&);
    void merge(List&&);
    template < typename Comp >
    void merge(List&, Comp);
    template < typename Comp >
    void merge(List&&, Comp);

    void clear() noexcept;
    void swap(List&) noexcept;

  private:
    using Node = detail::Node< value_type >;

    Node* end_ = nullptr;
    size_type size_ = 0;
  };

  template < typename T >
  List< T >::List(const List&)
  {
    // TODO: Implement constructors
  }

  template < typename T >
  List< T >::List(List&&) noexcept
  {
    // TODO: Implement constructors
  }

  template < typename T >
  List< T >::List(size_type, const_reference)
  {
    // TODO: Implement constructors
  }

  template < typename T >
  template < typename InputIt, detail::enable_if_input_iterator< InputIt > >
  List< T >::List(InputIt, InputIt)
  {
    // TODO: Implement constructors
  }

  template < typename T >
  List< T >::~List()
  {
    clear();
  }

  template < typename T >
  List< T >& List< T >::operator=(const List&)
  {
    // TODO: Implement assignment operators
    return *this; // stub for tests running
  }

  template < typename T >
  List< T >& List< T >::operator=(List&&) noexcept
  {
    // TODO: Implement assignment operators
    return *this; // stub for tests running
  }

  template < typename T >
  List< T >& List< T >::operator=(std::initializer_list< value_type >)
  {
    // TODO: Implement assignment operators
    return *this; // stub for tests running
  }

  template < typename T >
  typename List< T >::iterator List< T >::begin() noexcept
  {
    // TODO: Implement begin/end
    return iterator(); // stub for tests running
  }

  template < typename T >
  typename List< T >::iterator List< T >::end() noexcept
  {
    // TODO: Implement begin/end
    return iterator(); // stub for tests running
  }

  template < typename T >
  typename List< T >::const_iterator List< T >::begin() const noexcept
  {
    // TODO: Implement begin/end
    return const_iterator(); // stub for tests running
  }

  template < typename T >
  typename List< T >::const_iterator List< T >::end() const noexcept
  {
    // TODO: Implement begin/end
    return const_iterator(); // stub for tests running
  }

  template < typename T >
  typename List< T >::reference List< T >::front()
  {
    // TODO: Implement front/back
    return end_->data; // stub for tests running
  }

  template < typename T >
  typename List< T >::reference List< T >::back()
  {
    // TODO: Implement front/back
    return end_->data; // stub for tests running
  }

  template < typename T >
  typename List< T >::const_reference List< T >::front() const
  {
    // TODO: Implement front/back
    return end_->data; // stub for tests running
  }

  template < typename T >
  typename List< T >::const_reference List< T >::back() const
  {
    // TODO: Implement front/back
    return end_->data; // stub for tests running
  }

  template < typename T >
  bool List< T >::empty() const noexcept
  {
    return size_ == 0;
  }

  template < typename T >
  typename List< T >::size_type List< T >::size() const noexcept
  {
    return size_;
  }

  template < typename T >
  void List< T >::push_back(const_reference value)
  {
    emplace_back(value);
  }

  template < typename T >
  void List< T >::push_back(value_type&& value)
  {
    emplace_back(std::move(value));
  }

  template < typename T >
  void List< T >::push_front(const_reference value)
  {
    emplace_front(value);
  }

  template < typename T >
  void List< T >::push_front(value_type&& value)
  {
    emplace_front(std::move(value));
  }

  template < typename T >
  void List< T >::pop_back() noexcept
  {
    // TODO: Implement pop
  }

  template < typename T >
  void List< T >::pop_front() noexcept
  {
    // TODO: Implement pop
  }

  template < typename T >
  template < typename... Args >
  void List< T >::emplace_back(Args&&...)
  {
    // TODO: Implement emplace
  }

  template < typename T >
  template < typename... Args >
  void List< T >::emplace_front(Args&&...)
  {
    // TODO: Implement emplace
  }

  template < typename T >
  template < typename... Args >
  typename List< T >::iterator List< T >::emplace(const_iterator, Args&&...)
  {
    // TODO: Implement emplace
    return iterator(); // stub for tests running
  }

  template < typename T >
  void List< T >::assign(size_type, const_reference)
  {
    // TODO: Implement assign
  }

  template < typename T >
  template < typename InputIt, detail::enable_if_input_iterator< InputIt > >
  void List< T >::assign(InputIt, InputIt)
  {
    // TODO: Implement assign
  }

  template < typename T >
  void List< T >::assign(std::initializer_list< value_type > l)
  {
    assign(l.begin(), l.end());
  }

  template < typename T >
  typename List< T >::iterator List< T >::insert(const_iterator position,
      const_reference value)
  {
    return emplace(position, value);
  }

  template < typename T >
  typename List< T >::iterator List< T >::insert(const_iterator position,
      value_type&& value)
  {
    return emplace(position, std::move(value));
  }

  template < typename T >
  typename List< T >::iterator List< T >::insert(const_iterator, size_type,
      const_reference)
  {
    // TODO: Implement insert
    return iterator(); // stub for tests running
  }

  template < typename T >
  template < typename InputIt, detail::enable_if_input_iterator< InputIt > >
  typename List< T >::iterator List< T >::insert(const_iterator, InputIt, InputIt)
  {
    // TODO: Implement insert
    return iterator(); // stub for tests running
  }

  template < typename T >
  typename List< T >::iterator List< T >::insert(const_iterator,
      std::initializer_list< value_type > l)
  {
    return insert(l.begin(), l.end());
  }

  template < typename T >
  typename List< T >::iterator List< T >::erase(iterator)
  {
    // TODO: Implement erase
    return iterator(); // stub for tests running
  }

  template < typename T >
  typename List< T >::iterator List< T >::erase(const_iterator)
  {
    // TODO: Implement erase
    return iterator(); // stub for tests running
  }

  template < typename T >
  typename List< T >::iterator List< T >::erase(iterator, iterator)
  {
    // TODO: Implement erase
    return iterator(); // stub for tests running
  }

  template < typename T >
  typename List< T >::iterator List< T >::erase(const_iterator, const_iterator)
  {
    // TODO: Implement erase
    return iterator(); // stub for tests running
  }

  template < typename T >
  void List< T >::remove(const_reference value)
  {
    remove_if([&value](const_reference rhs) -> bool { return value == rhs; });
  }

  template < typename T >
  template < typename UnaryPredicate >
  void List< T >::remove_if(UnaryPredicate)
  {
    // TODO: Implement remove
  }

  template < typename T >
  void List< T >::reverse() noexcept
  {
    // TODO: Implement reverse
  }

  template < typename T >
  void List< T >::unique()
  {
    // TODO: Implement unique
  }

  template < typename T >
  template < typename BinaryPredicate >
  void List< T >::unique(BinaryPredicate)
  {
    // TODO: Implement unique
  }

  template < typename T >
  void List< T >::sort()
  {
    // TODO: Implement sort
  }

  template < typename T >
  template < typename Comp >
  void List< T >::sort(Comp)
  {
    // TODO: Implement sort
  }

  template < typename T >
  void List< T >::merge(List&)
  {
    // TODO: Implement merge
  }

  template < typename T >
  void List< T >::merge(List&&)
  {
    // TODO: Implement merge
  }

  template < typename T >
  template < typename Comp >
  void List< T >::merge(List&, Comp)
  {
    // TODO: Implement merge
  }

  template < typename T >
  template < typename Comp >
  void List< T >::merge(List&&, Comp)
  {
    // TODO: Implement merge
  }

  template < typename T >
  void List< T >::clear() noexcept
  {
    // TODO: Implement clear
  }

  template < typename T >
  void List< T >::swap(List&) noexcept
  {
    // TODO: Implement swap
  }
}

#endif

