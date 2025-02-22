#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <limits>

namespace {
  using list_t = std::list< unsigned long long >;
  using pairs_list_t = std::list< std::pair< std::string, list_t > >;

  std::size_t get_max_pairs_list_size(const pairs_list_t& list) noexcept
  {
    std::size_t maximum = 0, size = 0;
    for (auto i = list.begin(); i != list.end(); ++i) {
      for (auto j = i->second.begin(); j != i->second.end(); ++j) {
        ++size;
      }
      maximum = maximum > size ? maximum : size;
    }
    return maximum;
  }

  int safe_sum(unsigned long long a, unsigned long long b)
  {
    const unsigned long long max_ull = std::numeric_limits< unsigned long long >::max();
    if (max_ull - a > b) {
      return a + b;
    }
    throw std::overflow_error("overflow");
  }

  std::size_t get_sum_of_list_elements(const list_t& list)
  {
    std::size_t result = 0;
    for (auto i = list.begin(); i != list.end(); ++i) {
      result = safe_sum(result, *i);
    }
    return result;
  }

  void print_lists_info(std::ostream& out, const pairs_list_t& pairs_list)
  {
    pairs_list_t copy = pairs_list;
    std::size_t max_pairs_list_size = get_max_pairs_list_size(pairs_list);
    list_t sums;
    for (std::size_t i = 0; i != max_pairs_list_size; ++i) {
      list_t column_elements;
      for (auto j = copy.begin(); j != copy.end(); ++j) {
        if (!j->second.empty()) {
          column_elements.push_back(j->second.front());
          j->second.pop_front();
        }
      }
      if (!column_elements.empty()) {
        out << *column_elements.begin();
        for (auto j = ++column_elements.begin(); j != column_elements.end(); ++j) {
          out << ' ' << *j;
        }
        std::cout << '\n';
        sums.push_back(get_sum_of_list_elements(column_elements));
      }
    }
    out << *sums.begin();
    for (auto j = ++sums.begin(); j != sums.end(); ++j) {
      out << ' ' << *j;
    }
  }
}

int main()
{
  pairs_list_t pairs_list;
  std::string list_name = "";

  while (std::cin >> list_name) {
    list_t list;
    unsigned long long num = 0;
    while (std::cin >> num) {
      list.push_back(num);
    }
    pairs_list.push_back(std::make_pair(list_name, list));
    std::cin.clear();
  }

  if (!pairs_list.empty()) {
    std::cout << 0;
  } else {
    std::cout << pairs_list.begin()->first;
    for (auto i = ++pairs_list.begin(); i != pairs_list.end(); ++i) {
      std::cout << ' ' << i->first;
    }
    std::cout << '\n';
    try {
      print_lists_info(std::cout, pairs_list);
    } catch (const std::overflow_error&) {
      std::cerr << "Overflow error\n";
      return 1;
    }
  }
  std::cout << '\n';
}
