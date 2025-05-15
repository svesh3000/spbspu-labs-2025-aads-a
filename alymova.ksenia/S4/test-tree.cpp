#include <boost/test/unit_test.hpp>
#include "tree-2-3.hpp"
#include "tree-iterators.hpp"

BOOST_AUTO_TEST_CASE(test_constructors_operators)
{
  using Tree = alymova::TwoThreeTree< size_t, std::string, std::less< size_t > >;

  Tree tree1;
  BOOST_TEST(tree1.empty());
  Tree tree2(tree1);
  BOOST_TEST(tree1 == tree2);

  Tree tree3(Tree({}));
  BOOST_TEST(tree3 == tree1);

  Tree tree4({});
  BOOST_TEST(tree4 == tree1);

  Tree tree5({{1, "cat"}, {2, "dog"}});
  BOOST_TEST(tree5.size() == 2);
  BOOST_TEST(tree5[1] == "cat");

  Tree tree6(tree5);
  BOOST_TEST(tree6 == tree5);

  Tree tree7(tree1.begin(), tree2.end());
  BOOST_TEST(tree7 == tree1);
  Tree tree8(tree5.begin(), tree5.end());
  BOOST_TEST(tree8 == tree5);

  tree2 = tree5;
  BOOST_TEST(tree2 == tree5);

  tree3 = Tree(tree5.begin(), tree5.end());
  BOOST_TEST(tree5 == tree5);
}
BOOST_AUTO_TEST_CASE(test_iterators)
{
  using Tree = alymova::TwoThreeTree< size_t, std::string, std::less< size_t > >;
  using Iterator = alymova::TTTIterator< size_t, std::string, std::less< size_t > >;
  using ConstIterator = alymova::TTTConstIterator< size_t, std::string, std::less< size_t > >;

  std::pair< size_t, std::string > p1(1, "a");
  std::pair< size_t, std::string > p2(2, "b");
  Tree tree({p1, p2});
  Iterator it1 = tree.begin();
  Iterator it2 = tree.end();
  BOOST_TEST((*it1 == p1));
  BOOST_TEST((*(--it2) == p2));

  ConstIterator cit1 = tree.cbegin();
  ConstIterator cit2 = tree.cend();
  BOOST_TEST((*cit1 == const_cast< const std::pair< size_t, std::string >& >(p1)));
  BOOST_TEST((*(--cit2) == const_cast< const std::pair< size_t, std::string >& >(p2)));

  Iterator it3 = tree.begin();
  Iterator it4 = tree.end();
  ConstIterator cit3 = tree.cbegin();
  ConstIterator cit4 = tree.cend();
  BOOST_TEST(it3->first == 1);
  BOOST_TEST((--it4)->first == 2);
  BOOST_TEST(cit3->first == 1);
  BOOST_TEST((--cit4)->first == 2);

  BOOST_TEST((it1 == it3));
  BOOST_TEST((it2 == it4));
  BOOST_TEST((it1 != it2));
  BOOST_TEST((cit1 == cit3));
  BOOST_TEST((cit2 == cit4));
  BOOST_TEST((cit1 != cit2));
}
BOOST_AUTO_TEST_CASE(test_iterators_increment)
{
  using Tree = alymova::TwoThreeTree< size_t, std::string, std::less< size_t > >;
  using Iterator = alymova::TTTIterator< size_t, std::string, std::less< size_t > >;

  Tree tree({{1, "a"}});
  Iterator it = tree.begin();
  BOOST_TEST((++it == tree.end()));

  tree.emplace(2, "b");
  it = tree.begin();
  BOOST_TEST((++it)->first == 2);
  BOOST_TEST((++it == tree.end()));

  tree.emplace(3, "c");
  it = tree.begin();
  BOOST_TEST((++it)->first == 2);

  tree.emplace(4, "d");
  it = (++tree.begin());
  BOOST_TEST((++it)->first == 3);

  tree.emplace(5, "e");
  it = (++tree.begin());
  BOOST_TEST((++it)->first == 3);

  BOOST_TEST((++it)->first == 4);
  BOOST_TEST((++it)->first == 5);

  it = tree.begin();
  BOOST_TEST((it++)->first == 1);
  BOOST_TEST(it->first == 2);
}
BOOST_AUTO_TEST_CASE(test_iterator_decrement)
{
  using Tree = alymova::TwoThreeTree< size_t, std::string, std::less< size_t > >;
  using Iterator = alymova::TTTIterator< size_t, std::string, std::less< size_t > >;

  Tree tree({{1, "a"}});
  Iterator it = tree.begin();
  BOOST_TEST((--it == tree.end()));

  tree.emplace(2, "b");
  it = tree.begin();
  BOOST_TEST((--it == tree.end()));

  it = (++tree.begin());
  BOOST_TEST((--it)->first == 1);

  tree.emplace(3, "c");
  it = (++tree.begin());
  BOOST_TEST((--it)->first == 1);

  it = (--tree.end());
  BOOST_TEST((--it)->first == 2);

  tree.emplace(4, "d");
  tree.emplace(5, "e");
  it = (++tree.begin());
  BOOST_TEST((--it)->first == 1);

  it = (--(--tree.end()));
  BOOST_TEST((--it)->first == 3);
  BOOST_TEST((--it)->first == 2);

  BOOST_TEST((it--)->first == 2);
  BOOST_TEST(it->first == 1);
}
BOOST_AUTO_TEST_CASE(test_size)
{
  using Tree = alymova::TwoThreeTree< size_t, std::string, std::less< size_t > >;

  Tree tree;
  BOOST_TEST(tree.empty());
  BOOST_TEST(tree.size() == 0);

  tree.insert({1, "cat"});
  BOOST_TEST(!tree.empty());
  BOOST_TEST(tree.size() == 1);

  tree.erase(1);
  BOOST_TEST(tree.empty());
}
BOOST_AUTO_TEST_CASE(test_lookup)
{
  using Tree = alymova::TwoThreeTree< size_t, std::string, std::less< size_t > >;
  using Iterator = alymova::TTTIterator< size_t, std::string, std::less< size_t > >;

  Tree tree;
  BOOST_TEST((tree.find(1) == tree.end()));

  tree.emplace(1, "a");
  BOOST_TEST(tree.find(1)->first == 1);
  BOOST_TEST((tree.find(2) == tree.end()));

  BOOST_TEST(tree.count(1) == 1);
  BOOST_TEST(tree.count(2) == 0);

  tree.emplace(3, "b");
  BOOST_TEST(tree.lower_bound(1)->first == 1);
  BOOST_TEST((tree.lower_bound(4) == tree.end()));

  BOOST_TEST(tree.upper_bound(2)->first == 3);
  BOOST_TEST((tree.upper_bound(4) == tree.end()));

  std::pair< Iterator, Iterator > res = tree.equal_range(1);
  BOOST_TEST(res.first->first == 1);
  BOOST_TEST(res.second->first == 3);

  tree.clear();
  BOOST_TEST((tree.lower_bound(1) == tree.end()));
  BOOST_TEST((tree.upper_bound(1) == tree.end()));
}
BOOST_AUTO_TEST_CASE(test_empace_hint)
{
  using Tree = alymova::TwoThreeTree< int, std::string, std::less< int > >;
  using Iterator = alymova::TTTIterator< int, std::string, std::less< int > >;

  Tree tree;
  tree.emplace_hint(tree.cend(), 1, "a");
  BOOST_TEST(tree.size() == 1);
  BOOST_TEST(tree.begin()->first == 1);

  Iterator it = tree.emplace_hint(tree.cend(), 1, "a");
  BOOST_TEST(tree.size() == 1);
  BOOST_TEST(it->first == 1);

  tree.emplace_hint(tree.cend(), 2, "b");
  BOOST_TEST(tree.size() == 2);
  BOOST_TEST((--tree.end())->first == 2);

  tree.emplace_hint(tree.cbegin(), 3, "c");
  BOOST_TEST(tree.size() == 3);
  BOOST_TEST((--tree.end())->first == 3);

  tree.emplace_hint(tree.cbegin(), 10, "d");
  BOOST_TEST((--tree.end())->first == 10);

  tree.emplace_hint(tree.cbegin(), 15, "e");
  BOOST_TEST((--tree.end())->first == 15);

  tree.emplace_hint(tree.cbegin(), 8, "f");
  it = tree.emplace_hint(--tree.cend(), 7, "g");
  BOOST_TEST(it->first == 7);

  tree.emplace_hint(tree.cbegin(), 0, "u");
  tree.emplace_hint(tree.cbegin(), -1, "o");
  BOOST_TEST(tree.begin()->first == -1);

  tree.emplace_hint(tree.cbegin(), -2, "p");
  tree.emplace_hint(tree.cbegin(), -3, "r");
  BOOST_TEST(tree.begin()->first == -3);

  tree.emplace_hint(tree.cend(), 16, "x");
  tree.emplace_hint(tree.cend(), 17, "l");
  tree.emplace_hint(tree.cend(), 18, "w");
  tree.emplace_hint(tree.cend(), 19, "q");
  BOOST_TEST((--tree.end())->first == 19);
}
BOOST_AUTO_TEST_CASE(test_emplace_insert)
{
  using Tree = alymova::TwoThreeTree< int, std::string, std::less< int > >;
  using Iterator = alymova::TTTIterator< int, std::string, std::less< int > >;

  Tree tree;
  std::pair< Iterator, bool > res = tree.emplace(1, "a");
  BOOST_TEST(tree.size() == 1);
  BOOST_TEST(res.second);
  BOOST_TEST(res.first->first == 1);

  res = tree.emplace(1, "b");
  BOOST_TEST(tree.size() == 1);
  BOOST_TEST(!res.second);
  BOOST_TEST(res.first->second == "a");

  tree.insert({2, "b"});
  BOOST_TEST(tree.size() == 2);

  Tree tree1({{10, "ee"}, {20, "rr"}});
  tree.insert(tree1.begin(), tree1.end());
  BOOST_TEST(tree.size() == 4);
  BOOST_TEST((--tree.end())->first == 20);

  tree.insert({{30, "tt"}, {40, "yy"}});
  BOOST_TEST(tree.size() == 6);
  BOOST_TEST((--tree.end())->first == 40);

  tree.insert(tree.begin(), {0, "oo"});
  BOOST_TEST(tree.begin()->first == 0);
}
BOOST_AUTO_TEST_CASE(test_erase)
{
  using Tree = alymova::TwoThreeTree< int, std::string, std::less< int > >;
  using Iterator = alymova::TTTIterator< int, std::string, std::less< int > >;

  Tree tree1;
  tree1.emplace(1, "a");
  Iterator it = tree1.erase(tree1.begin());
  BOOST_TEST((it == tree1.end()));
}
