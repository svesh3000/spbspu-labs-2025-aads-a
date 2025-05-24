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

    AVLTree< Key, Value, Cmp >& operator=(const AVLTree< Key, Value, Cmp >&);
    AVLTree< Key, Value, Cmp >& operator=(AVLTree< Key, Value, Cmp >&&) noexcept;
    AVLTree< Key, Value, Cmp >& operator=(std::initializer_list< value >);
    Value& operator[](const Key&);
    const Value& operator[](const Key&) const;

    Value& at(const Key&);
    const Value& at(const Key&) const;

    size_t size() const noexcept;
    bool empty() const noexcept;

    Iterator begin() noexcept;
    ConstIterator cbegin() const noexcept;
    Iterator end() noexcept;
    ConstIterator cend() const noexcept;

    std::pair< Iterator, bool > insert(const value&);
    std::pair< Iterator, bool > insert(value&);
    std::pair< Iterator, bool > insert(value&&);
    Iterator insert(ConstIterator, const value&);
    Iterator insert(Iterator, const value&);
    template< typename InputIt >
    void insert(InputIt first, InputIt last);
    void insert(std::initializer_list< value >);

    Iterator erase(Iterator) noexcept;
    Iterator erase(ConstIterator) noexcept;
    size_t erase(const Key&) noexcept;
    Iterator erase(Iterator first, Iterator last) noexcept;
    Iterator erase(ConstIterator first, ConstIterator last) noexcept;

    template< typename... Args >
    std::pair< Iterator, bool > emplace(Args&&...);
    template< typename... Args >
    Iterator emplaceHint(ConstIterator, Args&&...);

    void swap(AVLTree< Key, Value, Cmp >&) noexcept;
    void clear() noexcept;

    Iterator find(const Key&) noexcept;
    ConstIterator find(const Key&) const noexcept;

    size_t count(const Key&) const noexcept;

    Iterator lowerBound(const Key&) noexcept;
    ConstIterator lowerBound(const Key&) const noexcept;
    Iterator upperBound(const Key&) noexcept;
    ConstIterator upperBound(const Key&) const noexcept;

    std::pair< Iterator, Iterator > equalRange(const Key&) noexcept;
    std::pair< ConstIterator, ConstIterator > equalRange(const Key&) const noexcept;

    TreeNode< Key, Value >* getMax() const noexcept;

  private:
    void rotateLeft(Node* node) noexcept;
    void rotateRight(Node* node) noexcept;
    void fixInsert(Node* node) noexcept;
    void fixDelete(Node* node) noexcept;
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
  AVLTree< Key, Value, Cmp >::AVLTree(AVLTree< Key, Value, Cmp >&& tree) noexcept:
    root_(std::exchange(tree.root_, nullptr)),
    size_(std::exchange(tree.size_, 0))
  {}

  template< typename Key, typename Value, typename Cmp >
  template< typename InputIt >
  AVLTree< Key, Value, Cmp >::AVLTree(InputIt first, InputIt last):
    AVLTree()
  {
    for (; first != last; first++)
    {
      insert(*first);
    }
  }

  template< typename Key, typename Value, typename Cmp >
  AVLTree< Key, Value, Cmp >::AVLTree(std::initializer_list< value > il):
    AVLTree(il.begin(), il.end())
  {}

  template< typename Key, typename Value, typename Cmp >
  AVLTree< Key, Value, Cmp >& AVLTree< Key, Value, Cmp >::operator=(const AVLTree< Key, Value, Cmp >& tree)
  {
    AVLTree< Key, Value, Cmp > cpy(tree);
    swap(cpy);
    return *this;
  }

  template< typename Key, typename Value, typename Cmp >
  AVLTree< Key, Value, Cmp >& AVLTree< Key, Value, Cmp >::operator=(AVLTree< Key, Value, Cmp >&& tree) noexcept
  {
    AVLTree< Key, Value, Cmp > temp(std::move(tree));
    swap(temp);
    return *this;
  }

  template< typename Key, typename Value, typename Cmp >
  AVLTree< Key, Value, Cmp >& AVLTree< Key, Value, Cmp >::operator=(std::initializer_list< value > il)
  {
    AVLTree< Key, Value, Cmp > temp(il);
    swap(temp);
    return *this;
  }
