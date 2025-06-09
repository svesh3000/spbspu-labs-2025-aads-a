#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <unordered_map>
#include <set>
#include <vector>

namespace maslov
{
  struct Graph
  {
   private:
    std::set< std::string > vertexes;
    std::unordered_map<std::pair< std::string, std::string>, std::vector< int > > edges;
  };
}

#endif
