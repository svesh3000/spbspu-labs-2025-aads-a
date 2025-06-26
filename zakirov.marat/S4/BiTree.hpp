#ifndef BITREE_HPP
#define BITREE_HPP
#include <initializer_list>
#include <utility>
#include "BiNode.hpp"
#include "BiIterator.hpp"

namespace zakirov
{
  template < class K, class T >
  class BiTree
  {
  public:
    BiTree();
    BiTree(const BiTree & rhs);
    BiTree(BiTree && rhs) noexcept;
    ~BiTree();
  
    BiTree< K, T > & operator=(const BiTree< K, T > & x);
    BiTree< K, T > & operator=(BiTree< K, T > && x);
    BiTree< K, T > & operator=(initializer_list< T > init_list);

    BiIter< K, T > begin();
    BiIter< K, T > end();
    CBiIter< K, T > cbegin();
    CBiIter< K, T > cend(); 

    T size() const noexcept;
    bool empty() const noexcept;
    max_size

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
    size_t size_;
  };
}

#endif
