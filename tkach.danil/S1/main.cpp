#include <iostream>
#include <forward_list>
#include <string>
#include <sstream>

int main()
{
  std::forward_list< std::pair< std::string, std::forward_list < size_t > > > fd_pair_list;
  std::string list_line = "";
  auto it_fd = fd_pair_list.before_begin();
  while(std::getline(std::cin, list_line))
  {
    std::istringstream iss(list_line);
    std::string list_name = "";
    iss >> list_name;
    std::forward_list < size_t > temp_list;
    size_t num = 0;
    auto it = temp_list.before_begin();
    while(iss >> num)
    {
      it = temp_list.insert_after(it, num);
    }
    it_fd = fd_pair_list.insert_after(it_fd, std::make_pair(list_name, temp_list));
    std::cin.clear();
  }
  std::cout << fd_pair_list.begin()->first;
  for (auto it = ++fd_pair_list.begin(); it != fd_pair_list.end(); ++it)
  {
    std::cout << " " << it->first;
  }
  std::cout << "\n";

  return 0;
}
