#ifndef LIST_HPP
#define LIST_HPP

namespace zholobov {
  template < typename T >
  class List {
    List();
    ~List();
    List(const List& other);
    List(List&& other) noexcept;
  };
}
#endif
