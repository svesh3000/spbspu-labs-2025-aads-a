#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <stdexcept>
#include "node.hpp"
#include "iterator.hpp"

namespace maslov
{
  template< typename T >
  struct FwdList
  {
    FwdList();
    FwdList(const FwdList< T > & rhs);
    FwdList(FwdList< T > && rhs) noexcept;
    ~FwdList();

    FwdList< T > & operator=(const FwdList< T > & rhs);
    FwdList< T > & operator=(FwdList< T > && rhs) noexcept;

    FwdListIterator< T > begin();
    FwdListIterator< T > end();

    T & front() noexcept;
    const T & front() const noexcept;

    bool empty() const noexcept;
    size_t max_size() const noexcept;

    void push_front(const T & value);
    void pop_front();
    void swap(FwdList< T > & rhs) noexcept;
    void clear();
    void reverse() noexcept;
   private:
    FwdListNode< T > * fake_;
    size_t size_;
  };

  template< typename T >
  FwdList< T >::FwdList():
    fake_(new FwdListNode< T >{T(), nullptr}),
    size_(0)
  {
    fake_->next = fake_;
  }

  template< typename T >
  FwdList< T >::~FwdList()
  {
    clear();
    delete fake_;
  }

  template< typename T >
  FwdList< T >::FwdList(const FwdList< T > & rhs):
    fake_(new FwdListNode< T >{T(), nullptr}),
    size_(0)
  {
    fake_->next = fake_;
    if (!rhs.empty())
    {
      FwdListNode< T > * current = rhs.fake_->next;
      while (current != rhs.fake_)
      {
        push_front(current->data);
        current = current->next;
      }
    }
  }

  template< typename T >
  FwdList< T >::FwdList(FwdList< T > && rhs) noexcept:
    fake_(rhs.fake_),
    size_(rhs.size_)
  {
    rhs.fake_ = nullptr;
    rhs.size_ = 0;
  }

  template< typename T >
  FwdList< T > & FwdList< T >::operator=(const FwdList< T > & rhs)
  {
    if (this != std::addressof(rhs))
    {
      FwdList temp(rhs);
      swap(temp);
    }
    return *this;
  }

  template< typename T >
  FwdList< T > & FwdList< T >::operator=(FwdList< T > && rhs) noexcept
  {
    if (this != std::addressof(rhs))
    {
      clear();
      delete fake_;
      fake_ = rhs.fake_;
      size_ = rhs.size_;
      rhs.fake_ = nullptr;
      rhs.size_ = 0;
    }
    return *this;
  }

  template< typename T >
  T & FwdList< T >::front() noexcept
  {
    return const_cast< T & >(static_cast< const FwdList & >(*this).front());
  }

  template< typename T >
  const T & FwdList< T >::front() const noexcept
  {
    if (empty())
    {
        throw std::runtime_error("ERROR:: empty list");
    }
    return fake_->next->data;
  }

  template< typename T >
  bool FwdList< T >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< typename T >
  size_t FwdList< T >::max_size() const noexcept
  {
    return size_;
  }

  template< typename T >
  void FwdList< T >::swap(FwdList< T > & rhs) noexcept
  {
    std::swap(fake_, rhs.fake_);
    std::swap(size_, rhs.size_);
  }

  template< typename T >
  void FwdList< T >::push_front(const T & value)
  {
    FwdListNode< T > * newNode = new FwdListNode< T >{value, nullptr};
    if (empty())
    {
        newNode->next = fake_;
        fake_->next = newNode;
    }
    else
    {
        newNode->next = fake_->next;
        fake_->next = newNode;
    }
    size_++;
  }

  template< typename T >
  void FwdList< T >::pop_front()
  {
    if (empty())
    {
        throw std::runtime_error("ERROR: empty list");
    }
    FwdListNode< T > * node = fake_->next;
    fake_->next = node->next;
    delete node;
    size_--;
  }

  template< typename T >
  void FwdList< T >::clear()
  {
    while (!empty())
    {
      pop_front();
    }
  }

  template< typename T >
  FwdListIterator< T > FwdList< T >::begin()
  {
    return FwdListIterator< T >(fake_->next);
  }

  template< typename T >
  FwdListIterator< T > FwdList< T >::end()
  {
    return FwdListIterator< T >(fake_);
  }

  template< typename T >
  void FwdList< T >::reverse() noexcept
  {
    if (empty() || max_size() == 1)
    {
      return;
    }
    FwdListNode< T > * current = fake_->next;
    FwdListNode< T > * prev = fake_;
    FwdListNode< T > * next = nullptr;
    while (current != fake_)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    fake_->next = prev;
  }
}
#endif
