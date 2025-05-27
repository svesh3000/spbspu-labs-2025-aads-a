#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <string>
#include <unordered_map>
#include <list.hpp>
#include <parser.hpp>

namespace rychkov
{
  struct PairHash
  {
    size_t operator()(const std::pair< std::string, std::string >& value) const;
  };
  class S7ParseProcessor
  {
  public:
    bool init(ParserContext& context, int argc, char** argv);
    bool graphs(ParserContext& context);
    bool vertexes(ParserContext& context);
    bool outbound(ParserContext& context);
    bool inbound(ParserContext& context);
    bool bind(ParserContext& context);
    bool cut(ParserContext& context);
    bool create(ParserContext& context);
    bool merge(ParserContext& context);
    bool extract(ParserContext& context);
  private:
    using edge = std::pair< std::string, std::string >;
    using inner_map = std::unordered_map< edge, rychkov::List< unsigned >, PairHash >;
    using outer_map = std::unordered_map< std::string, inner_map >;

    outer_map map;
  };
}

#endif
