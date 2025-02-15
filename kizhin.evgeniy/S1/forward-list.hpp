#ifndef SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S1_FORWARD_LIST_HPP
#define SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S1_FORWARD_LIST_HPP

#include <cassert>
#include <initializer_list>
#include <memory>
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

    ForwardList();
    ForwardList(const ForwardList&);
    ForwardList(ForwardList&&) noexcept;
    explicit ForwardList(size_type, const_reference = value_type());
    template < typename InputIt, detail::enable_if_input_iterator< InputIt > = 0 >
    ForwardList(InputIt, InputIt);
    ForwardList(std::initializer_list< value_type >);
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

    void pushBack(value_type);
    void pushFront(value_type);
    template < typename... Args >
    void emplaceBack(Args&&...);
    template < typename... Args >
    void emplaceFront(Args&&...);
    template < typename... Args >
    iterator emplaceAfter(const_iterator, Args&&...);

    void popBack();
    void popFront();
    iterator eraseAfter(const_iterator);
    iterator eraseAfter(const_iterator, const_iterator);

    void assign(size_type, const_reference);
    template < typename InputIt, detail::enable_if_input_iterator< InputIt > = 0 >
    void assign(InputIt, InputIt);
    void assign(std::initializer_list< value_type >);

    iterator insertAfter(const_iterator, value_type);
    iterator insertAfter(const_iterator, size_type, const_reference);
    template < typename InputIt, detail::enable_if_input_iterator< InputIt > = 0 >
    iterator insertAfter(const_iterator, InputIt, InputIt);
    iterator insertAfter(const_iterator, std::initializer_list< value_type >);

    void clear() noexcept;
    void swap(ForwardList&) noexcept;

    void reverse();
    void spliceAfter(const_iterator, ForwardList&);
    void spliceAfter(const_iterator, ForwardList&, const_iterator);
    void spliceAfter(const_iterator, ForwardList&, const_iterator, const_iterator);

    void remove(const_reference);
    template < typename UnaryPredicate >
    void removeIf(UnaryPredicate);
    void unique();
    template < typename BinaryPredicate >
    void unique(BinaryPredicate);
    void sort();
    template < typename Comp >
    void sort(Comp);
    void merge(ForwardList&);
    template < typename Comp >
    void merge(ForwardList&, Comp);

  private:
    using Node = detail::Node< value_type >;

    Node* begin_;
    Node* end_;
    size_type size_;
  };

  template < typename T >
  ForwardList< T >::ForwardList(): begin_(nullptr), end_(nullptr), size_(0)
  {
  }

  template < typename T >
  ForwardList< T >::ForwardList(const ForwardList& rhs): ForwardList()
  {
    for (const_iterator i = rhs.begin(), end = rhs.end(); i != end; ++i) {
      pushBack(*i);
    }
  }

  template < typename T >
  ForwardList< T >::ForwardList(ForwardList&& rhs) noexcept:
    begin_(std::exchange(rhs.begin_, nullptr)),
    end_(std::exchange(rhs.end_, nullptr)),
    size_(std::exchange(rhs.size_, 0))
  {
  }

  template < typename T >
  ForwardList< T >::ForwardList(size_type size, const_reference value): ForwardList()
  {
    for (size_type i = 0; i != size; ++i) {
      pushBack(value);
    }
  }

  template < typename T >
  template < typename InputIt, detail::enable_if_input_iterator< InputIt > >
  ForwardList< T >::ForwardList(InputIt first, InputIt last): ForwardList()
  {
    for (; first != last; ++first) {
      pushBack(*first);
    }
  }

  template < typename T >
  ForwardList< T >::ForwardList(std::initializer_list< value_type > init):
    ForwardList(init.begin(), init.end())
  {
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
    begin_ = std::exchange(rhs.begin_, nullptr);
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
    return iterator(begin_);
  }

  template < typename T >
  typename ForwardList< T >::iterator ForwardList< T >::end() noexcept
  {
    return iterator(nullptr);
  }

  template < typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::begin() const noexcept
  {
    return const_iterator(begin_);
  }

  template < typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::end() const noexcept
  {
    return const_iterator(nullptr);
  }

  template < typename T >
  typename ForwardList< T >::reference ForwardList< T >::front()
  {
    assert(!empty());
    return begin_->data;
  }

  template < typename T >
  typename ForwardList< T >::reference ForwardList< T >::back()
  {
    assert(!empty());
    return end_->data;
  }

  template < typename T >
  typename ForwardList< T >::const_reference ForwardList< T >::front() const
  {
    assert(!empty());
    return begin_->data;
  }

  template < typename T >
  typename ForwardList< T >::const_reference ForwardList< T >::back() const
  {
    assert(!empty());
    return end_->data;
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
  void ForwardList< T >::pushBack(value_type value)
  {
    emplaceBack(std::move(value));
  }

  template < typename T >
  void ForwardList< T >::pushFront(value_type value)
  {
    emplaceFront(std::move(value));
  }

  template < typename T >
  template < typename... Args >
  void ForwardList< T >::emplaceBack(Args&&... args)
  {
    std::unique_ptr< Node > newNode = std::make_unique< Node >(
        Node{ value_type(std::forward< Args >(args)...), nullptr });
    if (end_ == nullptr) {
      begin_ = end_ = newNode.release();
    } else {
      end_->next = newNode.release();
      end_ = end_->next;
    }
    ++size_;
  }

  template < typename T >
  template < typename... Args >
  void ForwardList< T >::emplaceFront(Args&&... args)
  {
    begin_ = new Node{ value_type(std::forward< Args >(args)...), begin_ };
    if (end_ == nullptr) {
      end_ = begin_;
    }
    ++size_;
  }

  template < typename T >
  template < typename... Args >
  typename ForwardList< T >::iterator ForwardList< T >::emplaceAfter(
      const_iterator position, Args&&... args)
  {
    if (position == end()) {
      emplaceBack(std::forward< Args >(args)...);
      return iterator(end_);
    }
    Node* prev = position.node_;
    Node* newNode = new Node{ value_type(std::forward< Args >(args)...), prev->next };
    prev->next = newNode;
    ++size_;
    return iterator(newNode);
  }

  template < typename T >
  void ForwardList< T >::popBack()
  {
    assert(!empty());
    if (begin_ == end_) {
      popFront();
    } else {
      Node* tmp = begin_;
      while (tmp->next != end_) {
        tmp = tmp->next;
      }
      delete tmp->next;
      tmp->next = nullptr;
      end_ = tmp;
      --size_;
    }
  }

  template < typename T >
  void ForwardList< T >::popFront()
  {
    assert(!empty());
    Node* tmp = begin_;
    begin_ = begin_->next;
    if (begin_ == nullptr) {
      end_ = nullptr;
    }
    --size_;
    delete tmp;
  }

  template < typename T >
  typename ForwardList< T >::iterator ForwardList< T >::eraseAfter(
      const_iterator position)
  {
    assert(!empty());
    return eraseAfter(position, std::next(position, 2));
  }

  template < typename T >
  typename ForwardList< T >::iterator ForwardList< T >::eraseAfter(const_iterator first,
      const_iterator last)
  {
    // TODO: Refactor
    assert(!empty());
    Node* firstPtr = first.node_->next;
    Node* lastPtr = last.node_;
    while (firstPtr != lastPtr) {
      Node* tmp = firstPtr->next;
      delete firstPtr;
      firstPtr = tmp;
      --size_;
    }
    first.node_->next = firstPtr;
    return iterator(first.node_);
  }

  template < typename T >
  void ForwardList< T >::assign(size_type size, const_reference value)
  {
    ForwardList tmp(size, value);
    swap(tmp);
  }

  template < typename T >
  template < typename InputIt, detail::enable_if_input_iterator< InputIt > >
  void ForwardList< T >::assign(InputIt first, InputIt last)
  {
    ForwardList tmp(first, last);
    swap(tmp);
  }

  template < typename T >
  void ForwardList< T >::assign(std::initializer_list< value_type > init)
  {
    ForwardList tmp(init);
    swap(tmp);
  }

  template < typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insertAfter(
      const_iterator position, value_type value)
  {
    return emplaceAfter(position, std::move(value));
  }

  template < typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insertAfter(
      const_iterator position, size_type size, const_reference value)
  {
    if (size == 0) {
      return iterator(position.node_);
    }
    iterator result = emplaceAfter(position, value);
    position = result;
    for (size_type i = 1; i != size; ++i) {
      position = emplaceAfter(position, value);
    }
    return result;
  }

  template < typename T >
  template < typename InputIt, detail::enable_if_input_iterator< InputIt > >
  typename ForwardList< T >::iterator ForwardList< T >::insertAfter(
      const_iterator position, InputIt first, InputIt last)
  {
    if (first == last) {
      return iterator(position.node_);
    }
    iterator result = emplaceAfter(position, *first);
    iterator pos = result;
    ++first;
    for (; first != last; ++first) {
      pos = emplaceAfter(pos, *first);
    }
    return result;
  }

  template < typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insertAfter(
      const_iterator position, std::initializer_list< value_type > init)
  {
    return insertAfter(position, init.begin(), init.end());
  }

  template < typename T >
  void ForwardList< T >::clear() noexcept
  {
    while (!empty()) {
      popFront();
    }
  }

  template < typename T >
  void ForwardList< T >::swap(ForwardList& rhs) noexcept
  {
    using std::swap;
    swap(begin_, rhs.begin_);
    swap(end_, rhs.end_);
    swap(size_, rhs.size_);
  }

  template < typename T >
  void ForwardList< T >::remove(const_reference value)
  {
    removeIf([&value](const_reference rhs) -> bool {
      return value == rhs;
    });
  }

  template < typename T >
  template < typename UnaryPredicate >
  void ForwardList< T >::removeIf(UnaryPredicate p)
  {
    for (; begin_ != nullptr && p(begin_->data); --size_) {
      Node* tmp = begin_;
      begin_ = begin_->next;
      delete tmp;
    }
    if (begin_ == nullptr) {
      end_ = nullptr;
      return;
    }
    Node* prev = begin_;
    Node* curr = begin_->next;
    while (curr != nullptr) {
      if (p(curr->data)) {
        prev->next = curr->next;
        if (curr == end_) {
          end_ = prev;
        }
        delete curr;
        --size_;
      } else {
        prev = curr;
      }
      curr = prev->next;
    }
  }

  template < typename T >
  void ForwardList< T >::spliceAfter(const_iterator, ForwardList&)
  {
    // TODO: Implement splice
  }

  template < typename T >
  void ForwardList< T >::spliceAfter(const_iterator, ForwardList&, const_iterator)
  {
    // TODO: Implement splice
  }

  template < typename T >
  void ForwardList< T >::spliceAfter(const_iterator, ForwardList&, const_iterator,
      const_iterator)
  {
    // TODO: Implement splice
  }

  template < typename T >
  void ForwardList< T >::reverse()
  {
    // TODO: Implement reverse
  }

  template < typename T >
  void ForwardList< T >::unique()
  {
    return unique(std::equal_to< value_type >{});
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
    return sort(std::less< value_type >{});
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
  template < typename Comp >
  void ForwardList< T >::merge(ForwardList&, Comp)
  {
    // TODO: Implement merge
  }
}

#endif

