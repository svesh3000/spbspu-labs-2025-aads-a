#ifndef LIST_HPP
#define LIST_HPP
#include <iterator>
#include <stdexcept>
#include "constIterator.hpp"
#include "iterator.hpp"
#include "node.hpp"

namespace kiselev
{
  template< typename T>
  class List
  {
  public:

    List(): head_(nullptr), size_(0) {};
    List(const List< T >&);
    List(List< T >&&);
    List(size_t, const T&);
    ~List();

    List< T >& operator=(const List< T >&);
    List< T >& operator=(const List< T >&&);

    Iterator< T > begin() const noexcept;
    ConstIterator< T > cbegin() const noexcept;
    Iterator< T > end() const noexcept;
    ConstIterator< T > cend() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    T& front() const noexcept;
    T& back() const noexcept;

    void push_back(const T&);
    void push_front(const T&);

    void pop_back();
    void pop_front();

    void clear();
    void swap(List< T >&) noexcept;
    void assign(size_t, const T&);
    Iterator< T > erase(ConstIterator< T >);
    Iterator< T > erase(ConstIterator< T > first, ConstIterator< T > last);

    void remove(const T&);
    template< typename Predicate >
    void remove_if(Predicate);
    void splice(ConstIterator< T >, List< T >&);
    void splice(ConstIterator< T >, List< T >&&);
    void splice(ConstIterator< T > position, List< T >&, ConstIterator< T > i);
    void splice(ConstIterator< T > position, List< T >&&, ConstIterator< T > i);
    void splice(ConstIterator< T > pos, List< T >&, ConstIterator< T > first, ConstIterator< T > last);
    void splice(ConstIterator< T > pos, List< T >&&, ConstIterator< T > first, ConstIterator< T > last);


  private:

    Node< T >* head_;
    size_t size_;

  };

  template< typename T>
  List< T >::List(const List< T >& list):
    List()
  {
    try
    {
      Iterator< T > it = list.begin();
      while(size() != list.size())
      {
        push_back(*it);
        ++it;
      }
    }
    catch(...)
    {
      clear();
    }
  }

  template< typename T >
  List< T >::List(List< T >&& list):
    head_(list.head_),
    size_(list.size_)
  {
    list.head_ = nullptr;
    list.size_ = 0;
  }

  template< typename T >
  List< T >::List(size_t count, const T& data):
    head_(nullptr),
    size_(0)
  {
    for (size_t i = 0; i < count; ++i)
    {
      push_back(data);
    }
  }

  template< typename T >
  List< T >::~List()
  {
    clear();
    delete head_;
  }

  template< typename T >
  List< T >& List< T >::operator=(const List< T >& list)
  {
    List< T > cpy(list);
    swap(cpy);
    return *this;
  }

  template< typename T >
  List< T >& List< T >::operator=(const List< T >&& list)
  {
    List< T > temp(std::move(list));
    swap(temp);
    return *this;
  }

  template< typename T >
  Iterator< T > List< T >::begin() const noexcept
  {
    return Iterator< T >(head_);
  }

  template< typename T >
  ConstIterator< T > List< T >::cbegin() const noexcept
  {
    return ConstIterator< T >(head_);
  }

  template< typename T >
  ConstIterator< T > List< T >::cend() const noexcept
  {
    return ConstIterator< T >(head_->prev_);
  }

  template< typename T >
  Iterator< T > List< T >::end() const noexcept
  {
    return Iterator< T >(head_->prev_);
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
  T& List< T >::front() const noexcept
  {
    return head_->data_;
  }

  template< typename T >
  T& List< T >::back() const noexcept
  {
    return head_->prev_->data_;
  }

  template< typename T >
  void List< T >::push_back(const T& data)
  {
    if (empty())
    {
      head_ = new Node< T >(data);
      head_->next_ = head_;
      head_->prev_ = head_;
    }
    else
    {
      Node< T >* newNode = new Node< T >(data);
      head_->prev_->next_ = newNode;
      newNode->prev_ = head_->prev_;
      newNode->next_ = head_;
      head_->prev_ = newNode;
    }
    ++size_;
  }

  template< typename T >
  void List< T >::push_front(const T& data)
  {
    if (empty())
    {
      head_ = new Node< T >(data);
      head_->next_ = head_;
      head_->prev_ = head_;
    }
    else
    {
      Node< T >* newNode = new Node< T >(data);
      newNode->next_ = head_;
      newNode->prev_ = head_->prev_;
      head_->prev_->next_ = newNode;
      head_->prev_ = newNode;
      head_ = newNode;
    }
    ++size_;
  }

  template< typename T >
  void List< T >::pop_back()
  {
    assert(!empty());
    if (size_ == 1)
    {
      delete head_;
      head_ = nullptr;
    }
    else
    {
      Node< T >* oldTail = head_->prev_;
      head_->prev_ = oldTail->prev_;
      head_->prev_->next_ = head_;
      delete oldTail;
    }
    --size_;
  }

  template< typename T >
  void List< T >::pop_front()
  {
    assert(!empty());
    if (size_ == 1)
    {
      delete head_;
      head_ = nullptr;
    }
    else
    {
      Node< T >* oldHead = head_;
      head_->prev_->next_ = head_->next_;
      head_->next_->prev_ = head_->prev_;
      head_ = head_->next_;
      delete oldHead;
    }
    --size_;
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
  void List< T >::swap(List<T>& list) noexcept
  {
    std::swap(head_, list.head_);
    std::swap(size_, list.size_);
  }

  template< typename T >
  void List< T >::assign(size_t count, const T& data)
  {
    List< T > temp(count, data);
    swap(temp);
  }

  template< typename T >
  Iterator< T > List< T >::erase(ConstIterator< T > position)
  {
    Iterator< T > it;
    if (position == cbegin())
    {
      pop_front();
      it = begin();
    }
    else if (position == cend())
    {
      pop_back();
      it = begin();
    }
    else
    {
      const Node< T >* node = position.getNode();
      node->prev_->next_ = node->next_;
      node->next_->prev_ = node->next_;
      it = node->next_;
      delete node;
    }
    size_--;
    return it;
  }

  template< typename T >
  Iterator< T > List< T >::erase(ConstIterator< T > first, ConstIterator< T > last)
  {
    if (distance(first, last) > size())
    {
      throw std::out_of_range("The range is too large");
    }
    for (; first != last;)
    {
      Iterator< T > it = erase(first);
      first = it.getNode();
    }
    return Iterator< T >(first.getNode());
  }

  template< typename T >
  void List< T >::remove(const T& data)
  {
    if (begin() == end())
    {
      if (head_ == data)
      {
        pop_front();
      }
    }
    for (Iterator< T > it = ++begin(); it != end();)
    {
      if (it.getNode() == data)
      {
        erase(it);
      }
      else
      {
        it++;
      }
    }
  }

  template< typename T >
  template< typename Predicate >
  void List< T >::remove_if(Predicate pred)
  {
    if (begin() == end())
    {
      if (pred(head_))
      {
        pop_front();
      }
      for (Iterator< T > it = ++begin(); it != end();)
      {
        if (pred(it.getNode()))
        {
          erase(it);
        }
        else
        {
          ++it;
        }
      }
    }
  }

  template< typename T >
  void List< T >::splice(ConstIterator< T > position, List< T >& list)
  {
    if (list.empty())
    {
      return;
    }
    Node< T >* node = position.getNode();
    Node< T >* listHead = list.front();
    Node< T >* listTail = list.back();
    listTail->next_ = node;
    listTail->prev_ = node->prev_;
    node->prev_->next_ = listHead;
    node->prev_ = listTail;
    size_ += list.size_;
    listHead = nullptr;
    list.size_ = 0;
  }

  template< typename T >
  void List< T >::splice(ConstIterator< T > position, List< T >&& list)
  {
    splice(position, list);
  }

  template< typename T >
  void List< T >::splice(ConstIterator< T > position, List< T >& list, ConstIterator< T > i)
  {
    Node< T >* iNode = i.getNode();
    iNode->prev_->next_ = iNode->next;
    iNode->next_->prev_ = iNode->prev_;
    if (list.head_ == iNode)
    {
      list.head_ = list.size_ == 1 ? nullptr : iNode->next_;
    }
    --list.size_;
    Node< T >* node = position.getNode();
    iNode->prev_ = node->prev_;
    iNode->next_ = node;
    node->prev_ = iNode;
    node->prev_->next_ = iNode;
    ++size_;
  }

  template< typename T >
  void List< T >::splice(ConstIterator< T > position, List< T >&& list, ConstIterator< T > i)
  {
    splice(position, list, i);
  }

  template< typename T >
  void List< T >::splice(ConstIterator< T > pos, List< T >& list, ConstIterator< T > first, ConstIterator< T > last)
  {
    list.size_ -= std::distance(first, last);
    Node< T >* fNode = first.getNode();
    Node< T >* lNode = last.getNode();
    fNode->prev_->next_ = lNode;
    lNode->prev_ = fNode->prev_;
    Node< T >* node = pos.getNode();
    fNode->prev_ = node->prev_;
    lNode->prev_->next_ = node;
    node->prev_->next_ = fNode;
    node->prev_ = lNode->prev_;
    size_ += std::distance(first, last);
  }

  template< typename T >
  void List< T >::splice(ConstIterator< T > pos, List< T >&& list, ConstIterator< T > first, ConstIterator< T > last)
  {
    splice(pos, list, first, last);
  }


}
#endif
