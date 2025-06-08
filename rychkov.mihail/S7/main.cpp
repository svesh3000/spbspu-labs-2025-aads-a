#include <iostream>
#include <exception>
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
  try
  {
    parser_type parser{{std::cin, std::cout, std::cerr}, {argc, argv}, std::move(call_map)};
    while (parser.run())
    {}
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
    return 1;
  }

}
