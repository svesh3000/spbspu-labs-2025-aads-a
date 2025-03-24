#include <iostream>
#include <fstream>
#include <string>
#include "queue.hpp"
#include "stack.hpp"

namespace
{
  void inputExprs(std::istream & in, mozhegova::Queue< mozhegova::Queue< std::string > > & queue)
  {
    std::string line;
    while (std::getline(in, line))
    {
      mozhegova::Queue< std::string > infExpr;
      if (line.empty())
      {
        continue;
      }
      std::string temp;
      for (char c : line)
      {
        if (std::isdigit(c))
        {
          temp += c;
        }
        else if (std::isspace(c))
        {
          if (!temp.empty())
          {
            infExpr.push(temp);
            temp.clear();
          }
        }
        else
        {
          temp += c;
          infExpr.push(temp);
          temp.clear();
        }
      }
      if (!infExpr.empty())
      {
        queue.push(infExpr);
      }
    }
  }

  bool isOperand(std::string str)
  {
    bool flag = true;
    for (char c : str)
    {
      if (!std::isdigit(c))
      {
        flag = false;
      }
    }
    return flag;
  }

  bool isOperation(std::string op)
  {
    return op == "*" || op == "/" || op == "%" || op == "+" || op == "-";
  }

  int getPriority(std::string op)
  {
    if (op == "+" || op == "-")
    {
      return 1;
    }
    else if (op == "*" || op == "/" || op == "%")
    {
      return 2;
    }
    else
    {
      return 0;
    }
  }

  mozhegova::Queue< mozhegova::Queue< std::string > > convertInfToPost(mozhegova::Queue< mozhegova::Queue< std::string > > & queue)
  {
    mozhegova::Queue< mozhegova::Queue< std::string > > newQueue;
    while (!queue.empty())
    {
      mozhegova::Queue< std::string > infExpr = queue.front();
      queue.pop();
      mozhegova::Queue< std::string > postExpr;
      mozhegova::Stack< std::string > stack;
      while (!infExpr.empty())
      {
        std::string token = infExpr.front();
        infExpr.pop();
        if (isOperand(token))
        {
          postExpr.push(token);
        }
        else if (token == "(")
        {
          stack.push(token);
        }
        else if (token == ")")
        {
          while (!stack.empty() && stack.top() != "(")
          {
            postExpr.push(stack.top());
            stack.pop();
          }
          if (stack.top() == "(")
          {
            stack.pop();
          }
          else
          {
            throw std::logic_error("invalid expression");
          }
        }
        else if (isOperation(token))
        {
          while (!stack.empty() && getPriority(token) <= getPriority(stack.top()))
          {
            postExpr.push(stack.top());
            stack.pop();
          }
          stack.push(token);
        }
        else
        {
          throw std::logic_error("invalid expression");
        }
      }
      while (!stack.empty())
      {
        if (stack.top() == "(")
        {
          throw std::logic_error("invalid expression");
        }
        postExpr.push(stack.top());
        stack.pop();
      }
      newQueue.push(postExpr);
    }
    return newQueue;
  }

  mozhegova::Stack< long long > calculateExprs(mozhegova::Queue< mozhegova::Queue< std::string > > & queue)
  {
    mozhegova::Stack< long long > res;
    while (!queue.empty())
    {
      mozhegova::Queue< std::string > postExpr = queue.front();
      queue.pop();
      mozhegova::Stack< long long > stack;
      while (!postExpr.empty())
      {
        std::string token = postExpr.front();
        postExpr.pop();
        if (isOperand(token))
        {
          stack.push(std::stoll(token));
        }
        else
        {
          long long b = stack.top();
          stack.pop();
          long long a = stack.top();
          stack.pop();
          if (token == "+")
          {
            stack.push(a + b);
          }
          else if (token == "-")
          {
            stack.push(a - b);
          }
          else if (token == "*")
          {
            stack.push(a * b);
          }
          else if (token == "/")
          {
            stack.push(a / b);
          }
          else if (token == "%")
          {
            stack.push(a % b);
          }
        }
      }
      res.push(stack.top());
    }
    return res;
  }

  void outputRes(std::ostream & out, mozhegova::Stack< long long > & res)
  {
    out << res.top();
    res.pop();
    while (!res.empty())
    {
      out << " " << res.top();
      res.pop();
    }
  }
}

int main(int argc, char * argv[])
{
  using namespace mozhegova;
  Queue< Queue< std::string > > infExprs;
  Queue< Queue< std::string > > postExprs;
  try
  {
    if (argc > 1)
    {
      std::ifstream file(argv[1]);
      inputExprs(file, infExprs);
    }
    else
    {
      inputExprs(std::cin, infExprs);
    }
    postExprs = convertInfToPost(infExprs);
  }
  catch(const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  Stack< long long > results = calculateExprs(postExprs);
  outputRes(std::cout, results);
  std::cout << "\n";
}
