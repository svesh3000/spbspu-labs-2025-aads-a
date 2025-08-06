#ifndef FWDLISTt_HPP
#define FWDLISTt_HPP
#include <cstddef>
#include <algorithm>
#include "iterator.hpp"
#include "citerator.hpp"
#include "nodelist.hpp"

namespace karnauhova
{
  template< typename T >
  class FwdList
  {
  public:
    using Node = NodeList< T >;
    using Iterator = ListIterator< T >;
    using CIterator = ConstListIterator< T >;
    FwdList();
    FwdList(Iterator first, Iterator last);
    FwdList(size_t size, const T& value);
    FwdList(std::initializer_list< T > FwdList);
    FwdList(const FwdList< T >& other);
    FwdList(FwdList< T > &&other) noexcept;
    ~FwdList();

    FwdList< T >& operator=(std::initializer_list< T > list);
    FwdList< T >& operator=(const FwdList< T >& other);
    FwdList< T >& operator=(FwdList &&other) noexcept;
    bool empty() const noexcept;
    size_t size() const noexcept;

    Iterator begin() noexcept;
    Iterator end() noexcept;
    CIterator cbegin() const noexcept;
    CIterator cend() const noexcept;

    T& front();
    T& back();
    const T& front() const;
    const T& back() const;
    void clear() noexcept;
    void swap(FwdList< T >& other) noexcept;
    void push_front(const T& data);
    void pop_front();
    void reverse() noexcept;

    bool operator==(const FwdList& oth) const noexcept;
    bool operator!=(const FwdList& oth) const noexcept;
    bool operator<(const FwdList& oth) const noexcept;
    bool operator>(const FwdList& oth) const noexcept;
    bool operator<=(const FwdList& oth) const noexcept;
    bool operator>=(const FwdList& oth) const noexcept;

    void remove(const T& value) noexcept;
    template< typename UnaryPredicate >
    void remove_if(UnaryPredicate c) noexcept;

    void assign(size_t size, const T& value);
    void assign(Iterator first, Iterator last);
    void assign(std::initializer_list< T > FwdList);

    Iterator erase(CIterator pos) noexcept;
    Iterator erase(CIterator first, CIterator last) noexcept;

    void splice(CIterator pos, FwdList< T >& oth) noexcept;
    void splice(CIterator pos, FwdList< T >&& oth) noexcept;
    void splice(CIterator pos, FwdList< T >& oth, CIterator it) noexcept;
    void splice(CIterator pos, FwdList< T >&& oth, CIterator it) noexcept;
    void splice(CIterator pos, FwdList< T >& oth, CIterator first, CIterator last) noexcept;
    void splice(CIterator pos, FwdList< T >&& oth, CIterator first, CIterator last) noexcept;

    Iterator insert(CIterator pos, const T& value);
    Iterator insert(CIterator pos, T&& value);
    Iterator insert(CIterator pos, size_t count, const T& value);
    template < class InputIt >
    Iterator insert(CIterator pos, InputIt first, InputIt last);
    Iterator insert(CIterator pos, std::initializer_list< T > init);
  private:
    Node* fake_;
    size_t size_;
  };

  template< class T >
  void FwdList< T >::reverse() noexcept
  {
    if (fake_->next == fake_)
    {
      return;
    }
    NodeList< T >* next = fake_->next;
    NodeList< T >* last = fake_;
    while (next->next != fake_)
    {
      NodeList< T >* remember = next->next;
      next->next = last;
      last = next;
      next = remember;
    }
    next->next = last;
    fake_->next = next;
  }

  template< typename T >
  FwdList< T >::FwdList():
    fake_(reinterpret_cast< NodeList< T >* >(new char[sizeof(NodeList< T >)])),
    size_(0)
  {
    fake_->next = fake_;
  }

  template< typename T >
  FwdList< T >::FwdList(size_t size, const T& value)
  {
    assign(size, value);
  }

  template< typename T >
  FwdList< T >::FwdList(std::initializer_list< T > FwdList)
  {
    assign(FwdList);
  }

  template< typename T >
  FwdList< T >::FwdList(Iterator first, Iterator last)
  {
    assign(first, last);
  }

  template< typename T >
  FwdList< T >& FwdList< T >::operator=(std::initializer_list< T > list)
  {
    assign(list);
    return *this;
  }

  template< typename T >
  void FwdList< T >::swap(FwdList< T >& other) noexcept
  {
    std::swap(fake_, other.fake_);
    std::swap(size_, other.size_);
  }

  template< class T >
  FwdList< T >::FwdList(FwdList< T > &&other) noexcept:
    fake_(other.fake_),
    size_(other.size_)
  {
    other.fake_ = nullptr;
    other.size_ = 0;
  }

  template< typename T >
  FwdList< T >& FwdList< T >::operator=(const FwdList< T >& other)
  {
    assign(other.begin(), other.end());
    return *this;
  }

  template< class T >
  FwdList< T >& FwdList< T >::operator=(FwdList &&other) noexcept
  {
    if (this != std::addressof(other))
    {
      clear();
      delete[] reinterpret_cast< char* >(fake_);
      fake_ = other.fake_;
      size_ = other.size_;
      other.fake_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  template< typename T >
  void FwdList< T >::pop_front()
  {
    fake_->next = fake_->next->next;
    if (fake_->next == fake_)
    {
      return;
    }
    delete fake_->next;
    size_--;
  }

  template< typename T >
  void FwdList< T >::push_front(const T& data)
  {
    Node* new_element = new Node{data, fake_->next};
    fake_->next = new_element;
    size_++;
  }

  template< typename T >
  FwdList< T >::FwdList(const FwdList< T >& other):
    FwdList()
  {
    auto it = other.cbegin();
    for (size_t i = other.size(); i > 0; i--)
    {
      push_front(*it);
      it++;
    }
    reverse();
  }

  template< typename T >
  void FwdList< T >::clear() noexcept
  {
    NodeList< T >* last = fake_->next;
    while (size_)
    {
      NodeList< T >* now = last->next;
      delete last;
      last = now;
      size_--;
    }
  }

  template< typename T >
  FwdList< T >::~FwdList()
  {
    clear();
    delete[] reinterpret_cast< char* >(fake_);
  }

  template< typename T >
  T& FwdList< T >::front()
  {
    return const_cast< T& >(static_cast< const FwdList< T >* >(this)->front());
  }

  template< typename T >
  T& FwdList< T >::back()
  {
    return const_cast< T& >(static_cast< const FwdList< T >* >(this)->back());
  }

  template< typename T >
  const T& FwdList< T >::front() const
  {
    return fake_->next->data;
  }

  template< typename T >
  const T& FwdList< T >::back() const
  {
    NodeList< T >* now = fake_;
    while (now->next != fake_)
    {
      now = now->next;
    }
    return now->data;
  }

  template< typename T >
  typename FwdList< T >::Iterator FwdList< T >::begin() noexcept
  {
    return Iterator(fake_->next);
  }

  template< typename T >
  typename FwdList< T >::CIterator FwdList< T >::cbegin() const noexcept
  {
    return CIterator(fake_->next);
  }

  template< typename T >
  typename FwdList< T >::CIterator FwdList< T >::cend() const noexcept
  {
    return CIterator(fake_);
  }

  template< typename T >
  typename FwdList< T >::Iterator FwdList< T >::end() noexcept
  {
    return Iterator(fake_);
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
  void FwdList< T >::assign(size_t size, const T& value )
  {
    clear();
    for (size_t i = 0; i < size; i++)
    {
      push_front(value);
    }
    reverse();
    size_ = size;
  }

  template< typename T >
  void FwdList< T >::assign(Iterator first, Iterator last)
  {
    clear();
    size_ = 0;
    for (auto it = first; it != last; it++)
    {
      push_front(it.node);
      size_++;
    }
    reverse();
  }

  template< typename T >
  void FwdList< T >::remove(const T& value) noexcept
  {
    Node* now = fake_->next;
    Node* last = fake_;
    while(now != fake_)
    {
      if (now->data == value)
      {
        Node* temp = now;
        last->next = now->next;
        now = now->next;
        delete temp;
        size_--;
      }
      else
      {
        last = now;
        now = now->next;
      }
    }
  }

  template< typename T >
  template< typename UnaryPredicate >
  void FwdList< T >::remove_if(UnaryPredicate c) noexcept
  {
    Node* now = fake_->next;
    Node* last = fake_;
    while(now != fake_)
    {
      if (c(now->data))
      {
        Node* temp = now;
        last->next = now->next;
        now = now->next;
        delete temp;
        size_--;
      }
      else
      {
        last = now;
        now = now->next;
      }
    }
  }

  template< typename T >
  void FwdList< T >::assign(std::initializer_list< T > FwdList)
  {
    clear();
    size_ = 0;
    for (const T& data : FwdList)
    {
      push_back(data);
      size_++;
    }
    reverse();
  }

  template< typename T >
  typename FwdList< T >::Iterator FwdList< T >::erase(FwdList< T >::CIterator pos) noexcept
  {
    Node* todelete = const_cast< Node* >(pos.node);
    if (pos == cend())
    {
      return end();
    }
    Node* prevNode = fake_;
    while (prevNode->next != todelete)
    {
      prevNode = prevNode->next;
    }
    prevNode->next = todelete->next;
    delete todelete;
    size_--;
    return Iterator(prevNode->next);
  }

  template< typename T >
  typename FwdList< T >::Iterator FwdList< T >::erase(CIterator first, CIterator last) noexcept
  {
    Iterator now;
    for (auto it = first; it != last; it++)
    {
      now = erase(it);
      size_--;
    }
    return now;
  }

  template< typename T >
  bool FwdList< T >::operator==(const FwdList& oth) const noexcept
  {
    if (size_ != oth.size_)
    {
      return false;
    }
    Iterator it = begin();
    Iterator it_oth = oth.begin();
    while (it != end())
    {
      if (*it != *it_oth)
      {
        return false;
      }
      it++;
      it_oth++;
    }
    return true;
  }

  template< typename T >
  bool FwdList< T >::operator!=(const FwdList& oth) const noexcept
  {
    return !(*this == oth);
  }

  template< typename T >
  bool FwdList< T >::operator<(const FwdList& oth) const noexcept
  {
    Iterator it = begin();
    Iterator it_oth = oth.begin();
    while ((it != end()) && (it_oth != oth.end()))
    {
      if (*it < *it_oth)
      {
        return true;
      }
      if (*it > *it_oth)
      {
        return false;
      }
      it++;
      it_oth++;
    }
    return size_ < oth.size_;
  }

  template< typename T >
  bool FwdList< T >::operator>(const FwdList& oth) const noexcept
  {
    return !(*this < oth);
  }

  template< typename T >
  bool FwdList< T >::operator>=(const FwdList& oth) const noexcept
  {
    return (*this > oth) || (*this == oth);
  }

  template< typename T >
  bool FwdList< T >::operator<=(const FwdList& oth) const noexcept
  {
    return (*this < oth) || (*this == oth);
  }

  template< typename T >
  void FwdList< T >::splice(CIterator pos, FwdList< T >& oth) noexcept
  {
    if (oth.empty())
    {
      return;
    }
    Node* first = oth.fake_->next;
    Node* last = first;
    while (last->next != oth.fake_)
    {
      last = last->next;
    }
    Node* it_node = pos.node;
    Node* next_node = it_node->next;
    it_node->next = first;
    last->next = next_node;
    size_ += oth.size_;
    oth.fake_->next = oth.fake_;
    oth.size_ = 0;
  }

  template< typename T >
  void FwdList< T >::splice(CIterator pos, FwdList< T >&& oth) noexcept
  {
    splice(pos, oth);
  }

  template< typename T >
  void FwdList< T >::splice(CIterator pos, FwdList< T >& oth, CIterator first, CIterator last) noexcept
  {
    if (last != CIterator(oth->fake_) || first == last || this == std::addressof(oth))
    {
      return;
    }
    size_t distance = std::distance(first, last);
    Node* prev_first = first.node;
    Node* last_it = prev_first->next;
    while (last_it != last.node && last_it != oth.fake_)
    {
      last_it = last_it->next;
    }
    Node* true_first = prev_first->next;
    Node* true_last = last_it;
    Node* next_pos = pos.node->next;
    pos.node->next = true_first;
    true_last->next = next_pos;
    size_ += distance;
    oth.size_ -= distance;
    prev_first->next = last_it->next;
  }

  template< typename T >
  void FwdList< T >::splice(CIterator pos, FwdList< T >&& oth, CIterator first, CIterator last) noexcept
  {
    splice(pos, oth, first, last);
  }

  template< typename T >
  void FwdList< T >::splice(CIterator pos, FwdList< T >& oth, CIterator it) noexcept
  {
    CIterator end = it;
    splice(pos, oth, it, end);
  }

  template< typename T >
  void FwdList< T >::splice(CIterator pos, FwdList< T >&& oth, CIterator it) noexcept
  {
    splice(pos, oth, it);
  }

  template< typename T >
  typename FwdList< T >::Iterator FwdList< T >::insert(CIterator pos, const T& value)
  {
    Node* node = pos.node;
    if (node == fake_)
    {
      push_front(value);
      return begin();
    }
    node->next = new Node{value, node->next};
    size_++;
    return Iterator(node->next);
  }

  template< typename T >
  typename FwdList< T >::Iterator FwdList< T >::insert(CIterator pos, T&& value)
  {
    return insert(pos, value);
  }

  template< typename T >
  typename FwdList< T >::Iterator FwdList< T >::insert(CIterator pos, size_t count, const T& value)
  {
    if (count == 0)
    {
      return Iterator(pos.node);
    }
    Iterator res = insert(pos, value);
    if (count != 1)
    {
      FwdList< T > list_val(--count, value);
      splice(pos, list_val);
    }
    return res;
  }

  template < class T >
  template < class InputIt >
  typename FwdList< T >::Iterator FwdList< T >::insert(CIterator pos, InputIt first, InputIt last)
  {
    if (first == last)
    {
      return Iterator(pos.node);
    }
    Iterator res = insert(pos, *first);
    FwdList< T > temp(++first, last);
    splice(pos, temp);
    return res;
  }

  template< typename T >
  typename FwdList< T >::Iterator FwdList< T >::insert(CIterator pos, std::initializer_list< T > init)
  {
    return insert(pos, init.begin(), init.end());
  }
}

#endif
