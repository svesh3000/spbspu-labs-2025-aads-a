#ifndef CIRCULARFWDLIST_HPP
#define CIRCULARFWDLIST_HPP

#include <cstddef>

namespace zholobov {

  template < typename T >
  class CircularFwdListIterator;

  template < typename T >
  class CircularFwdList {
  public:
    CircularFwdList():
      head_(nullptr), tail_(nullptr), size_(0) {};
    ~CircularFwdList();
    CircularFwdList(const CircularFwdList& other);
    CircularFwdList(CircularFwdList&& other) noexcept;

    friend class CircularFwdListIterator< T >;

  private:
    struct Node_t {
      T value;
      Node_t* next;
    };

    Node_t* head_;
    Node_t* tail_;
    size_t size_;
  };
}

#endif
