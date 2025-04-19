#ifndef TWO_THREE_TREE_DECLARATION_HPP
#define TWO_THREE_TREE_DECLARATION_HPP

#include "two_three_iterator.hpp"

namespace maslevtsov {
  template< class Key, class T, class Compare = std::less< Key > >
  class TwoThreeTree
  {
  public:
    using value_type = std::pair< const Key, T >;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using const_iterator = TwoThreeIterator< value_type >;

    TwoThreeTree();
    TwoThreeTree(const TwoThreeTree& rhs);
    TwoThreeTree(TwoThreeTree&& rhs) noexcept;
    ~TwoThreeTree();

    TwoThreeTree& operator=(const TwoThreeTree& rhs);
    TwoThreeTree& operator=(TwoThreeTree&& rhs) noexcept;

    T& operator[](const Key& key) noexcept;
    T& operator[](Key&& key) noexcept;
    T& at(const Key& key);
    const T& at(const Key& key) const;

    // iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const noexcept;
    // iterator end();
    const_iterator end() const;
    const_iterator cend() const noexcept;

    bool empty() const;
    size_type size() noexcept;

    void clear() noexcept;
    // std::pair< iterator, bool > insert(const value_type& value);
    // iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    size_type erase(const Key& key);
    void swap(TwoThreeTree& other) noexcept;

    size_type count(const Key& key) const;
    // iterator find(const Key& key);
    const_iterator find(const Key& key) const;
    // std::pair< iterator, iterator > equal_range(const Key& key);
    std::pair< const_iterator, const_iterator > equal_range(const Key& key) const;

  private:
    using Node = TwoThreeTreeNode< value_type >;

    Node* dummy_root_;
    size_type size_;

    void clear_subtree(Node* node) noexcept;
  };
}

#endif
