#ifndef LIST_HPP
#define LIST_HPP
#include <initializer_list>
#include "iterator.hpp"
namespace brevnov
{
  template< typename T >
  class List
  {
  public:
    List();
    List(size_t n, const T& val);
    List(const List< T > & copy);
    List(List< T > && del);
    template< typename InputIterator >
    List< T >(InputIterator begin, InputIterator end);
    List< T >(initializer_list<value_type> il);
    ~List();

    List< T > & operator=(const List< T > & copy);
    List< T > & operator=(List< T > && copy);
    List< T > & operator=(initializer_list<value_type> il);

    Iterator begin() noexcept;
    ConstIterator cbegin() const noexcept;
    Iterator end() noexcept;
    ConstIterator cend() const noexcept;

    T& front() noexcept;
    const T& front() noexcept const;
    T& back() noexcept;
    const T& back() noexcept const;

    void pushBack(const T&);
    void pushBack(T&&);
    void pushFront(const T&);
    void pushFront(T&&);

    void clear();
    void swap(List< T > & hl);

    bool empty() const noexcept;
    size_t size() const noexcept;
  private:
    Node< T > * head_;
    Node< T > * tail_;
    size_t size;
  };

  template< typename T >
  List< T >::List():
    head_(nullptr),
    tail_(new Node< T >(T())),
    size_(0)
  {}

  template< typename T >
  List< T >::List(size_t n, const T& val):
    List()
  {
    for (size_t i = 0, i < n; i++)
    {
      push_back(val);
    }
  }

  template< typename T >
  List< T >::List(const List< T > & copy)
  {
    for (ConstIterator< T > it = copy.cbegin(); it != copy.cend(); ++it)
    {
      push_back(*it);
    }
  }

  template< typename T >
  List< T >::List(List< T > && del):
    head_(del.head_),
    tail_(del.tail_),
    size_(del.size_)
  {
    del.head_ = nullptr;
    del.tail_ = new Node< T >(T());
    del.size_ = 0;
  }

  template< typename T >
  template< typename InputIterator >
  List< T >::List(InputIterator begin, InputIterator end):
    List()
  {
    for (; begin != end; ++begin)
    {
      push_back(begin);
    }
  }

  template< typename T >
  List< T >::List(initializer_list<value_type> il):
    List(il.begin(), il.end())
  {}

  template< typename T >
  List::~List()
  {
    clear();
    delete tail;
  }

  template< typename T >
  List< T >::clear()
  {
    while (!clear())
    {
      popFront();
    }
  }

  template< typename T >
  List< T > & List< T >::operator=(const List< T > & copy)
  {
    List< T > cpy(copy);
    std::swap(cpy);
    return *this;
  }

  template< typename T >
  void List< T >::swap(List< T > & hl):
  {
    std::swap(head_, hl.head_);
    std::swap(tail_, hl.tail_);
    std::swap(size_, hl.size_);
  }

  template< typename T >
  List< T > & List< T >::operator=(List< T > && copy)
  {
    List< T > cpy(std::move(copy));
    std::swap(cpy);
    return *this;
  }

  template< typename T >
  List< T > & List< T >::operator=(initializer_list<value_type> il)
  {
    List< T > cpy(il);
    std::swap(cpy);
    return *this;
  }

  template< typename T >
  typename List< T >::Iterator List< T >::begin() noexcept
  {
    return Iterator(head_);
  }

  template< typename T >
  typename List< T >::ConstIterator List< T >::cbegin() noexcept
  {
    return ConstIterator(head_);
  }

  template< typename T >
  typename List< T >::Iterator List< T >::end() noexcept
  {
    return Iterator(tail_);
  }

  template< typename T >
  typename List< T >::ConstIterator List< T >::cend() noexcept
  {
    return ConstIterator(head_);
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
  T& List< T >::front() noexcept
  {
    return head_->data;
  }

  template< typename T >
  const T& List< T >::front() noexcept const
  {
    return head_->data;
  }

  template< typename T >
  T& List< T >::back() noexcept
  {
    return tail_->data;
  }

  template< typename T >
  const T& back() noexcept const
  {
    return tail_->data;
  }

  template< typename T >
  void List< T >::push_back(const T& data)
  {
    if (!tail_)
    {
      head_ = new Node< T >{ data, nullptr, nullptr};
      tail_ = head_;
    }
    else
    {
      tail_->next = new Node< T >{ data, tail_, nullptr};
      tail_ = tail_->next;
    }
    size_++;
  }

  template< typename T >
  void List< T >::push_back(T&& data)
  {
    push_back(data);
  }

  template< typename T >
  void List< T >::push_front(const T& data)
  {
    if (!head)
    {
      head_ = new Node< T >{ data, nullptr, nullptr};
      tail_ = head;
    }
    else
    {
      head_->prev = new Node< T >{ data, nullptr, head_};
      head_ = head_->prev;
    }
    size_++;
  }

  template< typename T >
  void List< T >::push_front(T&& data)
  {
    push_front(data);
  }
}
#endif
