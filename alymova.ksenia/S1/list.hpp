#ifndef LIST_HPP
#define LIST_HPP
#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace alymova
{
  template< typename T >
  struct ListNode;
  template< typename T >
  struct Iterator;
  template< typename T >
  struct ConstIterator;

  template< typename T >
  class List
  {
  public:
    List();
    List(const List< T >& other);
    List(List< T >&& other) noexcept;
    List(size_t n, const T& value = T());
    ~List() noexcept;

    List< T >& operator=(const List< T >& other);
    List< T >& operator=(List< T >&& other) noexcept;

    Iterator< T > begin() noexcept;
    ConstIterator< T > begin() const noexcept;
    ConstIterator< T > cbegin() const noexcept;
    Iterator< T > end() noexcept;
    ConstIterator< T > end() const noexcept;
    ConstIterator< T > cend() const noexcept;

    T& front() noexcept;
    T& back() noexcept;
    const T& front() const noexcept;
    const T& back() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    void push_front(const T& value);
    void pop_front() noexcept;
    void push_back(const T& value);
    void pop_back() noexcept;
    void swap(List< T >& other) noexcept;
    void clear() noexcept;

    void remove(const T& value) noexcept;
    template< typename Predicate >
    void remove_if(Predicate pred);
  private:
    ListNode< T >* fake_;
    ListNode< T >* head_;

    void push_single(ListNode< T >* node);
    ListNode< T >* get_last_node();
    bool is_equal_node(const T& value, const T& data);
  };

  template< typename T >
  struct EqualNode
  {
    const T& value;
    EqualNode(const T& new_value):
      value(new_value)
    {}
    bool operator()(const T& data)
    {
      return value == data;
    }
  };

  template< typename T >
  bool operator==(const List< T >& lhs, const List< T >& rhs) noexcept
  {
    if (lhs.size() != rhs.size())
    {
      return false;
    }
    for (auto it_lhs = lhs.cbegin(), it_rhs = rhs.cbegin(); it_lhs != lhs.cend(); ++it_lhs, ++it_rhs)
    {
      if ((*it_lhs) != (*it_rhs))
      {
        return false;
      }
    }
    return true;
  }

  template< typename T >
  bool operator!=(const List< T >& lhs, const List< T >& rhs) noexcept
  {
    return (!(lhs == rhs));
  }

  template< typename T >
  List< T >::List():
    fake_(new ListNode< T >{T(), nullptr, nullptr}),
    head_(fake_)
  {}

  template< typename T >
  List< T >::List(const List< T >& other):
    List()
  {
    try
    {
      for (auto it = other.cbegin(); it != other.cend(); ++it)
      {
        push_back(*(it));
      }
    }
    catch (const std::bad_alloc& e)
    {
      clear();
      throw;
    }
  }

  template< typename T >
  List< T >::List(List< T >&& other) noexcept:
    fake_(std::exchange(other.fake_, nullptr)),
    head_(std::exchange(other.head_, nullptr))
  {}

  template< typename T >
  List< T >::List(size_t n, const T& value):
    List()
  {
    for (size_t i = 0; i < n; i++)
    {
      push_back(value);
    }
  }

  template< typename T >
  List< T >& List< T >::operator=(const List< T >& other)
  {
    assert(this != std::addressof(other) && "Assigning a list to itself");
    List< T > copy(other);
    swap(copy);
    return *this;
  }

  template< typename T >
  List< T >& List< T >::operator=(List< T >&& other) noexcept
  {
    assert(this != std::addressof(other) && "Assigning a list to itself");
    clear();
    fake_ = std::exchange(other.fake_, nullptr);
    head_ = std::exchange(other.head_, nullptr);
    return *this;
  }

  template< typename T >
  List< T >::~List() noexcept
  {
    clear();
    delete fake_;
  }

  template< typename T >
  Iterator< T > List< T >::begin() noexcept
  {
    return Iterator< T >(head_);
  }

  template< typename T >
  ConstIterator< T > List< T >::begin() const noexcept
  {
    return ConstIterator< T >(head_);
  }

  template< typename T >
  ConstIterator< T > List< T >::cbegin() const noexcept
  {
    return begin();
  }

  template< typename T >
  Iterator< T > List< T >::end() noexcept
  {
    return Iterator< T >(fake_);
  }

  template< typename T >
  ConstIterator< T > List< T >::end() const noexcept
  {
    return ConstIterator< T >(fake_);
  }

  template< typename T >
  ConstIterator< T > List< T >::cend() const noexcept
  {
    return end();
  }

  template< typename T >
  T& List< T >::front() noexcept
  {
    assert(!empty());
    return head_->data;
  }

  template< typename T >
  T& List< T >::back() noexcept
  {
    assert(!empty());
    return fake_->prev->data;
  }

  template< typename T >
  const T& List< T >::front() const noexcept
  {
    assert(!empty());
    return head_->data;
  }

  template< typename T >
  const T& List< T >::back() const noexcept
  {
    assert(!empty());
    return fake_->prev->data;
  }

  template< typename T >
  bool List< T >::empty() const noexcept
  {
    return cbegin() == cend();
  }

  template< typename T >
  size_t List< T >::size() const noexcept
  {
    size_t size = 0;
    auto it = begin();
    while (it != end())
    {
      ++it;
      ++size;
    }
    return size;
  }

  template< typename T >
  void List< T >::push_front(const T& value)
  {
    auto node = new ListNode< T >{value, nullptr, nullptr};
    if (empty())
    {
      push_single(node);
    }
    else
    {
      ListNode< T >* subhead = head_;
      head_ = node;
      head_->next = subhead;
      subhead->prev = head_;
    }
  }

  template< typename T >
  void List< T >::pop_front() noexcept
  {
    assert(!empty());
    ListNode< T >* subhead = head_->next;
    delete head_;
    head_ = subhead;
    head_->prev = nullptr;
  }

  template< typename T >
  void List< T >::push_back(const T& value)
  {
    auto node = new ListNode< T >{value, nullptr, nullptr};
    if (empty())
    {
      push_single(node);
    }
    else
    {
      ListNode< T >* subhead = get_last_node();
      subhead->next = node;
      node->prev = subhead;
      node->next = fake_;
      fake_->prev = node;
    }
  }

  template< typename T >
  void List< T >::pop_back() noexcept
  {
    assert(!empty());
    ListNode< T >* subhead = get_last_node();
    if (size() == 1)
    {
      head_ = fake_;
      fake_->prev = nullptr;
      delete subhead;
    }
    else
    {
      subhead->prev->next = fake_;
      fake_->prev = subhead->prev;
      delete subhead;
    }
  }

  template< typename T >
  void List< T >::swap(List< T >& other) noexcept
  {
    std::swap(fake_, other.fake_);
    std::swap(head_, other.head_);
  }

  template< typename T >
  void List< T >::clear() noexcept
  {
    while (!empty())
    {
      pop_front();
    }
  }

  template< typename T >
  void List < T >::remove(const T& value) noexcept
  {
    auto pred = EqualNode< T >{value};
    remove_if< EqualNode< T > >(pred);
  }

  template< typename T >
  template< typename Predicate >
  void List< T >::remove_if(Predicate pred)
  {
    assert(!empty());
    ListNode< T >* subhead = head_;
    auto it = begin();
    while (it != end())
    {
      Iterator< T > it_next = ++it;
      --it;
      ListNode< T >* subnext = subhead->next;
      if (pred(*it))
      {
        if (it == begin())
        {
          pop_front();
        }
        else if (it == --end())
        {
          pop_back();
        }
        else
        {
          subhead->prev->next = subhead->next;
          subhead->next->prev = subhead->prev;
          delete subhead;
        }
      }
      subhead = subnext;
      it = it_next;
    }
  }

  template< typename T >
  void List< T >::push_single(ListNode< T >* node)
  {
    head_ = node;
    head_->next = fake_;
    fake_->prev = head_;
  }

  template< typename T >
  ListNode< T >* List< T >::get_last_node()
  {
    ListNode< T >* subhead = head_;
    for (auto it = ++begin(); it != end(); ++it)
    {
      subhead = subhead->next;
    }
    return subhead;
  }

  template< typename T >
  bool is_equal_node(const T& value, const T& data)
  {
    return data == value;
  }
}
#endif
