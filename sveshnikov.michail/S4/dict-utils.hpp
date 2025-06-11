#ifndef DICT_UTILS_HPP
#define DICT_UTILS_HPP
#include <iostream>
#include <functional>
#include <map>

namespace sveshnikov
{
  using Dict_t = std::map< int, std::string >;
  using DataTree_t = std::map< std::string, Dict_t >;
  using CommandHolder_t =
      std::map< std::string, std::function< void(std::istream &, DataTree_t &) > >;

  DataTree_t loadDicts(char *filename);
  CommandHolder_t getCommands();

  void print_dict(std::istream &, const DataTree_t &);
  void complement_dict(std::istream &, DataTree_t &);
  void intersect_dict(std::istream &, DataTree_t &);
  void union_dict(std::istream &, DataTree_t &);
}
#endif
