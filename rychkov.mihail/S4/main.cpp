#include <iostream>
#include <memory>
#include "map.hpp"

int main()
{
  rychkov::Map< int, double > map;
  std::cout << std::addressof(map) << ' ' << map.fake_root() << '\n';
}
