#include <iostream>
#include <utility>
#include <string>
#include <list>
#include <algorithm>
#include <list/list.hpp>


namespace
{
  //using ListOfPairs = std::list< std::pair< std::string, std::list< int > > >;
  using ListOfPairs = demehin::List< std::pair< std::string, demehin::List< unsigned long long > > >;

  size_t defineMaxSize(ListOfPairs pairsList)
  {
    size_t max_size = 0;
    for (auto it = pairsList.begin(); it != pairsList.end(); ++it)
    {
      max_size = std::max(max_size, it->second.size());
    }
    return max_size;
  }

  unsigned long long* copyNums(const unsigned long long* nums, size_t nums_cnt)
  {
    unsigned long long* new_nums = new unsigned long long[nums_cnt];
    for (size_t i = 0; i < nums_cnt; i++)
    {
      new_nums[i] = nums[i];
    }
    return new_nums;
  }

  void printSumValues(std::ostream& out, const unsigned long long* vals, size_t size)
  {
    if (size > 0)
    {
      out << vals[0];
      for (size_t i = 1; i < size; i++)
      {
        out << " " << vals[i];
      }
    }
    else
    {
      out << 0;
    }
  }

  void printValues(std::ostream& out, ListOfPairs pairsList)
  {
    size_t capacity = 128;
    unsigned long long* sum_values = new unsigned long long[capacity]();
    size_t max_size = defineMaxSize(pairsList);
    size_t sum_vals_cnt = 0;
    unsigned long long max_int = std::numeric_limits< unsigned long long >::max();
    for (size_t i = 0; i < max_size; i++)
    {
      unsigned long long sum = 0;
      bool isFirst = true;
      for (auto it = pairsList.begin(); it != pairsList.end(); it++)
      {
        if (!it->second.empty())
        {
          if (!isFirst)
          {
            out << " ";
          }
          else
          {
            isFirst = false;
          }
          out << it->second.front();
          if (sum > max_int - it->second.front())
          {
            throw std::overflow_error("error: owerflow");
          }
          sum += it->second.front();
          it->second.pop_front();
        }
      }
      if (i >= capacity)
      {
        capacity *= 2;
        unsigned long long* new_values = nullptr;
        try
        {
          new_values = copyNums(sum_values, capacity);
        }
        catch (const std::bad_alloc&)
        {
          delete[] sum_values;
          throw;
        }
        delete[] sum_values;
        sum_values = new_values;
      }

      sum_values[sum_vals_cnt++] = sum;
      out << "\n";
    }
    printSumValues(out, sum_values, sum_vals_cnt);
    delete[] sum_values;
  }
}

int main()
{
  //std::list< std::pair< std::string, std::list< int > > > pairsList;
  demehin::List< std::pair< std::string, demehin::List< unsigned long long > > > pairsList;
  std::string nodeName;
  while (std::cin >> nodeName)
  {
    demehin::List< unsigned long long > numsList;
    unsigned long long num = 0;
    //std::string num_str;
    //int num = 0;
    //std::getline(std::cin, num_str);
    //while (std::cin >> num_str && std::cin.peek() != '\n')
    while (std::cin >> num)
    {
      //if (num_str.empty())
      //{
        //b/reak;
      //}
      //try
      //{
        //unsigned long long num = std::stoll(num_str);
        //if (len < num_str.length())
        //{
          //std::cerr << "erorr: overflow\n";
          //return 1;
        //}
        //numsList.push_back(num);
      //}
      //catch (const std::out_of_range&)
      //{
        //std::cerr << "error: overflow\n";
        //return 1;
      //}
      //catch (const std::invalid_argument&)
     // {
        //pairsList.push_back(std::make_pair(nodeName, numsList));
      //}
      //catch (const std::out_of_range&)
      //{
        //std::cerr << "error: overflow\n";
        //return 1;
      //}
      //numsList.push_back(num);
      numsList.push_back(num);
    }
    pairsList.push_back(std::make_pair(nodeName, numsList));
    std::cin.clear();
    //std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    //std::cin.clear();
  }

  if (pairsList.size() == 0)
  {
    std::cout << "0\n";
    return 0;
  }

  std::cout << pairsList.begin()->first;
  for (auto it = ++pairsList.begin(); it != pairsList.end(); ++it)
  {
    std::cout << " " << it->first;
  }
  std::cout << "\n";
  try
  {
    printValues(std::cout, pairsList);
  }
  catch (const std::overflow_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  std::cout << "\n";
}
