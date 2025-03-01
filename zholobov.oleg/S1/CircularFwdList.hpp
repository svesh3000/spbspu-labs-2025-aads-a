#ifndef CIRCULARFWDLIST_HPP
#define CIRCULARFWDLIST_HPP

#include <cstddef>

namespace zholobov {

  template < typename T >
  class CircularFwdListIterator;

  template < typename T >
  class CircularFwdListConstIterator;

  template < typename T >
  class CircularFwdList {
  public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const reference;
    using iterator = CircularFwdListIterator< T >;
    using const_iterator = CircularFwdListConstIterator< T >;

    CircularFwdList();
    explicit CircularFwdList(size_t n);
    CircularFwdList(size_t n, const value_type& val);

    CircularFwdList(const CircularFwdList& other);
    CircularFwdList(CircularFwdList&& other) noexcept;

    ~CircularFwdList();

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    iterator end() const noexcept;

    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    bool empty() const noexcept;
    size_t size() const;

    void assign(size_t n, const value_type& val);
    void push_front(const value_type& val);
    void push_front(value_type&& val);
    void push_back(const value_type& val);
    void push_back(value_type&& val);

    void pop_front();
    void pop_back();
    void remove(const value_type& val);
    template < class Predicate >
    void remove_if(Predicate pred);

    void splice_after(const_iterator pos, CircularFwdList< T >& other);
    void splice_after(const_iterator pos, CircularFwdList< T >&& other);
    void splice_after(const_iterator pos, CircularFwdList< T >& other, const_iterator it);
    void splice_after(const_iterator pos, CircularFwdList< T >&& other, const_iterator it);
    void splice_after(const_iterator pos, CircularFwdList< T >& other, const_iterator first, const_iterator last);
    void splice_after(const_iterator pos, CircularFwdList< T >&& other, const_iterator first, const_iterator last);

    void swap(CircularFwdList& other) noexcept;
    void clear() noexcept;

  private:
    struct Node_t {
      T value;
      Node_t* next;
    };

    Node_t* head_;
    Node_t* tail_;
    size_t size_;

    friend class CircularFwdListIterator< T >;
    friend class CircularFwdListConstIterator< T >;
  };
}

#endif
