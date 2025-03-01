#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <algorithm>
#include "IteratorFwd.hpp"

template< typename T >
struct NodeFwdList
{
  T data;
  NodeFwdList< T >* next;
};

template< typename T >
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
  
  IteratorFwd begin() const;
  IteratorFwd end() const;
  T& front();
  bool empty() const noexcept;
  size_t size() const noexcept;
  void push_front(const T& value);
  void pop_front();
  void clear();
  void remove(const T& value);
  void splice(const FwdList& other);
  void reverse();
private:
  NodeFwdList* fake_;
  size_t size_;
};

#endif