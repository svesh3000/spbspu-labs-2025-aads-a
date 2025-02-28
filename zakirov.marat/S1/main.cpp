#include <forward_list>
#include <iostream>
#include <utility>
#include "io_containers.hpp"

int main()
{
  std::forward_list <std::pair< std::string, std::forward_list< long long int > > > forward_list = {{"0", {0}}};
  auto filling_iterator = forward_list.begin();
  zakirov::get_list_pair(std::cin, forward_list);
  zakirov::output_result(std::cout, forward_list);
}
