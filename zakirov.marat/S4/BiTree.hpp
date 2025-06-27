#ifndef BITREE_HPP
#define BITREE_HPP
#include <initializer_list>
#include <utility>
#include <functional>
#include "BiNode.hpp"
#include "BiIterator.hpp"

namespace zakirov
{
  template< class K, class T, class C >
  class BiIter;

  template< class K, class T, class C >
  class CBiIter;

  template < class K, class T, class C = std::less< K > >
  class BiTree
  {
  public:
    BiTree() noexcept;
    BiTree(const BiTree & rhs);
    BiTree(BiTree && rhs) noexcept;
    ~BiTree();

    BiTree< K, T, C > & operator=(const BiTree< K, T, C > & other);
    BiTree< K, T, C > & operator=(BiTree< K, T, C > && other);
    T & operator[](const K & key);

    T & at(const K & key);
    const T & at(const K & key) const;

    BiIter< K, T, C > begin() noexcept;
    BiIter< K, T, C > end() noexcept;
    CBiIter< K, T, C > cbegin() const noexcept;
    CBiIter< K, T, C > cend() const noexcept; 

    T size() const noexcept;
    bool empty() const noexcept;

    std::pair< BiIter< K, T, C >, bool > insert(const std::pair< K, T > & value);
    std::pair< BiIter< K, T, C >, bool > insert(BiIter< K, T, C > pos, const std::pair< K, T > & value);
    BiIter< K, T, C > erase(BiIter< K, T, C > pos) noexcept;
    BiIter< K, T, C > erase(CBiIter< K, T, C > pos) noexcept;
    size_t erase(const K & key) noexcept;
    void clear() noexcept;

    BiIter find(const K & key);
    CBiIter find(const K & key) const;
    pair< CBiIter, CBiIter > equal_range (const K & k) const;
    pair< BiIter, BiIter > equal_range (const K & k);
    T count (const K & k) const;
  private:
    std::pair< BiIter< K, T, C >, bool > find_place_check(const K & k);
    std::pair< BiIter< K, T, C >, bool > find_place(const K & k,  BiNode< K, T > * pos);
    BiNode< K, T > * rotate_left(BiNode< K, T > * root);
    BiNode< K, T > * rotate_right(BiNode< K, T > * root);
    BiNode< K, T > * head_;
    size_t size_;
    C cmp_;
  };

  template < class K, class T, class C >
  BiTree< K, T, C >::BiTree() noexcept:
    head_(nullptr),
    size_(0)
    cmp_(C())
  {}

  template < class K, class T, class C >
  BiTree< K, T, C >::BiTree(const BiTree< K, T, C > & other):
    BiTree()
  {
    for (CBiIter< K, T, C > i = other.cbegin(); i != other.cend(); ++i)
    {
      insert(*it);
    }
  }

  template < class K, class T, class C >
  BiTree< K, T, C >::BiTree(BiTree< K, T, C > && other) noexcept:
    head_(other.head_),
    size_(other.size_)
  {
    other.head_ = nullptr;
    other.size_ = nullptr;
  }

  template < class K, class T, class C >
  BiTree< K, T, C >::~BiTree()
  {
    clear();
  }

  template < class K, class T, class C >
  BiTree< K, T, C > & BiTree< K, T, C >::operator=(const BiTree< K, T, C > & other)
  {
    BiTree< K, T, C > temp(other);
    swap(temp);
    return *this;
  }

  template < class K, class T, class C >
  BiTree< K, T, C > & BiTree< K, T, C >::operator=(BiTree< K, T, C > && other)
  {
    BiTree< K, T, C > temp(std::move(other));
    swap(temp);
    return *this;
  }

  template < class K, class T, class C >
  T & BiTree< K, T, C >::operator[](const K & key)
  {
    BiIter< K, T, C > result = insert(std::make_pair(key, T())).first;
    return *result;
  }

  template < class K, class T, class C >
  T & BiTree< K, T, C >::at(const K & key)
  {
    BiIter< K, T, C > iter = find(key);
    if (!iter)
    {
      throw std::out_of_range("No element in tree")
    }

    return *iter;
  }

  template < class K, class T, class C >
  const T & BiTree< K, T, C >::at(const K & key) const
  {
    CBiIter< K, T, C > iter = find(key);
    if (!iter)
    {
      throw std::out_of_range("No element in tree")
    }

    return *iter;
  }

  template < class K, class T, class C >
  BiIter< K, T, C > BiTree< K, T, C >::begin() noexcept
  {
    BiNode< K, T > * first = head_;
    if (!first)
    {
      BiIter< K, T, C > res(first);
      return res;
    }

    while (first->left_)
    {
      first = first->left_;
    }

    BiIter< K, T, C > res(first);
    return res
  }

  template < class K, class T, class C >
  BiIter< K, T, C > BiTree< K, T, C >::end() noexcept
  {
    BiNode< K, T > * last = head_;
    if (!last)
    {
      BiIter< K, T, C > res(last);
      return res;
    }

    while (last->right_)
    {
      last = last->right_;
    }

    BiIter< K, T, C > res(last);
    return res
  }

  template < class K, class T, class C >
  CBiIter< K, T, C > BiTree< K, T, C >::cbegin() const noexcept
  {
    BiNode< K, T > * first = head_;
    if (!first)
    {
      CBiIter< K, T, C > res(first);
      return res;
    }

    while (first->left_)
    {
      first = first->left_;
    }

    CBiIter< K, T, C > res(first);
    return res
  }

  template < class K, class T, class C >
  CBiIter< K, T, C > BiTree< K, T, C >::cend() const noexcept
  {
    BiNode< K, T > * last = head_;
    if (!last)
    {
      CBiIter< K, T, C > res(last);
      return res;
    }

    while (last->right_)
    {
      last = last->right_;
    }

    CBiIter< K, T, C > res(last);
    return res
  }

  template < class K, class T, class C >
  T BiTree< K, T, C >::size() const noexcept
  {
    return size_;
  }

  template < class K, class T, class C >
  bool BiTree< K, T, C >::empty() const noexcept
  {
    return size_ == 0;
  }

  template < class K, class T, class C >
  std::pair< BiIter< K, T, C >, bool > BiTree< K, T, C >::insert(const std::pair< K, T > & value)
  {
    if (empty())
    {
      head_ = new BiNode< K, T >(value);
      ++size_;
      return std::make_pair(begin(), true);
    }

    std::pair< BiIter< K, T, C >, bool > place = find_place(head_);
    if (!place.second)
    {
      place.second = value.second;
      return place;
    }

    BiIter< K, T, C > result;
    if (cmp_(value.first, place.first.node_->value.first))
    {
      place.first.node_->left_ = new BiNode< K, T >(value);
      place.first.node_->left_->parent_ = place.first.node_->left_;
      result.node_ = place.first.node_->left_;
    }
    else
    {
      place.first.node_->right_ = new BiNode< K, T >(value);
      place.first.node_->right_->parent_ = place.first.node_->right_;
      result.node_ = place.first.node_->right_;
    }

    ++size_;
    return std::make_pair(result, true);
  }

  template < class K, class T, class C >
  std::pair< BiIter< K, T, C >, bool > BiTree< K, T, C >::insert(BiIter< K, T, C > pos, const std::pair< K, T > & value)
  {
    if (!(*pos) && empty())
    {
      head_ = new BiNode< K, T >(value);
      ++size_;
      return std::make_pair(begin(), true);
    }
    else
    {
      throw std::invalid_argument("Nullptr and not empty tree");
    }

    BiIter< K, T, C > result(pos);
    if (!pos->left_ && cmp_(value.first, pos.node_->value_.first))
    {
      pos.node_->left_ = new BiNode< K, T >(value);
      pos.node_->left_->parent_ = pos.node_->left_;
      result.node_ = pos.node_->left_;
    }
    else if (!pos->right_ && cmp_(pos.node_->value_.first, value.first))
    {
      pos.node_->right_ = new BiNode< K, T >(value);
      pos.node_->right_->parent_ = pos.node_->right_;
      result.node_ = pos.node_->right_;
    }
    else
    {
      return insert(value);
    }

    ++size_;
    return std::make_pair(result, true);
  }

  template < class K, class T, class C >
  BiIter< K, T, C > BiTree< K, T, C >::erase(BiIter< K, T, C > pos) noexcept
  {
    BiNode< K, T > * to_deleted = pos.node_;
    BiNode< K, T > * next = pos.node_;
    BiNode< K, T > * child;
    detail::next(next);
    if (!to_deleted)
    {
      return pos;
    }

    if (!to_deleted->left_ && !to_deleted->right_)
    {
      if (parent->left == to_deleted)
      {
        parent->left = nullptr;
      }
      else
      {
        parent->right = nullptr;
      }

      delete to_deleted;
      --size_;
      BiIter< K, T, C > res(next);
      return res;
    }
    else if (!to_deleted->left_)
    {
      child = to_deleted->right_;
      if (to_deleted->parent_) 
      {
        if (to_deleted->parent_->left_ == to_deleted) 
        {
          to_deleted->parent_->left_ = child;
        } 
        else 
        {
          to_deleted->parent_->right_ = child;
        }
      }

      child->parent_ = to_deleted->parent_;
      to_deleted->parent_->right_ = child;
    }
    else if (!to_deleted->right_)
    {
      child = to_deleted->left_;
      if (to_deleted->parent_) 
      {
        if (to_deleted->parent_->left_ == to_deleted) 
        {
          to_deleted->parent_->left_ = child;
        } 
        else 
        {
          to_deleted->parent_->right_ = child;
        }
      }

      child->parent_ = to_deleted->parent_;
      to_deleted->parent_->left_ = child;
    }
    else
    {
      child = to_deleted->right_; 
      while (child->left_)
      {
        child = child->left_;
      }

      if (child != to_deleted->right_)
      {
        child->parent_->left_ = child->right_;
        if (child->right_)
        {
          child->right_->parent_ = child->parent_;
        }

        child->right_ = to_deleted->right_;
        to_deleted->right_->parent_ = child;
      }

      child->left_ = to_deleted->left_;
      to_deleted->left_->parent_ = child;
      child->parent_ = to_deleted->parent_;
      if (to_deleted->parent_) 
      {
        if (to_deleted->parent_->left_ == to_deleted) 
        {
          to_deleted->parent_->left_ = child;
        } 
        else 
        {
          to_deleted->parent_->right_ = child;
        }
      }
    }

    if (to_deleted == head_)
    {
      head_ = child;
    }

    delete to_deleted;
    --size_;
    BiIter< K, T, C > res(next);
    return res;
  }

  template < class K, class T, class C >
  BiIter< K, T, C > BiTree< K, T, C >::erase(CBiIter< K, T, C > pos) noexcept
  {
    BiNode< K, T > * to_deleted = pos.node_;
    BiNode< K, T > * next = pos.node_;
    BiNode< K, T > * child;
    detail::next(next);
    if (!to_deleted)
    {
      return pos;
    }

    if (!to_deleted->left_ && !to_deleted->right_)
    {
      if (parent->left == to_deleted)
      {
        parent->left = nullptr;
      }
      else
      {
        parent->right = nullptr;
      }

      delete to_deleted;
      --size_;
      BiIter< K, T, C > res(next);
      return res;
    }
    else if (!to_deleted->left_)
    {
      child = to_deleted->right_;
      if (to_deleted->parent_) 
      {
        if (to_deleted->parent_->left_ == to_deleted) 
        {
          to_deleted->parent_->left_ = child;
        } 
        else 
        {
          to_deleted->parent_->right_ = child;
        }
      }

      child->parent_ = to_deleted->parent_;
      to_deleted->parent_->right_ = child;
    }
    else if (!to_deleted->right_)
    {
      child = to_deleted->left_;
      if (to_deleted->parent_) 
      {
        if (to_deleted->parent_->left_ == to_deleted) 
        {
          to_deleted->parent_->left_ = child;
        } 
        else 
        {
          to_deleted->parent_->right_ = child;
        }
      }

      child->parent_ = to_deleted->parent_;
      to_deleted->parent_->left_ = child;
    }
    else
    {
      child = to_deleted->right_; 
      while (child->left_)
      {
        child = child->left_;
      }

      if (child != to_deleted->right_)
      {
        child->parent_->left_ = child->right_;
        if (child->right_)
        {
          child->right_->parent_ = child->parent_;
        }

        child->right_ = to_deleted->right_;
        to_deleted->right_->parent_ = child;
      }

      child->left_ = to_deleted->left_;
      to_deleted->left_->parent_ = child;
      child->parent_ = to_deleted->parent_;
      if (to_deleted->parent_) 
      {
        if (to_deleted->parent_->left_ == to_deleted) 
        {
          to_deleted->parent_->left_ = child;
        } 
        else 
        {
          to_deleted->parent_->right_ = child;
        }
      }
    }

    if (to_deleted == head_)
    {
      head_ = child;
    }

    delete to_deleted;
    --size_;
    BiIter< K, T, C > res(next);
    return res;
  }

  template < class K, class T, class C >
  size_t BiTree< K, T, C >::erase(const K & key) noexcept
  {
    BiIter< K, T > it = find(k);
    if (it == end())
    {
      return 0;
    }

    erase(it)
    return 1;
  }

  template < class K, class T, class C >
  void BiTree< K, T, C >::clear() noexcept
  {
    BiIter< K, T > it = first();
    while (it != end())
    {
      it = erase(it);
    }
  }

  template < class K, class T, class C >
  std::pair< BiIter< K, T, C >, bool > BiTree< K, T, C >::find_place_check(const K & k)
  {
    BiNode< K, T > * searcher = head_;
    if (!searcher)
    {
      return std::make_pair(begin(), true);
    }

    return find_place(k, searcher);
  }

  template < class K, class T, class C >
  std::pair< BiIter< K, T, C >, bool > BiTree< K, T, C >::find_place(const K & k,  BiNode< K, T > * pos)
  {
    if (cmp_(pos->value_.first, k))
    {
      if (pos->right_)
      {
        find_place(k, pos->right_);
      }

      BiIter<K, T, C> res(pos);
      return make_pair(res, true)
    }
    else if (cmp_(k, pos->value_.first, k))
    {
      if (pos->left_)
      {
        find_place(k, pos->left_);
      }

      BiIter<K, T, C> res(pos);
      return make_pair(res, true)
    }

    BiIter<K, T, C> res(pos);
    return make_pair(res, false)
  }

  template< class K, class T, class C >
  BiNode< K, T > * BiTree< K, T, C >::rotate_right(BiNode< K, T > * root)
  {
    if (!root)
    {
      throw std::invalid_argument("Invalid rotation");
    }

    if (!root->left_)
    {
      throw std::invalid_argument("Invalid rotation");
    }

    BiNode< K, T > * new_root = root->left_;
    new_root->parent_ = root->parent_;
    if (root->parent_)
    {
      if (root->parent_->left_ == root)
      {
        root->parent_->left_ = new_root;
      }
      else
      {
        root->parent_->right_ = new_root;
      }
    }
 
    root->parent_ = new_root;
    root->left_ = new_root->right_;
    new_root->right_ = root;
    new_root->right_->parent_ = new_root;
    return new_root;
  }

  template< class K, class T >
  BiNode< K, T >* rotate_left(BiNode< K, T > * root)
  {
    if (!root)
    {
      throw std::invalid_argument("Invalid rotation");
    }

    if (!root->right)
    {
      throw std::invalid_argument("Invalid rotation");
    }

    BiTree< T >* new_root = root->right_;
    new_root->parent_ = root->parent_;
    if (root->parent_)
    {
      if (root->parent_->left_ == root)
      {
        root->parent_->left_ = new_root;
      }
      else
      {
        root->parent_->right_ = new_root;
      }
    }

    root->parent_ = new_root;
    root->right_ = new_root->left_;
    new_root->left_ = root;
    new_root->left_->parent_ = new_root;
    return new_root;
  }
}

#endif
