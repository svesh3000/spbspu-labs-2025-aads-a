#include <iostream>
#include <fstream>
#include <variant>

#include "queue.hpp"
#include "variant.hpp"

int main(int argc, char** argv)
{
  if (argc != 1)
  {
    std::cerr << "console arguments count doesn't match requirenment\n";
    return 1;
  }
  std::ifstream in(argv[0]);
  if (!in)
  {
    std::cerr << "failed to open file \"" << argv[0] << "\"\n";
    return 1;
  }
  rychkov::Queue< std::variant< int, char > > expression;
  int number = 0;
  while (in)
  {
    if (in >> number)
    {
      expression.push(number);
    }
    else if (!in.eof())
    {
      in.clear();
      char c = '\0';
      if (in >> c)
      {
        expression.push(c);
      }
    }
  }
}
