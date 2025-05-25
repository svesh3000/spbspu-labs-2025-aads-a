#include "commands.hpp"
#include <vector/definition.hpp>

namespace {
  void sort(maslevtsov::Vector< std::string >& array)
  {
    for (size_t i = 0; i < array.size() - 1; ++i) {
      for (size_t j = 0; j < array.size() - i - 1; ++j) {
        if (array[j] > array[j + 1]) {
          std::swap(array[j], array[j + 1]);
        }
      }
    }
  }
}

void maslevtsov::print_graphs(const graphs_map_t& graphs, std::ostream& out)
{
  if (graphs.empty()) {
    out << '\n';
    return;
  }
  Vector< std::string > names;
  for (auto i = graphs.cbegin(); i != graphs.cend(); ++i) {
    names.push_back(i->first);
  }
  sort(names);
  for (std::string i: names) {
    out << i << '\n';
  }
}
