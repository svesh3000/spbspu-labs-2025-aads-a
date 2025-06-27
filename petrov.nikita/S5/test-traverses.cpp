#include <boost/test/unit_test.hpp>
#include <sstream>
#include <avl_tree.hpp>
#include "traverse_info_handler.hpp"

BOOST_AUTO_TEST_SUITE(traverse_lnr)

BOOST_AUTO_TEST_CASE(traverse_empty_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  petrov::SumUpKeys summator;
  petrov::SumUpKeys new_summator = tree.traverse_lnr(summator);
  out << new_summator.result;
  BOOST_TEST(out.str() == "0");
}

BOOST_AUTO_TEST_CASE(traverse_three_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  tree.insert({ 5, "good" });
  tree.insert({ 6, "vibes" });
  tree.insert({ 7, "forever" });
  petrov::SumUpKeys summator;
  petrov::SumUpKeys new_summator = tree.traverse_lnr(summator);
  out << new_summator.result;
  BOOST_TEST(out.str() == "18");
}

BOOST_AUTO_TEST_CASE(traverse_five_element_tree)
{
  std::ostringstream out;
  petrov::AVLTree< int, std::string > tree;
  petrov::SumUpKeys summator;
  tree.insert({ 5, "good" });
  tree.insert({ 6, "vibes" });
  tree.insert({ 7, "forever" });
  tree.insert({ 15, "trust" });
  tree.insert({ 16, "me" });
  petrov::SumUpKeys new_summator = tree.traverse_lnr(summator);
  out << new_summator.result;
  BOOST_TEST(out.str() == "49");
}

BOOST_AUTO_TEST_SUITE_END()
