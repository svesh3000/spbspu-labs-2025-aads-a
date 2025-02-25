#include <ostream>
#include <forward_list>

std::ostream& outNames(std::ostream& out, std::forward_list< std::pair< std::string, std::forward_list< int > > > list)
{
  auto ptr = list.begin();
  auto end = list.end();
  out << ptr->first;
  ++ptr;
  while (ptr != end) {
    out << " " << ptr->first; 
    ++ptr;
  }
  return out;
}
std::ostream& outNumbers(std::ostream& out, std::forward_list< std::pair< std::string, std::forward_list< int > > > list, size_t maxLen, size_t n)
{
  
  for (size_t i = 0; i < maxLen; ++i) {
    
  }
}
