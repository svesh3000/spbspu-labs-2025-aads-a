#include <iostream>
#include <parser.hpp>
#include "processor.hpp"

int main(int argc, char** argv)
{
  using processor = rychkov::S7ParseProcessor;
  using parser_type = rychkov::Parser< processor >;
  parser_type::map_type call_map = {
    {"graphs", &processor::graphs},
    {"vertexes", &processor::vertexes},
    {"outbound", &processor::outbound},
    {"inbound", &processor::inbound},
    {"bind", &processor::bind},
    {"cut", &processor::cut},
    {"create", &processor::create},
    {"merge", &processor::merge},
    {"extract", &processor::extract}
  };
  parser_type parser{{std::cin, std::cout, std::cerr}, {}, std::move(call_map)};
  if (!parser.processor.init(parser.context, argc, argv))
  {
    return 1;
  }

  while (parser.run())
  {}
}
