#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include "iterator.hpp"
#include <cstddef>
#include <utility>
#include <stdexcept>

namespace shramko
{
  template< typename T >
  class FwdList
  {
  public:
    using iterator = FwdListIterator< T, false >;
    using const_iterator = FwdListIterator< T, true >;

    FwdList();
    ~FwdList();
    FwdList(const FwdList& rhs);
    FwdList(FwdList&& rhs) noexcept;
    FwdList& operator=(FwdList rhs);
    FwdList& operator=(FwdList&& rhs);

    iterator begin() const noexcept;
    iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    T& front() const;
    T& back() const;
    size_t size() const noexcept;
    bool empty() const noexcept;

    void push_front(const T& value);
    void push_front(T&& value);
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_front() noexcept;
    void swap(FwdList& other) noexcept;
    void clear() noexcept;

  private:
    FwdListNode< T >* head_;
    FwdListNode< T >* tail_;
    size_t size_;

    void pushFrontNode(FwdListNode< T >* node);
    void pushBackNode(FwdListNode< T >* node);
  };
}

template< typename T >
shramko::FwdList< T >::FwdList():
  head_(nullptr),
  tail_(new FwdListNode< T >(T())),
  size_(0)
{
  tail_->next_ = tail_;
}

template< typename T >
shramko::FwdList< T >::FwdList(const FwdList& rhs):
  FwdList()
{
  FwdList< T > temp;
  for (auto it = rhs.begin(); it != rhs.end(); ++it)
  {
    temp.push_front(*it);
  }
  for (auto it = temp.begin(); it != temp.end(); ++it)
  {
    push_front(*it);
  }
}

template< typename T >
shramko::FwdList< T >::FwdList(FwdList&& rhs) noexcept:
  head_(std::exchange(rhs.head_, nullptr)),
  tail_(std::exchange(rhs.tail_, new FwdListNode< T >(T()))),
  size_(std::exchange(rhs.size_, 0))
{
  tail_->next_ = tail_;
}

template< typename T >
shramko::FwdList< T >& shramko::FwdList< T >::operator=(FwdList rhs)
{
  swap(rhs);
  return *this;
}

template< typename T >
shramko::FwdList< T >& shramko::FwdList< T >::operator=(FwdList&& rhs)
{
  if (this != &rhs)
  {
    clear();
    delete tail_;
    head_ = std::exchange(rhs.head_, nullptr);
    tail_ = std::exchange(rhs.tail_, new FwdListNode< T >(T()));
    size_ = std::exchange(rhs.size_, 0);
    tail_->next_ = tail_;
  }
  return *this;
}

template< typename T >
shramko::FwdList< T >::~FwdList()
{
  clear();
  delete tail_;
}

template< typename T >
typename shramko::FwdList< T >::iterator shramko::FwdList< T >::begin() const noexcept
{
  return iterator(head_);
}

template< typename T >
typename shramko::FwdList< T >::iterator shramko::FwdList< T >::end() const noexcept
{
  return iterator(tail_);
}

template< typename T >
typename shramko::FwdList< T >::const_iterator shramko::FwdList< T >::cbegin() const noexcept
{
  return const_iterator(head_);
}

template< typename T >
typename shramko::FwdList< T >::const_iterator shramko::FwdList< T >::cend() const noexcept
{
  return const_iterator(tail_);
}

template< typename T >
T& shramko::FwdList< T >::front() const
{
  if (empty())
  {
    throw std::logic_error("List is empty");
  }
  return head_->data_;
}

template< typename T >
T& shramko::FwdList< T >::back() const
{
  if (empty())
  {
    throw std::logic_error("List is empty");
  }
  FwdListNode< T >* current = head_;
  while (current->next_ != tail_)
  {
    current = current->next_;
  }
  return current->data_;
}

template< typename T >
size_t shramko::FwdList< T >::size() const noexcept
{
  return size_;
}

template< typename T >
bool shramko::FwdList< T >::empty() const noexcept
{
  return size_ == 0;
}

template< typename T >
void shramko::FwdList< T >::pushFrontNode(FwdListNode< T >* node)
{
  node->next_ = empty() ? tail_ : head_;
  tail_->next_ = node;
  head_ = node;
  ++size_;
}

template< typename T >
void shramko::FwdList< T >::push_front(const T& value)
{
  pushFrontNode(new FwdListNode< T >(value));
}

template< typename T >
void shramko::FwdList< T >::push_front(T&& value)
{
  pushFrontNode(new FwdListNode< T >(std::move(value)));
}

template< typename T >
void shramko::FwdList< T >::pushBackNode(FwdListNode< T >* node)
{
  if (empty())
  {
    pushFrontNode(node);
    return;
  }
  FwdListNode< T >* current = head_;
  while (current->next_ != tail_)
  {
    current = current->next_;
  }
  current->next_ = node;
  node->next_ = tail_;
  ++size_;
}

template< typename T >
void shramko::FwdList< T >::push_back(const T& value)
{
  pushBackNode(new FwdListNode< T >(value));
}

template< typename T >
void shramko::FwdList< T >::push_back(T&& value)
{
  pushBackNode(new FwdListNode< T >(std::move(value)));
}

template< typename T >
void shramko::FwdList< T >::pop_front() noexcept
{
  if (!empty())
  {
    FwdListNode< T >* temp = head_;
    head_ = head_->next_;
    tail_->next_ = head_;
    delete temp;
    --size_;
  }
}

template< typename T >
void shramko::FwdList< T >::swap(FwdList& other) noexcept
{
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template< typename T >
void shramko::FwdList< T >::clear() noexcept
{
  while (!empty())
  {
    pop_front();
  }
}

#endif
