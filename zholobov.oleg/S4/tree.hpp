#ifndef TREE_HPP
#define TREE_HPP

#include <functional>

#include "node.hpp"
#include "tree_iterators.hpp"

namespace zholobov {

  template < typename Key, typename T, typename Compare = std::less< Key > >
  class Tree {
  public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair< const Key, T >;
    using reference = value_type&;
    using const_reference = const value_type&;
    using node_type = Node< Key, T >;
    using iterator = TreeIterator< node_type >;
    using const_iterator = TreeConstIterator< node_type >;
    using size_type = size_t;

    Tree();
    explicit Tree(const Compare& comp);
    Tree(const Tree< Key, T, Compare >& other);
    Tree(Tree< Key, T, Compare >&& other);

    template < typename InputIt >
    Tree(InputIt first, InputIt last, const Compare& comp = Compare());

    explicit Tree(std::initializer_list< value_type > init, const Compare& comp = Compare());

    ~Tree();

    Tree& operator=(const Tree& other);
    Tree& operator=(Tree&& other) noexcept;

    Tree& operator=(std::initializer_list< value_type > ilist);

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    bool empty() const noexcept;
    size_type size() const noexcept;

    mapped_type& operator[](const key_type& key);
    mapped_type& at(const key_type& key);
    const mapped_type& at(const key_type& key) const;

    template < class... Args >
    std::pair< iterator, bool > emplace(Args&&... args);
    template < class... Args >
    iterator emplace_hint(const_iterator position, Args&&... args);

    std::pair< iterator, bool > insert(const value_type& value);
    iterator insert(const_iterator pos, const value_type& value);
    template < class InputIt >
    void insert(InputIt first, InputIt last);

    iterator erase(iterator position);
    iterator erase(const_iterator position);
    size_type erase(const key_type& key);
    iterator erase(const_iterator first, const_iterator last);

    void swap(Tree&) noexcept;
    void clear() noexcept;

    iterator find(const key_type& key);
    const_iterator find(const key_type& key) const;

    size_type count(const key_type& x) const;

    iterator lower_bound(const key_type& key);
    const_iterator lower_bound(const key_type& key) const;
    iterator upper_bound(const key_type& key);
    const_iterator upper_bound(const key_type& key) const;

    std::pair< iterator, iterator > equal_range(const key_type& key);
    std::pair< const_iterator, const_iterator > equal_range(const key_type& key) const;
  };

}

#endif
