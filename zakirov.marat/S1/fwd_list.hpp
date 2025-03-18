#ifndef MY_LIST_HPP
#define MY_LIST_HPP
#include <cstddef>
#include <utility>
#include "fwd_list_node.hpp"
#include "fwd_iterator.hpp"

namespace zakirov
{
  template< typename T >
  class FwdList
  {
  public:
    FwdList();
    FwdList(size_t node_quantity, const T & val);
    template< typename InputIterator >
    FwdList(InputIterator first, InputIterator second);
    FwdList(std::initializer_list< T > init_list);
    ~FwdList();
    FwdListNode< T > * front();
    FwdIterator< T > begin();
    FwdIterator< T > end();
    void pop_front();
    void push_front(const T & data);
    void push_front(const T && data);
    void erase_after(FwdIterator< T > element);
    void insert_after(FwdIterator< T > element, const T & data);
    bool empty();
    size_t size();
    void swap(FwdList & other);
    void splice_after(FwdIterator< T > pos, FwdList & fwdlst);
    void splice_after(FwdIterator< T > pos, FwdList & fwdlst, FwdIterator< T > i);
    void splice_after(FwdIterator< T > pos, FwdList & fwdlst, FwdIterator< T > first, FwdIterator< T > last);
    void assign(size_t n, const T & val);
    template< typename InputIterator >
    void assign(InputIterator first, InputIterator last);
    void assign(std::initializer_list< T > init_list);
    void clear();
    void remove(T data);
    template< typename P>
    void remove_if(P predicate);
  private:
    FwdListNode< T > * fake_node_;
  };

  template< typename T >
  FwdList< T >::FwdList():
    fake_node_(reinterpret_cast< FwdListNode< T >* >(new char[sizeof(FwdListNode< T >)]))
  {
    fake_node_->next_ = fake_node_;
  }

  template< typename T >
  FwdList< T >::FwdList(size_t node_quantity, const T & data)
  {
    FwdList();
    for (size_t i = 0; i < node_quantity; ++i)
    {
      push_front(data);

    }
  }

  template< typename T >
  template< typename InputIterator >
  FwdList< T >::FwdList(InputIterator first, InputIterator second):
    FwdList()
  {
    FwdIterator< T > inserter = begin();
    for (; first != second; ++first)
    {
      insert_after(last_node, * first);
      ++last_node;
    }
  }

  template< typename T >
  FwdList< T >::FwdList(std::initializer_list< T > init_list):
    FwdList()
  {
    FwdIterator< T > inserter = begin();
    for (auto i = init_list.begin(); i != init_list.end(); ++i)
    {
      insert_after(last_node, *i);
      ++last_node;
    }
  }

  template< typename T >
  FwdList< T >::~FwdList()
  {
    clear();
    delete fake_node_;
  }

  template< typename T >
  FwdListNode< T > * FwdList< T >::front()
  {
    return fake_node_->next_;
  }

  template< typename T >
  FwdIterator< T > FwdList< T >::begin()
  {
    return FwdIterator< T >(fake_node_->next_);
  }

  template< typename T >
  FwdIterator< T > FwdList< T >::end()
  {
    return FwdIterator< T >(fake_node_);
  }

  template< typename T >
  void FwdList< T >::pop_front()
  {
    FwdListNode< T > * new_begin = (fake_node_->next_)->next_;
    delete fake_node_->next_;
    fake_node_->next_ = new_begin;
  }

  template< typename T >
  void FwdList< T >::push_front(const T & data)
  {
    FwdListNode< T > * new_element = new FwdListNode< T >(data);
    new_element->next_ = fake_node_->next_;
    fake_node_->next_ = new_element;
  }

  template< typename T >
  void FwdList< T >::push_front(const T && data)
  {
    FwdListNode< T > * new_element = new FwdListNode< T >(std::move(data));
    new_element->next_ = fake_node_->next_;
    fake_node_->next_ = new_element;
  }

  template< typename T >
  void FwdList< T >::erase_after(FwdIterator< T > element)
  {
    FwdListNode< T > * temp_element = element.node_->next_->next_;
    delete element.node_->next_;
    element.node_->next_ = temp_element;
  }

  template< typename T >
  void FwdList< T >::insert_after(FwdIterator< T > element, const T & data)
  {
    FwdListNode< T > * new_element = new FwdListNode< T >(data);
    new_element->next_ = element.node_->next_;
    element.node_->next_ = new_element;
  }

  template< typename T >
  bool FwdList< T >::empty()
  {
    if (fake_node_->next_ == fake_node_)
    {
      return 1;
    }

    return 0;
  }

  template< typename T >
  size_t FwdList< T >::size()
  {
    size_t counter = 0;
    FwdListNode< T > * nailed_ptr = fake_node_;
    FwdListNode< T > * fillable_ptr = fake_node_->next_;
    while (nailed_ptr != fillable_ptr)
    {
      ++counter;
      fillable_ptr->next_;
    }

    return counter;
  }

  template< typename T >
  void FwdList< T >::swap(FwdList & other)
  {
    FwdListNode< T > * temporary_node = other.fake_node_;
    other.fake_node_ = fake_node_;
    fake_node_ = temporary_node;
  }

  template< typename T >
  void FwdList< T >::splice_after(FwdIterator< T > pos, FwdList & fwdlst)
  {
    splice_after(pos, fwdlst, fwdlst.begin(), fwdlst.end())
  }

  template< typename T >
  void FwdList< T >::splice_after(FwdIterator< T > pos, FwdList & fwdlst, FwdIterator< T > i)
  {
    FwdList< T > * next_base = pos.node_->next_;
    FwdList< T > * next_new = i.node_->next_->next_;
    pos.node_->next_ = i.node_->next_;
    pos.node_->next_->next_ = next_base;
    i.node_->next_ = next_new;
  }

  template< typename T >
  void FwdList< T >::splice_after(FwdIterator< T > pos, FwdList & fwdlst, FwdIterator< T > first, FwdIterator< T > last)
  {
    FwdIterator< T > after_first = first;
    ++after_first;
    for (; after_first != last; ++after_first, ++first)
    {
      splice_after(pos, fwd_list, first);
    }
  }

  template< typename T >
  void FwdList< T >::assign(size_t n, const T & val)
  {
    clear();
    for (size_t i = 0; i < n; ++i)
    {
      push_front(val);
    }
  }

  template< typename T >
  template< typename InputIterator >
  void FwdList< T >::assign(InputIterator first, InputIterator last)
  {
    clear();
    FwdIterator< T > inserter = begin();
    for (; first != last; ++first)
    {
      insert_after(inserter, *first);
    }
  }

  template< typename T >
  void FwdList< T >::clear()
  {
    while (!empty())
    {
      pop_front();
    }
  }

  template< typename T >
  void FwdList< T >::assign(std::initializer_list< T > init_list)
  {

  }

  template< typename T >
  void FwdList< T >::remove(T data)
  {
    FwdIterator< T > prev = end();
    FwdIterator< T > real = begin();
    for (FwdIterator< T > i = begin(); i != end(); ++i)
    {
      if (i.node_->data_ == data)
      {
        erase_after(prev);
        ++real;
      }
      else
      {
        ++prev;
        ++real;
      }
    }
  }

  template< typename T >
  template< typename P >
  void FwdList< T >::remove_if(P predicate)
  {
    FwdIterator< T > prev = end();
    FwdIterator< T > real = begin();
    for (FwdIterator< T > i = begin(); i != end(); ++i)
    {
      if (predicate(*real))
      {
        erase_after(prev);
        ++real;
      }
      else
      {
        ++prev;
        ++real;
      }
    }
  }
}

#endif
