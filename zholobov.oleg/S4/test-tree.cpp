#include <boost/test/unit_test.hpp>
#include <list>

#include "tree.hpp"

namespace {
  template < typename Key, typename Value, typename Cmp = std::less< Key > >
  std::string toString(const zholobov::Tree< Key, Value, Cmp >& tree)
  {
    std::stringstream ss;
    if (tree.size() != 0) {
      auto it = tree.begin();
      ss << it->first << " " << (it++)->second;
      for (; it != tree.end(); ++it) {
        ss << " " << it->first << " " << it->second;
      }
    }
    return ss.str();
  }
}

BOOST_AUTO_TEST_SUITE(Tree_Constructors)

BOOST_AUTO_TEST_CASE(default_ctor)
{
  zholobov::Tree< int, std::string > tree;
  BOOST_TEST(tree.empty());
  BOOST_TEST(tree.size() == 0);

  zholobov::Tree< int, std::string, std::greater< int > > reverse_tree;
  BOOST_TEST(reverse_tree.empty());
  BOOST_TEST(reverse_tree.size() == 0);
}

BOOST_AUTO_TEST_CASE(initializer_list_ctor)
{
  zholobov::Tree< std::string, int > tree{
      {"this", 10}, {"that", 11}, {"zoom", 12}, {"these", 13}, {"ahead", 14}, {"those", 15}};
  BOOST_TEST(!tree.empty());
  BOOST_TEST(tree.size() == 6);
  BOOST_TEST(toString(tree) == "ahead 14 that 11 these 13 this 10 those 15 zoom 12");

  zholobov::Tree< std::string, int, std::greater< std::string > > reverse_tree{
      {"this", 10}, {"that", 11}, {"zoom", 12}, {"these", 13}, {"ahead", 14}, {"those", 15}};
  BOOST_TEST(!reverse_tree.empty());
  BOOST_TEST(reverse_tree.size() == 6);
  BOOST_TEST(toString(reverse_tree) == "zoom 12 those 15 this 10 these 13 that 11 ahead 14");
}

BOOST_AUTO_TEST_CASE(copy_ctor)
{
  zholobov::Tree< std::string, int > tree{
      {"this", 10}, {"that", 11}, {"zoom", 12}, {"these", 13}, {"ahead", 14}, {"those", 15}};
  BOOST_TEST(tree.size() == 6);
  zholobov::Tree< std::string, int > treeCopy(tree);
  BOOST_TEST(treeCopy.size() == 6);
  BOOST_TEST(toString(tree) == toString(treeCopy));
}

BOOST_AUTO_TEST_CASE(move_ctor)
{
  zholobov::Tree< std::string, int > tree{
      {"this", 10}, {"that", 11}, {"zoom", 12}, {"these", 13}, {"ahead", 14}, {"those", 15}};
  BOOST_TEST(tree.size() == 6);
  std::string tree_contents = toString(tree);
  zholobov::Tree< std::string, int > treeCopy(std::move(tree));
  BOOST_TEST(tree.size() == 0);
  BOOST_TEST(treeCopy.size() == 6);
  BOOST_TEST(toString(tree) == "");
  BOOST_TEST(toString(treeCopy) == tree_contents);
}

BOOST_AUTO_TEST_CASE(range_ctor)
{
  std::list< std::pair< std::string, int > > list{
      {"this", 10}, {"that", 11}, {"zoom", 12}, {"these", 13}, {"ahead", 14}, {"those", 15}};

  zholobov::Tree< std::string, int > tree(list.begin(), list.end());
  BOOST_TEST(tree.size() == 6);
  BOOST_TEST(toString(tree) == "ahead 14 that 11 these 13 this 10 those 15 zoom 12");

  zholobov::Tree< std::string, int, std::greater< std::string > > reverse_tree(list.begin(), list.end());
  BOOST_TEST(reverse_tree.size() == 6);
  BOOST_TEST(toString(reverse_tree) == "zoom 12 those 15 this 10 these 13 that 11 ahead 14");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Assignment_Operators)

BOOST_AUTO_TEST_CASE(copy_assignment)
{
  zholobov::Tree< std::string, int > tree{
      {"this", 10}, {"that", 11}, {"zoom", 12}, {"these", 13}, {"ahead", 14}, {"those", 15}};
  zholobov::Tree< std::string, int > other_tree{{"something", 3}, {"anything", 5}};
  tree = other_tree;
  BOOST_TEST(tree.size() == 2);
  BOOST_TEST(toString(tree) == "anything 5 something 3");
  BOOST_TEST(toString(tree) == toString(other_tree));
}

BOOST_AUTO_TEST_CASE(move_assignment)
{
  zholobov::Tree< std::string, int > tree{
      {"this", 10}, {"that", 11}, {"zoom", 12}, {"these", 13}, {"ahead", 14}, {"those", 15}};
  zholobov::Tree< std::string, int > other_tree{{"something", 3}, {"anything", 5}};
  tree = std::move(other_tree);
  BOOST_TEST(tree.size() == 2);
  BOOST_TEST(toString(tree) == "anything 5 something 3");
  BOOST_TEST(other_tree.empty());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Iterators)

BOOST_AUTO_TEST_CASE(iterators)
{
  zholobov::Tree< std::string, int > tree{
      {"this", 10}, {"that", 11}, {"zoom", 12}, {"these", 13}, {"ahead", 14}, {"those", 15}};
  BOOST_TEST(tree.begin()->first == "ahead");
  BOOST_TEST((--(tree.end()))->first == "zoom");

  BOOST_TEST(tree.cbegin()->first == "ahead");
  BOOST_TEST((--(tree.cend()))->first == "zoom");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Modifiers)

BOOST_AUTO_TEST_CASE(clear)
{
  zholobov::Tree< std::string, int > tree{{"something", 3}, {"anything", 5}};
  BOOST_TEST(tree.size() == 2);
  tree.clear();
  BOOST_TEST(tree.size() == 0);
}

BOOST_AUTO_TEST_CASE(insertion)
{
  zholobov::Tree< std::string, int > tree;
  auto result = tree.insert(std::make_pair("red", 200));
  BOOST_TEST(result.second);
  BOOST_TEST(result.first->first == "red");
  result = tree.insert(std::make_pair("green", 50));
  BOOST_TEST(tree.size() == 2);
  BOOST_TEST(result.second);
  BOOST_TEST(result.first->first == "green");
  result = tree.insert(std::make_pair("red", 100));
  BOOST_TEST(tree.size() == 2);
  BOOST_TEST(!result.second);
  BOOST_TEST(result.first->first == "red");
  BOOST_TEST(result.first->second == 200);
  result = tree.emplace("blue", 230);
  BOOST_TEST(tree.size() == 3);
  BOOST_TEST(result.second);
  BOOST_TEST(result.first->first == "blue");
  result = tree.emplace(std::make_pair("green", 30));
  BOOST_TEST(tree.size() == 3);
  BOOST_TEST(!result.second);
  BOOST_TEST(result.first->first == "green");
  BOOST_TEST(result.first->second == 50);

  auto hint = tree.lower_bound("alpha");
  BOOST_TEST(hint->first == "blue");
  tree.emplace_hint(hint, "alpha", 255);
  BOOST_TEST(tree.size() == 4);
  hint = tree.lower_bound("green");
  BOOST_TEST(hint->first == "green");
  hint = tree.upper_bound("green");
  BOOST_TEST(hint->first == "red");
  tree.emplace_hint(tree.end(), "cyan", 0);
  BOOST_TEST(tree.size() == 5);
  auto it = tree.emplace_hint(tree.end(), "cyan", 1);
  BOOST_TEST(tree.size() == 5);
  BOOST_TEST(it->first == "cyan");
  BOOST_TEST(toString(tree) == "alpha 255 blue 230 cyan 0 green 50 red 200");

  zholobov::Tree< int, char > otherTree;
  auto otherTreeHint = otherTree.cend();
  for (int i = 0; i < 10; ++i) {
    otherTreeHint = otherTree.emplace_hint(otherTreeHint, i, 'a' + i);
  }
  BOOST_TEST(toString(otherTree) == "0 a 1 b 2 c 3 d 4 e 5 f 6 g 7 h 8 i 9 j");

  zholobov::Tree< int, char > otherTree2;
  otherTree2.insert(++otherTree.cbegin(), --otherTree.cend());
  BOOST_TEST(toString(otherTree2) == "1 b 2 c 3 d 4 e 5 f 6 g 7 h 8 i");
}

BOOST_AUTO_TEST_SUITE_END()
