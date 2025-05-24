#ifndef TREE_HPP
#define TREE_HPP
#include <cassert>
#include <initializer_list>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include "iterator.hpp"
#include "treeNode.hpp"

namespace brevnov
{
  template< typename Key, typename Value, typename Cmp = std::less< Key > >
  class AVLTree
  {
  public:
    using value = std::pair< Key, Value >;
    using Iterator = brevnov::Iterator< Key, Value, Cmp, false >;
    using ConstIterator = brevnov::Iterator< Key, Value, Cmp, true >;
    using IteratorPair = std::pair< Iterator, Iterator >;
    using ConstIteratorPair = std::pair< ConstIterator, ConstIterator >;
    using Node = TreeNode< Key, Value>;

    AVLTree();
    AVLTree(const AVLTree< Key, Value, Cmp >&);
    AVLTree(AVLTree< Key, Value, Cmp >&&) noexcept;
    AVLTree(std::initializer_list< value >);
    template< typename InputIt >
    AVLTree(InputIt first, InputIt last);
    ~AVLTree();



  private:

    Node * root_;
    Cmp cmp_;
    size_t size_;
  };

  template< typename Key, typename Value, typename Cmp >
  AVLTree< Key, Value, Cmp >::AVLTree():
    root_(nullptr),
    size_(0)
  {}

  template< typename Key, typename Value, typename Cmp >
  AVLTree< Key, Value, Cmp >::AVLTree(const AVLTree< Key, Value, Cmp >& tree):
    AVLTree()
  {
    for (ConstIterator it = tree.cbegin(); it != tree.cend(); ++it)
    {
      insert(*it);
    }
  }

  template< typename Key, typename Value, typename Cmp >
  RBTree< Key, Value, Cmp >::RBTree(RBTree< Key, Value, Cmp >&& tree) noexcept:
    root_(std::exchange(tree.root_, nullptr)),
    size_(std::exchange(tree.size_, 0))
  {}
