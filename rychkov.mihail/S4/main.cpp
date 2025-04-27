#include <iostream>
#include <memory>
#include "map.hpp"

int main()
{
  rychkov::Map< int, double > map;
  map.emplace_hint(map.begin(), 4, 6.94);
  map.emplace_hint(map.end(), 8, 9.0);
  map.emplace_hint(map.end(), 10, 7.1);
  map.emplace_hint(map.begin(), 2, -1.25);
  map.emplace_hint(map.begin(), 0, -0);
  map.emplace_hint(map.end(), 12, 0.5);
  map.emplace_hint(--map.end(), 11, 0.0);
  map.emplace_hint(map.begin(), -2, -11);
  for (auto pair: map)
  {
    std::cout << pair.first << ' ' << pair.second << '\n';
  }
}
