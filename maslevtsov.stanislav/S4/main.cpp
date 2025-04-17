#include <iostream>
#include <fstream>
#include <string>
#include <map>

namespace maslevtsov {
  using set_t = std::map< int, std::string >;
  using setmap_t = std::map< std::string, set_t >;

  void input_setmap(std::istream& in, setmap_t& map);
  void print(std::ostream& out, const std::string& setname, const setmap_t& map);
}

void maslevtsov::input_setmap(std::istream& in, setmap_t& map)
{
  std::string setname, value;
  int key = 0;
  while (in) {
    set_t set;
    in >> setname;
    while (in && in.peek() != '\n') {
      in >> key >> value;
      set.insert(std::make_pair(key, value));
    }
    map.insert(std::make_pair(setname, set));
  }
}

void maslevtsov::print(std::ostream& out, const std::string& setname, const setmap_t& map)
{
  set_t set = map.at(setname);
  out << setname;
  for (auto it = set.cbegin(); it != set.cend(); ++it) {
    out << ' ' << it->first << ' ' << it->second;
  }
}

int main(int argc, char** argv)
{
  using namespace maslevtsov;
  if (argc != 2) {
    std::cerr << "<INVALID PARAMETERS>\n";
    return 1;
  }
  std::ifstream fin(argv[1]);
  if (!fin) {
    std::cerr << "<INVALID DATA FILE>\n";
    return 1;
  }
  setmap_t data_map;
  input_setmap(fin, data_map);
}
