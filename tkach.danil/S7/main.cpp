#include <iostream>
#include <fstream>
#include <limits>
#include <cstddef>
#include <map>
#include <functional>
#include "hash_table.hpp"

int main()
{
  using namespace tkach;
  HashTable< size_t, std::string > hash_table;
  hash_table.insert(hash_table.cend(), std::make_pair(2, "second"));
  hash_table.insert(std::make_pair(1, "first"));
  hash_table.insert(hash_table.cbegin(), std::make_pair(3, "third"));
  hash_table.insert(hash_table.cbegin(), std::make_pair(3, "third"));
}
