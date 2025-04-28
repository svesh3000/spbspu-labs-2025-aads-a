#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "node.hpp"
#include "iterator.hpp"
#include "constIterator.hpp"
#include <utility>
#include <initializer_list>
#include <stdexcept>
#include <stack>

template < class Key, class Value, class Compare = std::less< Key > >
class Tree
{
public:
  using NodeType = Node< Key, Value >;
  using iterator = Iterator< Key, Value, Compare >;
  using const_iterator = ConstIterator< Key, Value, Compare >;

  Tree();
  explicit Tree(const Compare& cmp);
  Tree(const Tree& other);
  Tree(Tree&& other) noexcept;
  Tree(std::initializer_list< std::pair< const Key, Value > > init, const Compare& cmp);
  template< class InputIt >
  Tree(InputIt first, InputIt last, const Compare& cmp);
  ~Tree();

  Tree& operator=(const Tree& other);
  Tree& operator=(Tree&& other) noexcept;

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

  std::pair< iterator, bool > insert(const std::pair< const Key, Value >& value);
  template < class InputIt >
  void insert(InputIt first, InputIt last);
  void insert(std::initializer_list< std::pair< const Key, Value > > ilist);

  iterator erase(iterator pos);
  iterator erase(iterator first, iterator last);
  size_t erase(const Key& key);
  void clear();
  void swap(Tree& other) noexcept;

  size_t count(const Key& key) const;
  iterator find(const Key& key);
  const_iterator find(const Key& key) const;
  std::pair< iterator, iterator > equal_range(const Key& key);
  std::pair< const_iterator, const_iterator > equal_range(const Key& key) const;
  iterator lower_bound(const Key& key);
  const_iterator lower_bound(const Key& key) const;
  iterator upper_bound(const Key& key);
  const_iterator upper_bound(const Key& key) const;

  bool empty() const;
  size_t size() const;

private:
  NodeType* root;
  NodeType* fake_root;
  Compare comp;
  size_t size_;

  NodeType* copy_tree(NodeType* node, NodeType* parent);
  void destroy_tree(NodeType* NodeType);
  NodeType* find_NodeType(const Key& key) const;
  NodeType* find_min(NodeType* NodeType) const;
  NodeType* find_max(NodeType* NodeType) const;
  void transplant(NodeType* u, NodeType* v);

  void update_height(NodeType* NodeType);
  int balance_factor(NodeType* NodeType) const;
  NodeType* rotate_right(NodeType* y);
  NodeType* rotate_left(NodeType* x);
  NodeType* balance(NodeType* NodeType);
  NodeType* rebalance_path(std::stack< NodeType* >& path);
};

template< class Key, class Value >
using NodeType = Node< Key, Value >;

template < class Key, class Value, class Compare >
Tree< Key, Value, Compare >::Tree():
  root(nullptr),
  fake_root(new NodeType(Key(), Value(), nullptr)),
  comp(Compare()),
  size_(0)
{
  root = fake_root;
}

template < class Key, class Value, class Compare >
Tree< Key, Value, Compare >::Tree(const Compare& cmp):
  root(nullptr),
  fake_root(new NodeType(Key(), Value(), nullptr)),
  comp(cmp),
  size_(0)
{
  root = fake_root;
}

template < class Key, class Value, class Compare >
Tree< Key, Value, Compare >::Tree(const Tree& other):
  root(nullptr),
  fake_root(new NodeType(Key(), Value(), nullptr)),
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
Tree< Key, Value, Compare >::Tree(Tree&& other) noexcept:
  root(other.root),
  fake_root(other.fake_root),
  comp(std::move(other.comp)),
  size_(other.size_)
{
  other.root = other.fake_root;
  other.size_ = 0;
}

template <class Key, class Value, class Compare >
Tree< Key, Value, Compare >::Tree(std::initializer_list< std::pair< const Key, Value > > init, const Compare& cmp):
  root(nullptr),
  fake_root(new NodeType(Key(), Value())),
  comp(cmp),
  size_(0)
{
  root = fake_root;
  for (const auto& item : init)
  {
    insert(item);
  }
}

template < class Key, class Value, class Compare >
template < class InputIt >
Tree< Key, Value, Compare >::Tree( InputIt first, InputIt last, const Compare& cmp):
  root(nullptr),
  fake_root(new NodeType(Key(), Value())),
  comp(cmp),
  size_(0)
{
  root = fake_root;
  for (; first != last; ++first)
  {
    insert(*first);
  }
}

template < class Key, class Value, class Compare >
Tree< Key, Value, Compare >::~Tree()
{
  clear();
  if (fake_root) delete fake_root;
}

template < class Key, class Value, class Compare >
void Tree< Key, Value, Compare >::update_height(NodeType* NodeType)
{
  if (!NodeType || NodeType == fake_root) return;
  int left_height = NodeType->left ? NodeType->left->height : 0;
  int right_height = NodeType->right ? NodeType->right->height : 0;
  NodeType->height = 1 + std::max(left_height, right_height);
}

template < class Key, class Value, class Compare >
int Tree< Key, Value, Compare >::balance_factor(NodeType* NodeType) const
{
  if (!NodeType || NodeType == fake_root) return 0;
  int left_height = NodeType->left ? NodeType->left->height : 0;
  int right_height = NodeType->right ? NodeType->right->height : 0;
  return left_height - right_height;
}

template < class Key, class Value, class Compare >
class Tree< Key, Value, Compare >::NodeType*
Tree< Key, Value, Compare >::rotate_right(NodeType* y)
{
  if (!y || y == fake_root) return y;

  NodeType* x = y->left;
  y->left = x->right;

  if (x->right && x->right != fake_root)
  {
    x->right->parent = y;
  }

  x->right = y;
  x->parent = y->parent;
  y->parent = x;

  update_height(y);
  update_height(x);

  return x;
}

template < class Key, class Value, class Compare >
class Tree< Key, Value, Compare >::NodeType*
Tree< Key, Value, Compare >::rotate_left(NodeType* x)
{
  if (!x || x == fake_root) return x;

  NodeType* y = x->right;
  x->right = y->left;

  if (y->left && y->left != fake_root)
  {
    y->left->parent = x;
  }

  y->left = x;
  y->parent = x->parent;
  x->parent = y;

  update_height(x);
  update_height(y);

  return y;
}

template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::NodeType*
Tree< Key, Value, Compare >::balance(NodeType* NodeType)
{
  if (!NodeType || NodeType == fake_root) return NodeType;

  update_height(NodeType);
  int bf = balance_factor(NodeType);

  if (bf == 2)
  {
    if (balance_factor(NodeType->left) < 0)
    {
      NodeType->left = rotate_left(NodeType->left);
    }
    return rotate_right(NodeType);
  }

  if (bf == -2)
  {
    if (balance_factor(NodeType->right) > 0)
    {
      NodeType->right = rotate_right(NodeType->right);
    }
    return rotate_left(NodeType);
  }

  return NodeType;
}

template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::NodeType*
Tree< Key, Value, Compare >::rebalance_path(std::stack< NodeType* >& path)
{
  NodeType* new_root = nullptr;
  while (!path.empty())
  {
    NodeType* node = path.top();
    path.pop();

    NodeType* balanced_node = balance(node);

    if (!path.empty())
    {
      NodeType* parent_node = path.top();
      if (parent_node->left == node)
      {
        parent_node->left = balanced_node;
      }
      else
      {
        parent_node->right = balanced_node;
      }
    }
    else
    {
      new_root = balanced_node;
    }
  }
  return new_root;
}

template < class Key, class Value, class Compare >
Tree< Key, Value, Compare >& Tree< Key, Value, Compare >::operator=(const Tree& other)
{
  if (this != &other)
  {
    Tree temp(other);
    swap(temp);
  }
  return *this;
}

template < class Key, class Value, class Compare >
Tree< Key, Value, Compare >& Tree< Key, Value, Compare >::operator=(Tree&& other) noexcept
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
bool Tree< Key, Value, Compare >::empty() const
{
  return size_ == 0;
}

template < class Key, class Value, class Compare >
size_t Tree< Key, Value, Compare >::size() const
{
  return size_;
}

template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::iterator Tree< Key, Value, Compare >::begin()
{
  if (!root || root == fake_root)
  {
    return end();
  }
  NodeType* min_NodeType = root;
  while (min_NodeType->left)
  {
    min_NodeType = min_NodeType->left;
  }
  return iterator(min_NodeType);
}

template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::iterator Tree< Key, Value, Compare >::end()
{
  return iterator(fake_root);
}

template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::const_iterator Tree< Key, Value, Compare >::begin() const
{
  if (!root || root == fake_root)
  {
    return end();
  }
  NodeType* min_NodeType = root;
  while (min_NodeType->left)
  {
    min_NodeType = min_NodeType->left;
  }
  return const_iterator(min_NodeType);
}

template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::const_iterator Tree< Key, Value, Compare >::end() const
{
  return const_iterator(fake_root);
}

template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::const_iterator Tree< Key, Value, Compare >::cbegin() const
{
  return begin();
}

template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::const_iterator Tree< Key, Value, Compare >::cend() const
{
  return end();
}

template < class Key, class Value, class Compare >
void Tree< Key, Value, Compare >::clear()
{
  if (root)
  {
    destroy_tree(root);
  }
  root = nullptr;
  size_ = 0;
}

template < class Key, class Value, class Compare >
void Tree< Key, Value, Compare >::destroy_tree(NodeType* node)
{
 if (node)
  {
    destroy_tree(node->left);
    destroy_tree(node->right);
    delete node;
  }
}

template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::NodeType*
Tree< Key, Value, Compare >::find_NodeType(const Key& key) const
{
  NodeType* current = root;
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

template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::NodeType*
Tree< Key, Value, Compare >::find_min(NodeType* NodeType) const
{
  while (NodeType->left && NodeType->left != fake_root)
  {
    NodeType = NodeType->left;
  }
  return NodeType;
}

template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::NodeType*
Tree< Key, Value, Compare >::find_max(NodeType* NodeType) const
{
  while (NodeType->right && NodeType->right != fake_root)
  {
    NodeType = NodeType->right;
  }
  return NodeType;
}

template < class Key, class Value, class Compare >
void Tree< Key, Value, Compare >::transplant(NodeType* u, NodeType* v)
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


template < class Key, class Value, class Compare >
void Tree< Key, Value, Compare >::swap(Tree< Key, Value, Compare >& other) noexcept
{
  if (this != &other)
  {
    std::swap(root, other.root);
    std::swap(fake_root, other.fake_root);
    std::swap(comp, other.comp);
    std::swap(size_, other.size_);
  }
}

template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::iterator
Tree< Key, Value, Compare >::find(const Key& key)
{
  NodeType* NodeType = find_NodeType(key);
  if (NodeType && NodeType != fake_root)
  {
    return iterator(NodeType);
  }
  return end();
}

template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::const_iterator
Tree< Key, Value, Compare >::find(const Key& key) const
{
  const NodeType* NodeType = find_NodeType(key);
  if (NodeType && NodeType != fake_root)
  {
    return const_iterator(NodeType);
  }
  return end();
}

template < class Key, class Value, class Compare >
size_t Tree< Key, Value, Compare >::count(const Key& key) const
{
  return find(key) != end() ? 1 : 0;
}

template < class Key, class Value, class Compare >
std::pair< typename Tree< Key, Value, Compare >::iterator, typename Tree< Key, Value, Compare >::iterator >
Tree< Key, Value, Compare >::equal_range(const Key& key)
{
  return { lower_bound(key), upper_bound(key) };
}

template < class Key, class Value, class Compare >
std::pair< typename Tree< Key, Value, Compare >::const_iterator, typename Tree< Key, Value, Compare >::const_iterator >
Tree< Key, Value, Compare >::equal_range(const Key& key) const
{
  return { lower_bound(key), upper_bound(key) };
}

template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::iterator
Tree< Key, Value, Compare >::lower_bound(const Key& key)
{
  NodeType* current = root;
  NodeType* result = fake_root;

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

template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::const_iterator
Tree< Key, Value, Compare >::lower_bound(const Key& key) const
{
  const NodeType* current = root;
  const NodeType* result = fake_root;

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

template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::iterator
Tree< Key, Value, Compare >::upper_bound(const Key& key)
{
  NodeType* current = root;
  NodeType* result = fake_root;

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

template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::const_iterator
Tree< Key, Value, Compare >::upper_bound(const Key& key) const
{
  const NodeType* current = root;
  const NodeType* result = fake_root;

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

template < class Key, class Value, class Compare >
std::pair< typename Tree< Key, Value, Compare >::iterator, bool >
Tree< Key, Value, Compare >::insert(const std::pair< const Key, Value >& value)
{
  if (root == fake_root)
  {
    root = new NodeType(value.first, value.second, fake_root);
    size_ = 1;
    return { iterator(root), true };
  }

  std::stack<NodeType*> path;
  NodeType* current = root;
  NodeType* parent = fake_root;

  while (current && current != fake_root)
  {
    parent = current;
    path.push(current);

    if (comp(value.first, current->data.first))
    {
      current = current->left;
    }
    else if (comp(current->data.first, value.first))
    {
      current = current->right;
    }
    else
    {
      return { iterator(current), false };
    }
  }
  NodeType* new_NodeType = new NodeType(value.first, value.second, parent);
  if (comp(value.first, parent->data.first))
  {
    parent->left = new_NodeType;
  }
  else
  {
    parent->right = new_NodeType;
  }
  path.push(new_NodeType);
  root = rebalance_path(path) ? : root;
  size_++;
  return { iterator(new_NodeType), true };
}



template < class Key, class Value, class Compare >
template <typename InputIt>
void Tree< Key, Value, Compare >::insert(InputIt first, InputIt last)
{
  for (; first != last; ++first)
  {
    insert(*first);
  }
}

template < class Key, class Value, class Compare >
void Tree< Key, Value, Compare >::insert(std::initializer_list< std::pair< const Key, Value > > ilist)
{
  for (const auto& item : ilist)
  {
    insert(item);
  }
}
template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::iterator
Tree< Key, Value, Compare >::erase(iterator pos)
{
  if (pos == end())
  {
    return end();
  }

  NodeType* node = pos.current;
  std::stack< NodeType* > path;

  NodeType* current = node->parent;
  while (current && current != fake_root)
  {
    path.push(current);
    current = current->parent;
  }

  NodeType* replacement = nullptr;

  if (node->left == nullptr || node->left == fake_root)
  {
    transplant(node, node->right);
    replacement = node->right;
  }
  else if (node->right == nullptr || node->right == fake_root)
  {
    transplant(node, node->left);
    replacement = node->left;
  }
  else
  {
    NodeType* successor = find_min(node->right);
    path.push(successor);

    if (successor->parent != node)
    {
      path.push(successor->parent);
      transplant(successor, successor->right);
      successor->right = node->right;
      successor->right->parent = successor;
    }

    transplant(node, successor);
    successor->left = node->left;
    successor->left->parent = successor;
    replacement = successor;
  }

  if (!path.empty())
  {
    root = rebalance_path(path) ? : root;
  }
  else if (root == node)
  {
    root = replacement == fake_root ? nullptr : replacement;
  }

  delete node;
  size_--;

  if (replacement && replacement != fake_root)
  {
    return iterator(replacement);
  }
  return end();
}

template < class Key, class Value, class Compare >
size_t Tree< Key, Value, Compare >::erase(const Key& key)
{
  auto it = find(key);
  if (it != end())
  {
    erase(it);
    return 1;
  }
  return 0;
}

template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::iterator
Tree< Key, Value, Compare >::erase(iterator first, iterator last)
{
  while (first != last)
  {
    first = erase(first);
  }
  return last;
}

template < class Key, class Value, class Compare >
Value& Tree< Key, Value, Compare >::at(const Key& key)
{
  NodeType* NodeType = find_NodeType(key);
  if (!NodeType || NodeType == fake_root)
  {
    throw std::out_of_range("not found");
  }
  return NodeType->data.second;
}

template < class Key, class Value, class Compare >
const Value& Tree< Key, Value, Compare >::at(const Key& key) const
{
  const NodeType* NodeType = find_NodeType(key);
  if (!NodeType || NodeType == fake_root)
  {
    throw std::out_of_range("not found");
  }
  return NodeType->data.second;
}

template < class Key, class Value, class Compare >
Value& Tree< Key, Value, Compare >::operator[](const Key& key)
{
  auto result = insert(std::make_pair(key, Value()));
  return result.first->second;
}

template < class Key, class Value, class Compare >
const Value& Tree< Key, Value, Compare >::operator[](const Key& key) const
{
  return at(key);
}

template < class Key, class Value, class Compare >
typename Tree< Key, Value, Compare >::NodeType*
Tree< Key, Value, Compare >::copy_tree(NodeType* node, NodeType* parent)
{
  if (!node || node == fake_root)
  {
    return nullptr;
  }

  NodeType* new_node = new NodeType(node->data.first, node->data.second, parent);
  new_node->left = copy_tree(node->left, new_node);
  new_node->right = copy_tree(node->right, new_node);
  new_node->height = node->height;
  return balance(new_node);
}

#endif
