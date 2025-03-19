#include <iostream>

int main(int argc, char* argv[])
{
  if (argc > 1) {
    std::cout << "1 parameter. Will read from " << argv[1] << "\n";
  } else {
    std::cout << "No Params. Will read from std::cin\n";
  }
  return 0;
}
