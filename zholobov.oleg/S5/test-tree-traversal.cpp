#include <boost/test/unit_test.hpp>

#include <tree/tree.hpp>

namespace {

  zholobov::Tree< int, std::string > createTestTree()
  {
    zholobov::Tree< int, std::string > tree;
    tree[0] = "zero";
    tree[1] = "one";
    tree[2] = "two";
    tree[3] = "three";
    tree[4] = "four";
    tree[5] = "five";
    tree[6] = "six";
    tree[7] = "seven";
    tree[8] = "eight";
    tree[9] = "nine";
    return tree;
  }

}

BOOST_AUTO_TEST_SUITE(Tree_Traversal)

BOOST_AUTO_TEST_CASE(traversal_lnr)
{
  auto tree = createTestTree();
  int sum = 0;
  std::string result;
  auto func = [&sum, &result](const decltype(tree)::value_type& val) {
    sum += val.first;
    result += (" " + val.second);
  };
  tree.traverse_lnr(func);
  BOOST_TEST(sum == 45);
  BOOST_TEST(result == " zero one two three four five six seven eight nine");
}

BOOST_AUTO_TEST_CASE(traversal_rnl)
{
  auto tree = createTestTree();
  int sum = 0;
  std::string result;
  auto func = [&sum, &result](const decltype(tree)::value_type& val) {
    sum += val.first;
    result += (" " + val.second);
  };
  tree.traverse_rnl(func);
  BOOST_TEST(sum == 45);
  BOOST_TEST(result == " nine eight seven six five four three two one zero");
}

BOOST_AUTO_TEST_CASE(traversal_breadth)
{
  auto tree = createTestTree();
  int sum = 0;
  std::string result;
  auto func = [&sum, &result](const decltype(tree)::value_type& val) {
    sum += val.first;
    result += (" " + val.second);
  };
  tree.traverse_breadth(func);
  BOOST_TEST(sum == 45);
  BOOST_TEST(result == " three one seven zero two five eight four six nine");
}

BOOST_AUTO_TEST_SUITE_END()
