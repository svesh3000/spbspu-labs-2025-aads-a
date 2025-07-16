#ifndef FORWARD_RING_LIST_HPP
#define FORWARD_RING_LIST_HPP

#include <iterator>
#include <cstddef>
#include <memory>
#include <cassert>

namespace petrov
{
  template< typename T >
  struct ListNode
  {
    T data;
    ListNode< T > * next;
  };

  template< typename T >
  struct ForwardRingList;

  template< typename T >
  struct ConstForwardListIterator: std::iterator< std::forward_iterator_tag, T >
  {
    friend struct ForwardRingList< T >;
  public:
    using node_t = ListNode< T >;
    using this_t = ConstForwardListIterator< T >;
    ConstForwardListIterator();
    ConstForwardListIterator(const this_t & rhs) = default;
    ~ConstForwardListIterator() = default;
    this_t & operator=(const this_t & rhs) = default;
    this_t & operator++();
    this_t operator++(int);
    const T & operator*() const;
    const T * operator->() const;
    bool operator==(const this_t & rhs) const;
    bool operator!=(const this_t & rhs) const;
  private:
    const ListNode< T > * node_;
    explicit ConstForwardListIterator(const node_t * node);
  };

  template< typename T >
  struct ForwardListIterator: std::iterator< std::forward_iterator_tag, T >
  {
    friend struct ForwardRingList< T >;
  public:
    using node_t = ListNode< T >;
    using this_t = ForwardListIterator< T >;
    ForwardListIterator();
    ForwardListIterator(const this_t & rhs) = default;
    ~ForwardListIterator() = default;
    this_t & operator=(const this_t & rhs) = default;
    this_t & operator++();
    this_t operator++(int);
    T & operator*();
    T * operator->();
    bool operator==(const this_t & rhs) const;
    bool operator!=(const this_t & rhs) const;
  private:
    ListNode< T > * node_;
    explicit ForwardListIterator(node_t * node);
  };

  template< typename T >
  struct ForwardRingList
  {
  public:
    using this_t = ForwardRingList< T >;
    using node_t = ListNode< T >;
    using const_it_t = ConstForwardListIterator< T >;
    using it_t = ForwardListIterator< T >;
    ForwardRingList();
    ForwardRingList(const this_t & rhs);
    ForwardRingList(this_t && rhs);
    ForwardRingList(size_t n, const T & val);
    ~ForwardRingList();
    this_t & operator=(const this_t & rhs);
    this_t & operator=(this_t && rhs);
    bool operator==(const this_t & rhs) const;
    bool operator!=(const this_t & rhs) const;
    const_it_t cbegin() const;
    const_it_t cend() const;
    it_t begin();
    it_t end();
    T & front();
    const T & front() const;
    T & back();
    const T & back() const;
    bool empty() const noexcept;
    size_t size() const noexcept;
    void assign(size_t n, const T & val);
    template< typename T1 >
    void push_front(T1 && val);
    template< class THIS_T >
    void splice(const it_t pos, THIS_T && rhs);
    template< class THIS_T >
    void splice(const it_t pos, THIS_T && rhs, const it_t i);
    template< class THIS_T >
    void splice(const it_t pos, THIS_T && rhs, const it_t first, const it_t last);
    void pop_front();
    void remove(const T & val);
    template< typename Cond >
    void remove_if(Cond cond);
    void clear() noexcept;
    void reverse();
    void swap(this_t & rhs) noexcept;
  private:
    node_t * head_;
    node_t * tail_;
    size_t size_;
  };
  
  template< typename T >
  ConstForwardListIterator< T >::ConstForwardListIterator():
    node_(nullptr)
  {}

  template< typename T >
  typename ConstForwardListIterator< T >::this_t & ConstForwardListIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template< typename T >
  typename ConstForwardListIterator< T >::this_t ConstForwardListIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  const T & ConstForwardListIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T >
  const T * ConstForwardListIterator< T >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T >
  bool ConstForwardListIterator< T >::operator==(const this_t & rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename T >
  bool ConstForwardListIterator< T >::operator!=(const this_t & rhs) const
  {
    return !(rhs == *this);
  }

  template< typename T >
  ConstForwardListIterator< T >::ConstForwardListIterator(const node_t * node):
    node_(node)
  {}

  template< typename T >
  ForwardListIterator< T >::ForwardListIterator():
    node_(nullptr)
  {}

  template< typename T >
  typename ForwardListIterator< T >::this_t & ForwardListIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template< typename T >
  typename ForwardListIterator< T >::this_t ForwardListIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  T & ForwardListIterator< T >::operator*()
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T >
  T * ForwardListIterator< T >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T >
  bool ForwardListIterator< T >::operator==(const this_t & rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename T >
  bool ForwardListIterator< T >::operator!=(const this_t & rhs) const
  {
    return !(rhs == *this);
  }

  template< typename T >
  ForwardListIterator< T >::ForwardListIterator(node_t * node):
    node_(node)
  {}

  template< typename T >
  ForwardRingList< T >::ForwardRingList():
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}

  template< typename T >
  ForwardRingList< T >::ForwardRingList(const this_t & rhs):
    head_(nullptr),
    tail_(nullptr),
    size_(rhs.size_)
  {
    if (rhs.empty())
    {
      return;
    }
    auto it = rhs.cbegin();
    head_ = new node_t{ *it, nullptr };
    auto subhead = head_;
    try
    {
      while (it++ != rhs.cend())
      {
        subhead->next = new node_t{ *it, nullptr };
        subhead = subhead->next;
      }
    }
    catch (...)
    {
      while (head_->next)
      {
        auto todelete = head_;
        head_ = todelete->next;
        delete todelete;
      }
      delete head_;
      throw;
    }
    subhead->next = head_;
    tail_ = subhead;
  }

  template< typename T >
  ForwardRingList< T >::ForwardRingList(this_t && rhs):
    head_(rhs.head_),
    tail_(rhs.tail_),
    size_(rhs.size_)
  {
    rhs.head_ = nullptr;
    rhs.tail_ = nullptr;
  }

  template< typename T >
  ForwardRingList< T >::ForwardRingList(size_t n, const T & val):
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {
    try
    {
      for (size_t i = 0; i < n; i++)
      {
        push_front(val);
      }
    }
    catch (const std::bad_alloc & e)
    {
      clear();
      throw;
    }
  }

  template< typename T >
  ForwardRingList< T >::~ForwardRingList()
  {
    clear();
  }

  template< typename T >
  typename ForwardRingList< T >::this_t & ForwardRingList< T >::operator=(const this_t & rhs)
  {
    this_t cpy(rhs);
    swap(cpy);
    return *this;
  }

  template< typename T >
  typename ForwardRingList< T >::this_t & ForwardRingList< T >::operator=(this_t && rhs)
  {
    clear();
    head_ = rhs.head_;
    tail_ = rhs.tail_;
    size_ = rhs.size_;
    rhs.head_ = nullptr;
    rhs.tail_ = nullptr;
    rhs.size_ = 0;
    return *this;
  }

  template< typename T >
  bool ForwardRingList< T >::operator==(const this_t & rhs) const
  {
    if (empty() && rhs.empty())
    {
      return true;
    }
    else
    {
      if (size() == rhs.size() && size() != 0)
      {
        auto it = cbegin();
        auto rhs_it = rhs.cbegin();
        do
        {
          if (*it != *rhs_it)
          {
            return false;
          }
          ++rhs_it;
        }
        while (it++ != cend());
        return true;
      }
      else
      {
        return false;
      }
    }
  }

  template< typename T >
  bool ForwardRingList< T >::operator!=(const this_t & rhs) const
  {
    return !(*this == rhs);
  }

  template< typename T >
  typename ForwardRingList< T >::const_it_t ForwardRingList< T >::cbegin() const
  {
    return const_it_t(head_);
  }

  template< typename T >
  typename ForwardRingList< T >::const_it_t ForwardRingList< T >::cend() const
  {
    return const_it_t(tail_);
  }

  template< typename T >
  typename ForwardRingList< T >::it_t ForwardRingList< T >::begin()
  {
    return it_t(head_);
  }

  template< typename T >
  typename ForwardRingList< T >::it_t ForwardRingList< T >::end()
  {
    return it_t(tail_);
  }

  template< typename T >
  T & ForwardRingList< T >::front()
  {
    return const_cast< T >(static_cast< const ForwardRingList< T > * >(this)->front());
  }

  template< typename T >
  const T & ForwardRingList< T >::front() const
  {
    return head_->data;
  }

  template< typename T >
  T & ForwardRingList< T >::back()
  {
    return const_cast< T >(static_cast< const ForwardRingList< T > * >(this)->back());
  }

  template< typename T >
  const T & ForwardRingList< T >::back() const
  {
    return tail_->data;
  }

  template< typename T >
  bool ForwardRingList< T >::empty() const noexcept
  {
    return !size_;
  }

  template< typename T >
  size_t ForwardRingList< T >::size() const noexcept
  {
    return size_;
  }

  template< typename T >
  void ForwardRingList< T >::assign(size_t n, const T & val)
  {
    node_t * new_head = new node_t{ val, nullptr };
    node_t * new_tail = new_head;
    try
    {
      for (size_t i = 0; i < n - 1; i++)
      {
        new_tail->next = new node_t{ val, nullptr };
        new_tail = new_tail->next;
      }
    }
    catch (const std::bad_alloc & e)
    {
      while (new_head->next)
      {
        auto todelete = new_head;
        new_head = todelete->next;
        delete todelete;
      }
      delete new_head;
      throw;
    }
    clear();
    head_ = new_head;
    tail_ = new_tail;
    tail_->next = head_;
    size_ = n;
  }

  template< typename T >
  template< typename T1 >
  void ForwardRingList< T >::push_front(T1 && val)
  {
    if (empty())
    {
      head_ = new node_t{ std::forward< T1 >(val), head_ };
      tail_ = head_;
      tail_->next = head_;
    }
    else
    {
      auto temp = head_;
      tail_->next = new node_t{ std::forward< T1 >(val), nullptr };
      head_ = tail_->next;
      head_->next = temp;
    }
    size_++;
  }

  template< typename T >
  template< class THIS_T >
  void ForwardRingList< T >::splice(const it_t pos, THIS_T && rhs)
  {
    if (!rhs.empty())
    {
      if (pos.node_ != tail_)
      {
        auto temp = pos.node_->next;
        pos.node_->next = rhs.head_;
        rhs.tail_->next = temp;
      }
      else
      {
        pos.node_->next = rhs.head_;
        rhs.tail_->next = head_;
        tail_ = rhs.tail_;
      }
      size_ += rhs.size_;
      rhs.head_ = nullptr;
      rhs.tail_ = nullptr;
      rhs.size_ = 0;
    }
  }

  template< typename T >
  template< class THIS_T >
  void ForwardRingList< T >::splice(const it_t pos, THIS_T && rhs, const it_t i)
  {
    auto added = i.node_->next;
    if (added == rhs.head_)
    {
      rhs.tail_->next = rhs.head_->next;
      rhs.head_ = rhs.tail_->next;
    }
    else if (added == rhs.tail_)
    {
      rhs.tail_ = i.node_;
      rhs.tail_->next = rhs.head_;
    }
    else
    {
      i.node_->next = added->next;
    }
    rhs.size_--;
    if (rhs.empty())
    {
      rhs.head_ = nullptr;
      rhs.tail_ = nullptr;
    }
    if (pos.node_ != tail_)
    {
      auto temp = pos.node_->next;
      pos.node_->next = added;
      added->next = temp;
    }
    else
    {
      pos.node_->next = added;
      added->next = head_;
      tail_ = added;
    }
    size_++;
  }

  template< typename T >
  template< class THIS_T >
  void ForwardRingList< T >::splice(const it_t pos, THIS_T && rhs, const it_t first, const it_t last)
  {
    if (first.node_->next == last.node_)
    {
      return;
    }
    size_t nodes_removed = 0;
    bool is_head_removed = false;
    bool is_tail_removed = false;
    auto added_head = first.node_->next;
    if (added_head == rhs.head_)
    {
      is_head_removed = true;
    }
    else if (added_head == rhs.tail_)
    {
      is_tail_removed = true;
    }
    nodes_removed++;
    auto added_tail = added_head;
    while (added_tail->next != last.node_)
    {
      added_tail = added_tail->next;
      if (added_tail == rhs.head_)
      {
        is_head_removed = true;
      }
      else if (added_tail == rhs.tail_)
      {
        is_tail_removed = true;
      }
      nodes_removed++;
    }
    first.node_->next = last.node_;
    if (is_head_removed)
    {
      rhs.head_ = last.node_;
    }
    if (is_tail_removed)
    {
      rhs.tail_ = first.node_;
    }
    rhs.size_ -= nodes_removed;
    if (pos.node_ != tail_)
    {
      auto temp = pos.node_->next;
      pos.node_->next = added_head;
      added_tail->next = temp;
    }
    else
    {
      pos.node_->next = added_head;
      added_tail->next = head_;
      tail_ = added_tail;
    }
    size_ += nodes_removed;
  }

  template< typename T >
  void ForwardRingList< T >::pop_front()
  {
    if (empty())
    {
      return;
    }
    auto todelete = head_;
    head_ = head_->next;
    delete todelete;
    size_--;
    if (!size_)
    {
      head_ = nullptr;
      tail_ = nullptr;
    }
    else
    {
      tail_->next = head_;
    }
  }

  template< typename T >
  void ForwardRingList< T >::remove(const T & val)
  {
    if (empty())
    {
      return;
    }
    auto prev = head_;
    auto curr = head_->next;
    while (curr != tail_)
    {
      if (curr->data == val)
      {
        auto todelete = curr;
        curr = todelete->next;
        prev->next = curr;
        delete todelete;
        size_--;
      }
      else
      {
        curr = curr->next;
        prev = prev->next;
      }
    }
    if (tail_->data == val)
    {
      auto todelete = tail_;
      tail_ = prev;
      tail_->next = head_;
      delete todelete;
      size_--;
    }
    if (head_->data == val)
    {
      auto todelete = head_;
      head_ = todelete->next;
      tail_->next = head_;
      delete todelete;
      size_--;
    }
    if (!size_)
    {
      head_ = nullptr;
      tail_ = nullptr;
    }
  }

  template< typename T >
  template< typename Cond >
  void ForwardRingList< T >::remove_if(Cond cond)
  {
    if (empty())
    {
      return;
    }
    auto prev = head_;
    auto curr = head_->next;
    while (curr != tail_)
    {
      if (cond(curr->data))
      {
        auto todelete = curr;
        curr = todelete->next;
        prev->next = curr;
        delete todelete;
        size_--;
      }
      else
      {
        curr = curr->next;
        prev = prev->next;
      }
    }
    if (cond(tail_->data))
    {
      auto todelete = tail_;
      tail_ = prev;
      tail_->next = head_;
      delete todelete;
      size_--;
    }
    if (cond(head_->data))
    {
      auto todelete = head_;
      head_ = todelete->next;
      tail_->next = head_;
      delete todelete;
      size_--;
    }
    if (!size_)
    {
      head_ = nullptr;
      tail_ = nullptr;
    }
  }

  template< typename T >
  void ForwardRingList< T >::clear() noexcept
  {
    if (empty())
    {
      return;
    }
    while (head_ != tail_)
    {
      auto todelete = head_;
      head_ = head_->next;
      delete todelete;
    }
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
  }

  template< typename T >
  void ForwardRingList< T >::reverse()
  {
    if (empty())
    {
      return;
    }
    auto prev = tail_;
    auto curr = head_;
    auto next = head_->next;
    while (curr != tail_)
    {
      curr->next = prev;
      prev = curr;
      curr = next;
      next = next->next;
    }
    curr->next = prev;
    auto temp = head_;
    head_ = tail_;
    tail_ = temp;
  }

  template< typename T >
  void ForwardRingList< T >::swap(this_t & rhs) noexcept
  {
    std::swap(head_, rhs.head_);
    std::swap(tail_, rhs.tail_);
    std::swap(size_, rhs.size_);
  }
}

#endif
