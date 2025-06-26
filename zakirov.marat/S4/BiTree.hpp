#ifndef BITREE_HPP
#define BITREE_HPP
#include <initializer_list>
#include <utility>
#include <functional>
#include "BiNode.hpp"
#include "BiIterator.hpp"

namespace zakirov
{
  template< class K, class T, class C >
  class BiIter;

  template< class K, class T, class C >
  class CBiIter;

  template < class K, class T, class C = std::less< K > >
  class BiTree
  {
  public:
    BiTree() noexcept;
    BiTree(const BiTree & rhs);
    BiTree(BiTree && rhs) noexcept;
    ~BiTree();
  
    BiTree< K, T, C > & operator=(const BiTree< K, T, C > & other);
    BiTree< K, T, C > & operator=(BiTree< K, T, C > && other);

    BiIter< K, T, C > begin() noexcept;
    BiIter< K, T, C > end() noexcept;
    CBiIter< K, T, C > cbegin() const noexcept;
    CBiIter< K, T, C > cend() const noexcept; 

    T size() const noexcept;
    bool empty() const noexcept;

    T & operator[](const K & key);
    T & at(const K & key);
    const T & at(const K & key) const;

    std::pair< BiIter, bool > insert(const std::pair< K, T > & value);
    BiIter insert(CBiIter pos, const T & value);
    BiIter erase(BiIter pos);
    BiIter erase(CBiIter pos);
    T erase(const K & key);
    void clear() noexcept;

    BiIter find(const K & key);
    CBiIter find(const K & key) const;
    pair< CBiIter, CBiIter > equal_range (const K & k) const;
    pair< BiIter, BiIter > equal_range (const K & k);
    T count (const K & k) const;
  private:
    BiNode< K, T > * head_;
    C cmp_;
    size_t size_;
  };

  template < class K, class T, class C >
  BiTree< K, T, C >::BiTree() noexcept:
    head_(nullptr),
    size_(0)
  {}

  template < class K, class T, class C >
  BiTree< K, T, C >::BiTree(const BiTree< K, T, C > & other):
    BiTree()
  {
    for (CBiIter< K, T, C > i = other.cbegin(); i != other.cend(); ++i)
    {
      insert(*it);
    }
  }

  template < class K, class T, class C >
  BiTree< K, T, C >::BiTree(BiTree< K, T, C > && other) noexcept:
    head_(other.head_),
    size_(other.size_)
  {
    other.head_ = nullptr;
    other.size_ = nullptr;
  }

  template < class K, class T, class C >
  BiTree< K, T, C >::~BiTree()
  {
    clear();
  }

  template < class K, class T, class C >
  BiTree< K, T, C > & BiTree< K, T, C >::operator=(const BiTree< K, T, C > & other)
  {
    BiTree< K, T, C > temp(other);
    swap(temp);
    return *this;
  }

  template < class K, class T, class C >
  BiTree< K, T, C > & BiTree< K, T, C >::operator=(BiTree< K, T, C > && other)
  {
    BiTree< K, T, C > temp(std::move(other));
    swap(temp);
    return *this;
  }

  template < class K, class T, class C >
  T & BiTree< K, T, C >::operator[](const K & key)
  {
    BiIter< K, T, C > result = insert(std::make_pair(key, T())).first;
    return *result;
  }

  template < class K, class T, class C >
  T & BiTree< K, T, C >::at(const K & key)
  {
    BiIter< K, T, C > iter = find(key);
    if (!iter)
    {
      throw std::out_of_range("No element in tree")
    }

    return *iter;
  }

  template < class K, class T, class C >
  const T & BiTree< K, T, C >::at(const K & key) const
  {
    CBiIter< K, T, C > iter = find(key);
    if (!iter)
    {
      throw std::out_of_range("No element in tree")
    }

    return *iter;
  }

  template < class K, class T, class C >
  BiIter< K, T, C > BiTree< K, T, C >::begin() noexcept
  {
    BiNode< K, T > * first = head_;
    if (!first)
    {
      BiIter< K, T, C > res(first);
      return res;
    }

    while (first->left_)
    {
      first = first->left_;
    }

    BiIter< K, T, C > res(first);
    return res
  }

  template < class K, class T, class C >
  BiIter< K, T, C > BiTree< K, T, C >::end() noexcept
  {
    BiNode< K, T > * last = head_;
    if (!last)
    {
      BiIter< K, T, C > res(last);
      return res;
    }

    while (last->right_)
    {
      last = last->right_;
    }

    BiIter< K, T, C > res(last);
    return res
  }

  template < class K, class T, class C >
  CBiIter< K, T, C > BiTree< K, T, C >::cbegin() const noexcept
  {
    BiNode< K, T > * first = head_;
    if (!first)
    {
      CBiIter< K, T, C > res(first);
      return res;
    }

    while (first->left_)
    {
      first = first->left_;
    }

    CBiIter< K, T, C > res(first);
    return res
  }

  template < class K, class T, class C >
  CBiIter< K, T, C > BiTree< K, T, C >::cend() const noexcept
  {
    BiNode< K, T > * last = head_;
    if (!last)
    {
      CBiIter< K, T, C > res(last);
      return res;
    }

    while (last->right_)
    {
      last = last->right_;
    }

    CBiIter< K, T, C > res(last);
    return res
  }
}

#endif
