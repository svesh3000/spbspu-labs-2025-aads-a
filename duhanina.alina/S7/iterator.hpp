#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "HashTable.hpp"

namespace duhanina
{
 template< typename Key, typename Value, typename Hash, typename Equal >
 class HashTable;

 struct Bucket;

 template < class Key, class Value, class Hash, class Equal, bool isConst >
 class Iterator
 {
   friend class HashTable< Key, Value, Hash, Equal >;
   friend class Iterator< Key, Value, Hash, Equal, true >;
   friend class Iterator< Key, Value, Hash, Equal, false >;
 public:
   using value_type = std::conditional_t< isConst, const std::pair< Key, Value >, std::pair< Key, Value > >;
   using pointer = value_type*;
   using reference = value_type&;

   Iterator() noexcept;

   reference operator*() const noexcept;
   pointer operator->() const noexcept;

   Iterator& operator++() noexcept;
   Iterator operator++(int) noexcept;

   bool operator==(const Iterator& other) const noexcept;
   bool operator!=(const Iterator& other) const noexcept;

 private:
   using BucketPtr = std::conditional_t< isConst, const Bucket*, Bucket* >;
   BucketPtr current_;
   BucketPtr end_;

   Iterator(BucketPtr ptr, BucketPtr end_ptr) noexcept;
   void skip_empty();
 };

 template < class Key, class Value, class Hash, class Equal, bool isConst >
 void Iterator< Key, Value, Hash, Equal, isConst >::skip_empty()
 {
   while (current_ != end_ && (!current_->occupied || current_->deleted))
   {
     ++current_;
   }
 }

 template < class Key, class Value, class Hash, class Equal, bool isConst >
 Iterator< Key, Value, Hash, Equal, isConst >::Iterator() noexcept:
   current_(nullptr),
   end_(nullptr)
 {}

 template < class Key, class Value, class Hash, class Equal, bool isConst >
 Iterator< Key, Value, Hash, Equal, isConst >::Iterator(BucketPtr ptr, BucketPtr end_ptr) noexcept:
   current_(ptr),
   end_(end_ptr)
 {
   skip_empty();
 }

 template < class Key, class Value, class Hash, class Equal, bool isConst >
 typename Iterator< Key, Value, Hash, Equal, isConst >::reference
   Iterator< Key, Value, Hash, Equal, isConst >::operator*() const noexcept
 {
   return current_->data;
 }

 template < class Key, class Value, class Hash, class Equal, bool isConst >
 typename Iterator< Key, Value, Hash, Equal, isConst >::pointer
   Iterator< Key, Value, Hash, Equal, isConst >::operator->() const noexcept
 {
   return std::addressof(current_->data);
 }

 template < class Key, class Value, class Hash, class Equal, bool isConst >
 typename Iterator< Key, Value, Hash, Equal, isConst >::Iterator&
   Iterator< Key, Value, Hash, Equal, isConst >::operator++() noexcept
 {
   ++current_;
   skip_empty();
   return *this;
 }

 template < class Key, class Value, class Hash, class Equal, bool isConst >
 typename Iterator< Key, Value, Hash, Equal, isConst >::Iterator
   Iterator< Key, Value, Hash, Equal, isConst >::operator++(int) noexcept
 {
   Iterator tmp = *this;
   ++(*this);
   return tmp;
 }

 template < class Key, class Value, class Hash, class Equal, bool isConst >
 bool Iterator< Key, Value, Hash, Equal, isConst >::operator==(const Iterator& other) const noexcept
 {
   return current_ == other.current_;
 }

 template < class Key, class Value, class Hash, class Equal, bool isConst >
 bool Iterator< Key, Value, Hash, Equal, isConst >::operator!=(const Iterator& other) const noexcept
 {
   return !(*this == other);
 }
}

#endif
