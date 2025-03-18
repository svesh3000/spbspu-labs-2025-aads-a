#include <fstream>
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <cctype>

namespace {
  using expression_queue = std::queue< std::string >;
  using expression_stack = std::stack< expression_queue >;
  using results_stack = std::stack< long long >;

  void input_expressions(std::istream& in, expression_stack& exp_stack)
  {
    std::string str;
    while (in) {
      std::getline(in, str);
      if (str.empty()) {
        continue;
      }
      expression_queue exp_queue;
      std::string element;
      for (auto i = str.cbegin(); i != str.cend(); ++i) {
        if (std::isspace(*i)) {
          exp_queue.push(element);
          element.clear();
          continue;
        } else {
          element += *i;
        }
      }
      if (element != "") {
        exp_queue.push(element);
      }
      if (!exp_queue.empty()) {
        exp_stack.push(exp_queue);
      }
    }
  }

  void output_results(std::ostream& out, results_stack results)
  {
    std::cout << results.top();
    results.pop();
    while (!results.empty()) {
      out << " " << results.top();
      results.pop();
    }
  }

  bool is_num(const std::string& str)
  {
    try {
      std::stoll(str);
    } catch (...) {
      return false;
    }
    return true;
  }

  bool is_operation(const std::string& str)
  {
    return str == "*" || str == "/" || str == "%" || str == "+" || str == "-";
  }

  void convert(expression_queue& exp)
  {
    std::stack< std::string > dump;
    expression_queue result;
    while (!exp.empty()) {
      if (exp.front() == "(") {
        dump.push(exp.front());
      } else if (is_num(exp.front())) {
        result.push(exp.front());
      } else if (is_operation(exp.front())) {
      }
    }
  }

  void convert_stack(expression_stack& exp_stack)
  {
    expression_stack converted;
    while (!exp_stack.empty()) {
      convert(exp_stack.top());
      converted.push(exp_stack.top());
      exp_stack.pop();
    }
    exp_stack = converted;
  }

  long long calculate_expression(expression_queue& exp_queue)
  {}

  void calculate_expressions(expression_stack& exp_stack, results_stack& results)
  {
    expression_stack copy = exp_stack;
    while (!exp_stack.empty()) {
      results.push(calculate_expression(exp_stack.top()));
      exp_stack.pop();
    }
    exp_stack = copy;
  }
}

int main(int argc, char** argv)
{
  if (argc > 2) {
    std::cerr << "Invalid amount of arguments\n";
    return 1;
  }
  expression_stack exp_stack;
  try {
    if (argc == 0) {
      input_expressions(std::cin, exp_stack);
    }
    if (argc == 2) {
      std::ifstream fin(argv[1]);
      input_expressions(fin, exp_stack);
    }
  } catch (const std::bad_alloc&) {
    std::cerr << "Memory allocation error\n";
    return 1;
  }

  convert_stack(exp_stack);
  results_stack results;
  calculate_expressions(exp_stack, results);

  output_results(std::cout, results);
  std::cout << '\n';
}
