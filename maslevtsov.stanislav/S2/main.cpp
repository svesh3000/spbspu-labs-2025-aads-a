#include <fstream>
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <cctype>
#include "checked_operations.hpp"

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

  void output_results(std::ostream& out, results_stack& results) noexcept
  {
    out << results.top();
    results.pop();
    while (!results.empty()) {
      out << " " << results.top();
      results.pop();
    }
  }

  bool is_num(const std::string& str) noexcept
  {
    for (auto i = str.cbegin(); i != str.cend(); ++i) {
      if (!isdigit(*i)) {
        return false;
      }
    }
    return true;
  }

  bool is_operation(const std::string& str) noexcept
  {
    return str == "*" || str == "/" || str == "%" || str == "+" || str == "-";
  }

  int get_precedence(const std::string& operation) noexcept
  {
    if (operation == "*" || operation == "/" || operation == "%") {
      return 1;
    }
    if (operation == "+" || operation == "-") {
      return 2;
    }
    return -1;
  }

  void convert(expression_queue& exp)
  {
    std::stack< std::string > dump;
    expression_queue result;
    int operand_count = 0;
    bool is_operation_before = false;
    while (!exp.empty()) {
      if (exp.front() == "(") {
        dump.push(exp.front());
      } else if (is_num(exp.front())) {
        result.push(exp.front());
        ++operand_count;
      } else if (is_operation(exp.front())) {
        if ((operand_count > 2) || (operand_count == 1 && !is_operation_before)) {
          throw std::logic_error("invalid expression");
        }
        while (is_operation(dump.top()) && (get_precedence(dump.top()) >= get_precedence(exp.front()))) {
          result.push(dump.top());
          dump.pop();
        }
        dump.push(exp.front());
        operand_count = 0;
        is_operation_before = true;
      } else if (exp.front() == ")") {
        while (!dump.empty() && dump.top() != ")") {
          result.push(dump.top());
          dump.pop();
        }
        if (dump.empty()) {
          throw std::logic_error("invalid expression");
        }
        dump.pop();
        exp.pop();
      } else {
        throw std::logic_error("invalid expression");
      }
    }
    while (!dump.empty()) {
      if (!is_operation(dump.top())) {
        throw std::logic_error("invalid expression");
      }
      result.push(dump.top());
      dump.pop();
    }
    exp = result;
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

  long long calculate_expression(const expression_queue& exp_queue)
  {
    std::stack< long long > dump;
    expression_queue exp = exp_queue;
    while (!exp.empty()) {
      if (is_num(exp.front())) {
        dump.push(std::stoll(exp.front()));
      } else {
        if (dump.size() != 2) {
          throw std::logic_error("invalid expression");
        }
        long long operand2 = dump.top();
        dump.pop();
        long long operand1 = dump.top();
        dump.pop();
        dump.push(maslevtsov::checked_operation(operand1, operand2, exp.front()));
      }
    }
    if (dump.empty() || dump.size() > 1) {
      throw std::logic_error("invalid expression");
    }
    return dump.top();
  }

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

  try {
    convert_stack(exp_stack);
  } catch (const std::exception&) {
    std::cerr << "Invalid expression\n";
    return 1;
  }
  results_stack results;
  try {
    calculate_expressions(exp_stack, results);
  } catch (const std::exception&) {
    std::cerr << "Calculation error\n";
    return 1;
  }

  output_results(std::cout, results);
  std::cout << '\n';
}
