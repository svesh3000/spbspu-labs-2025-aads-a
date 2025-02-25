#ifndef DECL_HPP
#define DECL_HPP

#include <initializer_list>

#include "bidirectional_iterator.hpp"

namespace rychkov
{
  template< class T >
  class List
  {
  public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    using iterator = BidirectionalIterator< value_type, false, false >;
    using const_iterator = BidirectionalIterator< value_type, true, false >;
    using reverse_iterator = BidirectionalIterator< value_type, false, true >;
    using const_reverse_iterator = BidirectionalIterator< value_type, true, true >;

    List() noexcept;
    ~List();
    List(const List& rhs);
    List(List&& rhs) noexcept;
    List(value_type value, size_type count);
    template< class InputIt >
    List(InputIt from, InputIt to);
    List(std::initializer_list< value_type > rhs);

    List& operator=(const List& rhs);
    List& operator=(List&& rhs) noexcept;
    List& operator=(std::initializer_list< value_type > rhs);

    bool operator==(const List& rhs) const;
    bool operator!=(const List& rhs) const;
    bool operator<=(const List& rhs) const;
    bool operator>=(const List& rhs) const;
    bool operator<(const List& rhs) const;
    bool operator>(const List& rhs) const;

    void assign(value_type value, size_type count);
    template< class InputIt >
    void assign(InputIt from, InputIt to);
    void assign(std::initializer_list< value_type > rhs);

    template< class... Args >
    reference emplace(const_iterator pos, Args&&... args);

    size_type remove(const value_type& value);
    template< class C >
    size_type remove_if(C condition);
    void splice(const_iterator pos, List& rhs);
    void splice(const_iterator pos, List&& rhs);
    void splice(const_iterator pos, List& rhs, const_iterator from, const_iterator to);

    void insert(const_iterator pos, const value_type& value);
    void insert(const_iterator pos, value_type&& value);
    void insert(const_iterator pos, size_type count, value_type value);
    template< class InputIt >
    void insert(const_iterator pos, InputIt from, InputIt to);
    void insert(const_iterator pos, std::initializer_list< value_type > rhs);

    void erase(const_iterator pos);
    void erase(const_iterator from, const_iterator to);

    void reverse() noexcept;
    void merge(List& rhs);
    void merge(List&& rhs);
    template< class C >
    void merge(List& rhs, C compare);
    template< class C >
    void merge(List&& rhs, C compare);

    void unique();
    template< class P >
    void unique(P predicate);
    void sort();
    template< class C >
    void sort(C compare);

    void clear() noexcept;
    void swap(List& rhs) noexcept;
    bool empty() const noexcept;
    size_type size() const noexcept;

    void push_back(const value_type& value);
    void push_back(value_type&& value);
    void pop_back();
    value_type back() const;
    template< class... Args >
    reference emplace_back(Args&&... args);

    void push_front(const value_type& value);
    void push_front(value_type&& value);
    void pop_front();
    value_type front() const;
    template< class... Args >
    reference emplace_front(Args&&... args);

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
  private:
    node_t< value_type >* head_;
    node_t< value_type >* tail_;
    size_t size_;
  };
}

#endif
