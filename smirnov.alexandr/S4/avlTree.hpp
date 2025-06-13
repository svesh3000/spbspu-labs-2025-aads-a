#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP
#include <cstddef>
#include <stdexcept>
#include "node.hpp"
#include "constIterator.hpp"

namespace smirnov
{
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class AvlTree
  {
  public:
    using NodeType = Node< Key, Value >;
    using const_iterator = ConstIterator< Key, Value, Compare >;
    AvlTree();
    AvlTree(const AvlTree & other);
    AvlTree(AvlTree && other) noexcept;
    ~AvlTree();
    AvlTree & operator=(const AvlTree & other);
    AvlTree & operator=(AvlTree && other) noexcept;
    bool empty() const noexcept;
    size_t size() const noexcept;
    void clear() noexcept;
    void swap(AvlTree& other) noexcept;
    Value & operator[](const Key & key);
    const Value & operator[](const Key & key) const;
    Value & at(const Key & key);
    const Value & at(const Key & key) const;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    const_iterator find(const Key & key) const noexcept;
  private:
    NodeType * root_;
    size_t size_;
    Compare comp_;
    void clearNode(NodeType * node);
    int height(NodeType * node) const;
    void updateHeight(NodeType * node);
    int getBalanceFactor(NodeType * node) const;
    NodeType * rotateLeft(NodeType * node);
    NodeType * rotateRight(NodeType * node);
    NodeType * balance(NodeType * node);
    NodeType * addOrGet(NodeType * node, const Key & key, const Value & value, size_t & size);
    NodeType * findNode(NodeType * node, const Key & key) const;
    NodeType * minNode(Node<Key, Value>* node) const;
  };
}
#endif
