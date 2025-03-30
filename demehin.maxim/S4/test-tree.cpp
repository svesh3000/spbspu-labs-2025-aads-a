#include <boost/test/unit_test.hpp>
#include <sstream>
#include <tree/tree.hpp>

BOOST_AUTO_TEST_CASE(tree_construct_test)
{
  demehin::Tree< size_t, std::string > tree;
  tree.insert(std::make_pair(1, "1"));
  tree.insert(std::make_pair(3, "4"));
  tree.insert(std::make_pair(10, "11"));
  tree.insert(std::make_pair(2, "3"));
  std::cout << tree.at(1) << "\n";
  std::cout << tree.at(10) << "\n";
}
