#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
#include <iostream>
#include <algorithm>
#include <memory>
namespace asafov {


template<typename T>
class Forward_list {
    struct Node {
      T data_;
      Node* next_;
      Node(const T& data) : data_(data), next_(nullptr) {}
    };
  public:
    class const_iterator;

    Forward_list() : head_(nullptr), last_(nullptr) {}

    ~Forward_list() = default;

    void push_back(const T& value) {
      Node* new_node = new Node(value);
      if (!head_) {
        head_ = new_node;
        last_ = new_node;
        new_node->next_ = head_; // Указываем на себя
      } else {
        last_->next_ = new_node;
        new_node->next_ = head_;
        last_ = new_node;
      }
    }
  
  size_t size() const
    {
      size_t i = 0;
      for (const_iterator it = begin(); it != end(); ++it)
      {
        ++i;
      }
      return i;
    }

    const_iterator begin() const {
      return const_iterator(head_, last_);
    }

    const_iterator end() const {
      return const_iterator(nullptr, last_); // Указываем на nullptr для конца
    }

    class const_iterator {
      public:
      const_iterator() = default;
        const_iterator(Node* node, Node* last) : current_(node), last_(last) {}

        const T& operator*() const {
          return current_->data_;
        }
        T* operator->() const {
          return std::addressof(current_->data_);
        }

        const_iterator& operator++() {
          if (current_ && current_ != last_) {
            current_ = current_->next_;
          } else {
            current_ = nullptr;
          }
          return *this;
        }

        bool operator!=(const const_iterator& other) const {
          return current_ != other.current_;
        }

        bool operator==(const const_iterator& other) const {
          return current_ == other.current_;
        }

      private:
        Node* current_;
        Node* last_; // Храним указатель на последний элемент
    };

  private:

    Node* head_;
    Node* last_;
};

}
#endif
