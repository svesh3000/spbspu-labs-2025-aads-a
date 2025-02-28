#include <iostream>
#include <forward_list>
#include <string>
#include <utility>

namespace
{
    using list_t = std::forward_list< unsigned long long >;
    using pairs_list_t = std::forward_list< std::pair< std::string, list_t > >;
}
int main()
{
  pairs_list_t pairs_list{};
  pairs_list_t pairs_list;
  std::string list_name = "";
  bool isEmpty = true;

  while (std::cin >> list_name)
  {
    list_t list;
    unsigned long long num = 0;

    while (std::cin >> num)
    {
      list.push_front(num);
      isEmpty = false;
    }

    pairs_list.push_front(std::make_pair(list_name, list));
    std::cin.clear();
  }

  std::cout << pairs_list.begin()->first;
  for (auto i = ++pairs_list.begin(); i != pairs_list.end(); ++i)
  {
    std::cout << ' ' << i->first;
  }
  std::cout << '\n';
  if (isEmpty)
  {
    std::cout << 0 << '\n';
  }
  std::cout << '\n';
}
