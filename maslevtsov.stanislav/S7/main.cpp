#include <fstream>
#include <iostream>
#include <unordered_map>
#include <boost/hash2/siphash.hpp>
#include <tree/definition.hpp>
#include <fwd_list/definition.hpp>

namespace maslevtsov {
  struct PairDoubleHash
  {
    size_t operator()(const std::pair< std::string, std::string >& pair) const
    {
      size_t h1 = std::hash< std::string >{}(pair.first);
      size_t h2 = std::hash< std::string >{}(pair.second);
      boost::hash2::siphash_64 siph;
      siph.update(pair.first.data(), pair.first.size());
      size_t result;
      result ^= h1;
      result ^= h2;
      result ^= siph.result();
      return result;
    }
  };

  class Graph
  {
  public:
    void add_edge(const std::string& vertice1, const std::string& vertice2, unsigned weight);

  private:
    using vertices_pair_t = std::pair< std::string, std::string >;
    using edges_set_t = std::unordered_map< vertices_pair_t, FwdList< unsigned >, PairDoubleHash >;

    edges_set_t edges_set;
  };
}

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cerr << "<INVALID PARAMETERS NUMBER>\n";
    return 1;
  }
  std::ifstream fin(argv[1]);
  if (!fin) {
    std::cerr << "<INVALID DATA FILE>\n";
    return 1;
  }

  using graphs_tree_t = maslevtsov::Tree< std::string, maslevtsov::Graph >;

  graphs_tree_t graphs;
  std::string graph_name;
  while ((fin >> graph_name) && !fin.eof()) {
    size_t edges_count = 0;
    fin >> edges_count;
    maslevtsov::Graph graph;
    for (size_t i = 0; i < edges_count; ++i) {
      std::string vertice1, vertice2;
      unsigned weight = 0;
      fin >> vertice1 >> vertice2 >> weight;
      graph.add_edge(vertice1, vertice2, weight);
    }
    graphs[graph_name] = graph;
  }
}
