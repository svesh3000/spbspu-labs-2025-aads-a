#include <iostream>
#include <fstream>
#include <string>
#include "queue.hpp"

namespace
{
  void inputExprs(std::istream & in, mozhegova::Queue< mozhegova::Queue< std::string > > & queue)
  {
    std::string line;
    while (std::getline(in, line) && !line.empty())
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
}

int main(int argc, char * argv[])
{
  using namespace mozhegova;
  Queue< Queue< std::string > > infExprs;
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
  }
  catch(const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
