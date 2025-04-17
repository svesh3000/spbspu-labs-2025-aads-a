#include <iostream>
#include <fstream>
#include <string>
#include <map>

namespace maslevtsov {
  using set = std::map< int, std::string >;
  using setmap = std::map< std::string, set >;
  void input_setmap(std::istream& in, setmap& map);
}

void maslevtsov::input_setmap(std::istream& in, setmap& map)
{
  std::string setname, value;
  int key = 0;
  while (in) {
    set s;
    in >> setname;
    while (in && in.peek() != '\n') {
      in >> key >> value;
      s.insert(std::make_pair(key, value));
    }
    map.insert(std::make_pair(setname, s));
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
  setmap data_map;
  input_setmap(fin, data_map);
}
