#ifndef FWD_LIST_HPP
#define FWD_LIST_HPP
#include <cstddef>
#include <algorithm>
#include "iterator.hpp"
#include "citerator.hpp"
#include "nodelist.hpp"

namespace karnauhova
{
  template< typename T >
  class Fwd_list
  {
  public:
    using Node = NodeList< T >;
    using Iterator = ListIterator< T >;
    using CIterator = ConstListIterator< T >;
    Fwd_list();
    Fwd_list(Iterator first, Iterator last);
    Fwd_list(size_t size, const T& value);
    Fwd_list(std::initializer_list<T> Fwd_list);
    Fwd_list(const Fwd_list< T >& other);
    ~Fwd_list();

    Fwd_list< T >& operator=(std::initializer_list<T> Fwd_list);
    bool empty() const noexcept;
    size_t size() const noexcept;

    Iterator begin() const;
    Iterator end() const;
    CIterator cbegin() const;
    CIterator cend() const;

    T& front();
    T& back();
    void clear();
    void swap(Fwd_list< T >& other);
    void push_front(const T& data);
    void pop_front();
    void reverse();

    void remove(const T& value);
    template< typename UnaryPredicate >
    void remove_if(UnaryPredicate c) noexcept;

    void assign(size_t size, const T& value);
    void assign(Iterator first, Iterator last);
    void assign(std::initializer_list< T > Fwd_list);

    Iterator erase(CIterator pos) noexcept;
    Iterator erase(CIterator first, CIterator last) noexcept;
  private:
    Node* fake_;
    size_t size_;
  };

  template< class T >
  void Fwd_list< T >::reverse()
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
  Fwd_list< T >::Fwd_list():
    fake_(reinterpret_cast< NodeList< T >* >(new char[sizeof(NodeList< T >)])),
    size_(0)
  {
    fake_->next = fake_;
  }

  template< typename T >
  Fwd_list< T >::Fwd_list(size_t size, const T& value)
  {
    assign(size, value);
  }

  template< typename T >
  Fwd_list< T >::Fwd_list(std::initializer_list<T> Fwd_list)
  {
    assign(Fwd_list);
  }

  template< typename T >
  Fwd_list< T >::Fwd_list(Iterator first, Iterator last)
  {
    assign(first, last);
  }

  template< typename T >
  Fwd_list< T >& Fwd_list< T >::operator=(std::initializer_list<T> Fwd_list)
  {
    assign(Fwd_list);
    return *this;
  }

  template< typename T >
  void Fwd_list< T >::swap(Fwd_list< T >& other)
  {
    std::swap(fake_, other.fake_);
    std::swap(size_, other.size_);
  }

  template< typename T >
  void Fwd_list< T >::pop_front()
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
  void Fwd_list< T >::push_front(const T& data)
  {
    Node* new_element = new Node{data, fake_->next};
    fake_->next = new_element;
    size_++;
  }

  template< typename T >
  Fwd_list< T >::Fwd_list(const Fwd_list< T >& other):
    Fwd_list()
  {
    auto it = other.begin();
    for (size_t i = other.size(); i > 0; i--)
    {
      push_front(*it);
      it++;
    }
    reverse();
  }

  template< typename T >
  void Fwd_list< T >::clear()
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
  Fwd_list< T >::~Fwd_list()
  {
    clear();
    delete[] reinterpret_cast< char* >(fake_);
  }

  template< typename T >
  T& Fwd_list< T >::front()
  {
    return fake_->next->data;
  }

  template< typename T >
  T& Fwd_list< T >::back()
  {
    NodeList< T >* now = fake_;
    while (now->next != fake_)
    {
      now = now->next;
    }
    return now->data;
  }

  template< typename T >
  typename Fwd_list<T>::Iterator Fwd_list< T >::begin() const
  {
    return Iterator(fake_->next);
  }

  template< typename T >
  typename Fwd_list<T>::CIterator Fwd_list< T >::cbegin() const
  {
    return CIterator(fake_->next);
  }

  template< typename T >
  typename Fwd_list<T>::CIterator Fwd_list< T >::cend() const
  {
    return CIterator(fake_);
  }

  template< typename T >
  typename Fwd_list<T>::Iterator Fwd_list< T >::end() const
  {
    return Iterator(fake_);
  }

  template< typename T >
  bool Fwd_list< T >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< typename T >
  size_t Fwd_list< T >::size() const noexcept
  {
    return size_;
  }

  template< typename T >
  void Fwd_list< T >::assign(size_t size, const T& value )
  {
    clear();
    for (size_t i = 0; i < size; i++)
    {
      push_front(value);
    }
    size_ = size;
  }

  template< typename T >
  void Fwd_list< T >::assign(Iterator first, Iterator last)
  {
    clear();
    size_ = 0;
    for (auto it = first; it != last; it++)
    {
      push_front(it.node);
      size_++;
    }
  }

  template< typename T >
  void Fwd_list< T >::remove(const T& value)
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
  void Fwd_list< T >::remove_if(UnaryPredicate c) noexcept
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
  void Fwd_list< T >::assign(std::initializer_list< T > Fwd_list)
  {
    clear();
    size_ = 0;
    for (const T& data : Fwd_list)
    {
      push_back(data);
      size_++;
    }
  }

  template<typename T>
  typename Fwd_list<T>::Iterator Fwd_list<T>::erase(Fwd_list<T>::CIterator pos) noexcept 
  {
    Node* todelete = const_cast<Node*>(pos.node);
    if (pos == cend())
    {
      return end();
    }
    Node* prevNode = fake_;
    while (prevNode->next != todelete) {
        prevNode = prevNode->next;
    }
    prevNode->next = todelete->next;
    delete todelete;
    size_--;
    return Iterator(prevNode->next);
  }

  template< typename T >
  typename Fwd_list< T >::Iterator Fwd_list< T >::erase(CIterator first, CIterator last) noexcept
  {
    Iterator now;
    for (auto it = first; it != last; it++)
    {
      now = erase(it);
      size_--;
    }
    return now;
  }
}

#endif
