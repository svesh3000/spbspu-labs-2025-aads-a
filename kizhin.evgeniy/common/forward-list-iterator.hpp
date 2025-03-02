#ifndef SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_COMMON_FORWARD_LIST_ITERATOR_HPP
#define SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_COMMON_FORWARD_LIST_ITERATOR_HPP

#include <iterator>
#include <type_traits>
#include "forward-list-fwd-declaration.hpp"
#include "forward-list-node.hpp"

namespace kizhin {
  namespace detail {
    template < typename T, bool IsConst >
    class ForwardListIterator final
    {
    public:
      using value_type = T;
      using difference_type = std::ptrdiff_t;
      using pointer = std::conditional_t< IsConst, const value_type*, value_type* >;
      using reference = std::conditional_t< IsConst, const value_type&, value_type& >;
      using iterator_category = std::forward_iterator_tag;

      ForwardListIterator() = default;
      template < bool OtherIsConst,
          typename std::enable_if< IsConst && !OtherIsConst, int >::type = 0 >
      ForwardListIterator(const ForwardListIterator< T, OtherIsConst >& other);

      pointer operator->() const noexcept;
      reference operator*() const noexcept;

      ForwardListIterator& operator++();
      ForwardListIterator operator++(int);

    private:
      using Node = detail::Node< value_type >;

      Node* node_ = nullptr;

      explicit ForwardListIterator(Node* node): node_(node) {}

      friend class ForwardListIterator< T, !IsConst >;
      friend class ::kizhin::ForwardList< value_type >;
      template < typename U, bool c1, bool c2 >
      friend bool operator==(const ForwardListIterator< U, c1 >&,
          const ForwardListIterator< U, c2 >&);
    };

    template < typename T, bool IsConst >
    template < bool OtherIsConst,
        typename std::enable_if< IsConst && !OtherIsConst, int >::type >
    ForwardListIterator< T, IsConst >::ForwardListIterator(
        const ForwardListIterator< T, OtherIsConst >& rhs):
      node_(rhs.node_)
    {
    }

    template < typename T, bool c >
    typename ForwardListIterator< T, c >::pointer ForwardListIterator< T,
        c >::operator->() const noexcept
    {
      return std::addressof(node_->data);
    }

    template < typename T, bool c >
    typename ForwardListIterator< T, c >::reference ForwardListIterator< T,
        c >::operator*() const noexcept
    {
      return node_->data;
    }

    template < typename T, bool c >
    ForwardListIterator< T, c >& ForwardListIterator< T, c >::operator++()
    {
      node_ = node_->next;
      return *this;
    }

    template < typename T, bool c >
    ForwardListIterator< T, c > ForwardListIterator< T, c >::operator++(int)
    {
      ForwardListIterator tmp(*this);
      ++(*this);
      return tmp;
    }

    template < typename T, bool c1, bool c2 >
    bool operator==(const ForwardListIterator< T, c1 >& lhs,
        const ForwardListIterator< T, c2 >& rhs)
    {
      return lhs.node_ == rhs.node_;
    }

    template < typename T, bool c1, bool c2 >
    bool operator!=(const ForwardListIterator< T, c1 >& lhs,
        const ForwardListIterator< T, c2 >& rhs)
    {
      return !(lhs == rhs);
    }
  }
}

#endif

