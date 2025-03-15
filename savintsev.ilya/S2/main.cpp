#include <iostream>
#include <fstream>
#include <stack>
#include "postfix-utils.h"

int main(int argc, char ** argv)
{
  if (argc > 2)
  {
    std::cerr << "ERROR: Too many arguments\n";
    return 1;
  }

  std::ifstream in;

  if (argc == 2)
  {
    in.open(argv[1]);
    try
    {
      savintsev::io_postfix_results(in);
    }
    catch (const std::invalid_argument & e)
    {
      std::cerr << e.what() << '\n';
      in.close();
      return 2;
    }
    in.close();
  }
  else
  {
    try
    {
      savintsev::io_postfix_results(std::cin);
    }
    catch (const std::invalid_argument & e)
    {
      std::cerr << e.what() << '\n';
      return 2;
    }
  }
}
