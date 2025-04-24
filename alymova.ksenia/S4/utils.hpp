#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <functional>
#include <map>

namespace alymova
{
  using Dataset_t = std::map< size_t, std::string, std::less< size_t > >;
  using CompositeDataset_t = std::map< std::string, Dataset_t, std::less< std::string > >;
  using CommandDataset_t = std::map<
    std::string,
    std::function< void(CompositeDataset_t&) >,
    std::less< std::string >
  >;

  struct PrintCommand
  {
    std::istream& in;
    std::ostream& out;
    void operator()(const CompositeDataset_t& dicts);
  };
  struct ComplementCommand
  {
    std::istream& in;
    void operator()(CompositeDataset_t& dicts);
  };
  struct IntersectCommand
  {
    std::istream& in;
    void operator()(CompositeDataset_t& dicts);
  };
  struct UnionCommand
  {
    std::istream& in;
    void operator()(CompositeDataset_t& dicts);
  };

  Dataset_t readTree(const std::string& s);
  CommandDataset_t complectCommands();

  /*void print(std::ostream& out, const CompositeDataset_t& dicts, const std::string& dataset);
  Dataset_t complement(CompositeDataset_t& dicts, const std::string& newdataset,
    const std::string& dataset1, const std::string& dataset2);
  Dataset_t intersect(CompositeDataset_t& dicts, const std::string& newdataset,
    const std::string& dataset1, const std::string& dataset2);
  Dataset_t unionDict(CompositeDataset_t& dicts, const std::string& newdataset,
    const std::string& dataset1, const std::string& dataset2);*/
}

#endif
