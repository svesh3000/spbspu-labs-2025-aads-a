#ifndef KV_AGGREGATOR_HPP
#define KV_AGGREGATOR_HPP
#include <string>

namespace sveshnikov
{
  struct KeyValueAggregator
  {
    int key_sum_;
    std::string values_;

    void operator()(const std::pair< int, std::string > &key_value);
  };
}

#endif
