#include <cstddef>
#include <iostream>
#include <list>
#include <new>
#include <string>

int* createArr(std::istream& input, size_t size)
{
  int* array = new int[size];
  int number = 0;
  size_t count = 0;
  while (input >> number)
  {
    if (count >= size)
    {
      size_t previousSize = size;
      size += 5;
      int* newArray = nullptr;
      try
      {
        newArray = new int[size];
        for (size_t i = 0; i < previousSize; ++i)
        {
          newArray[i] = array[i];
        }
      }
      catch (const std::bad_alloc&)
      {
        delete[] array;
        throw;
      }
      delete[] array;
      array = newArray;
    }
    array[size++] = number;
  }
  return array;
}

int main()
{
  using pair = std::pair< std::string, int* >;
  using pairList = std::list< pair >;
  pairList list;
  std::string nameNode;
  size_t capacity = 20;
  while (std::cin >> nameNode)
  {
    int* numbers = createArr(std::cin, capacity);
    list.push_back(pair(nameNode, numbers));
  }
}
