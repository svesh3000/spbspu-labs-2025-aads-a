#ifndef EDGE_HPP
#define EDGE_HPP
#include <string>
#include <cstddef>

namespace abramov
{
  struct Edge
  {
    std::string from;
    std::string to;
    size_t weight;

    Edge();
    Edge(const std::string &f, const std::string &t, size_t w);
  };
}

abramov::Edge::Edge():
  from(std::string{}),
  to(std::string{}),
  weight(0)
{}

abramov::Edge::Edge(const std::string &f, const std::string &t, size_t w):
  from(f),
  to(t),
  weight(w)
{}
#endif
