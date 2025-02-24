#ifndef FWD_LIST
#define FWD_LIST

#include <cstddef>

namespace maslevtsov {
  template< typename T >
  class FwdListNode
  {
  public:
    T data_;
    FwdListNode< T >* next_;

    FwdListNode():
      data_(T()),
      next_(nullptr)
    {}
  };

  template< typename T >
  class FwdList
  {
  public:
    FwdList();

    ~FwdList();

    T& front() const;
    T& back() const;

    std::size_t size() const;
    bool empty() const;

    void push_front(const T& value);
    void push_front(T&& value);
    void push_back(const T& value);
    void push_back(T&& value);
    void swap(FwdList& other);
    void clear();

  private:
    FwdListNode< T >* head_;
    FwdListNode< T >* tail_;
    std::size_t size_;
  };
}

#endif
