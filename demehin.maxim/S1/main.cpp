#include <iostream>
#include <utility>
#include <string>
#include <list>

namespace
{
  int* copyNums(const int* orig_nums, size_t nums_cnt)
  {
    int* nums = new int[nums_cnt];
    for (size_t i = 0; i < nums_cnt; i++)
    {
      nums[i] = orig_nums[i];
    }
    return nums;
  }

  int* inputNums(std::istream& in, size_t capacity)
  {
    int* nums = new int[capacity];
    size_t size = 0;
    int num = 0;
    while (in >> num)
    {
      if (size >= capacity)
      {
        capacity *= 2;
        int* new_nums = nullptr;
        try
        {
          new_nums = copyNums(nums, capacity);
        }
        catch (const std::bad_alloc&)
        {
          delete[] nums;
          throw;
        }
        delete[] nums;
        nums = new_nums;
      }

      nums[size++] = num;
    }
    in.clear();
    return nums;
  }
}

int main()
{

  using pairsList = std::list< std::pair< std::string, int* > >;
  pairsList numsList;
  size_t nodes_cnt = 0;
  std::string nodeName;
  while (std::cin >> nodeName)
  {
    int* nums = inputNums(std::cin, 128);
    numsList.push_back(std::pair< std::string, int* >(nodeName, nums));
    nodes_cnt++;
  }

}
