#ifndef INPUTDICTIONARIES_HPP
#define INPUTDICTIONARIES_HPP
#include <istream>
#include <list>
#include <map>

namespace zakirov
{
  template < class K, class T >
  void get_dictionaries(std::istream & in, std::list< std::pair < std::string, std::map< K, T > > > & dictionaries);
}

#endif

