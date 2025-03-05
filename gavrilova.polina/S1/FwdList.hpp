#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <algorithm>
#include "NodeFwdList.hpp"
#include "IteratorFwd.hpp"

namespace gavrilova {

  template< class T >
  class FwdList
  {
  public:
    FwdList();
    FwdList(const FwdList& other);
    FwdList(FwdList&& other) noexcept;
    ~FwdList();

    FwdList& operator=(const FwdList& other);
    FwdList& operator=(FwdList&& other) noexcept;

    bool operator==(const FwdList& other) const;
    bool operator!=(const FwdList& other) const;
    bool operator<(const FwdList& other) const;
    bool operator>(const FwdList& other) const;

    IteratorFwd< T > begin() const;
    IteratorFwd< T > end() const;
    T& front();
    // T& back();
    bool empty() const noexcept;
    size_t size() const noexcept;
    void push_front(const T& value);
    void pop_front();
    void clear();
    void remove(const T& value);
    void splice(const FwdList& other);
    void reverse();
  private:
    NodeFwdList< T >* fake;
    size_t nodeCount;
  };

}

template< class T >
gavrilova::FwdList< T >::FwdList() :
  fake(reinterpret_cast< NodeFwdList< T >* >(new char[sizeof(NodeFwdList< T >)])),
  nodeCount(0)
{
  fake->next = fake;
}

template< class T >
gavrilova::FwdList< T >::FwdList(const FwdList &other) :
  FwdList()
{
  for (auto it = other.begin(); it != other.end(); ++it)
  {
    push_front(*it);
  }
  reverse();
}

template< class T >
gavrilova::FwdList< T >::FwdList(FwdList &&other) noexcept :
  fake(other.fake),
  nodeCount(other.nodeCount)
{
  other.fake = nullptr;
  other.nodeCount = 0;
}

template< class T >
gavrilova::FwdList< T >& gavrilova::FwdList< T >::operator=(const FwdList &other)
{
  if (this == &other)
  {
    return *this;
  }
  clear();
  for (auto it = other.begin(); it != other.end(); ++it)
  {
    push_front(*it);
  }
  reverse();
  return *this;
}

template< class T >
gavrilova::FwdList< T >& gavrilova::FwdList< T >::operator=(FwdList &&other) noexcept
{
  if (this == &other)
  {
    return *this;
  }
  clear();
  delete[] reinterpret_cast< char* >(fake);;
  fake = other.fake;
  nodeCount = other.nodeCount;

  other.fake = nullptr;
  other.nodeCount = 0;

  return *this;
}

template< class T >
gavrilova::FwdList< T >::~FwdList()
{
  clear();
  delete[] reinterpret_cast< char* >(fake);
}

template< class T >
gavrilova::IteratorFwd< T > gavrilova::FwdList< T >::begin() const
{
  return IteratorFwd< T >(fake->next);
}

template< class T >
gavrilova::IteratorFwd< T > gavrilova::FwdList< T >::end() const
{
  return IteratorFwd< T >(fake);
}

template< class T >
T & gavrilova::FwdList< T >::front()
{
  if (empty())
  {
    throw std::out_of_range("List is empty");
  }
  return fake->next->data;
}

// template< class T >
// T & gavrilova::FwdList< T >::back()
// {
//   if (empty())
//   {
//     throw std::out_of_range("List is empty");
//   }

//   NodeFwdList<T> *current = fake->next;
//   while (current->next != fake->next)
//   {
//     current = current->next;
//   }
//   return current->data;
// }

template< class T >
bool gavrilova::FwdList< T >::empty() const noexcept
{
  return nodeCount == 0;
}

template< class T >
size_t gavrilova::FwdList< T >::size() const noexcept
{
  return nodeCount;
}

template< class T >
void gavrilova::FwdList< T >::push_front(const T &value)
{
  NodeFwdList<T> *newNode = new NodeFwdList<T>{value, fake->next};
  fake->next = newNode;
  ++nodeCount;
}

template< class T >
void gavrilova::FwdList< T >::pop_front()
{
  if (empty())
  {
    throw std::out_of_range("List is empty");
  }
  NodeFwdList<T> *temp = fake->next;
  fake->next = fake->next->next;
  delete temp;
  --nodeCount;
}

template< class T >
void gavrilova::FwdList< T >::clear()
{
  while (!empty())
  {
    pop_front();
  }
}

template< class T >
void gavrilova::FwdList< T >::remove(const T &value)
{
  NodeFwdList<T> *current = fake;
  while (current->next != fake)
  {
    if (current->next->data == value)
    {
      NodeFwdList<T> *temp = current->next;
      current->next = current->next->next;
      delete temp;
      --nodeCount;
    }
    else
    {
      current = current->next;
    }
  }
}

template< class T >
void gavrilova::FwdList< T >::splice(const FwdList<T> &other)
{
  if (other.empty())
  {
    return;
  }

  NodeFwdList<T> *lastNode = fake;
  while (lastNode->next != fake)
  {
    lastNode = lastNode->next;
  }

  lastNode->next = other.fake->next;
  nodeCount += other.nodeCount;
}

template< class T >
void gavrilova::FwdList< T >::reverse()
{
  if (fake->next == fake)
  {
    return;
  }
  NodeFwdList< T >* next = fake->next;
  NodeFwdList< T >* last = fake;
  while (next->next != fake)
  {
    NodeFwdList< T >* remember = next->next;
    next->next = last;
    last = next;
    next = remember;
  }
  next->next = last;
  fake->next = next;
}

template< class T >
bool gavrilova::FwdList< T >::operator==(const FwdList<T> &other) const
{
  if (nodeCount != other.nodeCount)
  {
    return false;
  }

  IteratorFwd< T > it1 = begin();
  IteratorFwd< T > it2 = other.begin();
  while (it1 != end())
  {
    if (*it1 != *it2)
      return false;
    ++it1;
    ++it2;
  }
  return true;
}

template< class T >
bool gavrilova::FwdList< T >::operator!=(const FwdList<T> &other) const
{
  return !(*this == other);
}

template< class T >
bool gavrilova::FwdList< T >::operator<(const FwdList<T> &other) const
{
  IteratorFwd< T > it1 = begin();
  IteratorFwd< T > it2 = other.begin();
  while (it1 != end() && it2 != other.end())
  {
    if (*it1 < *it2)
    {
      return true;
    }
    if (*it1 > *it2)
    {
      return false;
    }
    ++it1;
    ++it2;
  }
  return nodeCount < other.nodeCount;
}

template< class T >
bool gavrilova::FwdList< T >::operator>(const FwdList<T> &other) const
{
  return other < *this;
}

#endif
