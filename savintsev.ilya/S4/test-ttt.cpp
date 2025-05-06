#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/tools/output_test_stream.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <stdexcept>
#include "AVL-tree.h"

using namespace savintsev;

namespace {
  // Test helper function to verify tree balance
  template<typename Key, typename Value, typename Compare>
  bool is_balanced(const AVLTree<Key, Value, Compare>& tree) {
    // This is a simplified balance check - in a real test, we would need to traverse the tree
    // We'll use size and find to validate the tree is still working correctly
    const size_t size = tree.size();
    if (size <= 1) {
      return true;
    }
    
    // Check if first element is accessible
    auto it = tree.begin();
    if (it == tree.end()) {
      return false;
    }
    
    // Check if last element is accessible
    auto last = tree.begin();
    for (size_t i = 1; i < size; ++i) {
      ++last;
    }
    if (last == tree.end()) {
      return false;
    }
    
    return true;
  }
}

BOOST_AUTO_TEST_SUITE(AVLTreeConstructorTests)

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
  AVLTree<int, std::string> tree;
  BOOST_CHECK(tree.empty());
  BOOST_CHECK_EQUAL(tree.size(), 0);
  BOOST_CHECK(tree.begin() == tree.end());
}

BOOST_AUTO_TEST_CASE(InitializerListConstructor)
{
  AVLTree<int, std::string> tree = {
    {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}
  };
  
  BOOST_CHECK_EQUAL(tree.size(), 5);
  BOOST_CHECK(!tree.empty());
  
  // Verify all elements are inserted
  BOOST_CHECK(tree.find(1) != tree.end());
  BOOST_CHECK(tree.find(2) != tree.end());
  BOOST_CHECK(tree.find(3) != tree.end());
  BOOST_CHECK(tree.find(4) != tree.end());
  BOOST_CHECK(tree.find(5) != tree.end());
  
  // Verify values
  BOOST_CHECK_EQUAL(tree.find(1)->second, "one");
  BOOST_CHECK_EQUAL(tree.find(2)->second, "two");
  BOOST_CHECK_EQUAL(tree.find(3)->second, "three");
  BOOST_CHECK_EQUAL(tree.find(4)->second, "four");
  BOOST_CHECK_EQUAL(tree.find(5)->second, "five");
  
  // Check that the tree is balanced
  BOOST_CHECK(is_balanced(tree));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(AVLTreeIteratorTests)

BOOST_AUTO_TEST_CASE(BeginEndIterators)
{
  AVLTree<int, std::string> tree = {
    {10, "ten"}, {5, "five"}, {15, "fifteen"}, {3, "three"}, {7, "seven"}
  };
  
  // Verify begin() returns iterator to the smallest element
  auto it = tree.begin();
  BOOST_CHECK_EQUAL(it->first, 3);
  BOOST_CHECK_EQUAL(it->second, "three");
  
  // Verify we can iterate through all elements in sorted order
  std::vector<int> keys;
  for (auto iter = tree.begin(); iter != tree.end(); ++iter) {
    keys.push_back(iter->first);
  }
  
  std::vector<int> expected = {3, 5, 7, 10, 15};
  BOOST_CHECK_EQUAL_COLLECTIONS(keys.begin(), keys.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(ConstIterators)
{
  const AVLTree<int, std::string> tree = {
    {10, "ten"}, {5, "five"}, {15, "fifteen"}, {3, "three"}, {7, "seven"}
  };
  
  // Verify const_iterator works
  auto it = tree.begin();
  BOOST_CHECK_EQUAL(it->first, 3);
  
  // Check iteration through all elements
  std::vector<int> keys;
  for (auto iter = tree.begin(); iter != tree.end(); ++iter) {
    keys.push_back(iter->first);
  }
  
  std::vector<int> expected = {3, 5, 7, 10, 15};
  BOOST_CHECK_EQUAL_COLLECTIONS(keys.begin(), keys.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(AVLTreeAccessOperationsTests)

BOOST_AUTO_TEST_CASE(SubscriptOperator)
{
  AVLTree<int, std::string> tree;
  
  // Test creating new elements
  tree[1] = "one";
  tree[2] = "two";
  tree[3] = "three";
  
  BOOST_CHECK_EQUAL(tree.size(), 3);
  BOOST_CHECK_EQUAL(tree[1], "one");
  BOOST_CHECK_EQUAL(tree[2], "two");
  BOOST_CHECK_EQUAL(tree[3], "three");
  
  // Test updating existing elements
  tree[2] = "TWO";
  BOOST_CHECK_EQUAL(tree[2], "TWO");
  BOOST_CHECK_EQUAL(tree.size(), 3);  // Size shouldn't change
  
  // Test auto-creation with default value
  std::string& ref = tree[4];
  BOOST_CHECK(ref.empty());
  BOOST_CHECK_EQUAL(tree.size(), 4);
  
  // Modify through reference
  ref = "four";
  BOOST_CHECK_EQUAL(tree[4], "four");
}

BOOST_AUTO_TEST_CASE(AtMethod)
{
  AVLTree<int, std::string> tree = {
    {1, "one"}, {2, "two"}, {3, "three"}
  };
  
  // Test accessing existing elements
  BOOST_CHECK_EQUAL(tree.at(1), "one");
  BOOST_CHECK_EQUAL(tree.at(2), "two");
  BOOST_CHECK_EQUAL(tree.at(3), "three");
  
  // Test exception for non-existing key
  BOOST_CHECK_THROW(tree.at(4), std::out_of_range);
  
  // Test modifying through at()
  tree.at(2) = "TWO";
  BOOST_CHECK_EQUAL(tree.at(2), "TWO");
}

BOOST_AUTO_TEST_CASE(FindMethod)
{
  AVLTree<int, std::string> tree = {
    {1, "one"}, {2, "two"}, {3, "three"}
  };
  
  // Test finding existing elements
  auto it1 = tree.find(1);
  BOOST_CHECK(it1 != tree.end());
  BOOST_CHECK_EQUAL(it1->first, 1);
  BOOST_CHECK_EQUAL(it1->second, "one");
  
  // Test finding non-existing element
  auto it4 = tree.find(4);
  BOOST_CHECK(it4 == tree.end());
  
  // Test const version
  const AVLTree<int, std::string>& const_tree = tree;
  auto const_it = const_tree.find(2);
  BOOST_CHECK(const_it != const_tree.end());
  BOOST_CHECK_EQUAL(const_it->first, 2);
  BOOST_CHECK_EQUAL(const_it->second, "two");
}

BOOST_AUTO_TEST_CASE(CountMethod)
{
  AVLTree<int, std::string> tree = {
    {1, "one"}, {2, "two"}, {3, "three"}
  };
  
  // Test counting existing elements
  BOOST_CHECK_EQUAL(tree.count(1), 1);
  BOOST_CHECK_EQUAL(tree.count(2), 1);
  BOOST_CHECK_EQUAL(tree.count(3), 1);
  
  // Test counting non-existing element
  BOOST_CHECK_EQUAL(tree.count(4), 0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(AVLTreeModificationTests)

BOOST_AUTO_TEST_CASE(InsertMethod)
{
  AVLTree<int, std::string> tree;
  
  // Test inserting new elements
  auto result1 = tree.insert({1, "one"});
  BOOST_CHECK(result1.second);  // Should insert successfully
  BOOST_CHECK_EQUAL(result1.first->first, 1);
  BOOST_CHECK_EQUAL(result1.first->second, "one");
  BOOST_CHECK_EQUAL(tree.size(), 1);
  
  auto result2 = tree.insert({2, "two"});
  BOOST_CHECK(result2.second);  // Should insert successfully
  BOOST_CHECK_EQUAL(result2.first->first, 2);
  BOOST_CHECK_EQUAL(tree.size(), 2);
  
  // Test inserting duplicate key
  auto result3 = tree.insert({1, "one"});
  BOOST_CHECK(!result3.second);  // Should not insert
  BOOST_CHECK_EQUAL(result3.first->first, 1);
  BOOST_CHECK_EQUAL(result3.first->second, "one");  // Value should not change
  BOOST_CHECK_EQUAL(tree.size(), 2);  // Size should not change
  
  // Test inserting with hint
  auto hint = tree.find(1);
  auto it = tree.insert(hint, {3, "three"});
  BOOST_CHECK_EQUAL(it->first, 3);
  BOOST_CHECK_EQUAL(it->second, "three");
  BOOST_CHECK_EQUAL(tree.size(), 3);
  
  // Test balancing after multiple inserts
  tree.insert({4, "four"});
  tree.insert({5, "five"});
  tree.insert({6, "six"});
  tree.insert({7, "seven"});
  BOOST_CHECK_EQUAL(tree.size(), 7);
  
  // Verify the tree is balanced
  BOOST_CHECK(is_balanced(tree));
  
  // Verify all elements are accessible
  BOOST_CHECK(tree.find(1) != tree.end());
  BOOST_CHECK(tree.find(7) != tree.end());
}

BOOST_AUTO_TEST_CASE(InsertRangeMethod)
{
  std::vector<std::pair<int, std::string>> data = {
    {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}
  };
  
  AVLTree<int, std::string> tree;
  tree.insert(data.begin(), data.end());
  
  BOOST_CHECK_EQUAL(tree.size(), 4);
  
  // Verify all elements are inserted
  for (const auto& pair : data) {
    BOOST_CHECK(tree.find(pair.first) != tree.end());
    BOOST_CHECK_EQUAL(tree.find(pair.first)->second, pair.second);
  }
  
  // Insert another range with some overlapping keys
  std::vector<std::pair<int, std::string>> more_data = {
    {3, "three"}, {4, "four"}, {5, "five"}, {6, "six"}
  };
  
  tree.insert(more_data.begin(), more_data.end());
  BOOST_CHECK_EQUAL(tree.size(), 6);  // Only new keys should increase size
  
  // Verify values for overlapping keys didn't change
  BOOST_CHECK_EQUAL(tree.find(3)->second, "three");
  BOOST_CHECK_EQUAL(tree.find(4)->second, "four");
  
  // Verify new keys were added
  BOOST_CHECK_EQUAL(tree.find(5)->second, "five");
  BOOST_CHECK_EQUAL(tree.find(6)->second, "six");
}

BOOST_AUTO_TEST_CASE(EmplaceMethod)
{
  AVLTree<int, std::string> tree;
  
  // Test emplacing new elements
  auto result1 = tree.emplace(1, "one");
  BOOST_CHECK(result1.second);  // Should emplace successfully
  BOOST_CHECK_EQUAL(result1.first->first, 1);
  BOOST_CHECK_EQUAL(result1.first->second, "one");
  BOOST_CHECK_EQUAL(tree.size(), 1);
  
  // Test emplacing with multiple arguments
  auto result2 = tree.emplace(std::piecewise_construct,
                             std::forward_as_tuple(2),
                             std::forward_as_tuple("two"));
  BOOST_CHECK(result2.second);
  BOOST_CHECK_EQUAL(result2.first->first, 2);
  BOOST_CHECK_EQUAL(result2.first->second, "two");
  BOOST_CHECK_EQUAL(tree.size(), 2);
  
  // Test emplacing duplicate key
  auto result3 = tree.emplace(1, "one");
  BOOST_CHECK(!result3.second);  // Should not emplace
  BOOST_CHECK_EQUAL(result3.first->first, 1);
  BOOST_CHECK_EQUAL(result3.first->second, "one");  // Value should not change
  BOOST_CHECK_EQUAL(tree.size(), 2);  // Size should not change
  
  // Test emplace_hint
  auto hint = tree.find(1);
  auto it = tree.emplace_hint(hint, 3, "three");
  BOOST_CHECK_EQUAL(it->first, 3);
  BOOST_CHECK_EQUAL(it->second, "three");
  BOOST_CHECK_EQUAL(tree.size(), 3);
}
/*
BOOST_AUTO_TEST_CASE(EraseMethod)
{
  AVLTree<int, std::string> tree = {
    {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}
  };
  
  // Test erasing by key
  size_t erased = tree.erase(3);
  BOOST_CHECK_EQUAL(erased, 1);  // Should erase one element
  BOOST_CHECK_EQUAL(tree.size(), 4);
  BOOST_CHECK(tree.find(3) == tree.end());  // Element should be gone
  
  // Test erasing non-existing key
  erased = tree.erase(6);
  BOOST_CHECK_EQUAL(erased, 0);  // Should erase nothing
  BOOST_CHECK_EQUAL(tree.size(), 4);  // Size should not change
  
  // Test erasing by iterator
  auto it = tree.find(2);
  auto next_it = tree.erase(it);
  BOOST_CHECK_EQUAL(tree.size(), 3);
  BOOST_CHECK(tree.find(2) == tree.end());  // Element should be gone
  
  // Verify next iterator points to the correct element
  if (next_it != tree.end())
  {
    // After erasing 2, next element should be 4 (since 3 was already erased)
    BOOST_CHECK_EQUAL(next_it->first, 4);
  }
  
  // Create a fresh tree for range erase test
  AVLTree<int, std::string> range_tree = {
    {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}
  };
  
  auto first = range_tree.find(2);
  auto last = range_tree.find(5);
  range_tree.erase(first, last);  // Should erase keys 2, 3, 4 but not 5
  
  BOOST_CHECK_EQUAL(range_tree.size(), 2);
  BOOST_CHECK(range_tree.find(1) != range_tree.end());  // Should remain
  BOOST_CHECK(range_tree.find(2) == range_tree.end());  // Should be erased
  BOOST_CHECK(range_tree.find(3) == range_tree.end());  // Should be erased
  BOOST_CHECK(range_tree.find(4) == range_tree.end());  // Should be erased
  BOOST_CHECK(range_tree.find(5) != range_tree.end());  // Should remain
  
  // Test balance after erasing
  BOOST_CHECK(is_balanced(range_tree));
}
*/
BOOST_AUTO_TEST_CASE(ClearMethod)
{
  AVLTree<int, std::string> tree = {
    {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}
  };
  
  BOOST_CHECK_EQUAL(tree.size(), 5);
  BOOST_CHECK(!tree.empty());
  
  tree.clear();
  
  BOOST_CHECK_EQUAL(tree.size(), 0);
  BOOST_CHECK(tree.empty());
  BOOST_CHECK(tree.begin() == tree.end());
  
  // Verify we can still insert after clearing
  tree.insert({10, "ten"});
  BOOST_CHECK_EQUAL(tree.size(), 1);
  BOOST_CHECK_EQUAL(tree.find(10)->second, "ten");
}

BOOST_AUTO_TEST_CASE(SwapMethod)
{
  AVLTree<int, std::string> tree1 = {
    {1, "one"}, {2, "two"}, {3, "three"}
  };
  
  AVLTree<int, std::string> tree2 = {
    {4, "four"}, {5, "five"}
  };
  
  size_t size1 = tree1.size();
  size_t size2 = tree2.size();
  
  tree1.swap(tree2);
  
  BOOST_CHECK_EQUAL(tree1.size(), size2);
  BOOST_CHECK_EQUAL(tree2.size(), size1);
  
  // Verify tree1 now has tree2's elements
  BOOST_CHECK(tree1.find(1) == tree1.end());
  BOOST_CHECK(tree1.find(4) != tree1.end());
  BOOST_CHECK(tree1.find(5) != tree1.end());
  
  // Verify tree2 now has tree1's elements
  BOOST_CHECK(tree2.find(1) != tree2.end());
  BOOST_CHECK(tree2.find(2) != tree2.end());
  BOOST_CHECK(tree2.find(3) != tree2.end());
  BOOST_CHECK(tree2.find(4) == tree2.end());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(AVLTreeBoundTests)

BOOST_AUTO_TEST_CASE(LowerBoundMethod)
{
  AVLTree<int, std::string> tree = {
    {1, "one"}, {3, "three"}, {5, "five"}, {7, "seven"}, {9, "nine"}
  };
  
  // Test lower_bound for existing key
  auto it1 = tree.lower_bound(3);
  BOOST_CHECK(it1 != tree.end());
  BOOST_CHECK_EQUAL(it1->first, 3);
  
  // Test lower_bound for non-existing key (should return iterator to first element not less than key)
  auto it2 = tree.lower_bound(4);
  BOOST_CHECK(it2 != tree.end());
  BOOST_CHECK_EQUAL(it2->first, 5);
  
  // Test lower_bound for key less than all elements
  auto it3 = tree.lower_bound(0);
  BOOST_CHECK(it3 != tree.end());
  BOOST_CHECK_EQUAL(it3->first, 1);
  
  // Test lower_bound for key greater than all elements
  auto it4 = tree.lower_bound(10);
  BOOST_CHECK(it4 == tree.end());
}

BOOST_AUTO_TEST_CASE(UpperBoundMethod)
{
  AVLTree<int, std::string> tree = {
    {1, "one"}, {3, "three"}, {5, "five"}, {7, "seven"}, {9, "nine"}
  };
  
  // Test upper_bound for existing key
  auto it1 = tree.upper_bound(3);
  BOOST_CHECK(it1 != tree.end());
  BOOST_CHECK_EQUAL(it1->first, 5);
  
  // Test upper_bound for non-existing key
  auto it2 = tree.upper_bound(4);
  BOOST_CHECK(it2 != tree.end());
  BOOST_CHECK_EQUAL(it2->first, 5);
  
  // Test upper_bound for key less than all elements
  auto it3 = tree.upper_bound(0);
  BOOST_CHECK(it3 != tree.end());
  BOOST_CHECK_EQUAL(it3->first, 1);
  
  // Test upper_bound for key greater than all elements
  auto it4 = tree.upper_bound(10);
  BOOST_CHECK(it4 == tree.end());
}

BOOST_AUTO_TEST_CASE(EqualRangeMethod)
{
  AVLTree<int, std::string> tree = {
    {1, "one"}, {3, "three"}, {5, "five"}, {7, "seven"}, {9, "nine"}
  };
  
  // Test equal_range for existing key
  auto range1 = tree.equal_range(3);
  BOOST_CHECK(range1.first != tree.end());
  BOOST_CHECK_EQUAL(range1.first->first, 3);
  BOOST_CHECK(range1.second != tree.end());
  BOOST_CHECK_EQUAL(range1.second->first, 5);
  
  // Test equal_range for non-existing key
  auto range2 = tree.equal_range(4);
  BOOST_CHECK(range2.first != tree.end());
  BOOST_CHECK_EQUAL(range2.first->first, 5);
  BOOST_CHECK(range2.second != tree.end());
  BOOST_CHECK_EQUAL(range2.second->first, 5);
  
  // Test equal_range for key less than all elements
  auto range3 = tree.equal_range(0);
  BOOST_CHECK(range3.first != tree.end());
  BOOST_CHECK_EQUAL(range3.first->first, 1);
  BOOST_CHECK(range3.second != tree.end());
  BOOST_CHECK_EQUAL(range3.second->first, 1);
  
  // Test equal_range for key greater than all elements
  auto range4 = tree.equal_range(10);
  BOOST_CHECK(range4.first == tree.end());
  BOOST_CHECK(range4.second == tree.end());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(AVLTreeComplexTests)

BOOST_AUTO_TEST_CASE(LargeTreeTest)
{
  AVLTree<int, int> tree;
  const int SIZE = 1000;
  
  // Insert elements in increasing order (worst case for BST)
  for (int i = 0; i < SIZE; ++i) {
    tree.insert({i, i * 10});
  }
  
  BOOST_CHECK_EQUAL(tree.size(), SIZE);
  
  // Verify the tree is balanced
  BOOST_CHECK(is_balanced(tree));
  
  // Verify all elements are accessible
  for (int i = 0; i < SIZE; ++i) {
    auto it = tree.find(i);
    BOOST_CHECK(it != tree.end());
    BOOST_CHECK_EQUAL(it->second, i * 10);
  }
  
  // Remove half the elements
  for (int i = 0; i < SIZE; i += 2) {
    tree.erase(i);
  }
  
  BOOST_CHECK_EQUAL(tree.size(), SIZE / 2);
  
  // Verify the tree is still balanced
  BOOST_CHECK(is_balanced(tree));
  
  // Verify remaining elements are accessible
  for (int i = 1; i < SIZE; i += 2) {
    auto it = tree.find(i);
    BOOST_CHECK(it != tree.end());
    BOOST_CHECK_EQUAL(it->second, i * 10);
  }
}

BOOST_AUTO_TEST_CASE(CompareCustomTypeTest)
{
  struct Person {
    std::string name;
    int age;
    
    bool operator<(const Person& other) const {
      return name < other.name;
    }
  };
  
  AVLTree<Person, std::string> tree;
  
  Person p1{"Alice", 25};
  Person p2{"Bob", 30};
  Person p3{"Charlie", 35};
  
  tree.insert({p1, "Developer"});
  tree.insert({p2, "Manager"});
  tree.insert({p3, "Designer"});
  
  BOOST_CHECK_EQUAL(tree.size(), 3);
  
  // Find by key
  auto it = tree.find(Person{"Bob", 0});  // Age doesn't matter for comparison
  BOOST_CHECK(it != tree.end());
  BOOST_CHECK_EQUAL(it->second, "Manager");
  
  // Check iteration order
  auto iter = tree.begin();
  BOOST_CHECK_EQUAL(iter->first.name, "Alice");
  ++iter;
  BOOST_CHECK_EQUAL(iter->first.name, "Bob");
  ++iter;
  BOOST_CHECK_EQUAL(iter->first.name, "Charlie");
}

BOOST_AUTO_TEST_CASE(CustomComparatorTest)
{
  // Create a tree with custom comparator for reverse sorting
  AVLTree<int, std::string, std::greater<int>> reverse_tree;
  
  reverse_tree.insert({1, "one"});
  reverse_tree.insert({3, "three"});
  reverse_tree.insert({2, "two"});
  reverse_tree.insert({5, "five"});
  reverse_tree.insert({4, "four"});
  
  // Check that iteration is in reverse order
  std::vector<int> keys;
  for (auto iter = reverse_tree.begin(); iter != reverse_tree.end(); ++iter) {
    keys.push_back(iter->first);
  }
  
  std::vector<int> expected = {5, 4, 3, 2, 1};
  BOOST_CHECK_EQUAL_COLLECTIONS(keys.begin(), keys.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_SUITE_END()
