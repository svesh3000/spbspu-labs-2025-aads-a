#ifndef LIST_HPP
#define LIST_HPP
#include <functional>
#include "node.hpp"
#include "constiterator.hpp"
#include "iterator.hpp"

namespace averenkov
{
  template< class T >
  class List
  {

  public:
    List();
    List(const List< T >&);
    List(List< T >&&);
    List(size_t, const T&);
    List(std::initializer_list< T > init);
    ~List();

    using Iter_t = ListIterator< T >;
    using Iterc_t = ConstListIterator< T >;

    Iter_t begin() const noexcept;
    Iter_t end() const noexcept;

    Iterc_t cbegin() const noexcept;
    Iterc_t cend() const noexcept;

    T& front() noexcept;
    const T& front() const noexcept;
    T& back() noexcept;
    const T& back() const noexcept;

    bool empty() const noexcept;

    size_t size() const noexcept;

    void push_front(const T&);
    void push_back(const T&);
    void pop_front() noexcept;
    void pop_back() noexcept;
    void swap(List&) noexcept;
    void clear() noexcept;

    void fill(Iter_t first, Iter_t last, const T&);

    void remove(const T&);
    template< class UnaryPredicate >
    void removeIf(UnaryPredicate);

    void splice(Iterc_t pos, List< T >&);
    void splice(Iterc_t pos, List< T >&&);
    void splice(Iterc_t pos, List< T >&, Iterc_t it);
    void splice(Iterc_t pos, List< T >&&, Iterc_t it);
    void splice(Iterc_t pos, List< T >&, Iterc_t first, Iterc_t last);
    void splice(Iterc_t pos, List< T >&&, Iterc_t first, Iterc_t last);

    void assign(size_t, const T&);

  private:

    size_t size_;
    Node< T >* fake_;

  };

  template < class T >
  List< T >::List():
    size_(0),
    fake_(new Node< T >{ T(), nullptr })
  {
    fake_->next = fake_;
  }

  template < class T >
  List< T >::List(const List< T >& rhs):
    List()
  {
    Node< T >* current = rhs.fake_->next;
    while (current != rhs.fake_)
    {
      push_back(current->data);
      current = current->next;
    }
  }

  template < class T >
  List< T >::List(List< T >&& rhs):
    List()
  {
    swap(rhs);
  }

  template< typename T >
  List< T >::List(std::initializer_list< T > init):
    List()
  {
    for (const T& value: init)
    {
      push_back(value);
    }
  }

  template < class T >
  List< T >::List(size_t count, const T& value):
    List()
  {
    while (count--)
    {
      push_back(value);
    }
  }

  template < class T >
  List< T >::~List()
  {
    clear();
    delete fake_;
  }

  template < class T >
  size_t List< T >::size() const noexcept
  {
    return size_;
  }

  template < class T >
  bool List< T >::empty() const noexcept
  {
    return size_ == 0;
  }

  template < class T >
  typename List< T >::Iter_t List< T >::begin() const noexcept
  {
    return Iter_t(fake_->next);
  }

  template < class T >
  typename List< T >::Iter_t List< T >::end() const noexcept
  {
    return Iter_t(fake_);
  }

  template < class T >
  typename List< T >::Iterc_t List<T>::cbegin() const noexcept
  {
    return Iterc_t(fake_->next);
  }

  template < class T>
  typename List< T >::Iterc_t List<T>::cend() const noexcept
  {
    return Iterc_t(fake_);
  }

  template < class T >
  T& List< T >::front() noexcept
  {
    assert(!empty());
    return fake_->next->data;
  }

  template < class T >
  const T& List< T >::front() const noexcept
  {
    assert(!empty());
    return fake_->next->data;
  }

  template < class T >
  T& List< T >::back() noexcept
  {
    assert(!empty());
    Node< T >* current = fake_;
    while (current->next != fake_)
    {
      current = current->next;
    }
    return current->data;
  }

  template < class T >
  const T& List< T >::back() const noexcept
  {
    assert(!empty());
    Node< T >* current = fake_;
    while (current->next != fake_)
    {
      current = current->next;
    }
    return current->data;
  }

  template < class T >
  void List< T >::push_front(const T& value)
  {
    Node< T >* newNode = new Node< T >{ value, nullptr };
    newNode->next = fake_->next;
    fake_->next = newNode;
    size_++;
  }

  template < class T >
  void List< T >::push_back(const T& value)
  {
    Node< T >* newNode = new Node< T >{ value, nullptr };
    newNode->next = fake_;
    Node< T >* current = fake_;
    while (current->next != fake_)
    {
      current = current->next;
    }
    current->next = newNode;
    size_++;
  }

  template < class T >
  void List< T >::pop_front() noexcept
  {
    assert(!empty());
    Node< T >* temp = fake_->next;
    fake_->next = temp->next;
    delete temp;
    size_--;
  }

  template < class T >
  void List< T >::pop_back() noexcept
  {
    assert(!empty());
    Node< T >* current = fake_;
    while (current->next->next != fake_)
    {
      current = current->next;
    }
    delete current->next;
    current->next = fake_;
    size_--;
  }

  template < class T >
  void List< T >::clear() noexcept
  {
    while (!empty())
    {
      pop_front();
    }
  }

  template < class T >
  void List< T >::swap(List& rhs) noexcept
  {
    std::swap(fake_, rhs.fake_);
    std::swap(size_, rhs.size_);
  }

  template < class T >
  void List< T >::remove(const T& value)
  {
    remove_if(std::bind(std::equal_to< T >(), std::placeholders::_1, value));
  }

  template < class T >
  template < class UnaryPredicate >
  void List< T >::removeIf(UnaryPredicate pred)
  {
    Node< T >* current = fake_;
    while (current->next != fake_)
    {
      if (pred(current->next->data))
      {
        Node< T >* toDelete = current->next;
        current->next = current->next->next;
        delete toDelete;
        size_--;
      }
      else
      {
        current = current->next;
      }
    }
  }

  template < class T >
  void List< T >::splice(Iterc_t pos, List< T >& rhs, Iterc_t first, Iterc_t last)
  {
    if (first == last || rhs.empty())
    {
      return;
    }
    Node< T >* posNode = pos.operator->();
    Node< T >* firstNode = first.operator->();
    Node< T >* lastNode = firstNode;
    while (lastNode->next != last.operator->())
    {
      lastNode = lastNode->next;
    }
    Node< T >* prevNode = rhs.fake_;
    while (prevNode->next != firstNode)
    {
      prevNode = prevNode->next;
    }
    prevNode->next = lastNode->next;
    lastNode->next = posNode->next;
    posNode->next = firstNode;
    size_t count = 0;
    Node< T >* temp = firstNode;
    while (temp != last.operator->())
    {
      count++;
      temp = temp->next;
    }
    size_ += count;
    rhs.size_ -= count;
  }

  template < class T >
  void List< T >::splice(Iterc_t pos, List< T >& rhs)
  {
    splice(pos, rhs, rhs.cbegin(), rhs.cend());
  }

  template < class T >
  void List< T >::splice(Iterc_t pos, List< T >&& rhs)
  {
    splice(pos, rhs);
  }

  template < class T >
  void List< T >::splice(Iterc_t pos, List< T >& rhs, Iterc_t it)
  {
    Iterc_t next = it;
    next++;
    splice(pos, rhs, it, next);
  }

  template < class T >
  void List< T >::splice(Iterc_t pos, List< T >&& rhs, Iterc_t it)
  {
    splice(pos, rhs, it);
  }

  template < class T >
  void List< T >::splice(Iterc_t pos, List< T >&& rhs, Iterc_t first, Iterc_t last)
  {
    splice(pos, rhs, first, last);
  }

  template < class T >
  void List< T >::assign(size_t count, const T& value)
  {
    List< T > copy(count, value);
    swap(copy);
  }
};


#endif
