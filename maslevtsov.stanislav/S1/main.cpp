#include <iostream>
#include <list>
#include <string>
#include <utility>

using list_t = std::list< unsigned int >;
using pairs_list_t = std::list< std::pair< std::string, list_t > >;

// namespace {
//   std::size_t get_max_pair_list_size(const pairs_list_t& list)
//   {
//     std::size_t maximum = *(*list.begin()).second.begin();
//     for (auto i = list.begin(); i != list.end(); ++i) {
//       maximum = maximum < (*i).second.size() ? (*i).second.size() : maximum;
//     }
//     return maximum;
//   }
// }

int main()
{
  pairs_list_t pairs_list{};
  bool is_empty_input = true;

  while (!std::cin.eof()) {
    list_t list{};
    std::string list_name = "";
    unsigned int num = 0;
    std::cin >> list_name;
    while (!std::cin.fail()) {
      std::cin >> num;
      if (std::cin.fail()) {
        break;
      }
      list.push_back(num);
      is_empty_input = false;
    }
    if (!std::cin.eof()) {
      std::cin.clear();
    }
    pairs_list.push_back(std::make_pair(list_name, list));
  }

  // std::cout << (*pairs_list.begin()).first;
  // for (auto i = ++pairs_list.begin(); i != pairs_list.end(); ++i) {
  //   std::cout << ' ' << (*i).first;
  // }
  // std::cout << '\n';
  // if (is_empty_input) {
  //   std::cout << 0 << '\n';
  // } else {
  //   list_t sum_list{};
  //   for (auto i = pairs_list.begin(); i != pairs_list.end(); ++i) {
  //     unsigned int sum = 0;
  //     std::cout << *(*i).second.begin();
  //     sum += *(*i).second.begin();
  //     for (auto j = ++(*i).second.begin(); j != (*i).second.end(); ++j) {
  //       std::cout << ' ' << *j;
  //       sum += *j;
  //     }
  //     std::cout << '\n';
  //     sum_list.push_back(sum);
  //   }
  //   std::cout << *sum_list.begin();
  //   for (auto i = ++sum_list.begin(); i != sum_list.end(); ++i) {
  //     std::cout << ' ' << *i;
  //   }
  // }
  // std::cout << '\n';
}
