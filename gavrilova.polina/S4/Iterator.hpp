// #ifndef ITERATOR_ TTT_HPP
// #define ITERATOR_TTT_HPP

// #include <iterator>
// #include <cassert>
// #include "TwoThreeTree.hpp"

// namespace gavrilova {
//   template< class Key, class Value, class Cmp >
//   struct Iterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
//   {
//     using this_t = Iterator< Key, Value, Cmp >;

//     Iterator();
//     ~Iterator() = default;
//     Iterator(const this_t&) = default;
//     // ConstIteratorFwd(IteratorFwd< T >& other);
//     this_t& operator=(const this_t&) = default;

//     this_t& operator++();
//     this_t operator++(int);
//     this_t& operator--();
//     this_t operator--(int);
//     const T& operator*() const;
//     const T* operator->() const;
//     bool operator!=(const this_t&) const;
//     bool operator==(const this_t&) const;

//   private:
//     TwoThreeTree< Key, Value, Cmp >* node_;
//     friend class TwoThreeTree< Key, Value, Cmp >;
//     friend class ConstIterator< Key, Value, Cmp >;
//     explicit Iterator(TwoThreeTree< Key, Value, Cmp >* node): node_(node) {};
//   };
// }