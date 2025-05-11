#ifndef ACTION_CALCULATOR_HPP
#define ACTION_CALCULATOR_HPP
#include "queue.hpp"
#include "stack.hpp"
#include <iostream>
#include <string>

namespace brevnov
{
  using example = Queue< std::string >;
  using queue = Queue< example >;
  using stack = Stack< std::string >;
  using stackNumber = Stack< long long int >;

  queue convert_example(queue& infix);
  stackNumber calculation_example(queue& postfix);
  void input_example(std::istream& input, queue& exprs);
  std::ostream& output_results(std::ostream& output, stackNumber& results);
}
#endif
