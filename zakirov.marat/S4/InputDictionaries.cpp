#include "InputDictionaries.hpp"
#include <string>

template < class K, class T >
void zakirov::get_dictionaries(std::istream & in, std::list< std::pair < std::string, std::map< K, T > > > & dictionaries)
{
  std::string name;
  std::map< K, T > dict;
  K key;
  T value;
  while (in)
  {
    in >> name;
    while (in && in >> key && in >> value && in.peek() != '\n')
    {
      dict.insert({key, value})
    }

    dictionaries.insert({name, std::move(dict)});
  }
}
