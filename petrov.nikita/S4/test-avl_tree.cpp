#include <boost/test/unit_test.hpp>
#include <sstream>
#include <random>
#include "avl_tree.hpp"

BOOST_AUTO_TEST_SUITE(empty_method)

BOOST_AUTO_TEST_CASE(empty_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  out << tree.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(not_empty_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "hi" });
  out << tree.empty();
  BOOST_TEST(out.str() == "0");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(size_method)

BOOST_AUTO_TEST_CASE(no_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  out << tree.size();
  BOOST_TEST(out.str() == "0");
}

BOOST_AUTO_TEST_CASE(one_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "hi" });
  out << tree.size();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(ya_one_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "hi" });
  tree.insert({ 1, "my" });
  tree.insert({ 1, "best" });
  tree.insert({ 1, "friend" });
  out << tree.size();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(three_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "hi" });
  tree.insert({ 2, "my" });
  tree.insert({ 3, "friend" });
  out << tree.size();
  BOOST_TEST(out.str() == "3");
}

BOOST_AUTO_TEST_CASE(ya_three_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "hi" });
  tree.insert({ 2, "my" });
  tree.insert({ 2, "best" });
  tree.insert({ 3, "friend" });
  out << tree.size();
  BOOST_TEST(out.str() == "3");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(clear_method)

BOOST_AUTO_TEST_CASE(clear_empty_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.clear();
  out << tree.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(clear_one_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "hi" });
  tree.clear();
  out << tree.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(clear_three_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "hi" });
  tree.insert({ 2, "my" });
  tree.insert({ 3, "friend" });
  tree.clear();
  out << tree.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(clear_five_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "I" });
  tree.insert({ 2, "like" });
  tree.insert({ 3, "eating" });
  tree.insert({ 4, "fresh"});
  tree.insert({ 5, "cats"});
  tree.clear();
  out << tree.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(insert_method)

BOOST_AUTO_TEST_CASE(insert_one_element)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "hi" });
  out << tree[1];
  BOOST_TEST(out.str() == "hi");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(going_through_tree)

BOOST_AUTO_TEST_CASE(empty_avl_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  for (auto it = tree.cbegin(); it != tree.cend(); ++it)
  {
    out << it->second;
    BOOST_TEST(out.str() == "");
  }
}

BOOST_AUTO_TEST_CASE(one_element_avl_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "hi" });
  for (auto it = tree.cbegin(); it != tree.cend(); ++it)
  {
    out << it->second;
  }
  BOOST_TEST(out.str() == "hi");
}

BOOST_AUTO_TEST_CASE(two_element_avl_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "hi" });
  tree.insert({ 2, "cute" });
  for (auto it = tree.cbegin(); it != tree.cend(); ++it)
  {
    out << it->second;
  }
  BOOST_TEST(out.str() == "hicute");
}

BOOST_AUTO_TEST_CASE(ya_two_element_avl_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 2, "cute" });
  tree.insert({ 1, "hi" });
  for (auto it = tree.begin(); it != tree.end(); ++it)
  {
    out << it->second;
  }
  BOOST_TEST(out.str() == "hicute");
}

BOOST_AUTO_TEST_CASE(three_element_avl_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 2, "cute" });
  tree.insert({ 1, "hi" });
  tree.insert({ 3, "cat" });
  for (auto it = tree.cbegin(); it != tree.cend(); ++it)
  {
    out << it->second;
  }
  BOOST_TEST(out.str() == "hicutecat");
}

BOOST_AUTO_TEST_CASE(five_element_avl_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 3, "very" });
  tree.insert({ 1, "hi" });
  tree.insert({ 2, "cute" });
  tree.insert({ 4, "tasty" });
  tree.insert({ 5, "cat" });
  for (auto it = tree.begin(); it != tree.end(); ++it)
  {
    out << it->second;
  }
  BOOST_TEST(out.str() == "hicuteverytastycat");
}

BOOST_AUTO_TEST_CASE(ya_five_element_avl_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "very" });
  tree.insert({ 2, "hi" });
  tree.insert({ 3, "cute" });
  tree.insert({ 4, "tasty" });
  tree.insert({ 5, "cat" });
  for (auto it = tree.begin(); it != tree.end(); ++it)
  {
    out << it->second;
  }
  BOOST_TEST(out.str() == "veryhicutetastycat");
}

BOOST_AUTO_TEST_CASE(eleven_element_avl_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  tree.insert({ 6, 6 });
  tree.insert({ 2, 2 });
  tree.insert({ 1, 1 });
  tree.insert({ 4, 4 });
  tree.insert({ 3, 3 });
  tree.insert({ 5, 5 });
  tree.insert({ 9, 9 });
  tree.insert({ 7, 7 });
  tree.insert({ 8, 8 });
  tree.insert({ 11, 11 });
  tree.insert({ 10, 10 });
  for (auto it = tree.begin(); it != tree.end(); ++it)
  {
    out << it->second;
  }
  BOOST_TEST(out.str() == "1234567891011");
}

BOOST_AUTO_TEST_CASE(return_it_val_test)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  auto it_1 = tree.insert({ 6, 6 }).first;
  auto it_2 = tree.insert({ 2, 2 }).first;
  tree.insert({ 1, 1 });
  auto it_3 = tree.insert({ 4, 4 }).first;
  tree.insert({ 3, 3 });
  auto it_4 = tree.insert({ 5, 5 }).first;
  tree.insert({ 9, 9 });
  tree.insert({ 7, 7 });
  tree.insert({ 8, 8 });
  tree.insert({ 11, 11 });
  tree.insert({ 10, 10 });
  out << *it_1 << " " << *it_2 << " " << *it_3 << " ";
  out << *it_4;
  BOOST_TEST(out.str() == "6 2 4 5");
 }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(stress_tests)

BOOST_AUTO_TEST_CASE(stress_test)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  for (size_t i = 0; i < 1000000; ++i)
  {
    tree.insert({ i, i });
  }
  tree.clear();
  out << tree.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(stress_test_2)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  for (size_t i = 1000000; i != 0; --i)
  {
    tree.insert({ i, i });
  }
  tree.clear();
  out << tree.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(stress_test_3)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  for (size_t i = 0; i < 53; ++i)
  {
    tree.insert({ i, i });
  }
  tree.clear();
  out << tree.empty();
  BOOST_TEST(out.str() == "1");
}
/*
BOOST_AUTO_TEST_CASE(stress_test_4)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  for (size_t i = 0; i < 10000000; ++i)
  {
    tree.insert({ i, i });
  }
  tree.clear();
  out << tree.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(stress_test_5)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  for (size_t i = 0; i < 10000001; ++i)
  {
    tree.insert({ i, i });
  }
  tree.clear();
  out << tree.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(stress_test_6)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  for (size_t i = 0; i < 10000002; ++i)
  {
    tree.insert({ i, i });
  }
  tree.clear();
  out << tree.empty();
  BOOST_TEST(out.str() == "1");
}
*/
BOOST_AUTO_TEST_CASE(stress_test_7)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  for (size_t i = 0; i < 500; ++i)
  {
    tree.insert({ rand(), i });
  }
  tree.clear();
  out << tree.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(find_method)

BOOST_AUTO_TEST_CASE(find_not_existent_element_1)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  auto it = tree.find(1);
  out << (it == tree.end());
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(find_not_existent_element_2)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  tree.insert({ 1, 1 });
  auto it = tree.find(2);
  out << (it == tree.end());
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(find_not_existent_element_3)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "very" });
  tree.insert({ 2, "hi" });
  tree.insert({ 3, "cute" });
  tree.insert({ 4, "tasty" });
  tree.insert({ 5, "cat" });
  auto it = tree.find(6);
  out << (it == tree.end());
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(find_one_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  tree.insert({ 1, 1 });
  auto it = tree.find(1);
  out << it->second;
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(find_eleven_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  for (size_t i = 1; i <= 11; ++i)
  {
    tree.insert({ i, i });
  }
  auto it_1 = tree.find(11);
  auto it_2 = tree.find(7);
  out << it_1->second << " " << it_2->second;
  BOOST_TEST(out.str() == "11 7");
}

BOOST_AUTO_TEST_CASE(find_five_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "very" });
  tree.insert({ 2, "hi" });
  tree.insert({ 3, "cute" });
  tree.insert({ 4, "tasty" });
  tree.insert({ 5, "cat" });
  auto it_1 = tree.find(2);
  auto it_2 = tree.find(5);
  out << it_1->second << " " << it_2->second;
  BOOST_TEST(out.str() == "hi cat");
}

BOOST_AUTO_TEST_CASE(find_hundred_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  for (size_t i = 0; i < 100; ++i)
  {
    tree.insert({ i, i });
  }
  out << tree.find(52)->first << " " << tree.find(52)->second;
  BOOST_TEST(out.str() == "52 52");
}

BOOST_AUTO_TEST_CASE(find_const_hundred_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  for (size_t i = 0; i < 100; ++i)
  {
    tree.insert({ i, i });
  }
  const petrov::AVLTree< int, int > c_tree(tree);
  petrov::ConstAVLTreeIterator< int, int > it = c_tree.find(52);
  out << it->first << " " << it->second;
  BOOST_TEST(out.str() == "52 52");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(erase_method)

BOOST_AUTO_TEST_CASE(erase_one_element)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  tree.insert({ 1, 1 });
  tree.erase(1);
  out << tree.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(erase_three_elements)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "very" });
  tree.insert({ 2, "hi" });
  tree.insert({ 3, "cute" });
  tree.insert({ 4, "tasty" });
  tree.insert({ 5, "cat" });
  tree.erase(2);
  tree.erase(3);
  tree.erase(5);
  for (auto it = tree.cbegin(); it != tree.cend(); ++it)
  {
    out << it->second;
  }
  BOOST_TEST(out.str() == "verytasty");
}

BOOST_AUTO_TEST_CASE(erase_five_elements)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  tree.insert({ 6, 6 });
  tree.insert({ 2, 2 });
  tree.insert({ 1, 1 });
  tree.insert({ 4, 4 });
  tree.insert({ 3, 3 });
  tree.insert({ 5, 5 });
  tree.insert({ 9, 9 });
  tree.insert({ 7, 7 });
  tree.insert({ 8, 8 });
  tree.insert({ 11, 11 });
  tree.insert({ 10, 10 });
  tree.erase(5);
  tree.erase(8);
  tree.erase(11);
  tree.erase(6);
  tree.erase(1);
  for (auto it = tree.cbegin(); it != tree.cend(); ++it)
  {
    out << it->second;
  }
  BOOST_TEST(out.str() == "2347910");
}

BOOST_AUTO_TEST_CASE(erase_stress_test)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  for (size_t i = 0; i < 1000000; ++i)
  {
    tree.insert({ i, i });
  }
  for (size_t i = 0; i < 1000000; ++i)
  {
    tree.erase(i);
  }
  out << tree.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(at_method)
/*
BOOST_AUTO_TEST_CASE(find_not_existent_element_1)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  auto val = tree.at(1);
  out << val;
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(find_not_existent_element_2)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  tree.insert({ 1, 1 });
  auto val = tree.at(2);
  out << val;
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(find_not_existent_element_3)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "very" });
  tree.insert({ 2, "hi" });
  tree.insert({ 3, "cute" });
  tree.insert({ 4, "tasty" });
  tree.insert({ 5, "cat" });
  auto val = tree.at(6);
  out << val;
  BOOST_TEST(out.str() == "1");
}
*/
BOOST_AUTO_TEST_CASE(find_one_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  tree.insert({ 1, 1 });
  auto val = tree.at(1);
  out << val;
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(find_eleven_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  for (size_t i = 1; i <= 11; ++i)
  {
    tree.insert({ i, i });
  }
  auto val_1 = tree.at(11);
  auto val_2 = tree.at(7);
  out << val_1 << " " << val_2;
  BOOST_TEST(out.str() == "11 7");
}

BOOST_AUTO_TEST_CASE(find_five_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "very" });
  tree.insert({ 2, "hi" });
  tree.insert({ 3, "cute" });
  tree.insert({ 4, "tasty" });
  tree.insert({ 5, "cat" });
  auto val_1 = tree.at(2);
  auto val_2 = tree.at(5);
  out << val_1 << " " << val_2;
  BOOST_TEST(out.str() == "hi cat");
}

BOOST_AUTO_TEST_CASE(find_hundred_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  for (size_t i = 0; i < 100; ++i)
  {
    tree.insert({ i, i });
  }
  out << tree.at(52) << " " << tree.at(52);
  BOOST_TEST(out.str() == "52 52");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(index_operator)

BOOST_AUTO_TEST_CASE(find_not_existent_element_1)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  tree[2];
  out << tree.find(2)->first;
  BOOST_TEST(out.str() == "2");
}

BOOST_AUTO_TEST_CASE(find_not_existent_element_2)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  tree[2] = 4;
  out << tree.find(2)->first << " " << tree.find(2)->second;
  BOOST_TEST(out.str() == "2 4");
}

BOOST_AUTO_TEST_CASE(find_not_existent_element_7)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  tree[2] = 5;
  tree[1] = 6;
  tree[3] = 7;
  out << tree[1] << " " << tree[2] << " " << tree[3];
  BOOST_TEST(out.str() == "6 5 7");
}

BOOST_AUTO_TEST_CASE(find_not_existent_element_3)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "very" });
  tree.insert({ 2, "hi" });
  tree.insert({ 3, "cute" });
  tree.insert({ 4, "tasty" });
  tree.insert({ 5, "cat" });
  tree[6] = "eat";
  out << tree.find(6)->first << " " << tree.find(6)->second;
  BOOST_TEST(out.str() == "6 eat");
}

BOOST_AUTO_TEST_CASE(find_not_existent_element_4)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "very" });
  tree.insert({ 2, "hi" });
  tree.insert({ 3, "cute" });
  tree.insert({ 4, "tasty" });
  tree.insert({ 5, "cat" });
  tree[7] = "hi";
  out << tree.find(7)->first << " " << tree.find(7)->second;
  BOOST_TEST(out.str() == "7 hi");
}

BOOST_AUTO_TEST_CASE(find_not_existent_element_5)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  for (size_t i = 1; i <= 11; ++i)
  {
    tree.insert({ i, i });
  }
  tree[100] = 101;
  tree[105] = 102;
  out << tree[100] << " " << tree[105];
  BOOST_TEST(out.str() == "101 102");
}

BOOST_AUTO_TEST_CASE(find_one_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  tree.insert({ 1, 1 });
  auto val = tree[1];
  out << val;
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(find_eleven_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  for (size_t i = 1; i <= 11; ++i)
  {
    tree.insert({ i, i });
  }
  auto val_1 = tree[11];
  auto val_2 = tree[7];
  out << val_1 << " " << val_2;
  BOOST_TEST(out.str() == "11 7");
}

BOOST_AUTO_TEST_CASE(find_five_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "very" });
  tree.insert({ 2, "hi" });
  tree.insert({ 3, "cute" });
  tree.insert({ 4, "tasty" });
  tree.insert({ 5, "cat" });
  auto val_1 = tree[2];
  auto val_2 = tree[5];
  out << val_1 << " " << val_2;
  BOOST_TEST(out.str() == "hi cat");
}

BOOST_AUTO_TEST_CASE(find_hundred_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  for (size_t i = 0; i < 100; ++i)
  {
    tree.insert({ i, i });
  }
  out << tree[52] << " " << tree[52];
  BOOST_TEST(out.str() == "52 52");
}

BOOST_AUTO_TEST_CASE(find_five_element_tree_2)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 1, "very" });
  tree.insert({ 2, "hi" });
  tree.insert({ 3, "cute" });
  tree.insert({ 4, "tasty" });
  tree.insert({ 5, "cat" });
  auto val_1 = tree[2];
  tree[100] = "meat";
  out << val_1 << " " << tree.find(100)->first << " " << tree.find(100)->second;
  BOOST_TEST(out.str() == "hi 100 meat");
}

BOOST_AUTO_TEST_CASE(ya_index_operator_test)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree[1] = "very";
  tree[2] = "hi";
  tree[3] = "cute";
  tree[2] = "hello";
  tree[4] = "tasty";
  tree[5] = "cat";
  tree[1] = "verymuch";
  tree[5] = "kitten";
  for (auto it = tree.cbegin(); it != tree.cend(); ++it)
  {
    out << *it << " ";
  }
  out << tree.size();
  BOOST_TEST(out.str() == "verymuch hello cute tasty kitten 5");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(equal_range_method)

BOOST_AUTO_TEST_CASE(equal_range_example)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 0, "zero" });
  tree.insert({ 1, "one" });
  tree.insert({ 2, "two" });
  auto p = tree.equal_range(1);
  out << p.first->first << " " << p.first->second << " ";
  out << p.second->first << " " << p.second->second << " ";
  auto pp = tree.equal_range(-1);
  out << pp.first->first << " " << pp.first->second << " ";
  out << pp.second->first << " " << pp.second->second << " ";
  auto ppp = tree.equal_range(3);
  out << std::boolalpha << (ppp.first == tree.end()) << " ";
  out << std::boolalpha << (ppp.second == tree.end());
  BOOST_TEST(out.str() == "1 one 2 two 0 zero 0 zero true true");
}

BOOST_AUTO_TEST_CASE(equal_range_example_const)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > first_tree;
  first_tree.insert({ 0, "zero" });
  first_tree.insert({ 1, "one" });
  first_tree.insert({ 2, "two" });
  const petrov::AVLTree< int, std::string > tree(first_tree);
  auto p = tree.equal_range(1);
  out << p.first->first << " " << p.first->second << " ";
  out << p.second->first << " " << p.second->second << " ";
  auto pp = tree.equal_range(-1);
  out << pp.first->first << " " << pp.first->second << " ";
  out << pp.second->first << " " << pp.second->second << " ";
  auto ppp = tree.equal_range(3);
  out << std::boolalpha << (ppp.first == tree.cend()) << " ";
  out << std::boolalpha << (ppp.second == tree.cend());
  BOOST_TEST(out.str() == "1 one 2 two 0 zero 0 zero true true");
}

BOOST_AUTO_TEST_CASE(equal_range_example_almost_end)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 0, "zero" });
  tree.insert({ 1, "one" });
  tree.insert({ 2, "two" });
  auto pair = tree.equal_range(2);
  out << pair.first->first << " " << pair.first->second << " ";
  out << std::boolalpha << (pair.second == tree.end());
  BOOST_TEST(out.str() == "2 two true");
}

BOOST_AUTO_TEST_CASE(equal_range_empty_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  auto pair = tree.equal_range(0);
  out << std::boolalpha << (pair.first == tree.end()) << " ";
  out << std::boolalpha << (pair.second == tree.end()) << " ";
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(count_method)

BOOST_AUTO_TEST_CASE(count_empty)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  out << tree.count(1);
  BOOST_TEST(out.str() == "0");
}

BOOST_AUTO_TEST_CASE(count_one_el_not_exists)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  tree.insert({ 0, 0 });
  out << tree.count(1);
  BOOST_TEST(out.str() == "0");
}

BOOST_AUTO_TEST_CASE(count_one_el_exists)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  tree.insert({ 0, 0 });
  out << tree.count(0);
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(count_three_el_not_exists)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  tree.insert({ 0, 0 });
  tree.insert({ 10, 10 });
  tree.insert({ 5, 5 });
  out << tree.count(3);
  BOOST_TEST(out.str() == "0");
}

BOOST_AUTO_TEST_CASE(count_three_el_exists)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  tree.insert({ 0, 0 });
  tree.insert({ 10, 10 });
  tree.insert({ 5, 5 });
  out << tree.count(0);
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(initializer_list_constructor)

BOOST_AUTO_TEST_CASE(empty_il)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree { };
  out << tree.empty() << " " << tree.size();
  BOOST_TEST(out.str() == "1 0");
}

BOOST_AUTO_TEST_CASE(one_el_il)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree { { 1, 1 } };
  out << tree.cbegin()->first << " " << tree.cbegin()->second << " " << tree.empty() << " " << tree.size();
  BOOST_TEST(out.str() == "1 1 0 1");
}

BOOST_AUTO_TEST_CASE(three_el_il)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree { { 1, 1 }, { -1, -1 }, { 0, 0 } };
  for (auto it = tree.cbegin(); it != tree.cend(); ++it)
  {
    out << it->first << " " << it->second << " ";
  }
  out << tree.empty() << " " << tree.size();
  BOOST_TEST(out.str() == "-1 -1 0 0 1 1 0 3");
}

BOOST_AUTO_TEST_CASE(five_el_il)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree { { 7, 7 }, { 4, 4 }, { 5, 5 }, { 1, 1 }, { 6, 6 }, { 7, 7 } };
  for (auto it = tree.cbegin(); it != tree.cend(); ++it)
  {
    out << it->first << " " << it->second << " ";
  }
  out << tree.empty() << " " << tree.size();
  BOOST_TEST(out.str() == "1 1 4 4 5 5 6 6 7 7 0 5");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(erase_range)

BOOST_AUTO_TEST_CASE(erase_empty)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree;
  auto it = tree.erase(tree.cbegin(), tree.cend());
  out << tree.empty() << " " << tree.size() << " ";
  out << std::boolalpha << (it == tree.end());
  BOOST_TEST(out.str() == "1 0 true");
}

BOOST_AUTO_TEST_CASE(erase_almost_all)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree { { 7, 7 }, { 4, 4 }, { 5, 5 }, { 1, 1 }, { 6, 6 } };
  auto it = tree.erase(++(tree.cbegin()), tree.cend());
  for (auto it = tree.cbegin(); it != tree.cend(); ++it)
  {
    out << it->first << " " << it->second << " ";
  }
  out << tree.empty() << " " << tree.size() << " " << std::boolalpha << (it == tree.end());;
  BOOST_TEST(out.str() == "1 1 0 1 true");
}

BOOST_AUTO_TEST_CASE(erase_three_between)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree { { 7, 7 }, { 4, 4 }, { 5, 5 }, { 1, 1 }, { 6, 6 } };
  auto first_it = ++tree.cbegin();
  auto last_it = ++tree.cbegin();
  ++last_it;
  ++last_it;
  ++last_it;
  auto it = tree.erase(first_it, last_it);
  for (auto it = tree.cbegin(); it != tree.cend(); ++it)
  {
    out << it->first << " " << it->second << " ";
  }
  out << tree.empty() << " " << tree.size() << " "<< it->first << " " << it->second;
  BOOST_TEST(out.str() == "1 1 7 7 0 2 7 7");
}

BOOST_AUTO_TEST_CASE(erase_nothing)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree { { 7, 7 }, { 4, 4 }, { 5, 5 }, { 1, 1 }, { 6, 6 } };
  auto first_it = ++tree.cbegin();
  auto last_it = ++tree.cbegin();
  auto it = tree.erase(first_it, last_it);
  for (auto it = tree.cbegin(); it != tree.cend(); ++it)
  {
    out << it->first << " " << it->second << " ";
  }
  out << tree.empty() << " " << tree.size() << " " << it->first << " " << it->second;
  BOOST_TEST(out.str() == "1 1 4 4 5 5 6 6 7 7 0 5 4 4");
}

BOOST_AUTO_TEST_CASE(erase_all)
{
  std::ostringstream out;
  petrov::AVLTree< int, int > tree { { 7, 7 }, { 4, 4 }, { 5, 5 }, { 1, 1 }, { 6, 6 } };
  auto it = tree.erase(tree.cbegin(), tree.cend());
  out << tree.empty() << " " << tree.size() << " " << std::boolalpha << (it == tree.end());
  BOOST_TEST(out.str() == "1 0 true");
}

BOOST_AUTO_TEST_SUITE_END()
