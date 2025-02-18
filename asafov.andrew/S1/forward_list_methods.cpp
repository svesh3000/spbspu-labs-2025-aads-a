#include "forward_list.h"

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







