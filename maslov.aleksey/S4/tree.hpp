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
    BiTreeNode< Key, T > * fakeRoot_;
    BiTreeNode< Key, T > * fakeLeaf_;
    size_t size_;
    void clearTree(BiTreeNode< Key, T > * root);
  };

  template< typename Key, typename T, typename Cmp >
  BiTree< Key, T, Cmp >::BiTree():
    fakeRoot_(new BiTreeNode< Key, T >{std::pair< const Key, Value >(), nullptr, nullptr, nullptr}),
    fakeLeaf_(new BiTreeNode< Key, T >{std::pair< const Key, Value >(), nullptr, nullptr, nullptr})
    size_(0)
  {
    fakeLeaf_->left = fakeLeaf_;
    fakeLeaf_->right = fakeLeaf_;
    fakeLeaf_->parent = fakeRoot_;
    fakeRoot_->left = fakeLeaf_;
    fakeRoot_->parent = fakeLeaf_;
  }

  template< typename Key, typename T, typename Cmp >
  BiTree< Key, T, Cmp >::~BiTree()
  {
    clear();
    delete fakeRoot_;
    delete fakeLeaf_;
  }

  template< typename Key, typename T, typename Cmp >
  void BiTree< Key, T, Cmp >::clear()
  {
    clearTree(fakeRoot_->left);
    clearTree(fakeRoot_->right);
    fakeRoot_->left = fakeLeaf_;
    fakeRoot_->right = fakeLeaf_;
    size_ = 0;
  }

  template< typename Key, typename T, typename Cmp >
  void BiTree< Key, T, Cmp >::clearTree(BiTreeNode< Key, T > * root)
  {
    if (root == fakeLeaf_)
    {
      return;
    }
    clearTree(node->left);
    clearTree(node->right);
    delete root;
  }
}
#endif
