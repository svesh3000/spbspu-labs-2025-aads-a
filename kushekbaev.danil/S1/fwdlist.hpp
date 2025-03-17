#ifndef FWDLIST_HPP
#define FWDLIST_HPP

#include <utility>
#include "iterator.hpp"

namespace kushekbaev
{
  template< typename T >
  struct FwdList
  {
    FwdList();
    FwdList(const FwdList& other);
    FwdList(FwdList&& other) noexcept;
    ~FwdList();
    FwdList& operator=(const FwdList& other) noexcept;
    FwdList& operator=(FwdList&& other) noexcept;

    Iterator< T > begin() const noexcept;
    Iterator< T > end() const noexcept;

    T& front() const noexcept;
    T& back() const noexcept;

    size_t size() const noexcept;
    bool empty() const noexcept;

    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front() noexcept;
    void pop_back() noexcept;
    void swap(FwdList& other) noexcept;
    void clear() noexcept;

    private:
      Node< T >* fake_;
      size_t size_;
  };

  template< typename T >
  FwdList< T >::FwdList():
    fake_(new Node< T >(T())),
    size_(0)
  {
    fake_ -> next_ = fake_;
  }

  template< typename T >
  FwdList< T >::FwdList(const FwdList& other):
    FwdList()
  {
    for (Iterator< T > it = other.begin(); it != other.end(); ++it)
    {
      push_back(*it);
    }
  }

  template< typename T >
  FwdList< T >::FwdList(FwdList&& other) noexcept:
    fake_(other.fake_),
    listSize_(other.listSize_)
  {
    other.fake_ = new Node< T >();
    other.fake_->next_ = other.fake_;
    other.listSize_ = 0;
  }

  template< typename T >
  FwdList< T >::~FwdList()
  {
    clear();
    delete fake_;
  }

  template< typename T >
  typename FwdList< T >::FwdList& FwdList< T >::operator=(const FwdList& other) noexcept
  {
    if (size() != other.size())
    {
      return false;
    }
    auto it1 = begin();
    auto it2 = other.begin();
    while (it1 != end())
    {
      if (*it1 != *it2)
      {
        return false;
      }
      ++it1;
      ++it2;
    }
    return true;
  }

  template< typename T >
  typename FwdList< T >::FwdList& FwdList< T >::operator=(FwdList&& other) noexcept
  {
    return !(*this == other);
  }

  template< typename T >
  Iterator< T > FwdList< T >::begin() const noexcept
  {
    return Iterator< T >(fake_ -> next_);
  }

  template< typename T >
  Iterator< T > FwdList< T >::end() const noexcept
  {
    return Iterator< T >(fake_);
  }

  template< typename T >
  T& FwdList< T >::front() const noexcept
  {
    assert(!empty());
    return fake_ -> next_ -> data_;
  }

  template< typename T >
  T& FwdList< T >::back() const noexcept
  {
    assert(!empty());
    Node< T >* current = fake_;
    while (current -> next_ != fake_)
    {
      current = current -> next_;
    }
    return current -> data_;
  }

  template< typename T >
  size_t FwdList< T >::size() const noexcept
  {
    return size_;
  }

  template< typename T >
  bool FwdList< T >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< typename T >
  void FwdList< T >::push_front(const T& value)
  {
    Node< T >* newNode = new Node< T >(value);
    newNode -> next_ = fake_ -> next_;
    fake_ -> next_ = newNode;
    ++size_;
  }

  template< typename T >
  void FwdList< T >::push_back(const T& value)
  {
    Node< T >* newNode = new Node< T >(value);
    Node< T >* current = fake_;
    while (current -> next_ != fake_)
    {
      current = current -> next_;
    }
    current -> next_ = newNode;
    newNode -> next_ = fake_;
    ++size_;
  }

  template< typename T >
  void FwdList< T >::pop_front() noexcept
  {
    assert(!empty());
    Node< T >* todelete = fake_ -> next_;
    fake_ -> next_ = todelete -> next_;
    delete todelete;
    --size_;
  }

  template < class T >
  void FwdList< T >::pop_back() noexcept
  {
    assert(!empty());
    Node< T >* todelete = fake_;
    while (todelete -> next_ -> next_ != fake_)
    {
      todelete = todelete -> next_;
    }
    delete todelete -> next_;
    todelete -> next_ = fake_;
    --size_;
  }

  template< typename T >
  void FwdList< T >::swap(FwdList& other) noexcept
  {
    std::swap(fake_, other.fake_);
    std::swap(size_, other.size_);
  }

  template< typename T >
  void FwdList< T >::clear() noexcept
  {
    while (!empty())
    {
      pop_front();
    }
  }
}

#endif
