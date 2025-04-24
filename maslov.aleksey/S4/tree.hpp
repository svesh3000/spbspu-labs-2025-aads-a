#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"

namespace maslov
{
  template< typename Key, typename T, typename Cmp >
  struct BiTree
  {
    using cIterator = TreeConstIterator< T >;
    using iterator = TreeIterator< T >;

    BiTree();
    ~BiTree();

    BiTree< Key, T, Cmp > & operator=(const BiTree< Key, T, Cmp > & rhs);
    BiTree< Key, T, Cmp > & operator=(BiTree< Key, T, Cmp > && rhs) noexcept;

    iterator begin() noexcept;
    cIterator begin() const noexcept;
    cIterator cbegin() const noexcept;
    iterator end() noexcept;
    cIterator end() const noexcept;
    cIterator cend() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    void clear();
    void swap(BiTree< Key, T, Cmp > & rhs) noexcept;
   private:
    BiTreeNode< Key, T > * node_;
    BiTreeNode< Key, T > * fakeRoot_;
    BiTreeNode< Key, T > * fakeLeaf_;
  };
}
#endif
