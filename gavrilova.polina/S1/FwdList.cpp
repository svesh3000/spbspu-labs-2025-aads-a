#include "FwdList.hpp"
#include "IteratorFwd.hpp"

FwdList::FwdList() : fake(new NodeFwdList<T>{T{}, nullptr}),
                     nodeCount(0)
{
}

FwdList::FwdList(const FwdList &other) : fake(new NodeFwdList<T>{T{}, nullptr}),
                                         nodeCount(0)
{
  for (auto it = other.begin(); it != other.end(); ++it)
  {
    push_front(*it);
  }
}

FwdList::FwdList(FwdList &&other) noexcept : fake(other.fake),
                                             nodeCount(other.nodeCount)
{
  other.fake = nullptr;
  other.nodeCount = 0;
}

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

FwdList::~FwdList()
{
  clear();
  delete fake;
}

IteratorFwd begin()
{
  return IteratorFwd(fake->next);
}

IteratorFwd end()
{
  return IteratorFwd(fake);
}

T &front()
{
  if (empty())
  {
    throw std::out_of_range("List is empty");
  }
  return fake->next->data;
}

T &back()
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

bool FwdList::empty() const
{
  return nodeCount == 0;
}

size_t FwdList::size() const
{
  return nodeCount;
}

void FwdList::push_front(const T &value)
{
  ListNode<T> *newNode = new ListNode<T>{value, fake->next};
  fake->next = newNode;
  ++nodeCount;
}

void FwdList::pop_front()
{
  if (empty())
  {
    throw std::out_of_range("List is empty");
  }
  ListNode<T> *temp = fake->next;
  fake->next = fake->next->next;
  delete temp;
  --nodeCount;
}

void FwdList::clear()
{
  while (!empty())
  {
    pop_front();
  }
}

void FwdList::remove(const T &value)
{
  ListNode<T> *current = fake;
  while (current->next != fake)
  {
    if (current->next->data == value)
    {
      ListNode<T> *temp = current->next;
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

void FwdList::splice(const FwdList<T> &other)
{
  if (other.empty())
  {
    return;
  }

  ListNode<T> *lastNode = fake->next;
  while (lastNode->next != fake)
  {
    lastNode = lastNode->next;
  }

  lastNode->next = other.fake->next;
  nodeCount += other.nodeCount;
}

void FwdList::reverse()
{
  if (empty())
    return;

  ListNode<T> *prev = nullptr;
  ListNode<T> *current = fake->next;
  ListNode<T> *next = nullptr;

  while (current != fake)
  {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  fake->next = prev;
}

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

bool FwdList::operator!=(const FwdList<T> &other) const
{
  return !(*this == other);
}

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

bool FwdList::operator>(const FwdList<T> &other) const
{
  return other < *this;
}
