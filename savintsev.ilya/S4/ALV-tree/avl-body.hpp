#ifndef AVL_BODY_HPP
#define AVL_BODY_HPP

#include <functional>
#include <initializer_list>
#include <utility>
#include <iterator>
#include <type_traits>
#include "avl-node.hpp"
#include "avl-iterator.hpp"

namespace savintsev
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class AVLTree
  {
  private:
    using node_type = node_t< Key, Value >;
    using value_type = typename node_type::value_type;
    using key_type = Key;
    using mapped_type = Value;

  public:
    using iterator = BidirectIterator< Key, Value >;
    using const_iterator = BidirectIterator< Key, Value >;

  private:
    node_type * root_ = nullptr;
    size_t size_ = 0;
    Compare comp_;

  public:
    AVLTree() = default;

    AVLTree(std::initializer_list< value_type > init)
    {
      for (const auto & item : init)
      {
        insert(item);
      }
    }

    template< typename InputIt,
    typename std::enable_if< !std::is_integral< InputIt >::value, int >::type = 0 >
    void insert(InputIt first, InputIt last)
    {
      for (; first != last; ++first)
      {
        insert(*first);
      }
    }

    ~AVLTree()
    {
      clear();
    }

    iterator begin()
    {
      return iterator(find_min(root_));
    }

    const_iterator begin() const
    {
      return const_iterator(find_min(root_));
    }

    iterator end()
    {
      return iterator(nullptr);
    }

    const_iterator end() const
    {
      return const_iterator(nullptr);
    }

    mapped_type & operator[](const key_type & key)
    {
      node_type * node = find_node(key);
      if (node)
      {
        return node->data_.second;
      }
      insert({key, mapped_type{}});
      return find_node(key)->data_.second;
    }

    mapped_type & at(const key_type & key) const
    {
      node_type * node = find_node(key);
      if (node)
      {
        return node->data_.second;
      }
      throw std::out_of_range("ERROR: Key not exist");
    }

    bool empty() const
    {
      return root_ == nullptr;
    }

    size_t size() const
    {
      return size_;
    }

    void clear()
    {
      clear_recursive(root_);
      root_ = nullptr;
      size_ = 0;
    }

    void swap(AVLTree & other)
    {
      std::swap(root_, other.root_);
      std::swap(size_, other.size_);
      std::swap(comp_, other.comp_);
    }

    template< typename... Args >
    std::pair< iterator, bool > emplace(Args &&... args)
    {
      value_type val(std::forward< Args >(args)...);
      auto result = insert(val);
      return {result.first, result.second};
    }

    template< typename... Args >
    iterator emplace_hint(iterator, Args &&... args)
    {
      value_type val(std::forward< Args >(args)...);
      insert(val);
      return iterator(find_node(val.first));
    }

    std::pair< iterator, bool > insert(const value_type & val)
    {
      bool inserted = false;
      root_ = insert_recursive(root_, nullptr, val, inserted);
      return { iterator(find_node(val.first)), inserted };
    }

    iterator insert(iterator, const value_type & val)
    {
      insert(val);
      return iterator(find_node(val.first));
    }

    iterator erase(iterator pos)
    {
      key_type key = pos->first;
      ++pos;
      remove(key);
      return pos;
    }

    size_t erase(const key_type & key)
    {
      return remove(key) ? 1 : 0;
    }

    iterator erase(iterator first, iterator last)
    {
      while (first != last)
      {
        first = erase(first);
      }
      return last;
    }

    size_t count(const key_type & key) const
    {
        return find(key) != end() ? 1 : 0;
    }

    iterator find(const key_type & key)
    {
      return iterator(find_node(key));
    }

    const_iterator find(const key_type & key) const
    {
      return const_iterator(find_node(key));
    }

    std::pair< iterator, iterator > equal_range(const key_type & key)
    {
      return { lower_bound(key), upper_bound(key) };
    }

    iterator lower_bound(const key_type & key)
    {
      node_type * current = root_;
      node_type * result = nullptr;
      while (current)
      {
        if (!comp_(current->data_.first, key))
        {
          result = current;
          current = current->left_;
        }
        else
        {
          current = current->right_;
        }
      }
      return iterator(result);
    }

    iterator upper_bound(const key_type & key)
    {
      node_type * current = root_;
      node_type * result = nullptr;
      while (current)
      {
        if (comp_(key, current->data_.first))
        {
          result = current;
          current = current->left_;
        }
        else
        {
          current = current->right_;
        }
      }
      return iterator(result);
    }

  private:
    bool remove(const key_type & key)
    {
      bool removed = false;
      root_ = remove_recursive(root_, key, removed);
      if (removed)
      {
        size_--;
      }
      return removed;
    }

    size_t get_height(node_type * node) const
    {
      return node ? node->height_ : 0;
    }

    int get_balance_factor(node_type * node) const
    {
      return node ? get_height(node->left_) - get_height(node->right_) : 0;
    }

    void update_height(node_type * node)
    {
      if (node)
      {
        node->height_ = 1 + std::max(get_height(node->left_), get_height(node->right_));
      }
    }

    node_type * rotate_right(node_type * y)
    {
      node_type * x = y->left_;
      node_type * T2 = x->right_;

      x->parent_ = y->parent_;
      y->parent_ = x;
      if (T2)
      {
        T2->parent_ = y;
      }
      x->right_ = y;
      y->left_ = T2;

      update_height(y);
      update_height(x);

      return x;
    }

    node_type * rotate_left(node_type * x)
    {
      node_type * y = x->right_;
      node_type * T2 = y->left_;

      y->parent_ = x->parent_;
      x->parent_ = y;
      if (T2)
      {
        T2->parent_ = x;
      }
      y->left_ = x;
      x->right_ = T2;

      update_height(x);
      update_height(y);

      return y;
    }

    node_type * balance(node_type * node)
    {
      if (!node)
      {
        return nullptr;
      }
      update_height(node);

      int balance = get_balance_factor(node);

      if (balance > 1)
      {
        if (get_balance_factor(node->left_) < 0)
        {
          node->left_ = rotate_left(node->left_);
        }
        return rotate_right(node);
      }

      if (balance < -1)
      {
        if (get_balance_factor(node->right_) > 0)
        {
          node->right_ = rotate_right(node->right_);
        }
        return rotate_left(node);
      }

      return node;
    }

    node_type * insert_recursive(node_type * node, node_type * parent, const value_type & data, bool & inserted)
    {
      if (!node)
      {
        inserted = true;
        size_++;
        node_type * new_node = new node_type{data};
        new_node->parent_ = parent;
        return new_node;
      }

      if (comp_(data.first, node->data_.first))
      {
        node->left_ = insert_recursive(node->left_, node, data, inserted);
      }
      else if (comp_(node->data_.first, data.first))
      {
        node->right_ = insert_recursive(node->right_, node, data, inserted);
      }
      else
      {
        node->data_.second = data.second;
        inserted = false;
      }

      node_type * balanced = balance(node);
      if (!balanced->parent_ && parent == nullptr)
      {
        root_ = balanced;
      }
      return balanced;
    }

    node_type * find_min(node_type * node) const
    {
      while (node && node->left_)
      {
        node = node->left_;
      }
      return node;
    }

    node_type * remove_recursive(node_type * node, const key_type & key, bool& removed)
    {
      if (!node)
      {
        return nullptr;
      }
      if (comp_(key, node->data_.first))
      {
        node->left_ = remove_recursive(node->left_, key, removed);
      }
      else if (comp_(node->data_.first, key))
      {
        node->right_ = remove_recursive(node->right_, key, removed);
      }
      else
      {
        removed = true;

        if (!node->left_ || !node->right_)
        {
          node_type * child = node->left_ ? node->left_ : node->right_;

          if (!child)
          {
            delete node;
            return nullptr;
          }

          child->parent_ = node->parent_;
          delete node;
          return child;
        }
        else
        {
          node_type * successor = find_min(node->right_);
          node->data_ = successor->data_;

          bool dummy = false;
          node->right_ = remove_recursive(node->right_, successor->data_.first, dummy);
        }
      }

      return balance(node);
    }

    node_type * find_node(const key_type & key) const
    {
      node_type * current = root_;
      while (current)
      {
        if (comp_(key, current->data_.first))
        {
          current = current->left_;
        }
        else if (comp_(current->data_.first, key))
        {
          current = current->right_;
        }
        else
        {
          return current;
        }
      }
      return nullptr;
    }

    void clear_recursive(node_type * node)
    {
      if (!node)
      {
        return;
      }
      clear_recursive(node->left_);
      clear_recursive(node->right_);
      delete node;
    }
  };
}

#endif
