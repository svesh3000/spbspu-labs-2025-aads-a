#include "sequencefunctions.h"

int main(int argc, char* argv[])
{
  //sequence_list_t sequences = asafov::getSequences();
  int* a = new int;
  *a = 1;
  sequence_list_t sequences;
  data_list_t data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  sequences.push_back(std::make_pair("asd", data));
  data_list_t data2;
  data2.push_back(4);
  data2.push_back(5);
  sequences.push_back(std::make_pair("fgh", data2));
  data_list_t data3;
  data3.push_back(6);
  sequences.push_back(std::make_pair("jkl", data3));
  asafov::outputSequences(sequences);

  /*for (auto it = sequences.begin(); it != sequences.end(); ++it)
  {
    std::cout << it->first << ':';
    for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) std::cout << ' ' << *it2;
    std::cout << '\n';
  }*/

  return 0;   
} 
