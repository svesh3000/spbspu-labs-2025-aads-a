#include <iostream>

int main(int argc, char **argv)
{

  if (argc ==1)
  {

  }
  else
  {
    std::cerr << "ERROR: the file is not specified!";
    return 1;
  }
  return 0;
}
