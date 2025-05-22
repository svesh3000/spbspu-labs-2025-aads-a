#ifndef CMDS_HPP
#define CMDS_HPP

#include <ostream>
#include <istream>
#include <string>
#include <map>


namespace dribas
{
  using data = std::map< size_t, std::string >;
  using dataset = std::map< std::string, data >;

  void print(std::ostream&, std::istream&, const dataset&);
  void complement(std::istream&, dataset&);
  void intersect(std::istream&, dataset&);
  void unite(std::istream&, dataset&);
}

#endif
