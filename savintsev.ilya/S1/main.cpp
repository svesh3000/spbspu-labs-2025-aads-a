#include <list>
#include <iostream>
#include <string>

int main()
{
  using pair_t = std::pair<std::string, std::list<size_t>>;
  using storage_t = std::list<pair_t>;
  storage_t storage;
  std::string buffer = "";
  size_t max_size = 0;
  std::cin >> buffer;
  while (!std::cin.eof())
  {
    pair_t temp_pair;
    temp_pair.first = buffer;
    std::cin >> buffer;
    size_t temp_max_size = 0;
    while (isdigit(buffer[0]) && !std::cin.eof())
    {
      temp_pair.second.push_back(strtoull(buffer.c_str(), nullptr, 10));
      temp_max_size++;
      std::cin >> buffer;
    }
    max_size = std::max(max_size, temp_max_size);
    storage.push_back(temp_pair);
  }
  for (storage_t::iterator it = storage.begin(); it != storage.end(); ++it)
  {
    std::cout << it->first;
    if (std::next(it) != storage.end())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";
  //std::list<size_t> sums;
  for (size_t i = 0; i < max_size; ++i)
  {
    size_t printed = 0;
    //sums.push_back(0);
    for (storage_t::iterator it = storage.begin(); it != storage.end(); ++it)
    {
      auto temp_it = it->second.begin();
      if (it->second.size() > i)
      {
        for (size_t next = 0; next < i; ++next)
        {
          temp_it++;
        }
        if (printed != 0)
        {
          std::cout << "_";
        }
        std::cout << *(temp_it);
        printed++;
      }
    }
  std::cout << "\n";
  }
}

/*
first 1 1 1
second 2 2 2 2
third
fourth 4 4
*/
