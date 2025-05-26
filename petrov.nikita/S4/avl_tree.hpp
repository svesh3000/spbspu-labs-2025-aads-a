#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <functional>
#include <cstddef>
#include <iterator>

namespace petrov
{
  template< typename Key, typename T >
  struct AVLTreeNode
  {
    std::pair< const Key, T > data;
    AVLTreeNode< Key, T > * left;
    AVLTreeNode< Key, T > * right;
  };

  template< typename Key, typename T, typename Comparator >
  struct AVLTree;

  template< typename Key, typename T, typename Comparator >
  struct ConstAVLTreeIterator: std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend struct AVLTree< Key, T, Comparator >;
  public:
    using node_t = AVLTreeNode< Key, T >;
    using this_t = ConstAVLTreeIterator< Key, T, Comparator >;
    ConstAVLTreeIterator():
      node_(nullptr)
    {}
    ConstAVLTreeIterator(const this_t & rhs) = default;
    ~ConstAVLTreeIterator() = default;
    this_t & operator=(const this_t & rhs) = default;
    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);
    const T & operator*() const;
    const T * operator->() const;
    bool operator==(const this_t & rhs) const;
    bool operator!=(const this_t & rhs) const;
  private:
    const AVLTreeNode< Key, T > * node_;
    explicit ConstAVLTreeIterator(const node_t & node):
      node_(node)
    {}
  };

  template< typename Key, typename T, typename Comparator >
  struct AVLTreeIterator: std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend struct AVLTree< Key, T, Comparator >;
  public:
    using node_t = AVLTreeNode< Key, T >;
    using this_t = AVLTreeIterator< Key, T, Comparator >;
    AVLTreeIterator():
      node_(nullptr)
    {}
    AVLTreeIterator(const this_t & rhs) = default;
    ~AVLTreeIterator() = default;
    this_t & operator=(const this_t & rhs) = default;
    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);
    const T & operator*() const;
    const T * operator->() const;
    bool operator==(const this_t & rhs) const;
    bool operator!=(const this_t & rhs) const;
  private:
    AVLTreeNode< Key, T > * node_;
    explicit AVLTreeIterator(const node_t & node):
      node_(node)
    {}
  };

  template< typename Key, typename T, typename Comparator = std::less< T > >
  struct AVLTree
  {
  public:
    using this_t = AVLTree< Key, T, Comparator >;
    using node_t = AVLTreeNode< Key, T >;
    using const_it_t = ConstAVLTreeIterator< Key, T, Comparator >;
    using it_t = AVLTreeIterator< Key, T, Comparator >;
    AVLTree():
      root_(nullptr),
      begin_node_(nullptr),
      end_node_(nullptr),
      size_(0)
    {}
    AVLTree(const this_t & rhs);
    AVLTree(this_t && rhs);
    ~AVLTree();
    this_t & operator=(const this_t & rhs);
    this_t & operator=(this_t && rhs);
    T & operator[](const Key & key);
    const T & operator[](const Key & key) const;
    const_it_t cbegin() const;
    const_it_t cend() const;
    it_t begin();
    it_t end();
    bool empty() const noexcept;
    size_t size() const noexcept;
    std::pair< const_it_t, bool > insert(const std::pair< Key, T > & val);
    std::pair< const_it_t, bool > insert(std::pair< Key, T > && val);
    T & at(const Key & key);
    const T & at(const Key & key) const;
    it_t find(const Key & key);
    const_it_t find(const Key & key) const;
    void clear();
    void swap(this_t & rhs) noexcept;
  private:
    node_t * root_;
    node_t * begin_node_;
    node_t * end_node_;
    size_t size_;
    Comparator cmp;
  };
}

#endif