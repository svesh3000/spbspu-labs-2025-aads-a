#include <fstream>
#include <iostream>
#include <sstream>

#include "queue.hpp"
#include "stack.hpp"

namespace zholobov {

  bool isOperator(const std::string& token)
  {
    return (token == "+") || (token == "-") || (token == "*") || (token == "/") || (token == "%");
  }

  int operatorPriority(const std::string& op)
  {
    if (op == "+" || op == "-") {
      return 1;
    }
    if (op == "*" || op == "/" || op == "%") {
      return 2;
    }
    return 0;
  }

  bool isNumber(const std::string& str)
  {
    if (str.empty()) {
      return false;
    }
    for (size_t i = 0; i < str.size(); ++i) {
      if (!std::isdigit(str[i])) {
        return false;
      }
    }
    return true;
  }

  Queue< std::string > infixToPostfix(Queue< std::string > tokens)
  {
    Queue< std::string > result;
    Stack< std::string > op_stack;

    while (!tokens.empty()) {
      std::string token = tokens.front();
      tokens.pop();

      if (isNumber(token)) {
        result.push(std::move(token));
      } else if (token == "(") {
        op_stack.push(std::move(token));
      } else if (token == ")") {
        while (!op_stack.empty() && op_stack.top() != "(") {
          result.push(op_stack.top());
          op_stack.pop();
        }
        if (op_stack.empty()) {
          throw std::runtime_error("Parentheses mismatch");
        }
        op_stack.pop();
      } else if (isOperator(token)) {
        while ((!op_stack.empty()) &&
               (op_stack.top() != "(") &&
               (operatorPriority(op_stack.top()) >= operatorPriority(token))) {
          result.push(op_stack.top());
          op_stack.pop();
        }
        op_stack.push(std::move(token));
      } else {
        throw std::runtime_error("Invalid token");
      }
    }

    while (!op_stack.empty()) {
      if (op_stack.top() == "(") {
        throw std::runtime_error("Parentheses mismatch");
      }
      result.push(op_stack.top());
      op_stack.pop();
    }

    return result;
  }

  long evaluatePostfixExpression(Queue< std::string > postfix_expr)
  {
    Stack< long > eval_stack;

    while (!postfix_expr.empty()) {
      std::string token = postfix_expr.front();
      postfix_expr.pop();

      if (isNumber(token)) {
        eval_stack.push(std::stol(token));
      } else {
        if (eval_stack.empty()) {
          throw std::runtime_error("Not enough operands");
        }
        long rhs = eval_stack.top();
        eval_stack.pop();
        if (eval_stack.empty()) {
          throw std::runtime_error("Not enough operands");
        }
        long lhs = eval_stack.top();
        eval_stack.pop();

        if (token == "+") {
          eval_stack.push(lhs + rhs);
        } else if (token == "-") {
          eval_stack.push(lhs - rhs);
        } else if (token == "*") {
          eval_stack.push(lhs * rhs);
        } else if (token == "/") {
          if (rhs == 0) {
            throw std::runtime_error("Division by zero");
          }
          eval_stack.push(lhs / rhs);
        } else if (token == "%") {
          if (rhs == 0) {
            throw std::runtime_error("Modulo by zero");
          }
          eval_stack.push(lhs % rhs);
        } else {
          throw std::runtime_error("Invalid operator");
        }
      }
    }

    if (eval_stack.empty()) {
      throw std::runtime_error("No result");
    }
    long result = eval_stack.top();
    eval_stack.pop();
    if (!eval_stack.empty()) {
      throw std::runtime_error("Too many operands");
    }
    return result;
  }

  Queue< std::string > readExpressions(std::istream& input)
  {
    Queue< std::string > expressions;
    std::string line;
    while (std::getline(input, line)) {
      if (!line.empty()) {
        expressions.push(std::move(line));
      }
    }
    return expressions;
  }

  Queue< std::string > stringToTokens(const std::string& str)
  {
    Queue< std::string > tokens;
    std::istringstream iss(str);
    std::string token;
    while (iss >> token) {
      tokens.push(std::move(token));
    }
    return tokens;
  }

  zholobov::Stack< long > precessExpressions(zholobov::Queue< std::string > expressions)
  {
    zholobov::Stack< long > results;
    while (!expressions.empty()) {
      std::string expr_str = expressions.front();
      expressions.pop();

      zholobov::Queue< std::string > tokens = zholobov::stringToTokens(expr_str);
      zholobov::Queue< std::string > postfix = zholobov::infixToPostfix(std::move(tokens));
      results.push(zholobov::evaluatePostfixExpression(std::move(postfix)));
    }
    return results;
  }

  void printResults(std::ostream& out, zholobov::Stack< long > results)
  {
    out << results.top();
    results.pop();
    while (!results.empty()) {
      out << " " << results.top();
      results.pop();
    }
  }

}

int main(int argc, char* argv[])
{
  try {
    zholobov::Queue< std::string > expressions;
    if (argc > 1) {
      std::ifstream file(argv[1]);
      if (!file) {
        throw std::runtime_error("Cannot open file");
      }
      expressions = zholobov::readExpressions(file);
    } else {
      expressions = zholobov::readExpressions(std::cin);
    }

    zholobov::Stack< long > results = zholobov::precessExpressions(std::move(expressions));
    if (!results.empty()) {
      zholobov::printResults(std::cout, std::move(results));
      std::cout << "\n";
    }
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
