#include <exception>
#include <fstream>
#include <iostream>
#include <string>

#include <tree/ConstIterator.hpp>
#include <tree/Iterator.hpp>
#include <tree/TwoThreeTree.hpp>

namespace detail {

  template < typename Key, typename Value >
  ArrayBuffer< std::pair< Key, Value > > parse_file(const std::string& filename)
  {
    std::ifstream file(filename);
    if (!file.is_open()) {
      throw std::runtime_error("Error! Invalid opening file!");
    }

    ArrayBuffer< std::pair< Key, Value > > data;
    Key key;
    Value value;

    while (file >> key >> value) {
      data.push_back(std::make_pair(key, value));
    }

    return data;
  }

}

int main(int argc, char* argv[])
{
  using namespace gavrilova;

  if (argc != 3) {
    std::cerr << "Incorrect format of input.\n";
    return 1;
  }

  try {
    ArrayBuffer< std::pair< int, std::string > > data = parse_file< int, std::string >(argv[2]);

    TwoThreeTree< Key, Value, Cmp > tree;

    for (size_t i = 0; i < data.size(); ++i) {
      tree.insert(data[i].first, data[i].second);
    }

    if (tree.empty()) {
      std::cout << "<EMPTY>\n";
      return 0;
    }

    Collector< Key, Value > collector;
    if (order == "ascending") {
      collector = tree.traverse_lnr(collector);
    } else if (order == "descending") {
      collector = tree.traverse_rnl(collector);
    } else if (order == "breadth") {
      collector = tree.traverse_breadth(collector);
    } else {
      std::cerr << "Invalid traversal order\n";
    }

    std::cout << collector.getSum();
    const ArrayBuffer< Value >& values = collector.getBuffer();
    for (size_t i = 0; i < values.size(); ++i) {
      std::cout << " " << values[i];
    }
    std::cout << "\n";
  } catch (const std::overflow_error& e) {
    std::cerr << e.what() << "\n";
    return 1;
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
