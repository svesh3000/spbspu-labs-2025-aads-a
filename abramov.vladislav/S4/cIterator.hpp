#ifndef CITERATOR_HPP
#define CITERATOR_HPP

namespace abramov
{
  template< class Key, class Value, class Cmp = std::less< Key > >
  struct ConstIterator
  {
    ConstIterator();
    ConstIterator(const Node< Key, Value > *node);
    ConstIterator(const ConstIterator< Key, Value, Cmp > &c_iter) = default;
    ~ConstIterator() = default;
    ConstIterator< Key, Value, Cmp > &operator=(const ConstIterator< Key, Value, Cmp > &c_iter) = default;
    ConstIterator< Key, Value, Cmp > &operator++() noexcept;
    ConstIterator< Key, Value, Cmp > operator++(int) noexcept;
    bool operator==(const ConstIterator< Key, Value, Cmp > &c_iter) const noexcept;
    bool operator!=(const ConstIterator< Key, Value, Cmp > &c_iter) const noexcept;
    const std::pair< Key, Value > &operator*() const noexcept;
    const std::pair< Key, Value > *operator->() const noexcept;
  private:
    Node< Key, Value > *node_;
  };

  template< class Key, class Value, class Cmp >
  ConstIterator< Key, Value, Cmp >::ConstIterator():
    node_(nullptr)
  {}

  template< class Key, class Value, class Cmp >
  ConstIterator< Key, Value, Cmp >::ConstIterator(const Node< Key, Value > *node):
    node_(node)
  {}

  template< class Key, class Value, class Cmp >
  ConstIterator< Key, Value, Cmp > &ConstIterator::operator++() noexcept
  {
    if (node_->right_)
    {
      node_ = node_->right_;
      while (node_->left_)
      {
        node_ = node_->left_;
      }
    }
    else
    {
      while (node_->parent_ && node_parent_->left_ != node_)
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
    }
  }
  return *this;

  template< class Key, class Value, class Cmp >
  ConstIterator< Key, Value, Cmp > ConstIterator::operator++(int) noexcept
  {
    ConstIterator< Key, Value, Cmp > c_iter(*this):
    ++(*this);
    return c_iter;
  }

  template< class Key, class Value, class Cmp >
  bool ConstIterator< Key, Value, Cmp >::operator==(const ConstIterator< Key, Value, Cmp > &c_iter) const noexcept
  {
    return node_ == c_iter.node_;
  }

  template< class Key, class Value, class Cmp >
  bool ConstIterator< Key, Value, Cmp >::operator!=(const ConstIterator< Key, Value, Cmp > &c_iter) const noexcept
  {
    return !(c_iter == *this);
  }

  template< class Key, class Value, class Cmp >
  const std::pair< Key, Value > &ConstIterator< Key, Value, Cmp >::operator*() const noexcept
  {
    return node_->data_;
  }

  template< class Key, class Value, class Cmp >
  const std::pair< Key, Value > *ConstIterator< Key, Value, Cmp >::operator->() const noexcept
  {
    return std::addressof(node_->data_);
  }
}
#endif
