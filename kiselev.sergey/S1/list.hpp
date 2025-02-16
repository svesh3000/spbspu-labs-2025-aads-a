#ifndef LIST_HPP
#define LIST_HPP
#include <stdexcept>

namespace kiselev
{
  template < typename T >
  struct Node
  {
    T data_;
    Node< T >* next_;
    Node< T >* prev_;

    Node(const T& data):
      data_(data),
      prev_(nullptr),
      next_(nullptr)
    {}

    Node():
      data_(T()),
      prev_(nullptr),
      next_(nullptr)
    {}

    ~Node()
    {
      delete data_;
    }
  };
  template< typename T>
  class List
  {
  public:

    List();
    List(const List& list);
    List(const List&& list);
    ~List();
  private:

    Node< T >* node;
    size_t size;

  };
}
#endif
