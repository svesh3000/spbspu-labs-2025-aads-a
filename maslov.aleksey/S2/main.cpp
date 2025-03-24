#include <iostream>
#include <fstream>
#include <string>
#include "queue.hpp"

void inputFile(const std::string & filename, maslov::Queue< std::string > & queue)
{
  if (!filename.empty())
  {
    std::ifstream fileInput(filename);
    if (!fileInput.is_open())
    {
      throw std::runtime_error("ERROR: cannot open the file");
    }
    inputExpression(fileInput, queue);
    fileInput.close();
  }
  else
  {
    inputExpression(std::cin, queue);
  }
}

int main(int argc, char ** argv)
{
  std::string filename;
  if (argc > 1)
  {
    filename = argv[1];
  }
  maslov::Queue< std::string > queue;
  try
  {
    inputFile(filename, queue);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
