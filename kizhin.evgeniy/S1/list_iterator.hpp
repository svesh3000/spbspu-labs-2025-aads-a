#ifndef SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S1_LIST_ITERATOR_HPP
#define SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S1_LIST_ITERATOR_HPP

#include <iterator>
#include <type_traits>
#include "list_fwd.hpp"
#include "list_node.hpp"

namespace kizhin {
  namespace detail {
    template < typename T, bool isConst >
    class ListIterator
    {
    public:
      using value_type = T;
      using difference_type = std::ptrdiff_t;
      using pointer = std::conditional_t< isConst, const value_type*, value_type* >;
      using reference = std::conditional_t< isConst, const value_type&, value_type& >;
      using iterator_category = std::bidirectional_iterator_tag;

      ListIterator() = default;
      ListIterator(const ListIterator&) = default;
      ListIterator& operator=(const ListIterator&) = default;

      pointer operator->();
      reference operator*();

      ListIterator& operator++();
      ListIterator operator++(int);
      ListIterator& operator--();
      ListIterator operator--(int);

    private:
      using Node = detail::Node< value_type >;
      friend class ::kizhin::List< value_type >;

      Node* node_ = nullptr;

      explicit ListIterator(Node* node): node_(node) {}
    };

    template < typename T, bool b >
    typename ListIterator< T, b >::pointer ListIterator< T, b >::operator->()
    {
      return std::addressof(node_->data);
    }

    template < typename T, bool b >
    typename ListIterator< T, b >::reference ListIterator< T, b >::operator*()
    {
      return node_->data;
    }

    template < typename T, bool b >
    ListIterator< T, b >& ListIterator< T, b >::operator++()
    {
      node_ = node_->next;
      return *this;
    }

    template < typename T, bool b >
    ListIterator< T, b > ListIterator< T, b >::operator++(int)
    {
      ListIterator tmp(*this);
      ++(*this);
      return tmp;
    }

    template < typename T, bool b >
    ListIterator< T, b >& ListIterator< T, b >::operator--()
    {
      node_ = node_->prev;
      return *this;
    }

    template < typename T, bool b >
    ListIterator< T, b > ListIterator< T, b >::operator--(int)
    {
      ListIterator tmp(*this);
      --(*this);
      return tmp;
    }
  }
}

#endif

