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
      bool operator==(const iterator& rhs) const;
      bool operator!=(const iterator& rhs) const;
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
#endif
