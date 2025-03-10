#include <iostream>
#include "getSequance.hpp"
#include "outSequance.hpp"

int main()
{
  dribas::List< std::pair< std::string, dribas::List< int > > > sequance;

  try {
    sequance = dribas::getSequance(std::cin);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }

  dribas::getSequanceName(std::cout, sequance);
  std::cout << '\n';
}
