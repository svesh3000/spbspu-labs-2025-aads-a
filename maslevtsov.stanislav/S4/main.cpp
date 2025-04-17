#include <iostream>
#include <fstream>
#include <string>
#include <map>

namespace maslevtsov {
  using set_t = std::map< int, std::string >;
  using setmap_t = std::map< std::string, set_t >;

  void input_setmap(std::istream& in, setmap_t& map);
  void print_set(std::ostream& out, const setmap_t& map, const std::string& setname);
  void complement_sets(setmap_t& map, const std::string& newname, const std::string& setname1,
    const std::string& setname2);
  void intersect_sets(setmap_t& map, const std::string& newname, const std::string& setname1,
    const std::string& setname2);
  void union_sets(setmap_t& map, const std::string& newname, const std::string& setname1, const std::string& setname2);
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

void maslevtsov::print_set(std::ostream& out, const setmap_t& map, const std::string& setname)
{
  set_t set;
  try {
    set = map.at(setname);
  } catch (const std::out_of_range&) {
    out << "<EMPTY>\n";
    return;
  }
  out << setname;
  for (auto it = set.cbegin(); it != set.cend(); ++it) {
    out << ' ' << it->first << ' ' << it->second;
  }
}

void maslevtsov::complement_sets(setmap_t& map, const std::string& newname, const std::string& setname1,
  const std::string& setname2)
{
  set_t set1 = map.at(setname1), set2 = map.at(setname2);
  set_t newset;
  for (auto it = set1.cbegin(); it != set1.cend(); ++it) {
    if (set2.find(it->first) == set2.end()) {
      newset.insert(std::make_pair(it->first, it->second));
    }
  }
  map.insert(std::make_pair(newname, newset));
}

void maslevtsov::intersect_sets(setmap_t& map, const std::string& newname, const std::string& setname1,
  const std::string& setname2)
{
  set_t set1 = map.at(setname1), set2 = map.at(setname2);
  set_t newset;
  for (auto it = set1.cbegin(); it != set1.cend(); ++it) {
    if (set2.find(it->first) != set2.end()) {
      newset.insert(std::make_pair(it->first, it->second));
    }
  }
  map.insert(std::make_pair(newname, newset));
}

void maslevtsov::union_sets(setmap_t& map, const std::string& newname, const std::string& setname1,
  const std::string& setname2)
{
  set_t set1 = map.at(setname1), set2 = map.at(setname2);
  set_t newset;
  for (auto it = set1.cbegin(); it != set1.cend(); ++it) {
    newset.insert(std::make_pair(it->first, it->second));
  }
  for (auto it = set2.cbegin(); it != set2.cend(); ++it) {
    newset.insert(std::make_pair(it->first, it->second));
  }
  map.insert(std::make_pair(newname, newset));
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

  std::string command;
  while (std::cin) {
    std::cin >> command;
    if (std::cin.eof()) {
      break;
    }
    std::string setname;
    try {
      if (command == "print") {
        std::cin >> setname;
        print_set(std::cout, data_map, setname);
        std::cout << '\n';
      } else if (command == "complement") {
        std::string newname, setname2;
        std::cin >> newname >> setname >> setname2;
        complement_sets(data_map, newname, setname, setname2);
      } else if (command == "intersect") {
        std::string newname, setname2;
        std::cin >> newname >> setname >> setname2;
        intersect_sets(data_map, newname, setname, setname2);
      } else if (command == "union") {
        std::string newname, setname2;
        std::cin >> newname >> setname >> setname2;
        union_sets(data_map, newname, setname, setname2);
      } else {
        std::cout << "<INVALID COMMAND>\n";
      }
    } catch (const std::out_of_range&) {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
