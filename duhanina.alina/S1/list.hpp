#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include "iterator.hpp"
#include "citerator.hpp"

namespace duhanina
{
  template < typename T >
  class List
  {
  public:
    List();
    List(size_t count, const T& value);
    ~List();

    List(const List< T >& list);
    List(List&& other) noexcept;

    Iterator< T > begin() const;
    Iterator< T > end() const;
    constIterator< T > cbegin() const;
    constIterator< T > cend() const;

    T& front();
    T& back();

    bool empty() const;
    size_t size() const;

    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    void clear();
    void swap(List& other) noexcept;
    void remove(const T& value);
    template < typename Predicate >
    void remove_if(Predicate pred);
    void assign(size_t count, const T& value);

  private:
    Node< T >* fake_;
    size_t listSize_;
  };

  template < typename T >
  List< T >::List():
    fake_(new Node< T >()),
    listSize_(0)
  {
    fake_->next_ = fake_;
  }

  template < typename T >
  List< T >::List(size_t count, const T& value):
    List()
  {
    for (size_t i = 0; i < count; ++i)
    {
      push_back(value);
    }
  }

  template < typename T >
  List< T >::~List()
  {
    clear();
    delete fake_;
  }

  template< typename T >
  List< T >::List(const List< T >& list):
    List()
  {
    for (constIterator< T > it = list.cbegin(); it != list.cend(); ++it)
    {
      push_back(*it);
    }
  }

  template < typename T >
  List< T >::List(List&& other) noexcept:
    fake_(other.fake_),
    listSize_(other.listSize_)
  {
    other.fake_ = new Node< T >();
    other.fake_->next_ = other.fake_;
    other.listSize_ = 0;
  }

  template < typename T >
  Iterator< T > List< T >::begin() const
  {
    return Iterator< T >(fake_->next_);
  }

  template < typename T >
  Iterator< T > List< T >::end() const
  {
    return Iterator< T >(fake_);
  }

  template < typename T >
  constIterator< T > List< T >::cbegin() const
  {
    return constIterator< T >(fake_->next_);
  }

  template < typename T >
  constIterator< T > List< T >::cend() const
  {
    return constIterator< T >(fake_);
  }

  template < typename T >
  T& List< T >::front()
  {
    return fake_->next_->data_;
  }

  template < typename T >
  T& List< T >::back()
  {
    Node< T >* current = fake_->next_;
    while (current->next_ != fake_)
    {
      current = current->next_;
    }
    return current->data_;
  }

  template < typename T >
  bool List< T >::empty() const
  {
    return listSize_ == 0;
  }

  template < typename T >
  size_t List< T >::size() const
  {
    return listSize_;
  }

  template < typename T >
  void List< T >::push_front(const T& value)
  {
    Node< T >* newNode = new Node< T >(value);
    newNode->next_ = fake_->next_;
    fake_->next_ = newNode;
    ++listSize_;
  }

  template < typename T >
  void List< T >::push_back(const T& value)
  {
    Node< T >* newNode = new Node< T >(value);
    Node< T >* current = fake_;
    while (current->next_ != fake_)
    {
      current = current->next_;
    }
    current->next_ = newNode;
    newNode->next_ = fake_;
    ++listSize_;
  }

  template < typename T >
  void List< T >::pop_front()
  {
    Node< T >* temp = fake_->next_;
    fake_->next_ = temp->next_;
    delete temp;
    --listSize_;
  }

  template < typename T >
  void List< T >::pop_back()
  {
    Node< T >* current = fake_;
    while (current->next_->next_ != fake_)
    {
      current = current->next_;
    }
    delete current->next_;
    current->next_ = fake_;
    --listSize_;
  }

  template < typename T >
  void List< T >::clear()
  {
    while (!empty())
    {
      pop_front();
    }
  }

  template < typename T >
  void List< T >::swap(List& other) noexcept
  {
    std::swap(fake_, other.fake_);
    std::swap(listSize_, other.listSize_);
  }

  template < typename T >
  void List< T >::remove(const T& value)
  {
    Node< T >* current = fake_->next_;
    Node< T >* prev = fake_;
    while (current != fake_)
    {
      if (current->data_ == value)
      {
        prev->next_ = current->next_;
        delete current;
        current = prev->next_;
        --listSize_;
      }
      else
      {
        prev = current;
        current = current->next_;
      }
    }
  }

  template < typename T >
  template <typename Predicate>
  void List< T >::remove_if(Predicate pred)
  {
    Node< T >* current = fake_->next_;
    Node< T >* prev = fake_;
    while (current != fake_)
    {
      if (pred(current->data_))
      {
        prev->next_ = current->next_;
        delete current;
        current = prev->next_;
        --listSize_;
      }
      else
      {
        prev = current;
        current = current->next_;
      }
    }
  }

  template < typename T >
  void List< T >::assign(size_t count, const T& value)
  {
    clear();
    for (size_t i = 0; i < count; ++i)
    {
      push_back(value);
    }
  }
}

#endif
