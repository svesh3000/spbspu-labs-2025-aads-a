#ifndef LIST
#define LIST

namespace shramko
{
  template< typename T >
  class FwdListNode
  {
  public:
    T data_;
    FwdListNode< T >* next_;
    FwdListNode();
  };
  
  template< typename T >
  class FwdList
  {
  public:
    FwdList();
    ~FwdList();
  
    T& front() const noexcept;
    T& back() const noexcept;
  
    std::size_t size() const noexcept;
    bool empty() const noexcept;
  
    void push_front(const T& value);
    void push_front(T&& value);
    void push_back(const T& value);
    void push_back(T&& value);
    void swap(FwdList& other);
    void clear() noexcept;
  
  private:
    FwdListNode< T >* head_;
    FwdListNode< T >* tail_;
    std::size_t size_;
  };
}

#endif