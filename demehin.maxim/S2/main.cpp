#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
  std::istream* inputStream;
  std::ifstream fileInput;

  if (argc > 1)
  {
    fileInput.open(argv[1]);
    inputStream = &fileInput;
  }
  else
  {
    inputStream = &std::cin;
  }

  std::string expr;
  char c;
  while (inputStream->get(c))
  {
    if (c == '\n')
    {
      if (!expr.empty())
      {
        expr.clear();
      }
    }
    else
    {
      expr += c;
    }
  }

}
