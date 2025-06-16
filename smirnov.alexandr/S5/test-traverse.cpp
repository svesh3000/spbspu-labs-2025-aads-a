#include <boost/test/unit_test.hpp>
#include <set>
#include <tree/avlTee.hpp>
#include "key_sum.hpp"

BOOST_AUTO_TEST_CASE(test_lnr_traversal)
{
    smirnov::AvlTree<int, std::string> tree;
    tree[5] = "five";
    tree[3] = "three";
    tree[7] = "seven";
    tree[2] = "two";
    tree[4] = "four";
    tree[6] = "six";
    tree[8] = "eight";

    smirnov::KeySum collector;
    collector = tree.traverse_lnr(collector);
    BOOST_TEST(collector.result == 35);
    BOOST_TEST(collector.elems == "two three four five six seven eight");
}
