#ifndef EDGE_HPP
#define EDGE_HPP

namespace abramov
{
  struct Edge
  {
    std::string from;
    std::string to;
    size_t weight;

    Edge(const std::string &f, const std::string &t, size_t w);
  };
}

abramov::Edge::Edge(const std::string &f, const std::string &t, size_t w):
  from(f),
  to(t),
  weight(w)
{}
#endif
