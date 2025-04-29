#ifndef LNR_ITERATOR_HPP
#define LNR_ITERATOR_HPP

namespace demehin
{
  template< typename Key, typename T, typename Cmp >
  class Tree;

  template< typename Key, typename T, typename Cmp, bool isConst >
  class LnrIterator
  {
    friend class LnrIterator< Key, T, Cmp, true >;
    friend class LnrIterator< Key, T, Cmp, false >;
    friend class Tree< Key, T, Cmp >;
  public:
    using Node = demehin::TreeNode< Key, T >;
    using this_t = LnrIterator< Key, T, Cmp, isConst >;
    using node_t = typename std::conditional< isConst, const Node, Node >::type;
    using stack_t = typename std::conditional< isConst, Stack< const Node* >, Stack< Node* > >::type;
    using data_t = typename std::conditional< isConst, const std::pair< Key, T >, std::pair< Key, T > >::type;

    LnrIterator() noexcept;

    this_t& operator++() noexcept;
    this_t operator++(int) noexcept;

    data_t& operator*() const;
    data_t* operator->() const;

    bool operator==(const this_t&) const noexcept;
    bool operator!=(const this_t&) const noexcept;

  private:
    node_t* node_;
    stack_t stack_;

    explicit LnrIterator(node_t* node);
  }
}

#endif
