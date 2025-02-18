#ifndef LIST_HPP
#define LIST_HPP
#include "iterator.hpp"
#include "cIterator.hpp"
#include "node.hpp"

namespace demehin
{
  template< typename T >
  struct List
  {
  public:
    using Iter = ListIterator< T >;
    using cIter = cListIterator< T >;

    List();

    ~List();

    List(const List< T >&);
    List(List< T >&&);

    Iter begin() const;
    Iter end() const;

    cIter cbegin() const;
    cIter cend() const;

    size_t size() const;

    void pop_front();
    void pop_back();

    void push_front(const T&);
    void push_back(const T&);

    T& front();
    T& back();

    bool empty();

    void clear();

    void swap(List&);

    void splice(cIter pos, List< T >&);
    void splice(cIter pos, List< T >&&);
    void splice(cIter pos, List< T >&, cIter it);
    void splice(cIter pos, List< T >&&, cIter it);
    void splice(cIter pos, List< T >&, cIter first, cIter last);
    void splice(cIter pos, List< T >&&, cIter first, cIter last);

    void fill(Iter first, Iter last, const T&);

    void remove(const T&);
    template< typename UnaryPredicate >
    void removeIf(UnaryPredicate p);

    void assign(size_t, const T&);
    void assign(Iter, Iter);

  private:
    using Node = demehin::Node< T >;

    Node* fake_;
    Node* tail_;
    size_t size_;

  };

  template< typename T >
  using Node = demehin::Node< T >;

  template< typename T >
  List< T >::List():
    fake_(reinterpret_cast< Node* >(new char[sizeof(Node)])),
    tail_(nullptr),
    size_(0)
  {
    fake_->next_ = nullptr;
    fake_->prev_ = nullptr;
  }

  template< typename T >
  List< T >::~List()
  {
    clear();
    delete[] reinterpret_cast< char* >(fake_);
  }

  template< typename T >
  void List< T >::clear()
  {
    while (!empty())
    {
      pop_back();
    }
  }

  template< typename T >
  List< T >::List(const List< T >& rhs):
    List()
  {
    Node* current = rhs.fake_->next_;
    while (current != nullptr)
    {
      push_back(current->data_);
      current = current->next_;
    }
  }

  template< typename T >
  List< T >::List(List< T >&& rhs):
    fake_(rhs.fake_),
    tail_(rhs.tail_),
    size_(rhs.size_)
  {
    rhs.fake_ = nullptr;
    rhs.tail_ = nullptr;
    rhs.size_ = 0;
  }

  template< typename T >
  ListIterator< T > List< T >::begin() const
  {
    return ListIterator< T >(fake_->next_);
  }

  template< typename T >
  ListIterator< T > List< T >::end() const
  {
    return ListIterator< T >(tail_->next_);
  }

  template< typename T >
  cListIterator< T > List< T >::cbegin() const
  {
    return cListIterator< T >(fake_->next_);
  }

  template< typename T >
  cListIterator< T > List< T >::cend() const
  {
    return cListIterator< T >(tail_->next_);
  }

  template< typename T >
  void List< T >::pop_front()
  {
    Node* todelete = fake_->next_;
    fake_->next_ = todelete->next_;
    if (fake_->next_ != nullptr)
    {
      fake_->next_->prev_ = fake_;
    }
    else
    {
      tail_ = nullptr;
    }
    delete todelete;
    size_--;
  }

  template< typename T >
  void List< T >::pop_back()
  {
    Node* todelete = tail_;
    tail_ = tail_->prev_;

    if (tail_ != nullptr)
    {
      tail_->next_ = nullptr;
    }
    else
    {
      fake_->next_ = nullptr;
    }

    delete todelete;
    size_--;
  }

  template< typename T >
  void List< T >::push_back(const T& data)
  {
    Node* new_node = new Node(data);
    new_node->next_ = nullptr;
    new_node->prev_ = tail_;
    if (tail_ != nullptr)
    {
      tail_->next_ = new_node;
    }
    else
    {
      fake_->next_ = new_node;
    }

    tail_ = new_node;
    size_++;
  }

  template< typename T >
  void List< T >::push_front(const T& data)
  {
    Node* new_node = new Node(data);
    new_node->next_ = fake_->next_;

    if (fake_->next_ != nullptr)
    {
      fake_->next_->prev_ = new_node;
    }
    else
    {
      tail_ = new_node;
    }

    new_node->prev_ = fake_;
    fake_->next_ = new_node;
    size_++;
  }

  template< typename T >
  T& List< T >::front()
  {
    return fake_->next_->data_;
  }

  template< typename T >
  T& List< T >::back()
  {
    return tail_->data_;
  }

  template< typename T >
  size_t List< T >::size() const
  {
    return size_;
  }

  template< typename T >
  bool List< T >::empty()
  {
    return size_ == 0;
  }

  template< typename T >
  void List< T >::swap(List< T >& other)
  {
    std::swap(fake_->next_, other.fake_->next_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }

  template< typename T >
  void List< T >::fill(ListIterator< T > first, ListIterator< T > last, const T& value)
  {
    for (; first != last; ++first)
    {
      *first = value;
    }
  }

  template< typename T >
  void List< T >::splice(cListIterator< T > pos, List< T >& other)
  {
    if (other.empty() || pos == end())
    {
      return;
    }

    Node* first = other.fake_->next_;
    Node* last = other.tail_;
    Node* posNode = pos.getNode();
    posNode->prev_->next_ = first;
    first->prev_ = posNode->prev_;
    last->next_ = posNode;
    posNode->prev_ = last;

    other.clear();
  }

  template< typename T >
  void List< T >::splice(cListIterator< T > pos, List< T >&& other)
  {
    List< T > tempList(std::move(other));
    splice(tempList);
  }

  template< typename T >
  void List< T >::splice(cListIterator< T > pos, List< T >& other, cListIterator< T > it)
  {
    if (other.empty() || pos == end() || it == other.begin())
    {
      return;
    }

    Node* itNode = it.getNode();
    Node* posNode = pos.getNode();
    Node* itPrevNode = itNode->prev_;

    itPrevNode->next_ = itNode->next_;
    itNode->prev_ = posNode->prev_;
    itNode->next_ = posNode;
    posNode->prev_->next_ = itNode;
    posNode->prev_ = itNode;
  }

  template< typename T >
  void List< T >::splice(cListIterator< T > pos, List< T >&& other, cListIterator< T > it)
  {
    List< T > tempList(std::move(other));
    splice(tempList);
  }

  template< typename T >
  void List< T >::splice(cListIterator< T > pos, List< T >& other, cListIterator< T > first,
    cListIterator< T > last)
  {
    if (other.empty() || pos == end())
    {
      return;
    }

    Node* posNode = pos.getNode();
    Node* firstNode = first.getNode();
    Node* lastNode = last.getNode();
  }

  template< typename T >
  void List< T >::remove(const T& value)
  {
  }

  template< typename T >
  template< typename UnaryPredicate >
  void List< T >::removeIf(UnaryPredicate p)
  {
  }

  template< typename T >
  void List< T >::assign(size_t count, const T& value)
  {
    clear();
    for (size_t i = 0; i < count; i++)
    {
      push_back(value);
    }
  }
}

#endif
