#ifndef TREE_2_3_HPP
#define TREE_2_3_HPP
#include <cstddef>
#include <cassert>
#include <functional>
#include <iostream>
#include "tree-iterators.hpp"
#include "tree-iterator-impl.hpp"
#include "tree-const-iterator-impl.hpp"

namespace alymova
{
  template< class Key, class Value, class Comparator >
  class TwoThreeTree
  {
  public:
    using Tree = TwoThreeTree< Key, Value, Comparator >;
    using Iterator = TTTIterator< Key, Value, Comparator >;
    using ConstIterator = TTTConstIterator< Key, Value, Comparator >;
    using Node = typename detail::TTTNode< Key, Value, Comparator >;
    using NodeType = typename Node::NodeType;
    using NodePoint = typename detail::NodePoint;
    using T = std::pair< Key, Value >;

    TwoThreeTree();
    TwoThreeTree(const Tree& other);
    TwoThreeTree(Tree&& other) noexcept;
    template< typename InputIterator>
    TwoThreeTree(InputIterator first, InputIterator last);
    TwoThreeTree(std::initializer_list< T > il);
    ~TwoThreeTree() noexcept;

    Tree& operator=(const Tree& other);
    Tree& operator=(Tree&& other) noexcept;

    Iterator begin();
    ConstIterator begin() const noexcept;
    ConstIterator cbegin() const noexcept;
    Iterator end();
    ConstIterator end() const noexcept;
    ConstIterator cend() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    std::pair< Iterator, bool > insert(const T& value);
    std::pair< Iterator, bool > insert(T&& value);
    template < class InputIterator >
    void insert(InputIterator first, InputIterator last);
    void insert(std::initializer_list< T > il);
    Iterator insert(Iterator hint, const T& value);
    Iterator insert(ConstIterator hint, const T& value);

    template< class... Args >
    std::pair< Iterator, bool > emplace(Args&&... args);
    template< class... Args >
    Iterator emplace_hint(ConstIterator hint, Args&&... args);

    size_t erase(const Key& key);
    Iterator erase(Iterator pos);
    Iterator erase(ConstIterator pos);
    Iterator erase(Iterator first, Iterator last);
    Iterator erase(ConstIterator first, ConstIterator last);

    void swap(Tree& other);
    void clear() noexcept;

    size_t count(const Key& key) const;
    Iterator find(const Key& key);
    ConstIterator find(const Key& key) const;
    std::pair< Iterator, Iterator > equal_range(const Key& key);
    std::pair< ConstIterator, ConstIterator > equal_range(const Key& key) const;
    Iterator lower_bound(const Key& key);
    ConstIterator lower_bound(const Key& key) const;
    Iterator upper_bound(const Key& key);
    ConstIterator upper_bound(const Key& key) const;

  private:
    size_t size_;
    Node* fake_;
    Node* root_;
    Comparator cmp_;

    void clear(Node* node) noexcept;
    void move_fake() noexcept;
    void split(Node* node);
    Node* find_to_insert(const Key& key) const;
    Node* find_to_insert(ConstIterator hint) const;
    bool check_hint(ConstIterator hint, const Key& key);
    Iterator find_to_erase(Iterator pos);
    bool have_triple_neighbor(Iterator pos);
    void distribute(Iterator pos);
    void merge(Iterator pos);

    bool is_balanced();
    size_t find_height(Node* node);
  };

  template< class Key, class Value, class Comparator >
  TwoThreeTree< Key, Value, Comparator >::TwoThreeTree():
    size_(0),
    fake_(new Node{}),
    root_(fake_)
  {
    fake_->type = NodeType::Fake;
  }

  template< class Key, class Value, class Comparator >
  TwoThreeTree< Key, Value, Comparator >::TwoThreeTree(const Tree& other):
    Tree(other.begin(), other.end())
  {}

  template< class Key, class Value, class Comparator >
  TwoThreeTree< Key, Value, Comparator >::TwoThreeTree(Tree&& other) noexcept:
    size_(std::exchange(other.size_, 0)),
    fake_(std::exchange(other.fake_, nullptr)),
    root_(std::exchange(other.root_, nullptr))
  {}

  template< class Key, class Value, class Comparator >
  template< class InputIterator >
  TwoThreeTree< Key, Value, Comparator >::TwoThreeTree(InputIterator first, InputIterator last):
    Tree()
  {
    for (auto it = first; it != last; it++)
    {
      emplace(*it);
    }
  }

  template< class Key, class Value, class Comparator >
  TwoThreeTree< Key, Value, Comparator >::TwoThreeTree(std::initializer_list< T > il):
    Tree(il.begin(), il.end())
  {}

  template< class Key, class Value, class Comparator >
  TwoThreeTree< Key, Value, Comparator >::~TwoThreeTree() noexcept
  {
    if (size_)
    {
      clear(root_);
    }
    delete fake_;
  }

  template< class Key, class Value, class Comparator >
  TwoThreeTree< Key, Value, Comparator >& TwoThreeTree< Key, Value, Comparator >::operator=(const Tree& other)
  {
    assert(this != std::addressof(other) && "Assigning a map to itself");
    Tree copy(other);
    swap(copy);
    return *this;
  }

  template< class Key, class Value, class Comparator >
  TwoThreeTree< Key, Value, Comparator >& TwoThreeTree< Key, Value, Comparator >::operator=(Tree&& other) noexcept
  {
    assert(this != std::addressof(other) && "Assigning a map to itself");
    Tree moved(std::move(other));
    swap(moved);
    return *this;
  }

  template< class Key, class Value, class Comparator >
  TTTIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::begin()
  {
    return Iterator(cbegin());
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::begin() const noexcept
  {
    return cbegin();
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::cbegin() const noexcept
  {
    if (size_ == 0)
    {
      return cend();
    }
    Node* tmp = root_;
    while (tmp->left)
    {
      tmp = tmp->left;
    }
    return ConstIterator(tmp, NodePoint::First);
  }

  template< class Key, class Value, class Comparator >
  TTTIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::end()
  {
    return Iterator(cend());
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::end() const noexcept
  {
    return cend();
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::cend() const noexcept
  {
    return ConstIterator(fake_, NodePoint::Fake);
  }

  template< class Key, class Value, class Comparator >
  size_t TwoThreeTree< Key, Value, Comparator >::size() const noexcept
  {
    return size_;
  }

  template< class Key, class Value, class Comparator >
  bool TwoThreeTree< Key, Value, Comparator >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< class Key, class Value, class Comparator >
  std::pair< TTTIterator< Key, Value, Comparator >, bool >
    TwoThreeTree< Key, Value, Comparator >::insert(const T& value)
  {
    return emplace(value);
  }

  template< class Key, class Value, class Comparator >
  std::pair< TTTIterator< Key, Value, Comparator >, bool >
    TwoThreeTree< Key, Value, Comparator >::insert(T&& value)
  {
    return emplace(std::forward< T >(value));
  }

  template< class Key, class Value, class Comparator >
  template< class InputIterator >
  void TwoThreeTree< Key, Value, Comparator >::insert(InputIterator first, InputIterator last)
  {
    for (auto it = first; it != last; it++)
    {
      insert(*it);
    }
  }

  template< class Key, class Value, class Comparator >
  void TwoThreeTree< Key, Value, Comparator >::insert(std::initializer_list< T > il)
  {
    insert(il.begin(), il.end());
  }

  template< class Key, class Value, class Comparator >
  TTTIterator< Key, Value, Comparator >
    TwoThreeTree< Key, Value, Comparator >::insert(Iterator hint, const T& value)
  {
    ConstIterator const_hint(hint);
    return emplace_hint(const_hint, value);
  }

  template< class Key, class Value, class Comparator >
  TTTIterator< Key, Value, Comparator >
    TwoThreeTree< Key, Value, Comparator >::insert(ConstIterator hint, const T& value)
  {
    return emplace_hint(hint, value);
  }

  template< class Key, class Value, class Comparator >
  template <class... Args >
  std::pair< TTTIterator< Key, Value, Comparator >, bool >
    TwoThreeTree< Key, Value, Comparator >::emplace(Args&&... args)
  {
    std::pair< Key, Value > value(std::forward< Args >(args)...);
    size_t size_before = size_;
    ConstIterator hint = lower_bound(value.first);
    Iterator it = emplace_hint(hint, value);
    if (size_before == size())
    {
      return {it, false};
    }
    return {it, true};
  }

  template< class Key, class Value, class Comparator >
  template <class... Args >
  TTTIterator< Key, Value, Comparator >
    TwoThreeTree< Key, Value, Comparator >::emplace_hint(ConstIterator hint, Args&&... args)
  {
    std::pair< Key, Value > value(std::forward< Args >(args)...);
    Iterator it_value = find(value.first);
    if (it_value != end())
    {
      return it_value;
    }
    Node* to_insert = find_to_insert(hint);
    if (!check_hint(hint, value.first))
    {
      to_insert = find_to_insert(value.first);
    }
    if (size_ == 0)
    {
      root_ = new Node();
      to_insert = root_;
    }
    to_insert->insert(value);
    split(to_insert);
    move_fake();
    size_++;
    return find(value.first);
  }

  template< class Key, class Value, class Comparator >
  size_t TwoThreeTree< Key, Value, Comparator >::erase(const Key& key)
  {
    Iterator it = find(key);
    if (it == end())
    {
      return 0;
    }
    erase(it);
    return 1;
  }

  template< class Key, class Value, class Comparator >
  TTTIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::erase(Iterator pos)
  {
    assert(!empty() && "Removing from empty map");
    if (pos == end())
    {
      return end();
    }
    if (size_ == 1)
    {
      delete pos.node_;
      size_--;
      return end();
    }
    Iterator pos_next = ++pos;
    --pos;
    Iterator pos_instead = find_to_erase(pos);
    std::swap(*pos, *pos_instead);
    pos_instead.node_->remove(pos_instead.point_);
    if (pos_instead.node_->type == NodeType::Double)
    {
      size_--;
      return pos_next;
    }
    else if (have_triple_neighbor(pos_instead))
    {
      distribute(pos_instead);
    }
    else
    {
      merge(pos_instead);
    }
    size_--;
    return pos_next;
  }

  template< class Key, class Value, class Comparator >
  void TwoThreeTree< Key, Value, Comparator >::swap(Tree& other)
  {
    std::swap(size_, other.size_);
    std::swap(fake_, other.fake_);
    std::swap(root_, other.root_);
    std::swap(cmp_, other.cmp_);
  }

  template< class Key, class Value, class Comparator >
  void TwoThreeTree< Key, Value, Comparator >::clear() noexcept
  {
    clear(root_);
  }

  template< class Key, class Value, class Comparator >
  size_t TwoThreeTree< Key, Value, Comparator >::count(const Key& key) const
  {
    if (find(key) != end())
    {
      return 1;
    }
    return 0;
  }

  template< class Key, class Value, class Comparator >
  TTTIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::find(const Key& key)
  {
    ConstIterator tmp = static_cast< const Tree& >(*this).find(key);
    return Iterator(tmp);
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::find(const Key& key) const
  {
    for (ConstIterator it = cbegin(); it != cend(); it++)
    {
      if (!cmp_(key, it->first) && !cmp_(it->first, key))
      {
        return it;
      }
    }
    return cend();
  }

  template< class Key, class Value, class Comparator >
  std::pair< TTTIterator< Key, Value, Comparator >, TTTIterator< Key, Value, Comparator > >
    TwoThreeTree< Key, Value, Comparator >::equal_range(const Key& key)
  {
    return {lower_bound(key), upper_bound(key)};
  }

  template< class Key, class Value, class Comparator >
  std::pair< TTTConstIterator< Key, Value, Comparator >, TTTConstIterator< Key, Value, Comparator > >
    TwoThreeTree< Key, Value, Comparator >::equal_range(const Key& key) const
  {
    return {lower_bound(key), upper_bound(key)};
  }

  template< class Key, class Value, class Comparator >
  TTTIterator< Key, Value, Comparator >
    TwoThreeTree< Key, Value, Comparator >::lower_bound(const Key& key)
  {
    ConstIterator tmp = static_cast< const Tree& >(*this).lower_bound(key);
    return Iterator(tmp);
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator >
    TwoThreeTree< Key, Value, Comparator >::lower_bound(const Key& key) const
  {
    for (auto it = cbegin(); it != cend(); it++)
    {
      if (!cmp_(it->first, key))
      {
        return it;
      }
    }
    return cend();
  }

  template< class Key, class Value, class Comparator >
  TTTIterator< Key, Value, Comparator >
    TwoThreeTree< Key, Value, Comparator >::upper_bound(const Key& key)
  {
    ConstIterator tmp = static_cast< const Tree& >(*this).upper_bound(key);
    return Iterator(tmp);
  }

  template< class Key, class Value, class Comparator >
  TTTConstIterator< Key, Value, Comparator >
    TwoThreeTree< Key, Value, Comparator >::upper_bound(const Key& key) const
  {
    for (auto it = cbegin(); it != cend(); it++)
    {
      if (cmp_(key, it->first))
      {
        return it;
      }
    }
    return cend();
  }

  template< class Key, class Value, class Comparator >
  void TwoThreeTree< Key, Value, Comparator >::clear(Node* root) noexcept
  {
    if (!root || root == fake_)
    {
      return;
    }
    clear(root->left);
    clear(root->mid);
    clear(root->right);
    delete root;
  }

  template< class Key, class Value, class Comparator >
  void TwoThreeTree< Key, Value, Comparator >::split(Node* node)
  {
    if (node->type != NodeType::Overflow)
    {
      return;
    }
    Node* left = nullptr, *right = nullptr, *parent = nullptr;
    try
    {
      parent = node->parent;
      if (!parent)
      {
        parent = new Node();
        root_ = parent;
      }
      left = new Node(node->data[0], parent, node->left, nullptr, node->mid, nullptr);
      right = new Node(node->data[2], parent, node->right, nullptr, node->overflow, nullptr);
      if (left->left)
      {
        left->left->parent = left;
        left->right->parent = left;
        right->left->parent = right;
        right->right->parent = right;
      }
      if (right->left == fake_)
      {
        right->left = nullptr;
      }

      parent->insert(node->data[1]);
      {
        if (parent->type == NodeType::Double)
        {
          parent->left = left;
          parent->right = right;
        }
        else if (parent->right == node && parent->type == NodeType::Triple)
        {
          parent->mid = left;
          parent->right = right;
        }
        else if (parent->right == node && parent->type == NodeType::Overflow)
        {
          parent->right = left;
          parent->overflow = right;
        }
        else if (parent->mid == node)
        {
          parent->mid = left;
          parent->right = right;
        }
        else if (parent->left == node)
        {
          parent->left = left;
          parent->mid = right;
        }
      }
    }
    catch (...)
    {
      delete left;
      delete right;
      delete parent;
      throw;
    }
    delete node;
    split(parent);
  }

  template< class Key, class Value, class Comparator >
  void TwoThreeTree< Key, Value, Comparator >::move_fake() noexcept
  {
    Node* tmp = root_;
    while (tmp->right && tmp->right != fake_)
    {
      tmp = tmp->right;
    }
    tmp->right = fake_;
    fake_->parent = tmp;
  }

  template< class Key, class Value, class Comparator >
  detail::TTTNode< Key, Value, Comparator >*
    TwoThreeTree< Key, Value, Comparator >::find_to_insert(const Key& key) const
  {
    Node* tmp = root_;
    while (!tmp->isLeaf())
    {
      if (cmp_(key, tmp->data[0].first))
      {
        tmp = tmp->left;
      }
      else if (tmp->type == NodeType::Triple && cmp_(key, tmp->data[1].first))
      {
        tmp = tmp->mid;
      }
      else
      {
        tmp = tmp->right;
      }
    }
    return tmp;
  }

  template< class Key, class Value, class Comparator >
  detail::TTTNode< Key, Value, Comparator >*
    TwoThreeTree< Key, Value, Comparator >::find_to_insert(ConstIterator hint) const
  {
    Iterator tmp = hint;
    if (hint == cbegin())
    {
      return tmp.node_;
    }
    return (--tmp).node_;
  }

  template< class Key, class Value, class Comparator >
  bool TwoThreeTree< Key, Value, Comparator >::check_hint(ConstIterator hint, const Key& key)
  {
    if (hint != cend())
    {
      if (!cmp_(key, hint->first))
      {
        return false;
      }
    }
    if (hint != cbegin())
    {
      return cmp_((--hint)->first, key);
    }
    return true;
  }

  template< class Key, class Value, class Comparator >
  TTTIterator< Key, Value, Comparator > TwoThreeTree< Key, Value, Comparator >::find_to_erase(Iterator pos)
  {
    Node* node = pos.node_;
    Node* node_instead = node;
    if (pos.point_ == NodePoint::First)
    {
      if (node_instead->left)
      {
        node_instead = node_instead->left;
        while (node_instead->right && node_instead->right != fake_)
        {
          node_instead = node_instead->right;
        } 
      }
    }
    else if (pos.point_ == NodePoint::Second)
    {
      if (node_instead->right && node_instead->right != fake_)
      {
        node_instead = node_instead->right;
        while (node_instead->left->type != NodeType::Fake)
        {
          node_instead = node_instead->left;
        }
      }
    }
    NodePoint point = NodePoint::First;
    if (pos.point_ == NodePoint::First && node_instead->type == NodeType::Triple)
    {
      point = NodePoint::Second;
    }
    return {node_instead, point};
  }

  template< class Key, class Value, class Comparator >
  bool TwoThreeTree< Key, Value, Comparator >::have_triple_neighbor(Iterator pos)
  {
    Node* node = pos.node_;
    if (!node->parent)
    {
      return false;
    }
    if (node->parent->type == NodeType::Triple)
    {
      return true;
    }
    if (node->parent->left->type == NodeType::Triple)
    {
      return true;
    }
    return node->parent->right->type == NodeType::Triple;
  }

  template< class Key, class Value, class Comparator >
  void TwoThreeTree< Key, Value, Comparator >::distribute(Iterator pos)
  {
    Node* node = pos.node_;
    Node* parent = node->parent;
    Node* left = parent->left;
    Node* mid = parent->mid;
    Node* right = parent->right;
    if (parent->type == NodeType::Double)
    {
      Node* brother;
      NodePoint point;
      if (left == node)
      {
        brother = right;
        point = NodePoint::First;
      }
      else
      {
        brother = left;
        point = NodePoint::Second;
      }
      node->insert(parent->data[0]);
      parent->remove(NodePoint::First);
      parent->insert(brother->data[point - 1]);
      brother->remove(point);
      return;
    }
    if (left == node)
    {
      node->insert(parent->data[0]);
      parent->remove(NodePoint::First);
      if (mid->type == NodeType::Triple)
      {
        parent->insert(mid->data[0]);
        mid->remove(NodePoint::First);
        return;
      }
      node->insert(mid->data[0]);
      delete mid;
      mid = nullptr;
      return;
    }
    if (mid == node)
    {
      node->insert(parent->data[0]);
      parent->remove(NodePoint::First);
      if (left->type == NodeType::Triple)
      {
        parent->insert(left->data[1]);
        left->remove(NodePoint::Second);
        return;
      }
      node->insert(left->data[0]);
      std::swap(left, mid);
      delete mid;
      mid = nullptr;
      return;
    }
    if (right == node)
    {
      node->insert(parent->data[1]);
      parent->remove(NodePoint::Second);
      if (mid->type == NodeType::Triple)
      {
        parent->insert(mid->data[1]);
        mid->remove(NodePoint::Second);
        return;
      }
      node->insert(mid->data[0]);
      delete mid;
      mid = nullptr;
      return;
    }
  }

  template< class Key, class Value, class Comparator >
  void TwoThreeTree< Key, Value, Comparator >::merge(Iterator pos)
  {
    Node* node = pos.node_;
    Node* parent = node->parent;
    Node* left = parent->left;
    Node* mid = parent->mid;
    Node* right = parent->right;
    Node* node_merge, *deleted;
    if (left == node)
    {
      node_merge = right;
    }
    else
    {
      node_merge = left;
    }
    node_merge->insert(parent->data[0]);
    parent->remove(NodePoint::First);
    delete node;
    deleted = parent;
    parent = deleted->parent;
    if (!parent)
    {
      delete deleted;
      root_ = node_merge;
    }
  }

  template< class Key, class Value, class Comparator >
  bool TwoThreeTree< Key, Value, Comparator >::is_balanced()
  {
    return find_height(root_) != -1;
  }

  template< class Key, class Value, class Comparator >
  size_t TwoThreeTree< Key, Value, Comparator >::find_height(Node* node)
  {
    if (node == nullptr || node == fake_)
    {
      return 0;
    }
    size_t left_height = find_height(node->left);
    size_t right_height = find_height(node->right);
    size_t mid_height = find_height(node->mid);
    if (left_height < 0 || right_height < 0 || mid_height < 0)
    {
      return -1;
    }
    if (left_height != right_height)
    {
      return -1;
    }
    if (left_height != mid_height && node->type == NodeType::Triple)
    {
      return -1;
    }
    return left_height + 1;
  }
}

#endif
