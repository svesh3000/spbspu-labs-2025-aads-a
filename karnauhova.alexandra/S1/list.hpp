#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <algorithm>
#include "iterator.hpp"
#include "citerator.hpp"
#include "nodelist.hpp"

namespace karnauhova
{
  template< typename T >
  class List
  {
  public:
    using Node = NodeList< T >;
    using Iterator = ListIterator< T >;
    using CIterator = ConstListIterator< T >;
    List();
    List(Iterator first, Iterator last);
    List(size_t size, const T& value);
    List(std::initializer_list<T> list);
    List(const List< T >& other);
    ~List();

    List< T >& operator=(std::initializer_list<T> list);
    bool empty() const noexcept;
    size_t size() const noexcept;

    Iterator begin() const;
    Iterator end() const;
    CIterator cbegin() const;
    CIterator cend() const;

    T& front();
    T& back();
    void clear();
    void swap(List< T >& other);
    void push_front(const T& data);
    void pop_front();
    void reverse();

    void remove(const T& value);
    template< typename UnaryPredicate >
    void remove_if(UnaryPredicate c) noexcept;

    void assign(size_t size, const T& value);
    void assign(Iterator first, Iterator last);
    void assign(std::initializer_list< T > list);
  private:
    Node* fake_;
    size_t size_;
  };

  template< class T >
  void List< T >::reverse()
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
  List< T >::List():
    fake_(reinterpret_cast< NodeList< T >* >(new char[sizeof(NodeList< T >)])),
    size_(0)
  {
    fake_->next = fake_;
  }

  template< typename T >
  List< T >::List(size_t size, const T& value)
  {
    assign(size, value);
  }

  template< typename T >
  List< T >::List(std::initializer_list<T> list)
  {
    assign(list);
  }

  template< typename T >
  List< T >::List(Iterator first, Iterator last)
  {
    assign(first, last);
  }

  template< typename T >
  List< T >& List< T >::operator=(std::initializer_list<T> list)
  {
    assign(list);
    return *this;
  }

  template< typename T >
  void List< T >::swap(List< T >& other)
  {
    std::swap(fake_, other.fake_);
    std::swap(size_, other.size_);
  }

  template< typename T >
  void List< T >::pop_front()
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
  void List< T >::push_front(const T& data)
  {
    Node* new_element = new Node{data, fake_->next};
    fake_->next = new_element;
    size_++;
  }

  template< typename T >
  List< T >::List(const List< T >& other):
    List()
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
  void List< T >::clear()
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
  List< T >::~List()
  {
    clear();
    delete[] reinterpret_cast< char* >(fake_);
  }

  template< typename T >
  T& List< T >::front()
  {
    return fake_->next->data;
  }

  template< typename T >
  T& List< T >::back()
  {
    NodeList< T >* now = fake_;
    while (now->next != fake_)
    {
      now = now->next;
    }
    return now->data;
  }

  template< typename T >
  ListIterator< T > List< T >::begin() const
  {
    return ListIterator< T >(fake_->next);
  }

  template< typename T >
  ConstListIterator< T > List< T >::cbegin() const
  {
    return CIterator(fake_->next);
  }

  template< typename T >
  ConstListIterator< T > List< T >::cend() const
  {
    return CIterator(fake_);
  }

  template< typename T >
  ListIterator< T > List< T >::end() const
  {
    return ListIterator< T >(fake_);
  }

  template< typename T >
  bool List< T >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< typename T >
  size_t List< T >::size() const noexcept
  {
    return size_;
  }

  template< typename T >
  void List< T >::assign(size_t size, const T& value )
  {
    clear();
    for (size_t i = 0; i < size; i++)
    {
      push_front(value);
    }
    size_ = size;
  }

  template< typename T >
  void List< T >::assign(Iterator first, Iterator last)
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
  void List< T >::remove(const T& value)
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
  void List< T >::remove_if(UnaryPredicate c) noexcept//aaaaaaa плиз кил ми
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
  void List< T >::assign(std::initializer_list< T > list)
  {
    clear();
    size_ = 0;
    for (const T& data : list)
    {
      push_back(data);
      size_++;
    }
  }

}

#endif
