#ifndef SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_COMMON_INTERNAL_MAP_NODE_HPP
#define SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_COMMON_INTERNAL_MAP_NODE_HPP

#include <algorithm>
#include <array>
#include <cassert>
#include "algorithm-utils.hpp"

namespace kizhin {
  namespace detail {
    constexpr std::size_t maxValues = 3;
    constexpr std::size_t maxChildren = 4;

    template < typename T >
    struct Node final
    {
      alignas(T) char buffer[maxValues * sizeof(T)];
      T* begin = reinterpret_cast< T* >(buffer);
      T* end = reinterpret_cast< T* >(buffer);
      std::array< Node*, maxChildren > children{};
      Node* parent = nullptr;

      Node() = default;
      Node(const Node&) = delete;
      ~Node() { destroy(begin, end); }
      Node& operator=(const Node&) = delete;
    };

    template < typename T >
    bool isEmpty(const Node< T >*) noexcept;
    template < typename T >
    std::size_t size(const Node< T >*) noexcept;

    template < typename T >
    bool isLeaf(const Node< T >*) noexcept;

    template < typename T >
    bool isLeft(const Node< T >*) noexcept;
    template < typename T >
    bool isMiddle(const Node< T >*) noexcept;
    template < typename T >
    bool isRight(const Node< T >*) noexcept;

    template < typename T >
    const Node< T >* treeMin(const Node< T >*) noexcept;
    template < typename T >
    Node< T >* treeMin(Node< T >*) noexcept;

    template < typename T >
    const Node< T >* treeMax(const Node< T >*) noexcept;
    template < typename T >
    Node< T >* treeMax(Node< T >*) noexcept;

    template < typename T >
    std::tuple< Node< T >*, T* > nextIter(Node< T >*, T*);
    template < typename T >
    std::tuple< Node< T >*, const T* > nextIter(Node< T >*, const T*);

    template < typename T >
    std::tuple< Node< T >*, T* > prevIter(Node< T >*, T*);
    template < typename T >
    std::tuple< Node< T >*, const T* > prevIter(Node< T >*, const T*);

    template < typename T >
    void popBack(Node< T >*) noexcept;
    template < typename T >
    void popFront(Node< T >*) noexcept;
    template < typename T >
    void popMiddle(Node< T >*) noexcept; /* TODO: Implement */

    template < typename T, typename... Args >
    T* emplaceBack(Node< T >*, Args&&...);
    template < typename T, typename... Args >
    T* emplaceFront(Node< T >*, Args&&...);
    template < typename T, typename Cmp, typename... Args >
    T* emplace(Node< T >*, const Cmp&, Args&&...);
  }
}

template < typename T >
bool kizhin::detail::isLeaf(const Node< T >* node) noexcept
{
  assert(node && "Attempt to check is nullptr node a leaf");
  return node->children[0] == nullptr;
}

template < typename T >
bool kizhin::detail::isEmpty(const Node< T >* node) noexcept
{
  assert(node && "Attempt to check is nullptr node empty");
  return node->end == node->begin;
}

template < typename T >
bool kizhin::detail::isLeft(const Node< T >* node) noexcept
{
  assert(node && "Attempt to check nullptr");
  assert(node->parent && "Attempt to check node without parent");
  return node == node->parent->children[0];
}

template < typename T >
bool kizhin::detail::isMiddle(const Node< T >* node) noexcept
{
  assert(node && "Attempt to check nullptr");
  assert(node->parent && "Attempt to check node without parent");
  const bool isParentThree = size(node->parent) == 2;
  return isParentThree && node == node->parent->children[1];
}

template < typename T >
bool kizhin::detail::isRight(const Node< T >* node) noexcept
{
  assert(node && "Attempt to check nullptr");
  assert(node->parent && "Attempt to check node without parent");
  const Node< T >* parent = node->parent;
  const size_t parentSz = size(parent);
  const bool checkTwo = parentSz == 1 && node == parent->children[1];
  const bool checkThree = parentSz == 2 && node == parent->children[2];
  return checkTwo || checkThree;
}

template < typename T >
std::size_t kizhin::detail::size(const Node< T >* node) noexcept
{
  assert(node && "Attempt to check is nullptr node empty");
  return node->end - node->begin;
}

template < typename T >
const kizhin::detail::Node< T >* kizhin::detail::treeMin(const Node< T >* root) noexcept
{
  assert(root && "Root cannot be nullptr");
  while (root->children[0]) {
    root = root->children[0];
  }
  return root;
}

template < typename T >
kizhin::detail::Node< T >* kizhin::detail::treeMin(Node< T >* root) noexcept
{
  const Node< T >* constRoot = root;
  return const_cast< Node< T >* >(treeMin(constRoot));
}

template < typename T >
const kizhin::detail::Node< T >* kizhin::detail::treeMax(const Node< T >* root) noexcept
{
  assert(root && "Root cannot be nullptr");
  while (!isLeaf(root)) {
    root = root->children[size(root)];
  }
  return root;
}

template < typename T >
kizhin::detail::Node< T >* kizhin::detail::treeMax(Node< T >* root) noexcept
{
  const Node< T >* constRoot = root;
  return const_cast< Node< T >* >(treeMax(constRoot));
}

template < typename T >
std::tuple< kizhin::detail::Node< T >*, const T* > kizhin::detail::nextIter(
    Node< T >* node, const T* valuePtr)
{
  assert(node && valuePtr && "Incrementing empty iterator");
  if (!isLeaf(node)) {
    Node< T >* rightSibling = node->children[(valuePtr - node->begin) + 1];
    node = treeMin(rightSibling);
    return std::make_tuple(node, node->begin);
  }
  if (valuePtr + 1 != node->end) {
    return std::make_tuple(node, ++valuePtr);
  }
  while (node->parent) {
    Node< T >* parent = node->parent;
    if (isLeft(node) || (size(parent) == 2 && isMiddle(node))) {
      valuePtr = isLeft(node) ? parent->begin : parent->begin + 1;
      node = parent;
      return std::make_tuple(node, valuePtr);
    }
    node = parent;
  }
  return std::make_tuple(nullptr, nullptr);
}

template < typename T >
std::tuple< kizhin::detail::Node< T >*, T* > kizhin::detail::nextIter(Node< T >* node,
    T* valuePtr)
{
  const T* constValuePtr = valuePtr;
  std::tie(node, constValuePtr) = nextIter(node, constValuePtr);
  return make_tuple(node, const_cast< T* >(constValuePtr));
}

template < typename T >
std::tuple< kizhin::detail::Node< T >*, const T* > kizhin::detail::prevIter(
    Node< T >* node, const T* valuePtr)
{
  assert(node && valuePtr && "Decrementing empty iterator");
  if (!isLeaf(node)) {
    Node< T >* leftSibling = node->children[valuePtr - node->begin];
    node = treeMax(leftSibling);
    return std::make_tuple(node, node->end - 1);
  }
  if (valuePtr != node->begin) {
    return std::make_tuple(node, --valuePtr);
  }
  while (node->parent) {
    Node< T >* parent = node->parent;
    if (!isLeft(node)) {
      const bool useBegin = !(size(parent) == 1 || isMiddle(node));
      return std::make_tuple(parent, parent->begin + useBegin);
    }
    node = parent;
  }
  return std::make_tuple(nullptr, nullptr);
}

template < typename T >
std::tuple< kizhin::detail::Node< T >*, T* > kizhin::detail::prevIter(Node< T >* node,
    T* valuePtr)
{
  const T* constValuePtr = valuePtr;
  std::tie(node, constValuePtr) = prevIter(node, constValuePtr);
  return make_tuple(node, const_cast< T* >(constValuePtr));
}

template < typename T >
void kizhin::detail::popBack(Node< T >* node) noexcept
{
  assert(node && "Attempt to pop from nullptr node");
  assert(isEmpty(node) && "Attempt to pop from empty node");
  --node->end;
  node->end->~T();
}

template < typename T >
void kizhin::detail::popFront(Node< T >* node) noexcept
{
  assert(node && "Attempt to pop from nullptr node");
  assert(isEmpty(node) && "Attempt to pop from empty node");
  node->begin->~T();
  --node->begin;
}

template < typename T, typename... Args >
T* kizhin::detail::emplaceBack(Node< T >* node, Args&&... args)
{
  /* NOTE: Basic safety */
  assert(node && "Attempt to emplace in nullptr node");
  assert(size(node) < maxValues && "Node already filled");
  const T* const realEnd = reinterpret_cast< T* >(node->buffer) + maxValues;
  if (node->end == realEnd) {
    std::move(node->begin, node->end, node->begin - 1);
    --node->begin;
    --node->end;
  }
  T* result = new (node->end) T(std::forward< Args >(args)...);
  ++node->end;
  return result;
}

template < typename T, typename... Args >
T* kizhin::detail::emplaceFront(Node< T >* node, Args&&... args)
{
  /* NOTE: Basic safety */
  assert(node && "Attempt to emplace in nullptr node");
  assert(size(node) < maxValues && "Node already filled");
  const T* const realBegin = reinterpret_cast< T* >(node->buffer);
  if (node->begin == realBegin) {
    std::move_backward(node->begin, node->end, node->begin + 1);
    ++node->begin;
    ++node->end;
  }
  T* result = new (node->begin - 1) T(std::forward< Args >(args)...);
  --node->begin;
  return result;
}

template < typename T, typename Cmp, typename... Args >
T* kizhin::detail::emplace(Node< T >* node, const Cmp& cmp, Args&&... args)
{
  /*
   * TODO: Cannot use std::sort & std::move with const Key
   * Create a new node with ordered values, then swap with old node in the tree
   */
  assert(node && "Attempt to emplace in nullptr node");
  assert(size(node) < maxValues && "Node already filled");
  T* result = emplaceBack(node, std::forward< Args >(args)...);
  std::sort(node->begin, node->end, cmp);
  return result;
}

#endif

