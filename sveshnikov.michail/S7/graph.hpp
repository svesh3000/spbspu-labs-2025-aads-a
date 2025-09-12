#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <unordered_map>
#include <list/fwdlist-ring.hpp>
#include <tree/tree.hpp>
#include <array.hpp>
#include "pair_hash.hpp"

namespace sveshnikov
{
  class Graph
  {
  public:
    Graph() = default;
    Graph(const Graph &graph1, const Graph &graph2);

    void add_vertice(std::string vert);
    void bind(std::pair< std::string, std::string > name, unsigned int weight);
    void cut(std::string graph, std::string vert_out, std::string vert_in, size_t weight) noexcept;

    Array< std::string > &get_vertices() const;
    Array< std::pair< std::string, size_t > > get_outbounds(const std::string &vert) const;
    Array< std::pair< std::string, size_t > > get_inbounds(const std::string &vert) const;

  private:
    std::unordered_map< std::pair< std::string, std::string >, FwdList< unsigned int >, PairHash >
        graph_;
    AvlTree< std::string, char > vertices;
  };
}

#endif
