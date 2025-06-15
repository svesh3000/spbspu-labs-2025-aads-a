#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include "ArrayBuffer.hpp"
#include "ConstIterator.hpp"
#include "Iterator.hpp"
#include "TwoThreeTree.hpp"
// Accumulator из предыдущего примера
struct Accumulator {
  gavrilova::ArrayBuffer< int > keys;
  gavrilova::ArrayBuffer< std::string > values;
  long long sum_keys = 0;

  void operator()(const std::pair< int, std::string >& p)
  {
    if (sum_keys > std::numeric_limits< long long >::max() - p.first) {
      throw std::overflow_error("Sum overflow");
    }
    sum_keys += p.first;
    keys.push_back(p.first);
    values.push_back(p.second);
  }
};

int main()
{
  // Тест 1: Пустое дерево
  {
    gavrilova::TwoThreeTree< int, std::string > tree;
    Accumulator acc = tree.traverse_lnr(Accumulator{});
    if (!tree.empty()) {
      std::cerr << "TestTraverseLNREmptyTree failed: tree is not empty\n";
      return 1;
    }
    if (acc.keys.size() != 0) {
      std::cerr << "TestTraverseLNREmptyTree failed: keys size is not 0\n";
      return 1;
    }
    if (acc.values.size() != 0) {
      std::cerr << "TestTraverseLNREmptyTree failed: values size is not 0\n";
      return 1;
    }
    if (acc.sum_keys != 0) {
      std::cerr << "TestTraverseLNREmptyTree failed: sum_keys is not 0\n";
      return 1;
    }
    std::cout << "TestTraverseLNREmptyTree passed\n";
  }

  // Тест 2: LNR обход непустого дерева
  {
    gavrilova::TwoThreeTree< int, std::string > tree;
    tree.insert({10, "ten"});
    tree.insert({5, "five"});
    tree.insert({15, "fifteen"});
    tree.insert({12, "twelve"});

    Accumulator acc = tree.traverse_lnr(Accumulator{});

    if (acc.keys.size() != 4) {
      std::cerr << "TestTraverseLNR failed: expected keys size 4, got " << acc.keys.size() << "\n";
      return 1;
    }

    // Проверяем порядок ключей (возрастание)
    if (!(acc.keys[0] == 5 && acc.keys[1] == 10 && acc.keys[2] == 12 && acc.keys[3] == 15)) {
      std::cerr << "TestTraverseLNR failed: keys order incorrect\n";
      return 1;
    }

    // Проверяем порядок значений
    if (!(acc.values[0] == "five" && acc.values[1] == "ten" && acc.values[2] == "twelve" && acc.values[3] == "fifteen")) {
      std::cerr << "TestTraverseLNR failed: values order incorrect\n";
      return 1;
    }

    // Проверяем сумму ключей
    if (acc.sum_keys != 5 + 10 + 12 + 15) {
      std::cerr << "TestTraverseLNR failed: sum_keys incorrect, got " << acc.sum_keys << "\n";
      return 1;
    }

    std::cout << "TestTraverseLNR passed\n";
  }

  return 0;
}
