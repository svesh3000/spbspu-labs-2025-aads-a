#include <list>
#include <iostream>
#include <string>

int main()
{
  using pair_t = std::pair<std::string, std::list<size_t>>;
  using storage_t = std::list<pair_t>;
  storage_t storage;
  std::string buffer = "";
  std::cin >> buffer;
  while (!std::cin.eof())
  {
    pair_t temp_pair;
    temp_pair.first = buffer;
    std::cin >> buffer;
    while (isdigit(buffer[0]) && !std::cin.eof())
    {
      temp_pair.second.push_back(strtoull(buffer.c_str(), nullptr, 10));
      std::cin >> buffer;
    }
    storage.push_back(temp_pair);
  }
  for (storage_t::iterator i = storage.begin(); i != storage.end(); ++i)
  {
    std::cout << i->first;
    if (std::next(i) != storage.end())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";
  storage_t::iterator it = storage.begin();
  for (std::list<size_t>::iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
  {
    for (; it != storage.end(); ++it)
    {
      std::cout << *jt;
      if (std::next(it) != storage.end())
      {
        std::cout << " ";
      }
    }
    std::cout << '\n';
    it = storage.begin();
  }
}
