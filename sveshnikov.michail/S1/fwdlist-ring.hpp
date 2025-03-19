#ifndef FWDLIST_RING_HPP
#define FWDLIST_RING_HPP
#include <cassert>
#include "fwd-iterator.hpp"
#include "fwd-citerator.hpp"

namespace sveshnikov
{
  template < typename T >
  class FwdList
  {
  public:
    explicit FwdList();
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
    T &front();
    const T &front() const;
    T &back();
    const T &back() const;
    bool empty() const noexcept;
    size_t getSize() const noexcept;
    void push_front(const T &val);
    void push_front(T &&val);
    void push_back(const T &val);
    void push_back(T &&val);
    void pop_front();
    void pop_back();
    void swap(FwdList< T > &fwdlst);
    void clear() noexcept;

  private:
    node_t< T > *head_;
    node_t< T > *tail_;
    size_t size_;
    void push_impl(node_t< T > *node);
  };

  template < typename T >
  FwdList< T >::FwdList():
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}

  template < typename T >
  FwdList< T >::FwdList(const FwdList< T > &fwdlst):
    head_(nullptr),
    tail_(nullptr),
    size_(0)
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
  T &FwdList< T >::front()
  {
    return const_cast<T &>(static_cast<const FwdList< T > &>(*this).front());
  }

  template < typename T >
  const T &FwdList< T >::front() const
  {
    assert(head_ != nullptr);
    return head_->data_;
  }

  template < typename T >
  T &FwdList< T >::back()
  {
    return const_cast<T &>(static_cast<const FwdList< T > &>(*this).back());
  }

  template < typename T >
  const T &FwdList< T >::back() const
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
  void FwdList< T >::pop_front()
  {
    assert(!empty());
    node_t< T > *node = head_->next_;
    delete head_;
    head_ = node;
    tail_->next_ = node;
    size_--;
  }

  template < typename T >
  void FwdList< T >::pop_back()
  {
    assert(!empty());
    node_t< T > *current = tail_;
    for (ConstFwdIterator< T > it = cbegin(); it != cbefore_begin(); it++)
    {
      current = current->next_;
    }
    delete tail_;
    tail_ = current;
    tail_->next_ = head_;
    size_--;
  }

  template < typename T >
  void FwdList< T >::swap(FwdList< T > &fwdlst)
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
}

#endif
