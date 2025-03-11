#include <iostream>
#include <fstream>
#include <string>
#include <stack.hpp>
#include <queue.hpp>
#include "expr_convert.hpp"

namespace
{
  using ExprsStack = demehin::Stack< demehin::Queue < std::string > >;

  void inputExprs(std::istream& in, ExprsStack& stack)
  {
    demehin::Queue< std::string > exprQueue;
    std::string line;

    while (std::getline(in, line))
    {
      if (line.empty())
      {
        if (!exprQueue.empty())
        {
          stack.push(exprQueue);
        }
        break;
      }

      std::string token;
      for (char c : line)
      {
        if (std::isspace(c))
        {
          continue;
        }
        else if (std::isdigit(c))
        {
          token += c;
        }
        else
        {
          if (!token.empty())
          {
            exprQueue.push(token);
            token.clear();
          }
          exprQueue.push(std::string(1, c));
        }
      }
      if (!token.empty())
      {
        exprQueue.push(token);
      }
      if (!exprQueue.empty())
      {
        stack.push(exprQueue);
        exprQueue.clear();
      }
    }
  }

  void printValues(std::ostream& out, demehin::Stack< int > stack)
  {
    if (stack.empty())
    {
      return;
    }
    out << stack.top();
    stack.pop();
    while (!stack.empty())
    {
      std::cout << " " << stack.top();
      stack.pop();
    }
  }

  void printExprs(ExprsStack stack)
  {
    while (!stack.empty())
    {
      while (!stack.top().empty())
      {
        std::cout << stack.top().front();
        stack.top().pop();
      }
      stack.pop();
      std::cout << "\n";
    }
  }
}

int main(int argc, char* argv[])
{
  ExprsStack infExprsStack;
  if (argc > 1)
  {
    std::ifstream file(argv[1]);
    inputExprs(file, infExprsStack);
  }
  else
  {
    inputExprs(std::cin, infExprsStack);
  }

  printExprs(infExprsStack);
  ExprsStack postExprsStack;
  try
  {
    demehin::convertStack(infExprsStack, postExprsStack);
  }
  catch (std::logic_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  demehin::Stack< int > res;
  try
  {
    demehin::getExprsValues(postExprsStack, res);
  }
  catch (std::logic_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  printValues(std::cout, res);
  std::cout << "\n";
}

