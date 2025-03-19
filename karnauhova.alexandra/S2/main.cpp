#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
  if (argc > 1)
  {
    std::ifstream file(argv[1]);
    if (file.is_open())
    {
      //processInput(file);
      file.close();
    }
    else
    {
      std::cerr << "Incorrect name file\n";
      return 1;
    }
  }
  else
  {
    //processInput(std::cin);
  }
  return 0;
}

void input_str(std::ifstream& in)
{
  std::string str;
  while (std::getline(in, str))
  {

  }
  in.clear();
}