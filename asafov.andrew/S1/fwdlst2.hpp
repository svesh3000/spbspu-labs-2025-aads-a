#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <memory>
#include <iostream>
namespace asafov
{
  template<typename T>
  class Forward_list
  {
  public:
    Forward_list()
    {
      next_ = nullptr;
    }
    Forward_list(T data, Forward_list<T>* next)
    {
      data_ = data;
      next_ = next;
    }
    ~Forward_list() = default;

    //const-iterators
    class const_iterator
    {
    public:
      friend class Forward_list<T>;
      const_iterator() = default;
      ~const_iterator() = default;
      const_iterator(const const_iterator&) = default;
      const_iterator(const_iterator&&) = default;
      const_iterator& operator=(const const_iterator&) = default;
      const_iterator& operator=(const_iterator&&) = default;

      const_iterator& operator++()
      {
        node_ = node_->next_;
        return this;
      }
      const_iterator operator++(int)
      {
        asafov::Forward_list<T> result(*this);
        ++(*this);
        return result;
      }
      T& operator*()
      {
        return node_->data_;
      }
      T* operator->()
      {
        return *node_;
      }
      bool operator==(const const_iterator& rhs) const
      {
        if (this->node_ == rhs.node_)
        {
          return true;
        }
        else
        {
          return false;
        }
      }
      bool operator!=(const const_iterator& rhs) const
      {
        if (this->node_ != rhs.node_)
        {
          return true;
        }
        else
        {
          return false;
        }
      }
    private:
      Forward_list<T>* node_;
    };
    const_iterator cbegin();
    const_iterator cend();
    
    //iterators
    class iterator
    {
    public:
      friend class Forward_list<T>;
      iterator()
      {
        node_ = nullptr;
      }
      iterator(Forward_list<T>* node)
      {
        node_ = node;
      }
      ~iterator() = default;
      iterator(const iterator&) = default;
      iterator(iterator&&) = default;
      iterator& operator=(const iterator&) = default;
      iterator& operator=(iterator&&) = default;

      iterator& operator++()
      {
        node_ = node_->next_;
        return *this;
      }
      iterator next()
      {
        std::cout << "next:" << node_->next_ << std::endl;
        return node_->next_;
      }
      iterator operator++(int)
      {
        asafov::Forward_list<T>::iterator result(*this);
        ++(*this);
        return result;
      }
      T& operator*()
      {
        return node_->data_;
      }
      T* operator->()
      {
        return std::addressof(node_->data_);
      }
      bool operator==(iterator rhs)
      {
        if (this->node_ == rhs.node_)
        {
          return true;
        }
        else
        {
          return false;
        }
      }
      bool operator!=(iterator rhs)
      {
        if (this->node_ != rhs.node_)
        {
          return true;
        }
        else
        {
          return false;
        }
      }
    private:
      Forward_list<T>* node_;
    };
    
    iterator begin()
    {
      iterator it;
      it.node_ = this;
      std:: cout << "begin :" << it.node_ << '\n';
      return it;
    }
    iterator end()
    {
      iterator it;
      it.node_ = this->next_;
      //std:: cout << "begin :" << it.node_ << '\n';
      return it;
    }
    
    //element access
    T front();
    T back();

    //capacity
    bool empty();
    size_t size()
    {      
      size_t i = 0;
      for (iterator it = begin(); it != end(); ++it)
      {
        ++i;
      }
      std::cout << i << '\n';
      return i;
    }

    //modifiers
    void push_front(T& data);
    void push_back(const T data)  
    {
      if (this->next_ == nullptr)
      {
        this->data_ = data;
        this->next_ = this;
      }
      else if (this->next_ == this)
      {
        this->next_ = new Forward_list<T>(data, this);
      }
      else
      {
        Forward_list<T>* temp = this->next_;
        while (temp->next_->next_ != this->next_)
        {
          temp = temp->next_;
        }
        temp->next_ = new Forward_list<T>(data, this);
      }
    }
    void pop_front();
    void pop_back();
    void swap(size_t pos1, size_t pos2);
    void clear();
  private:
    T data_;
    Forward_list<T>* next_;
  };
}
#endif
