#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include <cstddef>
#include <iterator>
#include <stdexcept>

namespace krylov
{
  template< class T >
  class List;

  template < typename T >
  class Node
  {
  public:
    T data_;
    Node< T >* prev_;
    Node< T >* next_;
    Node(const T& value);
  };

  template < typename T >
  class Iterator
  {
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    Iterator();
    Iterator(Node< T >* node);
    Iterator(Node< T >* node, const List< T >* list);
    T& operator*();
    T* operator->();
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    bool operator!=(const Iterator& other) const;
    bool operator==(const Iterator& other) const;
  private:
    Node< T >* current_;
    const List< T >* list_;
    friend class List< T >;
  };

  template < typename T >
  class List
  {
  public:
    friend class Iterator< T >;
    List();
    List(const List< T >& other);
    List(List< T >&& other) noexcept;
    List< T >& operator=(const List< T >& other);
    List< T >& operator=(List< T >&& other) noexcept;
    List(size_t n, const T& value);
    ~List();
    Iterator< T > begin() const;
    Iterator< T > end() const;
    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back() noexcept;
    void pop_front() noexcept;
    T& front();
    T& back();
    bool empty() const noexcept;
    size_t size() const noexcept;
    void clear() noexcept;
    void swap(List< T >& other) noexcept;
    void assign(size_t n, const T& value) noexcept;
  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };

  template < typename T >
  Node< T >::Node(const T& value):
    data_(value),
    prev_(nullptr),
    next_(nullptr)
  {}

  template < typename T >
  List< T >::List():
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}

  template < typename T >
  List< T >::List(const size_t n, const T& value):
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {
    try
    {
      for (size_t i = 0; i < n; ++i)
      {
        push_back(value);
      }
    }
    catch (const std::bad_alloc& e)
    {
      clear();
    }
  }

  template < typename T >
  List< T >::~List()
  {
    clear();
  }

  template < typename T >
  List< T >::List(const List< T >& other):
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {
    Node< T >* current = other.head_;
    while (current)
    {
      push_back(current->data_);
      current = current->next_;
    }
  }

  template <typename T>
  List<T>::List(List<T>&& other) noexcept:
    head_(other.head_),
    tail_(other.tail_),
    size_(other.size_)
  {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }

  template< typename T >
  void List< T >::assign(size_t n, const T& value) noexcept
  {
    List< T > temp(n, value);
    if (temp.head_ != nullptr)
    {
      swap(temp);
    }
  }

  template < typename T >
  List< T >& List< T >::operator=(const List< T >& other)
  {
    if (this == &other)
    {
      return *this;
    }
    List< T > temp;
    Node< T >* current = other.head_;
    while (current)
    {
      temp.push_back(current->data_);
      current = current->next_;
    }
    swap(temp);
    return *this;
  }

  template < typename T >
  List< T >& List< T >::operator=(List< T >&& other) noexcept
  {
    if (this == &other)
    {
      return *this;
    }
    clear();
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
    return *this;
  }

  template < typename T >
  Iterator< T >::Iterator(Node< T >* node):
    current_(node),
    list_(nullptr)
  {}

  template < typename T >
  Iterator< T >::Iterator(Node< T >* node, const List< T >* list):
    current_(node),
    list_(list)
  {}

  template < typename T >
  T& Iterator< T >::operator*()
  {
    return current_->data_;
  }

  template < typename T >
  T* Iterator< T >::operator->()
  {
    return &(current_->data_);
  }

  template < typename T >
  Iterator< T >& Iterator< T >::operator++()
  {
    if (current_ && current_->next_)
    {
      current_ = current_->next_;
    }
    else
    {
      current_ = nullptr;
    }
    return *this;
  }

  template < typename T >
  Iterator< T > Iterator< T >::operator++(int)
  {
    Iterator< T > temp = *this;
    ++(*this);
    return temp;
  }

  template < typename T >
  Iterator< T >& Iterator< T >::operator--()
  {
    if (!current_)
    {
      current_ = list_->tail_;
    }
    else
    {
      current_ = current_->prev_;
    }
    return *this;
  }

  template < typename T >
  Iterator< T > Iterator< T >::operator--(int)
  {
    Iterator< T > temp = *this;
    --(*this);
    return temp;
  }

  template < typename T >
  bool Iterator< T >::operator!=(const Iterator& other) const
  {
    return current_ != other.current_;
  }

  template < typename T >
  bool Iterator < T >::operator==(const Iterator& other) const
  {
    return current_ == other.current_;
  }

  template < typename T >
  Iterator< T > List< T >::begin() const
  {
    return Iterator< T >(head_);
  }

  template < typename T >
  Iterator< T > List< T >::end() const
  {
    return Iterator< T >(nullptr, this);
  }

  template < typename T >
  void List< T >::push_back(const T& value)
  {
    Node< T >* newNode = new Node< T >(value);
    if (!tail_)
    {
      head_ = newNode;
      tail_ = newNode;
    }
    else
    {
      tail_->next_ = newNode;
      newNode->prev_ = tail_;
      tail_ = newNode;
    }
    ++size_;
  }

  template < typename T >
  void List< T >::push_front(const T& value)
  {
    Node< T >* newNode = new Node< T >(value);
    if (!head_)
    {
      head_ = newNode;
      tail_ = newNode;
    }
    else
    {
      head_->prev_ = newNode;
      newNode->next_ = head_;
      head_ = newNode;
    }
    ++size_;
  }

  template < typename T >
  void List< T >::pop_back() noexcept
  {
    if (!tail_)
    {
      return;
    }
    Node< T >* temp = tail_;
    tail_ = tail_->prev_;
    if (tail_)
    {
      tail_->next_ = nullptr;
    }
    else
    {
      head_ = nullptr;
    }
    delete temp;
    --size_;
  }

  template < typename T >
  void List< T >::pop_front() noexcept
  {
    if (!head_)
    {
      return;
    }
    Node< T >* temp = head_;
    head_ = head_->next_;
    if (head_)
    {
      head_->prev_ = nullptr;
    }
    else
    {
      tail_ = nullptr;
    }
    delete temp;
    --size_;
  }

  template < typename T >
  T& List< T >::front()
  {
    if (!head_)
    {
      throw std::out_of_range("List is empty");
    }
    return head_->data_;
  }

  template < typename T >
  T& List< T >::back()
  {
    if (!tail_)
    {
      throw std::out_of_range("List is empty");
    }
    return tail_->data_;
  }

  template < typename T >
  bool List< T >::empty() const noexcept
  {
    return size_ == 0;
  }

  template < typename T >
  size_t List< T >::size() const noexcept
  {
    return size_;
  }

  template < typename T >
  void List< T >::clear() noexcept
  {
    while (!empty())
    {
      pop_back();
    }
  }

  template < typename T >
  void List< T >::swap(List< T >& other) noexcept
  {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }
}

#endif
