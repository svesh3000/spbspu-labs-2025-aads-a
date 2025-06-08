#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <string>
#include <unordered_map>
#include <boost/hash2/fnv1a.hpp>
#include <boost/hash2/hash_append.hpp>
#include <boost/hash2/get_integral_result.hpp>
#include <set.hpp>
#include <list.hpp>
#include <parser.hpp>

namespace rychkov
{
  template< class T = void >
  struct Hash
  {
    size_t operator()(const T& value) const
    {
      boost::hash2::fnv1a_64 hasher;
      boost::hash2::hash_append(hasher, {}, value);
      return boost::hash2::get_integral_result< size_t >(hasher);
    }
  };
  template<>
  struct Hash< void >
  {
    template< class T >
    size_t operator()(const T& value) const
    {
      boost::hash2::fnv1a_64 hasher;
      boost::hash2::hash_append(hasher, {}, value);
      return boost::hash2::get_integral_result< size_t >(hasher);
    }
  };
  class S7ParseProcessor
  {
  public:
    S7ParseProcessor(int argc, char** argv);

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
    using weights_set = MultiSet< unsigned >;
    using inner_map = std::unordered_map< edge, weights_set, Hash< edge > >;

    using vertexes_set = Set< std::string >;
    using outer_mapped_type = std::pair< inner_map, vertexes_set >;
    using outer_map = std::unordered_map< std::string, outer_mapped_type >;

    outer_map map;
  };
}

#endif
