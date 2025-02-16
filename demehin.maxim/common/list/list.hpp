#ifndef LIST_HPP
#define LIST_HPP
#include "iterator.hpp"
#include "node.hpp"

namespace demehin
{
  template< typename T >
  struct List
  {
  public:
    using Iter = ListIterator< T >;

    List();

    ~List();

    List(const List< T >&);
    List(List< T >&&);

    Iter begin() const;
    Iter end() const;

    size_t size() const;

    void pop_front();

    void push_back(const T&);

    T& front();

    bool empty();

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
    //fake_(new Node()),
    tail_(nullptr),
    size_(0)
  {
    //new (fake_) Node(T());
    fake_->next_ = nullptr;
    fake_->prev_ = nullptr;
  }

  template< typename T >
  List< T >::~List()
  {
    Node* current = fake_->next_;
    while (current != nullptr)
    {
      Node* next = current->next_;
      delete current;
      current = next;
    }
    delete[] reinterpret_cast< char* >(fake_);
    //delete fake_;
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
    //rhs.fake_ = new Node();
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
    return ListIterator< T >(nullptr);
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
  T& List< T >::front()
  {
    return fake_->next_->data_;
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

}

#endif
