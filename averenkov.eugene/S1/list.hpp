#ifndef LIST_HPP
#define LIST_HPP
#include "node.hpp"

namespace averenkov
{
  template< class T>
  class List
  {
  private:
    Node* fake;
    Node* head;
    size_t size;
  public:
    List();
    List(const List< T >&);
    List(List< T >&&);
    List(size_t, const T&);
    ~List();

    using Iter = ListIterator< T >;
    using Iterc = ConstListIterator< T >;

    Iter begin() const;
    Iter end() const;

    Iterc cbegin() const;
    Iterc cend() const;

    T& front();
    T& back();

    bool empty();

    size_t size() const;

    void push_front(const T&);
    void push_back(const T&);
    void pop_front();
    void pop_back();
    void swap(List&);    
    void clear();

    void fill(Iter first, Iter last, const T&);

    void remove(const T&);
    template< typename UnaryPredicate >
    void removeIf(UnaryPredicate);

    void splice(Iterc pos, List< T >&);
    void splice(Iterc pos, List< T >&&);
    void splice(Iterc pos, List< T >&, Iterc it);
    void splice(Iterc pos, List< T >&&, Iterc it);
    void splice(Iterc pos, List< T >&, Iterc first, Iterc last);
    void splice(Iterc pos, List< T >&&, Iterc first, Iterc last);



    void assign(size_t, const T&);


  private:

    Node< T >* fake_;
    Node< T >* tail_;
    size_t size_;

  };
};


#endif
