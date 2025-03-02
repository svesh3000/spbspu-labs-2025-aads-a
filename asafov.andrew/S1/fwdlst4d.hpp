#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
#include <iostream>
#include <memory>
namespace asafov
{
  template<typename T>
  class Forward_list
  {
    class Node
    {
    public:
      T data_;
      Node* next_;
      Node() noexcept: data_(NULL), next_(nullptr) {}
      Node(const T& smh, Node* ptr) noexcept: data_(smh), next_(ptr) {}
      Node(const T& smh) noexcept: data_(smh), next_(nullptr) {}
      ~Node()
      {
        delete next_;
      };
    };
  public:
    Forward_list() noexcept:
    head_(nullptr),
    last_(nullptr)
    {}

    ~Forward_list()
    {
      delete head_;
    }

    class const_iterator
    {
      friend class Forward_list;
    public:
      const_iterator():
      current_(nullptr),
      last_(nullptr)
      {}
      const_iterator(Node* node, Node* last):
      current_(node),
      last_(last)
      {}
      ~const_iterator() = default;

      const T& operator*() const
      {
        return current_->data_;
      }

      T* operator->() const
      {
        return std::addressof(current_->data_);
      }

      const_iterator& operator++()
      {
        if (current_ && current_ != last_)
        {
          current_ = current_->next_;
        }
        else
        {
          current_ = nullptr;
        }
        return *this;
      }

      bool operator==(const const_iterator& rhs) const
      {
        return current_ == rhs.current_;
      }

      bool operator!=(const const_iterator& rhs) const
      {
        return !(*this == rhs);
      }
    private:
      Node* current_;
      Node* last_;
    };
    const_iterator cbegin() const
    {
      return const_iterator(head_, last_);
    }
    const_iterator cend() const
    {
      return const_iterator(nullptr, last_);
    }

    void push_front(const T& value);
    void pop_front();
    void push_back(const T& value)
    {
      Node* new_node = new Node(value);
      if (!head_)
      {
        head_ = new_node;
        last_ = new_node;
        new_node->next_ = head_;
      }
      else
      {
        last_->next_ = new_node;
        new_node->next_ = head_;
        last_ = new_node;
      }
    }
    void pop_back();
    void swap();

    size_t size() const
    {
      size_t i = 0;
      for (const_iterator it = cbegin(); it != cend(); ++it)
      {
        ++i;
      }
      return i;
    }
    bool empty() const
    {
      if (size() == 0)
      {
        return true;
      }
      else
      {
        return false;
      }
    }

    T& front()
    {
      return head_->data_;
    }
    T& back();
    void clear();
  private:
    Node* head_;
    Node* last_;
  };
}
#endif
