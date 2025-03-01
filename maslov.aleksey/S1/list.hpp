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
    FwdList(size_t k, const T & value);
    FwdList(const FwdList< T > & rhs);
    FwdList(FwdList< T > && rhs) noexcept;
    ~FwdList();

    FwdList< T > & operator=(const FwdList< T > & rhs);
    FwdList< T > & operator=(FwdList< T > && rhs) noexcept;

    bool operator==(const FwdList< T > & rhs) const;
    bool operator!=(const FwdList< T >& rhs) const;

    FwdListIterator< T > begin();
    FwdListConstIterator< T > begin() const;
    FwdListIterator< T > end();
    FwdListConstIterator< T > end() const;

    T & front();
    const T & front() const;

    bool empty() const noexcept;
    size_t size() const noexcept;

    void pushFront(const T & value);
    void popFront();
    void swap(FwdList< T > & rhs) noexcept;
    void clear();

    void reverse() noexcept;
    void remove(const T & value);
    template < typename Predicate >
    void removeIf(Predicate pred);
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
  FwdList< T >::FwdList(size_t k, const T & value):
    fake_(new FwdListNode< T >{T(), nullptr}),
    size_(0)
  {
    fake_->next = fake_;
    for (size_t i = 0; i < k; ++i)
    {
      pushFront(value);
    }
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
        pushFront(current->data);
        current = current->next;
      }
      reverse();
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
  T & FwdList< T >::front()
  {
    return const_cast< T & >(static_cast< const FwdList & >(*this).front());
  }

  template< typename T >
  const T & FwdList< T >::front() const
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
  size_t FwdList< T >::size() const noexcept
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
  void FwdList< T >::pushFront(const T & value)
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
  void FwdList< T >::popFront()
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
      popFront();
    }
  }

  template< typename T >
  FwdListIterator< T > FwdList< T >::begin()
  {
    return FwdListIterator< T >(fake_->next);
  }

  template< typename T >
  FwdListConstIterator< T > FwdList< T >::begin() const
  {
    return FwdListConstIterator< T >(fake_->next);
  }

  template< typename T >
  FwdListIterator< T > FwdList< T >::end()
  {
    return FwdListIterator< T >(fake_);
  }

  template< typename T >
  FwdListConstIterator< T > FwdList< T >::end() const
  {
    return FwdListConstIterator< T >(fake_);
  }

  template < typename T >
  void FwdList< T >::remove(const T & value)
  {
    auto isEqual = [value](const T & element)
    {
      return element == value;
    };
    removeIf(isEqual);
  }

  template< typename T >
  template < typename Predicate >
  void FwdList< T >::removeIf(Predicate pred)
  {
    FwdListNode< T > * current = fake_->next;
    FwdListNode< T > * prev = fake_;
    while (current != fake_)
    {
      if (pred(current->data))
      {
        prev->next = current->next;
        delete current;
        current = prev->next;
        size_--;
      }
      else
      {
        prev = current;
        current = current->next;
      }
    }
  }

  template< typename T >
  void FwdList< T >::reverse() noexcept
  {
    if (empty() || size() == 1)
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

  template< typename T >
  bool FwdList< T >::operator==(const FwdList< T > & rhs) const
  {
    if (size_ != rhs.size_)
    {
      return false;
    }
    auto it1 = begin();
    auto it2 = rhs.begin();
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
  bool FwdList< T >::operator!=(const FwdList< T > & rhs) const
  {
    return !(*this == rhs);
  }
}
#endif
