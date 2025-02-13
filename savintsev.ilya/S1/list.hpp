#ifndef LIST_HPP
#define LIST_HPP
#include <iterator>

namespace savintsev
{
  template< typename T >
  class ListNode
  {
    T data;
    ListNode< T > * next;
    ListNode< T > * prev;
    ListNode(const T & value, ListNode * nextNode = nullptr, ListNode * prevNode = nullptr):
      data(value),
      next(nextNode),
      prev(prevNode)
    {}
  };

  template< typename T>
  class List
  {
  public:
    class Iterator:
      public std::iterator<std::bidirectional_iterator_tag, int>
    {
    public:
      Iterator(ListNode< T > * n);
      T & operator*();
      Iterator & operator++();
      Iterator & operator--();
      bool operator!=(const Iterator & rhs) const;
    private:
      ListNode< T > * node;
    };

    List();
    ~List();

    Iterator begin();
    Iterator end();

    T & front();
    T & back();

    bool empty() const;
    size_t size() const;

    void push_front(const T & value);
    void push_back(const T & value);
    void pop_front();
    void pop_back();
    void swap(List & rhs);
    void clear();
  private:
    ListNode< T > * dummy;
    size_t list_size;
  };
}
#endif
