#include <iostream>
#include <fstream>
#include <tree/tree.hpp>
#include "key_summ.hpp"

namespace
{
  using Map = demehin::Tree< int, std::string >;

  void inputTree(std::istream& in, Map& tree)
  {
    int key;
    std::string val;
    while (in >> key >> val)
    {
      tree.insert(std::make_pair(key, val));
    }
  }
}

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    return 1;
  }

  std::ifstream file(argv[2]);
  Map tree;
  inputTree(file, tree);

  demehin::KeySumm sum;
  sum = tree.traverse_lnr(sum);
  std::cout << sum.val_res << " " << sum.str_res << "\n";
}
