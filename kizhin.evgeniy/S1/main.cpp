#include <stdexcept>
#include "io-utils.hpp"
#include "list-utils.hpp"

int main()
{
  using namespace kizhin;
  try {
    NamesT names;
    ForwardList< NumbersT > numbers;
    if (!inputSequences(std::cin, names, numbers)) {
      throw std::logic_error("Failed to input");
    }
    numbers = convert(numbers);
    outputList(std::cout, names);
    if (!names.empty()) {
      std::cout << '\n';
    }
    auto isEmptyList = [](const auto& list) -> bool
    {
      return list.empty();
    };
    if (names.empty() || std::all_of(numbers.begin(), numbers.end(), isEmptyList)) {
      std::cout << "0\n";
      return 0;
    }
    for (const NumbersT& num : numbers) {
      outputList(std::cout, num);
      if (!num.empty()) {
        std::cout << '\n';
      }
    }
    ForwardList< NumbersT::value_type > sums;
    using iterator = ForwardList< NumbersT >::iterator;
    for (iterator i = numbers.begin(), end = numbers.end(); i != end; ++i) {
      sums.pushBack(safeAccumulate(*i));
    }
    outputList(std::cout, sums);
    if (!sums.empty()) {
      std::cout << '\n';
    }
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
}
