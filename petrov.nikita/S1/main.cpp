#include "forward_ring_list.hpp"
#include <string>
#include "manipulations_with_fwd_ring_list.hpp"
#include <iostream>
#include <limits>

int main()
{
  petrov::ForwardRingList< std::pair< std::string, petrov::ForwardRingList< size_t > > > fwd_ring_list = {};
  petrov::inputValuesIntoFwdRingList(std::cin, fwd_ring_list);
  if (fwd_ring_list.empty())
  {
    std::cout << 0;
    std::cout << "\n";
    return 0;
  }
  petrov::outputNamesOfSuquences(std::cout, fwd_ring_list);
  petrov::ForwardRingList< size_t > sums = {};
  try
  {
    sums = petrov::getListOfSequencesFromListOfSums(fwd_ring_list);
  }
  catch(const std::out_of_range & e)
  {
    std::cerr << "\n" << e.what() << "\n";
    return 1;
  }
  sums.reverse();
  if (sums.empty())
  {
    std::cout << 0;
  }
  else
  {
    petrov::outputSums(std::cout, sums);
  }
  std::cout << "\n";
}
