#include "FwdList.hpp"
#include "IteratorFwd.hpp"

template< class T >
FwdList::FwdList() :
  fake(new NodeFwdList<T>{T{}, nullptr}),
  nodeCount(0)
{}

template< class T >
FwdList::FwdList(const FwdList &other) :
  fake(new NodeFwdList<T>{T{}, nullptr}),
  nodeCount(0)
{
  for (auto it = other.begin(); it != other.end(); ++it)
  {
    push_front(*it);
  }
}

template< class T >
FwdList::FwdList(FwdList &&other) noexcept :
  fake(other.fake),
  nodeCount(other.nodeCount)
{
  other.fake = nullptr;
  other.nodeCount = 0;
}

template< class T >
FwdList &FwdList::operator=(const FwdList &other)
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
  return *this;
}

template< class T >
FwdList &FwdList::operator=(FwdList &&other) noexcept
{
  if (this == &other)
  {
    return *this;
  }
  clear();
  delete fake;
  fake = other.fake;
  nodeCount = other.nodeCount;

  other.fake = nullptr;
  other.nodeCount = 0;

  return *this;
}

template< class T >
FwdList::~FwdList()
{
  clear();
  delete fake;
}

template< class T >
IteratorFwd FwdList::begin() const
{
  return IteratorFwd(fake->next);
}

template< class T >
IteratorFwd FwdList::end() const
{
  return IteratorFwd(fake);
}

template< class T >
T & FwdList::front()
{
  if (empty())
  {
    throw std::out_of_range("List is empty");
  }
  return fake->next->data;
}

template< class T >
T & FwdList::back()
{
  if (empty())
  {
    throw std::out_of_range("List is empty");
  }

  NodeFwdList<T> *current = fake->next;
  while (current->next != fake->next)
  {
    current = current->next;
  }
  return current->data
}

template< class T >
bool FwdList::empty() const
{
  return nodeCount == 0;
}

template< class T >
size_t FwdList::size() const
{
  return nodeCount;
}

template< class T >
void FwdList::push_front(const T &value)
{
  NodeFwdList<T> *newNode = new NodeFwdList<T>{value, fake->next};
  fake->next = newNode;
  ++nodeCount;
}

template< class T >
void FwdList::pop_front()
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
void FwdList::clear()
{
  while (!empty())
  {
    pop_front();
  }
}

template< class T >
void FwdList::remove(const T &value)
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
void FwdList::splice(const FwdList<T> &other)
{
  if (other.empty())
  {
    return;
  }

  NodeFwdList<T> *lastNode = fake->next;
  while (lastNode->next != fake)
  {
    lastNode = lastNode->next;
  }

  lastNode->next = other.fake->next;
  nodeCount += other.nodeCount;
}

template< class T >
void FwdList::reverse()
{
  if (empty())
    return;

  NodeFwdList<T> *prev = nullptr;
  NodeFwdList<T> *current = fake->next;
  NodeFwdList<T> *next = nullptr;

  while (current != fake)
  {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  fake->next = prev;
}

template< class T >
bool FwdList::operator==(const FwdList<T> &other) const
{
  if (nodeCount != other.nodeCount)
  {
    return false;
  }

  IteratorFwd it1 = begin();
  IteratorFwd it2 = other.begin();
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
bool FwdList::operator!=(const FwdList<T> &other) const
{
  return !(*this == other);
}

template< class T >
bool FwdList::operator<(const FwdList<T> &other) const
{
  IteratorFwd it1 = begin();
  IteratorFwd it2 = other.begin();
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
bool FwdList::operator>(const FwdList<T> &other) const
{
  return other < *this;
}
