#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP
#include <memory>
#include <stdexcept>

namespace asafov
{
  template< typename T , typename Comparator = std::less< T > >
  class ForwardList
  {
    struct Node
    {
      explicit Node(const T& value, Node* ptr = nullptr) noexcept:
        data_(value),
        next_(ptr)
      {}
      T data_;
      Node* next_;
    };
  public:
    ForwardList() noexcept:
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {}
    ForwardList(const ForwardList& list):
      ForwardList()
    {
      for (auto i = list.cbegin(); i != list.cend(); ++i)
      {
        push_back(*i);
      }
    }
    ForwardList(ForwardList&& list) noexcept:
      head_(list.head_),
      tail_(list.tail_),
      size_(list.size_)
    {
      list.head_ = nullptr;
      list.tail_ = nullptr;
      list.size_ = 0;
    }
    ForwardList(const size_t count, const T value):
      ForwardList()
    {
      for (size_t i = 0; i < count; ++i)
      {
        push_back(value);
      }
    }
    ~ForwardList() noexcept
    {
      clear();
    }

    ForwardList& operator=(const ForwardList& list)
    {
      if (this != std::addressof(list))
      {
        ForwardList temp(list);
        swap(temp);
      }
      return *this;
    }
    ForwardList& operator=(ForwardList&& list) noexcept
    {
      if (this != std::addressof(list))
      {
        ForwardList temp(std::move(list));
        swap(temp);
      }
      return *this;
    }

    class ConstIterator
    {
    public:
      ConstIterator():
        current_(nullptr),
        last_(nullptr)
      {}

      T& operator*() const noexcept
      {
        return current_->data_;
      }
      T* operator->() const noexcept
      {
        return std::addressof(current_->data_);
      }

      ConstIterator& operator++()
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
      ConstIterator& operator++(int)
      {
        ConstIterator temp = *this;
        ConstIterator::operator++();
        return temp;
      }

      bool operator==(const ConstIterator& rhs) const
      {
        return current_ == rhs.current_ && last_ == rhs.last_;
      }
      bool operator!=(const ConstIterator& rhs) const
      {
       return !(*this == rhs);
      }
    private:
      friend class ForwardList;

      ConstIterator(Node* node, Node* last):
        current_(node),
        last_(last)
      {}

      Node* current_;
      Node* last_;
    };
    class Iterator final: public ConstIterator
    {
    public:
      using ConstIterator::ConstIterator;
      T& operator*()
      {
        return const_cast<T&>(ConstIterator::operator*());
      }
      T* operator->()
      {
        return const_cast<T&>(ConstIterator::operator->());
      }

      Iterator& operator++()
      {
        ConstIterator::operator++();
        return *this;
      }
      Iterator& operator++(int)
      {
        ConstIterator temp = *this;
        ConstIterator::operator++();
        return temp;
      }
    };

    ConstIterator begin() const noexcept
    {
      return ConstIterator(head_, tail_);
    }
    ConstIterator end() const noexcept
    {
      return ConstIterator(nullptr, tail_);
    }
    Iterator begin() noexcept
    {
      return Iterator(head_, tail_);
    }
    Iterator end() noexcept
    {
      return Iterator(nullptr, tail_);
    }

    ConstIterator cbegin() const noexcept
    {
      return begin();
    }
    ConstIterator cend() const noexcept
    {
      return end();
    }

    T& front()
    {
      if (head_->data_)
      {
        return head_->data_;
      }
      else
      {
        throw std::logic_error("list is empty!");
      }
    }
    const T& front() const
    {
      if (head_->data_)
      {
        return head_->data_;
      }
      else
      {
        throw std::logic_error("list is empty!");
      }
    }
    T& back()
    {
      if (tail_->data_)
      {
        return tail_->data_;
      }
      else
      {
        throw std::logic_error("list is empty!");
      }
    }
    const T& back() const
    {
      if (tail_->data_)
      {
        return tail_->data_;
      }
      else
      {
        throw std::logic_error("list is empty!");
      }
    }
    bool empty() const noexcept
    {
      return !head_;
    }
    size_t size() const noexcept
    {
      return size_;
    }
    void pop_front() noexcept
    {
      size_--;
      Node* temp = head_;
      if (head_ != nullptr)
      {
        if (head_ == tail_)
        {
          delete head_;
          head_ = nullptr;
          tail_ = nullptr;
        }
        else
        {
          head_ = head_->next_;
          tail_->next_ = head_;
          delete temp;
        }
      }
    }
    void push_back(const T& value)
    {
      Node* new_node = new Node(value);
      if (!head_)
      {
        head_ = new_node;
        tail_ = new_node;
        new_node->next_ = head_;
      }
      else
      {
        tail_->next_ = new_node;
        new_node->next_ = head_;
        tail_ = new_node;
      }
      size_++;
    }
    void clear() noexcept
    {
      while (size_ != 0)
      {
        pop_front();
      }
    }

    ForwardList& swap(ForwardList& list) noexcept
    {
      std::swap(head_, list.head_);
      std::swap(tail_, list.tail_);
      std::swap(size_, list.size_);
      return *this;
    }
    template< class C >
    void remove_if(C condition) noexcept
    {
      if (!head_)
      {
        return;
      }

      Node* current = head_;
      Node* prev = tail_;
      bool changed;

      do
      {
        changed = false;
        do
        {
          if (condition(current->data_))
          {
            Node* toDelete = current;
            if (current == head_)
            {
              head_ = head_->next_;
              tail_->next_ = head_;
              if (head_ == tail_ && condition(tail_->data_))
              {
                prev = tail_;
                current = head_;
                continue;
              }
            }
            else if (current == tail_)
            {
              tail_ = prev;
              tail_->next_ = head_;
            }
            else
            {
              prev->next_ = current->next_;
            }

            current = current->next_;
            delete toDelete;
            size_--;
            changed = true;
            if (size_ == 0)
            {
              head_ = tail_ = nullptr;
              return;
            }
          }
          else
          {
            prev = current;
            current = current->next_;
          }
        }
        while (current != head_);
      }
      while (changed);
    }
  private:
    class Equal
    {
    public:
      Equal(const T& value, Comparator cmp):
        value_(value)
        cmp_(cmp)
      {}

      operator(T other)
      {
        reurn !cmp_(value_, other) && !cmp_(other, value_);
      }

    private:
      Const T& value_;
      Comparator cmp_;
    }
  public:
    void remove(const T& value) noexcept
    {
      remove_if(Equal(value, Comaparator()));
    }
    void assign(size_t count, const T& value)
    {
      ForwardList temp;
      for (size_t i = 0; i < count; ++i)
      {
        temp.push_back(value);
      }
      clear();
      swap(temp);
    }

  private:
    Node* head_;
    Node* tail_;
    size_t size_;
  };
}
#endif
