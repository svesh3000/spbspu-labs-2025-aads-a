#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <unordered_map>
#include <string>
#include <list/fwdlist-ring.hpp>
#include "pair_hash.hpp"

namespace sveshnikov
{
  class Graph
  {
  public:
    Graph() = default;
    void add(std::pair< std::string, std::string > name, unsigned int weight);

  private:
    std::unordered_map< std::pair< std::string, std::string >, FwdList< unsigned int >, PairHash >
        graph_;
  };
}

#endif
