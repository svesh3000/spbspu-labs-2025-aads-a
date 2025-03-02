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
    T& back();
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


#endif