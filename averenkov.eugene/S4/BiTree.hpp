#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "node.hpp"
#include "iterator.hpp"
#include "constIterator.hpp"
#include <utility>
#include <initializer_list>
#include <stdexcept>

template <typename Key, typename Value, typename Compare = std::less<Key>>
class BinarySearchTree
{
public:
  using Node = Node< Key, Value >;
  using iterator = Iterator< Key, Value, Compare >;
  using const_iterator = ConstIterator< Key, Value, Compare >;

  BinarySearchTree();
  explicit BinarySearchTree(const Compare& cmp);
  BinarySearchTree(const BinarySearchTree& other);
  BinarySearchTree(BinarySearchTree&& other) noexcept;
  ~BinarySearchTree();

  BinarySearchTree& operator=(const BinarySearchTree& other);
  BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;

  Value& at(const Key& key);
  const Value& at(const Key& key) const;
  Value& operator[](const Key& key);
  const Value& operator[](const Key& key) const;

  std::pair<iterator, bool> insert(const std::pair<const Key, Value>& value);
  iterator insert(iterator hint, const std::pair<const Key, Value>& value);
  template <typename InputIt>
  void insert(InputIt first, InputIt last);
  void insert(std::initializer_list<std::pair<const Key, Value>> ilist);

  iterator erase(iterator pos);
  iterator erase(iterator first, iterator last);
  size_t erase(const Key& key);
  void clear();
  void swap(BinarySearchTree& other) noexcept;

  size_t count(const Key& key) const;
  iterator find(const Key& key);
  const_iterator find(const Key& key) const;
  std::pair<iterator, iterator> equal_range(const Key& key);
  std::pair<const_iterator, const_iterator> equal_range(const Key& key) const;
  iterator lower_bound(const Key& key);
  const_iterator lower_bound(const Key& key) const;
  iterator upper_bound(const Key& key);
  const_iterator upper_bound(const Key& key) const;

  bool empty() const;
  size_t size() const;

private:
  Node* root;
  Node* fake_root;
  Compare comp;
  size_t size_;

  Node* copy_tree(Node* node, Node* parent);
  void destroy_tree(Node* node);
  Node* find_node(const Key& key) const;
  Node* find_min(Node* node) const;
  Node* find_max(Node* node) const;
  void transplant(Node* u, Node* v);
};

using Tree = BinarySearchTree< Key, Value, Compare >;

template < typename Key, typename Value, typename Compare >
Tree::BinarySearchTree():
  root(nullptr),
  fake_root(new Node(Key(), Value())),
  comp(Compare()),
  size_(0)
{
  root = fake_root;
}

template < class Key, class Value, class Compare >
Tree::BinarySearchTree(const Compare& cmp):
  root(nullptr),
  fake_root(new Node(Key(), Value())),
  comp(cmp),
  size_(0)
{
  root = fake_root;
}

template < class Key, class Value, class Compare >
Tree::BinarySearchTree(const BinarySearchTree& other):
  root(nullptr),
  fake_root(new Node(Key(), Value())),
  comp(other.comp),
  size_(0)
{
  if (other.root != other.fake_root)
  {
    root = copy_tree(other.root, fake_root);
  }
  size_ = other.size_;
}

template < class Key, class Value, class Compare >
Tree::BinarySearchTree(BinarySearchTree&& other) noexcept:
  root(other.root),
  fake_root(other.fake_root),
  comp(std::move(other.comp)),
  size_(other.size_)
{
  other.root = other.fake_root;
  other.size_ = 0;
}

template < class Key, class Value, class Compare >
Tree::~BinarySearchTree()
{
  clear();
  delete fake_root;
}

template < class Key, class Value, class Compare >
Tree& Tree::operator=(const BinarySearchTree& other)
{
  if (this != &other)
  {
    BinarySearchTree temp(other);
    swap(temp);
  }
  return *this;
}

template < class Key, class Value, class Compare >
Tree& Tree::operator=(BinarySearchTree&& other) noexcept
{
  if (this != &other)
  {
    clear();
    delete fake_root;
    root = other.root;
    fake_root = other.fake_root;
    comp = std::move(other.comp);
    size_ = other.size_;
    other.root = other.fake_root;
    other.size_ = 0;
  }
  return *this;
}

template < class Key, class Value, class Compare >
typename Tree::iterator Tree::begin()
{
  if (!root || root == fake_root)
  {
    return end();
  }
  Node* min_node = root;
  while (min_node->left)
  {
    min_node = min_node->left;
  }
  return iterator(min_node);
}

template < class Key, class Value, class Compare >
typename Tree::iterator Tree::end()
{
  return iterator(fake_root);
}

template < class Key, class Value, class Compare >
typename Tree::const_iterator Tree::begin() const
{
  if (!root || root == fake_root)
  {
    return end();
  }
  Node* min_node = root;
  while (min_node->left)
  {
    min_node = min_node->left;
  }
  return const_iterator(min_node);
}

template < class Key, class Value, class Compare >
typename Tree::const_iterator Tree::end() const
{
  return const_iterator(fake_root);
}

template < class Key, class Value, class Compare >
typename Tree::const_iterator Tree::cbegin() const
{
  return begin();
}

template < class Key, class Value, class Compare >
typename Tree::const_iterator Tree::cend() const
{
  return end();
}

template <typename Key, typename Value, typename Compare>
void Tree::clear()
{
  if (root && root != fake_root)
  {
    destroy_tree(root);
  }
  root = fake_root;
  size_ = 0;
}

template <typename Key, typename Value, typename Compare>
void Tree::destroy_tree(Node* node)
{
  if (node->left && node->left != fake_root)
  {
    destroy_tree(node->left);
  }
  if (node->right && node->right != fake_root)
  {
    destroy_tree(node->right);
  }
  delete node;
}

template <typename Key, typename Value, typename Compare>
typename Tree::Node*
Tree::find_node(const Key& key) const
{
  Node* current = root;
  while (current && current != fake_root)
  {
    if (comp(key, current->data.first))
    {
      current = current->left;
    }
    else if (comp(current->data.first, key))
    {
      current = current->right;
    }
    else
    {
      return current;
    }
  }
  return nullptr;
}

template <typename Key, typename Value, typename Compare>
typename Tree::Node*
Tree::find_min(Node* node) const
{
  while (node->left && node->left != fake_root)
  {
    node = node->left;
  }
  return node;
}

template <typename Key, typename Value, typename Compare>
typename Tree::Node*
Tree::find_max(Node* node) const
{
  while (node->right && node->right != fake_root)
  {
    node = node->right;
  }
  return node;
}

template <typename Key, typename Value, typename Compare>
void Tree::transplant(Node* u, Node* v)
{
  if (u->parent == fake_root)
  {
    root = v;
  }
  else if (u == u->parent->left)
  {
    u->parent->left = v;
  }
  else
  {
    u->parent->right = v;
  }

  if (v && v != fake_root)
  {
    v->parent = u->parent;
  }
}

template <typename Key, typename Value, typename Compare>
size_t Tree::erase(const Key& key)
{
  Node* node = find_node(key);
  if (!node || node == fake_root)
  {
    return 0;
  }

  erase(iterator(node));
  return 1;
}

template <typename Key, typename Value, typename Compare>
void Tree::swap(BiTree& other) noexcept
{
  if (this != &other)
  {
    std::swap(root, other.root);
    std::swap(fake_root, other.fake_root);
    std::swap(comp, other.comp);
    std::swap(size_, other.size_);
  }
}

template <typename Key, typename Value, typename Compare>
typename Tree::iterator
Tree::find(const Key& key)
{
  Node* node = find_node(key);
  if (node && node != fake_root)
  {
    return iterator(node);
  }
  return end();
}

template <typename Key, typename Value, typename Compare>
typename Tree::const_iterator
Tree::find(const Key& key) const
{
  const Node* node = find_node(key);
  if (node && node != fake_root)
  {
    return const_iterator(node);
  }
  return end();
}

template <typename Key, typename Value, typename Compare>
size_t Tree::count(const Key& key) const
{
  return find(key) != end() ? 1 : 0;
}

template <typename Key, typename Value, typename Compare>
std::pair<
  typename Tree::iterator,
  typename Tree::iterator
>
Tree::equal_range(const Key& key)
{
  return {lower_bound(key), upper_bound(key)};
}

template <typename Key, typename Value, typename Compare>
std::pair< typename Tree::const_iterator, typename Tree::const_iterator >
Tree::equal_range(const Key& key) const
{
  return {lower_bound(key), upper_bound(key)};
}

template <typename Key, typename Value, typename Compare>
typename Tree::iterator
Tree::lower_bound(const Key& key)
{
  Node* current = root;
  Node* result = fake_root;

  while (current && current != fake_root)
  {
    if (!comp(current->data.first, key))
    {
      result = current;
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }
  return iterator(result);
}

template <typename Key, typename Value, typename Compare>
typename Tree::const_iterator
Tree::lower_bound(const Key& key) const
{
  const Node* current = root;
  const Node* result = fake_root;

  while (current && current != fake_root)
  {
    if (!comp(current->data.first, key))
    {
      result = current;
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }
  return const_iterator(result);
}

template <typename Key, typename Value, typename Compare>
typename Tree::iterator
Tree::upper_bound(const Key& key)
{
  Node* current = root;
  Node* result = fake_root;

  while (current && current != fake_root)
  {
    if (comp(key, current->data.first))
    {
      result = current;
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }
  return iterator(result);
}

template <typename Key, typename Value, typename Compare>
typename Tree::const_iterator
Tree::upper_bound(const Key& key) const
{
  const Node* current = root;
  const Node* result = fake_root;

  while (current && current != fake_root)
  {
    if (comp(key, current->data.first))
    {
      result = current;
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }
  return const_iterator(result);
}

template <typename Key, typename Value, typename Compare>
typename Tree::iterator
Tree::insert(iterator hint, const PairType& value)
{
  if (hint == end() || comp(value.first, hint->first))
  {
    iterator prev = hint;
    if (prev == begin() || comp((--prev)->first, value.first))
    {
      if (hint.current->left == fake_root)
      {
        Node* new_node = new Node(value.first, value.second, hint.current);
        hint.current->left = new_node;
        size_++;
        return iterator(new_node);
      }
    }
  }
  return insert(value).first;
}

template <typename Key, typename Value, typename Compare>
template <typename InputIt>
void Tree::insert(InputIt first, InputIt last)
{
  for (; first != last; ++first)
  {
    insert(*first);
  }
}

template <typename Key, typename Value, typename Compare>
void Tree::insert(
    std::initializer_list<PairType> ilist)
{
  for (const auto& item : ilist)
  {
    insert(item);
  }
}

template <typename Key, typename Value, typename Compare>
typename Tree::iterator
Tree::erase(iterator first, iterator last)
{
  while (first != last)
  {
    first = erase(first);
  }
  return last;
}

#endif
