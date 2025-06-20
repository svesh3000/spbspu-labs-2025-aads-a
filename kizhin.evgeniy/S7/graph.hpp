#ifndef SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S7_GRAPH_HPP
#define SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S7_GRAPH_HPP

#include <unordered_map>
#include <set>
#include <string>

namespace kizhin {
  using Vertex = std::string;
  struct VertexPair
  {
    Vertex from{};
    Vertex to{};
  };
}

namespace std {
  template <>
  struct hash< kizhin::VertexPair >
  {
    size_t operator()(const kizhin::VertexPair&) const;
  };
}

namespace kizhin {
  using Weight = std::size_t;
  using WeightContiner = std::multiset< Weight >;

  bool operator==(const VertexPair&, const VertexPair&);

  using Graph = std::unordered_map< VertexPair, WeightContiner >;
  using VertexContainer = std::set< Vertex >;

  VertexContainer getVertices(const Graph&);
  Graph getOutbound(const Graph&, const Vertex&);
  Graph getInbound(const Graph&, const Vertex&);
}

#endif

