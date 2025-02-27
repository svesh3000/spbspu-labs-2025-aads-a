#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
namespace asafov
{
  template<typename T>
  class Forward_list
  {
  public:
    Forward_list() = default;
    Forward_list(T data, Forward_list<T>* next);
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

      const_iterator& operator++();
      const_iterator operator++(int);
      T& operator*();
      T* operator->();
      bool operator==(const const_iterator& rhs) const;
      bool operator!=(const const_iterator& rhs) const;
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
      iterator() = default;
      ~iterator() = default;
      iterator(const iterator&) = default;
      iterator(iterator&&) = default;
      iterator& operator=(const iterator&) = default;
      iterator& operator=(iterator&&) = default;

      iterator& operator++();
      iterator operator++(int);
      T& operator*();
      T* operator->();
      bool operator==(iterator rhs);
      bool operator!=(iterator rhs);
    private:
      Forward_list<T>* node_;
    };
    iterator begin();
    iterator end();
    iterator last();

    

    //element access
    T front();
    T back();

    //capacity
    bool empty();
    size_t size();

    //modifiers
    void push_front(T& data);
    void push_back(T& data);
    void pop_front();
    void pop_back();
    void swap(size_t pos1, size_t pos2);
    void clear();
  private:
    T data_;
    Forward_list<T>* next_;
  };
}

//const-iterators
template <typename T>
T& asafov::Forward_list<T>::const_iterator::operator*()
{
  return node_->data_;
}

template <typename T>
T* asafov::Forward_list<T>::const_iterator::operator->()
{
  return *node_->data_;
}

template <typename T>
typename asafov::Forward_list<T>::const_iterator& asafov::Forward_list<T>::const_iterator::operator++()
{
  node_ = node_->next_;
  return *this;
  
}

template <typename T>
typename asafov::Forward_list<T>::const_iterator asafov::Forward_list<T>::const_iterator::operator++(int)
{
  asafov::Forward_list<T> result(*this);
  ++(*this);
  return result;
}

template <typename T>
bool asafov::Forward_list<T>::const_iterator::operator==(const const_iterator& rhs) const
{
  return node_ == rhs.node_;
}

template <typename T>
bool asafov::Forward_list<T>::const_iterator::operator!=(const const_iterator& rhs) const
{
  return !(rhs == *this);
}

template <typename T>
typename asafov::Forward_list<T>::const_iterator asafov::Forward_list<T>::cbegin()
{
  return *this;
}

template <typename T>
typename asafov::Forward_list<T>::const_iterator asafov::Forward_list<T>::cend()
{
  asafov::Forward_list<T>::const_iterator it = *this;
  while (it++->next != *this);
  return it;
}

//iterators
template <typename T>
T& asafov::Forward_list<T>::iterator::operator*()
{
  return node_->data_;
}

template <typename T>
T* asafov::Forward_list<T>::iterator::operator->()
{
  return *node_->data_;
}

template <typename T>
typename asafov::Forward_list<T>::iterator& asafov::Forward_list<T>::iterator::operator++()
{
  node_ = node_->next_;
  return *this;
  
}

template <typename T>
typename asafov::Forward_list<T>::iterator asafov::Forward_list<T>::iterator::operator++(int)
{
  asafov::Forward_list<T> result(*this);
  ++(*this);
  return result;
}

template <typename T>
bool asafov::Forward_list<T>::iterator::operator==(iterator rhs)
{
  if (node_ == rhs.node_)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template <typename T>
bool asafov::Forward_list<T>::iterator::operator!=(iterator rhs)
{
  return !(rhs == *this);
}

template <typename T>
typename asafov::Forward_list<T>::iterator asafov::Forward_list<T>::begin()
{
  asafov::Forward_list<T>::iterator it;
  it.node_ = this;
  return it;
}

template <typename T>
typename asafov::Forward_list<T>::iterator asafov::Forward_list<T>::end()
{
  asafov::Forward_list<T>::iterator it = this->begin();
  for (;it.node_ != *this;++it);
  return it;
}

template <typename T>
typename asafov::Forward_list<T>::iterator asafov::Forward_list<T>::last()
{
  asafov::Forward_list<T>::iterator it = *this;
  while (it++->next != this.end());
  return it;
}

//methods

template <typename T>
asafov::Forward_list<T>::Forward_list<T>(T data, asafov::Forward_list<T>* next)
{
  data_ = data;
  next_ = next;  
}

template <typename T>
void asafov::Forward_list<T>::push_back(T& data)
{
  *this->end().next = new asafov::Forward_list<T>(data, *this->begin());
}

template <typename T>
void asafov::Forward_list<T>::pop_back()
{
  asafov::Forward_list<T>::iterator it = this->begin();
  do
  {
    ++it;
  } while (*it->next != this->end());
  *it.next = *this->begin();
}

template <typename T>
void asafov::Forward_list<T>::push_front(T& data)
{
  
}


template <typename T>
void asafov::Forward_list<T>::pop_front()
{
  *this.end()->next = ++this->begin();
  
}

template <typename T>
T asafov::Forward_list<T>::front()
{
  
}

template <typename T>
T asafov::Forward_list<T>::back()
{
  
}

template <typename T>
bool asafov::Forward_list<T>::empty()
{
  
}

template <typename T>
size_t asafov::Forward_list<T>::size()
{
  
}

template <typename T>
void asafov::Forward_list<T>::swap(size_t pos1, size_t pos2)
{
  auto it = this->begin();
}

template <typename T>
void asafov::Forward_list<T>::clear()
{
  
}

#endif
