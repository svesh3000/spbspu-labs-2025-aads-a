#ifndef BITREE_HPP
#define BITREE_HPP
#include <initializer_list>
#include <utility>
#include <functional>
#include "BiNode.hpp"
#include "BiIterator.hpp"

namespace zakirov
{
  template < class K, class T, class C = std::less< K > >
  class BiTree
  {
  public:
    BiTree() noexcept;
    BiTree(const BiTree & rhs);
    BiTree(BiTree && rhs) noexcept;
    ~BiTree();
  
    BiTree< K, T > & operator=(const BiTree< K, T > & x);
    BiTree< K, T > & operator=(BiTree< K, T > && x);
    BiTree< K, T > & operator=(initializer_list< T > init_list);

    BiIter< K, T > begin() const noexcept;
    BiIter< K, T > end() const noexcept;
    CBiIter< K, T > cbegin() const noexcept;
    CBiIter< K, T > cend() const noexcept; 

    T size() const noexcept;
    bool empty() const noexcept;

    T & operator[](const K & key);
    T & operator[](K && key);
    T & at(const K & key) const;
    T & at(K && key) const;

    std::pair< iterator, bool > insert(const T & value);
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
}

#endif
