#ifndef TREE_ITERATORS_HPP
#define TREE_ITERATORS_HPP

#include <functional>

namespace zholobov {

  template < typename Node >
  class TreeIterator {
    template < typename, typename >
    friend class Tree;

  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = typename Node::value_type;
    using pointer = value_type*;
    using reference = value_type&;

    TreeIterator();
    explicit TreeIterator(const TreeIterator& other);
    TreeIterator& operator++() noexcept;
    TreeIterator operator++(int) noexcept;
    reference operator*() const noexcept;
    pointer operator->() const noexcept;
    bool operator==(const TreeIterator& other) const noexcept;
    bool operator!=(const TreeIterator& other) const noexcept;

  private:
    TreeIterator(Node* node);
    Node* node_;
  };

  template < typename Node >
  class TreeConstIterator {
    template < typename, typename >
    friend class Tree;

  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = typename Node::value_type;
    using pointer = const value_type*;
    using reference = const value_type&;

    TreeConstIterator();
    explicit TreeConstIterator(const TreeConstIterator& other);
    TreeConstIterator& operator++() noexcept;
    TreeConstIterator operator++(int) noexcept;
    reference operator*() const noexcept;
    pointer operator->() const noexcept;
    bool operator==(const TreeConstIterator& other) const noexcept;
    bool operator!=(const TreeConstIterator& other) const noexcept;

  private:
    TreeConstIterator(Node* node);
    Node* node_;
  };

}

#endif
