#include <iostream>
#include <forward_list>
#include <string>
#include <utility>

namespace {
  using list_t = std::forward_list< unsigned long long >;
  using pairs_list_t = std::forward_list< std::pair< std::string, list_t > >;

  // std::size_t get_max_pair_list_size(const pairs_list_t& list)
  // {
  //   std::size_t maximum = 0;
  //   std::size_t size = 0;
  //   for (auto i = list.begin(); i != list.end(); ++i) {
  //     for (auto j = i->second.begin(); j != i->second.begin(); ++j) {
  //       ++size;
  //     }
  //     maximum = maximum > size ? maximum : size;
  //   }
  //   return maximum;
  // }
}

int main()
{
  pairs_list_t pairs_list;
  std::string list_name = "";
  bool is_empty_input = true;

  while (std::cin >> list_name) {
    list_t list;
    unsigned long long num = 0;
    while (std::cin >> num) {
      list.push_front(num);
      is_empty_input = false;
    }
    pairs_list.push_front(std::make_pair(list_name, list));
    std::cin.clear();
  }

  std::cout << pairs_list.begin()->first;
  for (auto i = ++pairs_list.begin(); i != pairs_list.end(); ++i) {
    std::cout << ' ' << i->first;
  }
  std::cout << '\n';
  if (is_empty_input) {
    std::cout << 0 << '\n';
  }
  std::cout << '\n';
}
