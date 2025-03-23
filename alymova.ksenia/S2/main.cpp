#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>

/*int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Incorrect arguments\n";
    return 1;
  }
  std::ifstream input("file.txt");
  while (input.is_open() && !input.eof())
  {
    std::string s;
    std::getline(input, s);
    std::cout << s << "\n";
  }
  input.close();
}*/
int main()
{
  std::ifstream input("file.txt");
  while (input.is_open() && !input.eof())
  {
    std::string s;
    std::getline(input, s);
    std::cout << s << "\n";
  }
  input.close();
}
