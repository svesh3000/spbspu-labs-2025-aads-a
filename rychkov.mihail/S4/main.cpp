#include <iostream>
#include <memory>
#include "map.hpp"

int main()
{
  rychkov::Map< int, double > map;
  map.emplace(4, 6.94);
  map.emplace(8, 9.0);
  map.emplace(10, 7.1);
  map.emplace(2, -1.25);
  map.emplace(0, -0);
  map.emplace(12, 0.5);
  map.emplace(11, 0.0);
  map.emplace(-2, -11);
  for (auto pair: map)
  {
    std::cout << pair.first << ' ' << pair.second << '\n';
  }
  std::cout << '\n';
  for (int key: {0, 3, 8, 11})
  {
    auto pair = *map.upper_bound(key);
    std::cout << pair.first << ' ' << pair.second << '\n';
  }
  std::cout << '\n';
  std::cout << map.contains(0.0) << '\n';
  std::cout << map.contains(1) << '\n';
}
