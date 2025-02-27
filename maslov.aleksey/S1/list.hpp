#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include "node.hpp"
#include "iterator.hpp"

namespace maslov
{
  template< typename T >
  struct FwdList
  {
    FwdList();
    bool empty() const noexcept;
    size_t max_size() const noexcept;
    void push_front(const T &);
    T & front() noexcept;
    const T & front() const noexcept;
    void swap(FwdList< T > &)
    FwdListIterator< T > begin() const;
    FwdListIterator< T > end() const;
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

}
#endif
