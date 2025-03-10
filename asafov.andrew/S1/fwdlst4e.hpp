#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
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
      Node(const T& smh, Node* ptr = nullptr) noexcept: data_(smh), next_(ptr) {}
    };

  public:
    Forward_list() noexcept: head_(nullptr), last_(nullptr) {}
    
    ~Forward_list() { clear(); }

    class const_iterator
    {
      friend class Forward_list;
    public:
      const_iterator(Node* node, Node* last) : current_(node), last_(last) {}

      const T& operator*() const { return current_->data_; }

      const_iterator& operator++()
      {
        if (current_)
        {
          current_ = (current_ == last_) ? nullptr : current_->next_;
        }
        return *this;
      }

      bool operator==(const const_iterator& rhs) const { return current_ == rhs.current_; }
      bool operator!=(const const_iterator& rhs) const { return !(*this == rhs); }

    private:
      Node* current_;
      Node* last_;
    };

    const_iterator cbegin() const { return const_iterator(head_, last_); }
    const_iterator cend() const { return const_iterator(nullptr, last_); }

    void push_back(const T& value)
    {
      Node* new_node = new Node(value);
      if (!head_)
      {
        head_ = last_ = new_node;
        new_node->next_ = new_node;
      }
      else
      {
        last_->next_ = new_node;
        new_node->next_ = head_;
        last_ = new_node;
      }
    }

    size_t size() const
    {
      if (!head_) return 0;
      size_t count = 1;
      for (Node* it = head_; it != last_; it = it->next_)
        ++count;
      return count;
    }

    bool empty() const { return head_ == nullptr; }

    void pop_front()
    {
      if (!head_) return;
      
      if (head_ == last_)
      {
        delete head_;
        head_ = last_ = nullptr;
      }
      else
      {
        Node* temp = head_;
        head_ = head_->next_;
        last_->next_ = head_;
        delete temp;
      }
    }

    void clear()
    {
      while (head_) { pop_front(); }
    }

  private:
    Node* head_;
    Node* last_;
  };
}
#endif
