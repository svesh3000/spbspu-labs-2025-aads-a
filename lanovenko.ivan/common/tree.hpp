#ifndef TREE_HPP
#define TREE_HPP

#include <stack>
#include <queue>
#include <cassert>
#include <stdexcept>
#include "tree_node.hpp"
#include "tree_iterator.hpp"
#include "tree_const_iterator.hpp"

namespace lanovenko
{
  template< typename Key, typename Value, typename Comparator >
  class TreeIterator;

  template< typename Key, typename Value, typename Comparator >
  class TreeConstIterator;

  template< typename Key, typename Value, typename Comparator >
  class Tree
  {
  public:
    ~Tree();
    Tree();
    Tree(const Tree< Key, Value, Comparator >& rhs);
    Tree(Tree< Key, Value, Comparator >&& rhs) noexcept;
    Tree< Key, Value, Comparator >& operator=(const Tree< Key, Value, Comparator >& rhs);
    Tree< Key, Value, Comparator >& operator=(Tree< Key, Value, Comparator >&& rhs) noexcept;
    TreeIterator< Key, Value, Comparator > begin() const noexcept;
    TreeIterator< Key, Value, Comparator > end() const noexcept;
    TreeConstIterator< Key, Value, Comparator > cbegin() const noexcept;
    TreeConstIterator< Key, Value, Comparator > cend() const noexcept;
    size_t size() const noexcept;
    bool empty() const noexcept;
    void clear() noexcept;
    void swap(Tree< Key, Value, Comparator >& rhs) noexcept;
    TreeIterator< Key, Value, Comparator > find(const Key& key) const;
    void insert(const std::pair< Key, Value >& value);
    TreeIterator< Key, Value, Comparator > erase(TreeIterator< Key, Value, Comparator > position);
    Value& at(const Key& key);
    size_t count(const Key& k) const;
    Value& operator[](const Key& key);
    template< typename F >
    F traverseLnr(F f);
    template< typename F >
    F traverseLnr(F f) const;
    template< typename F >
    F traverseRnl(F f);
    template< typename F >
    F traverseRnl(F f) const;
    template< typename F >
    F traverseBreadth(F f);
    template< typename F >
    F traverseBreadth(F f) const;
  private:
    TreeNode< Key, Value >* root_;
    TreeNode< Key, Value >* fakeLeaf_;
    size_t size_;
    unsigned short int height(TreeNode< Key, Value >* node) const noexcept;
    void fixHeight(TreeNode< Key, Value >* node) const noexcept;
    short int balanceFactor(TreeNode< Key, Value >* node) const noexcept;
    TreeNode< Key, Value >* balance(TreeNode< Key, Value >* node);
    TreeNode< Key, Value >* rotateRight(TreeNode< Key, Value >* root) const noexcept;
    TreeNode< Key, Value >* rotateLeft(TreeNode< Key, Value >* root) const noexcept;
    TreeNode< Key, Value >* insert(TreeNode< Key, Value >* node, const std::pair< Key, Value >& value, Comparator cmp);
    static TreeNode< Key, Value >* minValueNode(TreeNode< Key, Value >* node);
    TreeNode< Key, Value >* erase(TreeNode< Key, Value >* node, const std::pair< Key, Value >& value, Comparator cmp);
    TreeIterator< Key, Value, Comparator > find(const Key& key, Comparator cmp) const;
    void clear(TreeNode< Key, Value >* root) noexcept;
    friend class TreeIterator< Key, Value, Comparator >;
  };

  template< typename Key, typename Value, typename Comparator >
  Tree< Key, Value, Comparator >::~Tree()
  {
    clear();
  }

  template< typename Key, typename Value, typename Comparator >
  Tree< Key, Value, Comparator >::Tree():
    root_(nullptr),
    fakeLeaf_(new TreeNode< Key, Value >({ {}, {} })),
    size_(0)
  {}

  template< typename Key, typename Value, typename Comparator >
  Tree< Key, Value, Comparator >::Tree(const Tree< Key, Value, Comparator >& rhs):
    Tree()
  {
    try
    {
      for (TreeIterator< Key, Value, Comparator > it = rhs.begin(); it != rhs.end(); it++)
      {
        insert(*it);
      }
    }
    catch (...)
    {
      clear();
      throw;
    }
  }

  template< typename Key, typename Value, typename Comparator >
  Tree< Key, Value, Comparator >::Tree(Tree< Key, Value, Comparator >&& rhs) noexcept:
    root_(rhs.root_),
    fakeLeaf_(rhs.fakeLeaf_),
    size_(rhs.size_)
  {
    rhs.root_ = rhs.fakeLeaf_ = nullptr;
    rhs.size_ = 0;
  }

  template< typename Key, typename Value, typename Comparator >
  Tree< Key, Value, Comparator >& Tree< Key, Value, Comparator >::operator=(const Tree< Key, Value, Comparator >& rhs)
  {
    if (this == std::addressof(rhs))
    {
      return *this;
    }
    Tree< Key, Value, Comparator > temp(rhs);
    swap(temp);
    return *this;
  }

  template<typename Key, typename Value, typename Comparator>
  Tree<Key, Value, Comparator>& Tree<Key, Value, Comparator>::operator=(Tree<Key, Value, Comparator>&& rhs) noexcept
  {
    if (this == std::addressof(rhs))
    {
      return *this;
    }
    Tree< Key, Value, Comparator > temp(std::move(rhs));
    swap(temp);
    return *this;
  }

  template< typename Key, typename Value, typename Comparator >
  inline TreeIterator< Key, Value, Comparator > Tree< Key, Value, Comparator >::begin() const noexcept
  {
    return TreeIterator< Key, Value, Comparator >(minValueNode(root_));
  }

  template< typename Key, typename Value, typename Comparator >
  inline TreeIterator< Key, Value, Comparator > Tree< Key, Value, Comparator >::end() const noexcept
  {
    return TreeIterator< Key, Value, Comparator >();
  }

  template< typename Key, typename Value, typename Comparator >
  inline TreeConstIterator< Key, Value, Comparator > Tree< Key, Value, Comparator >::cbegin() const noexcept
  {
    return TreeConstIterator< Key, Value, Comparator >(minValueNode(root_));
  }

  template< typename Key, typename Value, typename Comparator >
  inline TreeConstIterator< Key, Value, Comparator > Tree< Key, Value, Comparator >::cend() const noexcept
  {
    return TreeConstIterator< Key, Value, Comparator >();
  }

  template<typename Key, typename Value, typename Comparator>
  inline size_t Tree<Key, Value, Comparator>::size() const noexcept
  {
    return size_;
  }

  template<typename Key, typename Value, typename Comparator>
  inline bool Tree<Key, Value, Comparator>::empty() const noexcept
  {
    return size_ == 0;
  }


  template< typename Key, typename Value, typename Comparator >
  void Tree< Key, Value, Comparator >::clear() noexcept
  {
    clear(root_);
    delete fakeLeaf_;
    fakeLeaf_ = root_ = nullptr;
  }

  template< typename Key, typename Value, typename Comparator >
  inline void Tree< Key, Value, Comparator >::swap(Tree< Key, Value, Comparator >& rhs) noexcept
  {
    std::swap(root_, rhs.root_);
    std::swap(fakeLeaf_, rhs.fakeLeaf_);
    std::swap(size_, rhs.size_);
  }

  template<typename Key, typename Value, typename Comparator>
  inline TreeIterator<Key, Value, Comparator> Tree<Key, Value, Comparator>::find(const Key& key) const
  {
    return find(key, Comparator{});
  }

  template<typename Key, typename Value, typename Comparator>
  void Tree< Key, Value, Comparator >::insert(const std::pair< Key, Value >& value)
  {
    try
    {
      root_ = insert(root_, value, Comparator{});
      size_++;
    }
    catch (...)
    {
      clear();
      throw;
    }
  }

  template< typename Key, typename Value, typename Comparator >
  TreeIterator< Key, Value, Comparator > Tree< Key, Value, Comparator >::erase(TreeIterator< Key, Value, Comparator > position)
  {
    if (position == end() || find((*position).first) == end())
    {
      throw std::out_of_range("Wrong key");
    }
    root_ = erase(root_, *(position), Comparator{});
    size_--;
    return ++position;
  }

  template< typename Key, typename Value, typename Comparator >
  inline Value& Tree< Key, Value, Comparator >::at(const Key& key)
  {
    TreeIterator< Key, Value, Comparator > position = find(key);
    if (position != end())
    {
      return (*position).second;
    }
    throw std::out_of_range("<INVALID COMMAND>");
  }

  template< typename Key, typename Value, typename Comparator >
  size_t Tree< Key, Value, Comparator >::count(const Key& k) const
  {
    size_t count = 0;
    Comparator cmp = Comparator{};
    for (auto it = cbegin(); it != cend(); ++it)
    {
      if (!cmp(k, it->first) && !cmp(it->first, k))
      {
        ++count;
      }
    }
    return count;
  }

  template<typename Key, typename Value, typename Comparator>
  Value& Tree<Key, Value, Comparator>::operator[](const Key& key)
  {
    TreeIterator<Key, Value, Comparator> node = find(key);
    if (node == end())
    {
      insert({ key, Value() });
      node = find(key);
    }
    return node->second;
  }

  template< typename Key, typename Value, typename Comparator >
  inline unsigned short int Tree< Key, Value, Comparator >::height(TreeNode< Key, Value >* node) const noexcept
  {
    return !node ? 0 : node->height_;
  }

  template< typename Key, typename Value, typename Comparator >
  inline void Tree< Key, Value, Comparator >::fixHeight(TreeNode< Key, Value >* node) const noexcept
  {
    unsigned short int hl = height(node->left_), hr = height(node->right_);
    node->height_ = (hl > hr ? hl : hr) + 1;
  }

  template<typename Key, typename Value, typename Comparator>
  inline short int Tree< Key, Value, Comparator >::balanceFactor(TreeNode< Key, Value >* node) const noexcept
  {
    return !node ? 0 : height(node->left_) - height(node->right_);
  }

  template< typename Key, typename Value, typename Comparator >
  TreeNode< Key, Value >* Tree< Key, Value, Comparator >::balance(TreeNode< Key, Value >* node)
  {
    short int balance = balanceFactor(node);
    if (balance > 1)
    {
      if (balanceFactor(node->left_) < 0)
      {
        node->left_ = rotateLeft(node->left_);
      }
      node = rotateRight(node);
    }
    if (balance < -1)
    {
      if (balanceFactor(node->right_) > 0)
      {
        node->right_ = rotateRight(node->right_);
      }
      node = rotateLeft(node);
    }
    return node;
  }

  template< typename Key, typename Value, typename Comparator >
  TreeNode< Key, Value >* Tree< Key, Value, Comparator >::rotateRight(TreeNode< Key, Value >* root) const noexcept
  {
    assert(root && root->left_);
    TreeNode< Key, Value  >* newRoot = root->left_;
    if (root->parent_)
    {
      newRoot->parent_ = root->parent_;
      if (root->parent_->right_ == root)
      {
        newRoot->parent_->right_ = newRoot;
      }
      else
      {
        newRoot->parent_->left_ = newRoot;
      }
    }
    else
    {
      newRoot->parent_ = nullptr;
    }
    root->parent_ = newRoot;
    if (newRoot->right_)
    {
      root->left_ = newRoot->right_;
      root->left_->parent_ = root;
    }
    else
    {
      root->left_ = nullptr;
    }
    newRoot->right_ = root;
    fixHeight(root);
    fixHeight(newRoot);
    return newRoot;
  }

  template< typename Key, typename Value, typename Comparator >
  TreeNode< Key, Value >* Tree< Key, Value, Comparator >::rotateLeft(TreeNode < Key, Value >* root) const noexcept
  {
    assert(root && root->right_);
    TreeNode< Key, Value >* newRoot = root->right_;
    if (root->parent_)
    {
      newRoot->parent_ = root->parent_;
      if (root->parent_->right_ == root)
      {
        newRoot->parent_->right_ = newRoot;
      }
      else
      {
        newRoot->parent_->left_ = newRoot;
      }
    }
    else
    {
      newRoot->parent_ = nullptr;
    }
    root->parent_ = newRoot;
    if (newRoot->left_)
    {
      root->right_ = newRoot->left_;
      root->right_->parent_ = root;
    }
    else
    {
      root->right_ = nullptr;
    }
    newRoot->left_ = root;
    fixHeight(root);
    fixHeight(newRoot);
    return newRoot;
  }

  template< typename Key, typename Value, typename Comparator >
  TreeNode< Key, Value >* Tree< Key, Value, Comparator >::insert(
    TreeNode< Key, Value >* node,
    const std::pair< Key, Value >& value,
    Comparator cmp)
  {
    if (!node)
    {
      return new TreeNode< Key, Value >{ {value.first, value.second} };
    }
    else if (cmp(value.first, node->data_.first))
    {
      node->left_ = insert(node->left_, value, cmp);
      node->left_->parent_ = node;
    }
    else if (cmp(node->data_.first, value.first))
    {
      node->right_ = insert(node->right_, value, cmp);
      node->right_->parent_ = node;
    }
    else
    {
      node->data_.second = value.second;
      return node;
    }
    fixHeight(node);
    return balance(node);
  }

  template< typename Key, typename Value, typename Comparator >
  TreeNode< Key, Value >* Tree< Key, Value, Comparator >::minValueNode(TreeNode< Key, Value >* node)
  {
    while (node && node->left_)
    {
      node = node->left_;
    }
    return node;
  }

  template< typename Key, typename Value, typename Comparator >
  TreeNode< Key, Value >* Tree< Key, Value, Comparator >::erase(
    TreeNode< Key, Value >* node,
    const std::pair< Key, Value >& value, Comparator cmp
  )
  {
    if (!node)
    {
      return node;
    }
    if (cmp(value.first, node->data_.first))
    {
      node->left_ = erase(node->left_, value, cmp);
    }
    else if (cmp(node->data_.first, value.first))
    {
      node->right_ = erase(node->right_, value, cmp);
    }
    else
    {
      if (!node->left_ || !node->right_)
      {
        TreeNode< Key, Value >* temp = node->left_ ? node->left_ : node->right_;
        if (!temp)
        {
          delete node;
          return nullptr;
        }
        else
        {
          node->data_ = temp->data_;
          node->left_ = temp->left_;
          node->right_ = temp->right_;
          if (node->left_) node->left_->parent_ = node;
          if (node->right_) node->right_->parent_ = node;
        }
        delete temp;
      }
      else
      {
        TreeNode< Key, Value >* temp = minValueNode(node->right_);
        node->data_ = temp->data_;
        node->right_ = erase(node->right_, temp->data_, cmp);
      }
    }
    fixHeight(node);
    return balance(node);
  }

  template< typename Key, typename Value, typename Comparator >
  TreeIterator< Key, Value, Comparator > Tree< Key, Value, Comparator >::find(
    const Key& key,
    Comparator cmp) const
  {
    TreeNode< Key, Value >* root = root_;
    while (root && key != root->data_.first)
    {
      if (cmp(key, root->data_.first))
      {
        root = root->left_;
      }
      else
      {
        root = root->right_;
      }
    }
    return TreeIterator< Key, Value, Comparator >(root);
  }

  template< typename Key, typename Value, typename Comparator >
  void Tree< Key, Value, Comparator >::clear(TreeNode< Key, Value >* root) noexcept
  {
    if (!root || root == fakeLeaf_)
    {
      return;
    }
    clear(root->left_);
    clear(root->right_);
    delete root;
    size_--;
  }

  template < typename Key, typename Value, typename Comparator >
  template < typename F >
  inline F Tree< Key, Value, Comparator >::traverseLnr(F f)
  {
      if (empty())
    {
      throw std::logic_error("<EMPTY>");
    }
    std::stack< TreeNode< Key, Value > * > stack;
    TreeNode< Key, Value > * current = root_;
    bool leftDone = false;
    while (current != nullptr || !stack.empty())
    {
      if (!leftDone && current != nullptr)
      {
        stack.push(current);
        current = current->left_;
      }
      else
      {
        current = stack.top();
        stack.pop();
        f(current->data_);
        current = current->right_;
        leftDone = (current == nullptr);
      }
    }
    return f;
  }

  template <typename Key, typename Value, typename Comparator>
  template <typename F>
  inline F Tree< Key, Value, Comparator >::traverseLnr(F f) const
  {
    return const_cast< Tree< Key, Value, Comparator > * >(this)->traverseLnr(f);
  }

  template < typename Key, typename Value, typename Comparator >
  template < typename F >
  inline F Tree<Key, Value, Comparator>::traverseRnl(F f)
  {
    if (empty())
    {
      throw std::logic_error("<EMPTY>");
    }
    std::stack< TreeNode< Key, Value > * > stack;
    TreeNode< Key, Value > * current = root_;
    bool rightDone = false;
    while (current != nullptr || !stack.empty())
    {
      if (!rightDone && current != nullptr)
      {
        stack.push(current);
        current = current->right_;
      }
      else
      {
        current = stack.top();
        stack.pop();
        f(current->data_);
        current = current->left_;
        rightDone = (current == nullptr);
      }
    }
    return f;
  }

  template < typename Key, typename Value, typename Comparator >
  template < typename F >
  inline F Tree< Key, Value, Comparator >::traverseRnl(F f) const
  {
    return const_cast< Tree< Key, Value , Comparator> * >(this)->traverseRnl(f);
  }

  template <typename Key, typename Value, typename Comparator>
  template <typename F>
  inline F Tree<Key, Value, Comparator>::traverseBreadth(F f)
  {
    if (empty())
    {
      throw std::logic_error("<EMPTY>");
    }
    std::queue< TreeNode< Key, Value > * > queue;
    queue.push(root_);
    while (!queue.empty())
    {
      TreeNode< Key, Value > * current = queue.front();
      queue.pop();
      f(current->data_);
      if (current->left_ != nullptr)
      {
        queue.push(current->left_);
      }
      if (current->right_ != nullptr)
      {
        queue.push(current->right_);
      }
    }
    return f;
  }

  template < typename Key, typename Value, typename Comparator >
  template < typename F >
  inline F Tree<Key, Value, Comparator>::traverseBreadth(F f) const
  {
    return const_cast< Tree< Key, Value, Comparator > * >(this)->traverseBreadth(f);
  }
}

#endif
