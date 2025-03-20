#ifndef FWDLIST_RING_HPP
#define FWDLIST_RING_HPP
#include <cassert>
#include "fwd-iterator.hpp"
#include "fwd-citerator.hpp"

namespace
{
  template < typename T >
  struct Comparator
  {
  public:
    Comparator(const T &val):
      val_(val)
    {}

    bool operator()(const T &other) const
    {
      return val_ == other;
    }

  private:
    T val_;
  };
}

namespace sveshnikov
{
  template < typename T >
  class FwdList
  {
  public:
    explicit FwdList();
    explicit FwdList(size_t n, const T& val);
    FwdList(const FwdList< T > &fwdlst);
    FwdList(FwdList< T > &&fwdlst);
    ~FwdList();
    FwdIterator< T > begin() noexcept;
    ConstFwdIterator< T > begin() const noexcept;
    ConstFwdIterator< T > cbegin() const noexcept;
    FwdIterator< T > end() noexcept;
    ConstFwdIterator< T > end() const noexcept;
    ConstFwdIterator< T > cend() const noexcept;
    FwdIterator< T > before_begin() noexcept;
    ConstFwdIterator< T > before_begin() const noexcept;
    ConstFwdIterator< T > cbefore_begin() const noexcept;
    T &front() noexcept;
    const T &front() const noexcept;
    T &back() noexcept;
    const T &back() const noexcept;
    bool empty() const noexcept;
    size_t getSize() const noexcept;
    void push_front(const T &val);
    void push_front(T &&val);
    void push_back(const T &val);
    void push_back(T &&val);
    void pop_front() noexcept;
    void pop_back() noexcept;
    void swap(FwdList< T > &fwdlst) noexcept;
    void clear() noexcept;
    void remove(const T& val) noexcept;
    template <class Predicate>
    void remove_if (Predicate pred) noexcept;

  private:
    node_t< T > *head_;
    node_t< T > *tail_;
    size_t size_;
    void push_impl(node_t< T > *node);
    void resetPointers();
  };

  template < typename T >
  FwdList< T >::FwdList():
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}

  template < typename T >
  FwdList< T >::FwdList(size_t n, const T& val):
    FwdList()
  {
    for (size_t size = 0; size < n; size++)
    {
      try
      {
        push_back(val);
      }
      catch (std::bad_alloc &e)
      {
        clear();
        throw;
      }
    }
  }

  template < typename T >
  FwdList< T >::FwdList(const FwdList< T > &fwdlst):
    FwdList()
  {
    if (!fwdlst.empty())
    {
      push_back(fwdlst.front());
      for (ConstFwdIterator< T > it = ++fwdlst.cbegin(); it != fwdlst.cend(); it++)
      {
        try
        {
          push_back(*it);
        }
        catch (std::bad_alloc &e)
        {
          clear();
          throw;
        }
      }
    }
  }

  template < typename T >
  FwdList< T >::FwdList(FwdList< T > &&fwdlst):
    head_(fwdlst.head_),
    tail_(fwdlst.tail_),
    size_(fwdlst.size_)
  {
    fwdlst.head_ = nullptr;
    fwdlst.tail_ = nullptr;
    fwdlst.size_ = 0;
  }

  template < typename T >
  FwdList< T >::~FwdList()
  {
    clear();
  }

  template < typename T >
  FwdIterator< T > FwdList< T >::begin() noexcept
  {
    return FwdIterator< T >(head_);
  }

  template < typename T >
  ConstFwdIterator< T > FwdList< T >::begin() const noexcept
  {
    return cbegin();
  }

  template < typename T >
  ConstFwdIterator< T > FwdList< T >::cbegin() const noexcept
  {
    return ConstFwdIterator< T >(head_);
  }

  template < typename T >
  FwdIterator< T > FwdList< T >::end() noexcept
  {
    return begin();
  }

  template < typename T >
  ConstFwdIterator< T > FwdList< T >::end() const noexcept
  {
    return cbegin();
  }

  template < typename T >
  ConstFwdIterator< T > FwdList< T >::cend() const noexcept
  {
    return cbegin();
  }

  template < typename T >
  FwdIterator< T > FwdList< T >::before_begin() noexcept
  {
    return FwdIterator< T >(tail_);
  }

  template < typename T >
  ConstFwdIterator< T > FwdList< T >::before_begin() const noexcept
  {
    return cbefore_begin();
  }

  template < typename T >
  ConstFwdIterator< T > FwdList< T >::cbefore_begin() const noexcept
  {
    return ConstFwdIterator< T >(tail_);
  }

  template < typename T >
  T &FwdList< T >::front() noexcept
  {
    return const_cast<T &>(static_cast< const FwdList< T > & >(*this).front());
  }

  template < typename T >
  const T &FwdList< T >::front() const noexcept
  {
    assert(head_ != nullptr);
    return head_->data_;
  }

  template < typename T >
  T &FwdList< T >::back() noexcept
  {
    return const_cast<T &>(static_cast< const FwdList< T > & >(*this).back());
  }

  template < typename T >
  const T &FwdList< T >::back() const noexcept
  {
    assert(tail_ != nullptr);
    return tail_->data_;
  }

  template < typename T >
  bool FwdList< T >::empty() const noexcept
  {
    return size_ == 0;
  }

  template < typename T >
  size_t FwdList< T >::getSize() const noexcept
  {
    return size_;
  }

  template < typename T >
  void FwdList< T >::push_impl(node_t< T > *node)
  {
    if (empty())
    {
      node->next_ = node;
      tail_ = node;
      head_ = node;
    }
    else
    {
      tail_->next_ = node;
    }
    size_++;
  }

  template < typename T >
  void FwdList< T >::push_front(const T &val)
  {
    node_t< T > *node = new node_t< T >{val, head_};
    push_impl(node);
    head_ = node;
  }

  template < typename T >
  void FwdList< T >::push_front(T &&val)
  {
    push_front(val);
  }

  template < typename T >
  void FwdList< T >::push_back(const T &val)
  {
    node_t< T > *node = new node_t< T >{val, head_};
    push_impl(node);
    tail_ = node;
  }

  template < typename T >
  void FwdList< T >::push_back(T &&val)
  {
    push_back(val);
  }

  template < typename T >
  void FwdList< T >::resetPointers()
  {
    head_ = nullptr;
    tail_ = nullptr;
  }

  template < typename T >
  void FwdList< T >::pop_front() noexcept
  {
    assert(!empty());
    node_t< T > *node = head_->next_;
    delete head_;
    size_--;
    if (empty())
    {
      resetPointers();
    }
    else
    {
      head_ = node;
      tail_->next_ = head_;
    }
  }

  template < typename T >
  void FwdList< T >::pop_back() noexcept
  {
    assert(!empty());
    node_t< T > *current = tail_;
    for (ConstFwdIterator< T > it = cbegin(); it != cbefore_begin(); it++)
    {
      current = current->next_;
    }
    delete tail_;
    size_--;
    if (empty())
    {
      resetPointers();
    }
    else
    {
      tail_ = current;
      tail_->next_ = head_;
    }
  }

  template < typename T >
  void FwdList< T >::swap(FwdList< T > &fwdlst) noexcept
  {
    std::swap(head_, fwdlst.head_);
    std::swap(tail_, fwdlst.tail_);
    std::swap(size_, fwdlst.size_);
  }

  template < typename T >
  void FwdList< T >::clear() noexcept
  {
    while (!empty())
    {
      pop_front();
    }
  }

  template < typename T >
  void FwdList< T >::remove(const T& val) noexcept
  {
    remove_if(Comparator< T >(val));
  }

  template <typename T>
  template <class Predicate>
  void FwdList<T>::remove_if(Predicate pred) noexcept
  {
    if (empty())
    {
      return;
    }
    node_t<T>* prev = tail_;
    node_t<T>* current = head_;
    size_t count = size_;
    while (count > 0)
    {
      node_t<T>* next = current->next_;
      if (pred(current->data_))
      {
        if (current == head_)
        {
          head_ = next;
        }
        if (current == tail_)
        {
          tail_ = prev;
        }
        prev->next_ = next;
        delete current;
        size_--;
        if (size_ == 0)
        {
          head_ = nullptr;
          tail_ = nullptr;
        }
      }
      else
      {
        prev = current;
      }
      current = next;
      count--;
    }
  }
}

#endif
