#include <boost/test/unit_test.hpp>
#include <sstream>
#include <tree/tree.hpp>

namespace
{
}

BOOST_AUTO_TEST_CASE(tree_test)
{
  demehin::Tree< size_t, std::string > tree;
  tree.insert(std::make_pair(1, "1"));
  tree.insert(std::make_pair(3, "4"));
  tree.insert(std::make_pair(10, "11"));
  tree.insert(std::make_pair(2, "3"));
  tree.insert(std::make_pair(4, "5"));
  for (auto it = tree.begin(); it != tree.end(); ++it)
  {
    std::cout << (*it).second << "\n";
  }
  demehin::Tree< size_t, std::string > cpy_tree(tree);

  tree.swap(cpy_tree);
  for (auto it = tree.begin(); it != tree.end(); ++it)
  {
    std::cout << (*it).second << "\n";
  }

  //auto it = cpy_tree.begin();
  //auto it2 = ++it;
  cpy_tree.erase(cpy_tree.begin(), cpy_tree.end());
  for (auto it = cpy_tree.begin(); it != cpy_tree.end(); ++it)
  {
    std::cout << (*it).second << "\n";
  }
}

BOOST_AUTO_TEST_CASE(tree_construct_test)
{
  demehin::Tree< size_t, std::string > tree;
  tree.insert(std::make_pair(1, "1"));
  tree.insert(std::make_pair(10, "10"));
  tree.insert(std::make_pair(3, "3"));
  demehin::Tree< size_t, std::string > tree_cpy(tree);
  BOOST_TEST(tree_cpy.size() == 3);
  BOOST_TEST((*tree_cpy.begin()).second == "1");
}
