#ifndef TREE_HPP
#define TREE_HPP

#include <functional>
#include <map>

namespace zholobov {

  template < typename T >
  class TreeIterator;

  template < typename T >
  class TreeConstIterator;

  template < typename Key, typename T, typename Compare = std::less< Key > >
  class Tree {
  public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair< const Key, T >;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = TreeIterator< value_type >;
    using const_iterator = TreeConstIterator< value_type >;
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
    size_type max_size() const noexcept;

    mapped_type& operator[](const key_type& x);
    mapped_type& at(const key_type& x);
    const mapped_type& at(const key_type& x) const;

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

    iterator find(const key_type& x);
    const_iterator find(const key_type& x) const;
  };

}

#endif
