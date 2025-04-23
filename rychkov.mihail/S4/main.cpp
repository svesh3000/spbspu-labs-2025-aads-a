#include <iostream>
#include <memory>
#include "map.hpp"

int main()
{
  rychkov::Map< int, double > map;
  std::cout << std::addressof(map) << ' ' << map.fake_root() << '\n';
  map.emplace_hint(map.begin(), 4, 6.94);
  for (auto pair: map)
  {
    std::cout << pair.first << ' ' << pair.second << '\n';
  }
}
