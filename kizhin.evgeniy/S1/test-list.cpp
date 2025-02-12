#include <initializer_list>
#include <iterator>
#include <boost/test/unit_test.hpp>
#include "list.hpp"

using ListT = kizhin::List< double >;

void testInvariants(const ListT& list)
{
  const bool isEmpty = list.empty();
  const bool isZeroSize = list.size() == 0;
  const bool areEqualIters = list.begin() == list.end();
  BOOST_TEST(isEmpty == isZeroSize);
  BOOST_TEST(isEmpty == areEqualIters);
  if (!isEmpty) {
    ListT::const_iterator beg = list.begin();
    ListT::const_iterator end = list.end();
    BOOST_TEST(std::addressof(list.front()) == std::addressof(*beg));
    BOOST_TEST(std::addressof(list.back()) == std::addressof(*(--end)));
  }
}

BOOST_AUTO_TEST_CASE(default_constructor)
{
  const ListT list;
  BOOST_TEST(list.empty());
  testInvariants(list);
}

BOOST_AUTO_TEST_CASE(copy_constructor_from_empty)
{
  const ListT list;
  const ListT copy{ list };
  BOOST_TEST(copy.empty());
  testInvariants(copy);
}

BOOST_AUTO_TEST_CASE(copy_constructor)
{
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5, 6 };
  const ListT list{ init };
  const ListT copy{ list };
  BOOST_TEST(list.size() == init.size());
  testInvariants(copy);
  BOOST_TEST(std::equal(copy.begin(), copy.end(), init.begin()));
}

BOOST_AUTO_TEST_CASE(move_constructor)
{
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5, 6 };
  const ListT list{ init };
  const ListT copy{ std::move(list) };
  BOOST_TEST(list.size() == init.size());
  testInvariants(copy);
  BOOST_TEST(std::equal(copy.begin(), copy.end(), init.begin()));
}

BOOST_AUTO_TEST_CASE(initializer_list_constructor)
{
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5, 6 };
  const ListT list{ init };
  testInvariants(list);
  BOOST_TEST(list.size() == init.size());
  BOOST_TEST(std::equal(list.begin(), list.end(), init.begin()));
}

BOOST_AUTO_TEST_CASE(range_constructor)
{
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5, 6 };
  const ListT list{ init.begin(), init.end() };
  BOOST_TEST(list.size() == init.size());
  testInvariants(list);
  BOOST_TEST(std::equal(list.begin(), list.end(), init.begin()));
}

BOOST_AUTO_TEST_CASE(fill_constructor)
{
  constexpr ListT::size_type size = 100;
  const ListT::value_type value = 7;
  const ListT list{ size, value };
  BOOST_TEST(list.size() == size);
  testInvariants(list);
  BOOST_TEST(std::all_of(list.begin(), list.end(),
      [&value](ListT::const_reference v) -> bool { return value == v; }));
}

BOOST_AUTO_TEST_CASE(copy_assignment_operator)
{
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5, 6 };
  ListT list{ 9, 1 };
  const ListT anotherList{ init };
  list = anotherList;
  BOOST_TEST(list.size() == init.size());
  testInvariants(list);
  BOOST_TEST(std::equal(list.begin(), list.end(), init.begin()));
}

BOOST_AUTO_TEST_CASE(move_assignment_operator)
{
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5, 6 };
  ListT list{ 9, 1 };
  const ListT anotherList{ init };
  list = std::move(anotherList);
  BOOST_TEST(list.size() == init.size());
  testInvariants(list);
  BOOST_TEST(std::equal(list.begin(), list.end(), init.begin()));
}

BOOST_AUTO_TEST_CASE(initializer_list_assignment_operator)
{
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5, 6 };
  ListT list{ 9, 1 };
  list = init;
  BOOST_TEST(list.size() == init.size());
  testInvariants(list);
  BOOST_TEST(std::equal(list.begin(), list.end(), init.begin()));
}

// TODO: IMPORTANT: code duplicating in push_[back|front] tests
BOOST_AUTO_TEST_CASE(push_back_lvalue)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  ListT list{ initSize };
  list.push_back(value);
  BOOST_TEST(list.size() == initSize + 1);
  testInvariants(list);
  BOOST_TEST(list.back() == value);
}

BOOST_AUTO_TEST_CASE(push_back_rvalue)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  ListT list{ initSize };
  list.push_back(std::move(value));
  BOOST_TEST(list.size() == initSize + 1);
  testInvariants(list);
  BOOST_TEST(list.back() == value);
}

BOOST_AUTO_TEST_CASE(push_front_lvalue)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  ListT list{ initSize };
  list.push_front(value);
  BOOST_TEST(list.size() == initSize + 1);
  testInvariants(list);
  BOOST_TEST(list.front() == value);
}

BOOST_AUTO_TEST_CASE(push_front_rvalue)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  ListT list{ initSize };
  list.push_front(std::move(value));
  BOOST_TEST(list.size() == initSize + 1);
  testInvariants(list);
  BOOST_TEST(list.front() == value);
}

BOOST_AUTO_TEST_CASE(pop_back)
{
  // TODO: should here be more checks?
  const ListT::size_type initSize = 77;
  ListT list{ initSize };
  list.pop_back();
  BOOST_TEST(list.size() == initSize - 1);
  testInvariants(list);
}

BOOST_AUTO_TEST_CASE(pop_front)
{
  const ListT::size_type initSize = 77;
  ListT list{ initSize };
  list.pop_front();
  BOOST_TEST(list.size() == initSize - 1);
  testInvariants(list);
}

BOOST_AUTO_TEST_CASE(emplace_back)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  ListT list{ initSize };
  list.emplace_back(value);
  BOOST_TEST(list.size() == initSize + 1);
  testInvariants(list);
  BOOST_TEST(list.back() == value);
}

BOOST_AUTO_TEST_CASE(emplace_front)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  ListT list{ initSize };
  list.emplace_front(value);
  BOOST_TEST(list.size() == initSize + 1);
  testInvariants(list);
  BOOST_TEST(list.front() == value);
}

BOOST_AUTO_TEST_CASE(emplace)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  ListT list{ initSize };
  ListT::const_iterator pos = static_cast< const ListT& >(list).begin();
  std::advance(pos, initSize / 2);
  ListT::iterator it = list.emplace(pos, value);
  BOOST_TEST(list.size() == initSize + 1);
  testInvariants(list);
  BOOST_TEST(*it == value);
}

BOOST_AUTO_TEST_CASE(assign_fill)
{
  constexpr ListT::size_type size = 100;
  const ListT::value_type value = 7;
  ListT list;
  list.assign(size, value);
  BOOST_TEST(list.size() == size);
  testInvariants(list);
  BOOST_TEST(std::all_of(list.begin(), list.end(),
      [&value](ListT::const_reference v) -> bool { return value == v; }));
}

BOOST_AUTO_TEST_CASE(assign_range)
{
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5, 6 };
  ListT list;
  list.assign(init.begin(), init.end());
  BOOST_TEST(list.size() == init.size());
  testInvariants(list);
  BOOST_TEST(std::equal(list.begin(), list.end(), init.begin()));
}

BOOST_AUTO_TEST_CASE(assign_initializer_list)
{
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5, 6 };
  ListT list;
  list.assign(init);
  testInvariants(list);
  BOOST_TEST(list.size() == init.size());
  BOOST_TEST(std::equal(list.begin(), list.end(), init.begin()));
}

// TODO: Remove code duplicating: lvalue/rvalue
BOOST_AUTO_TEST_CASE(insert_lvalue)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  ListT list{ initSize };
  ListT::const_iterator pos = static_cast< const ListT& >(list).begin();
  std::advance(pos, initSize / 2);
  ListT::iterator it = list.insert(pos, value);
  BOOST_TEST(list.size() == initSize + 1);
  testInvariants(list);
  BOOST_TEST(*it == value);
}

BOOST_AUTO_TEST_CASE(insert_rvalue)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  ListT list{ initSize };
  ListT::const_iterator pos = static_cast< const ListT& >(list).begin();
  std::advance(pos, initSize / 2);
  ListT::iterator it = list.insert(pos, std::move(value));
  BOOST_TEST(list.size() == initSize + 1);
  testInvariants(list);
  BOOST_TEST(*it == value);
}

BOOST_AUTO_TEST_CASE(insert_size)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  const ListT::size_type insertSize = 10;
  ListT list{ initSize };
  ListT::const_iterator pos = static_cast< const ListT& >(list).begin();
  std::advance(pos, initSize / 2);
  ListT::iterator it = list.insert(pos, insertSize, value);
  BOOST_TEST(list.size() == initSize + insertSize);
  testInvariants(list);
  BOOST_TEST(*it == value); // TODO: improve test
}

BOOST_AUTO_TEST_CASE(insert_range)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5, 6 };
  ListT list{ initSize };
  ListT::const_iterator pos = static_cast< const ListT& >(list).begin();
  std::advance(pos, initSize / 2);
  ListT::iterator it = list.insert(pos, init.begin(), init.end());
  BOOST_TEST(list.size() == initSize + init.size());
  testInvariants(list);
  BOOST_TEST(*it == value); // TODO: improve test
}

BOOST_AUTO_TEST_CASE(insert_initializer_list)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5, 6 };
  ListT list{ initSize };
  ListT::const_iterator pos = static_cast< const ListT& >(list).begin();
  std::advance(pos, initSize / 2);
  ListT::iterator it = list.insert(pos, init);
  BOOST_TEST(list.size() == initSize + init.size());
  testInvariants(list);
  BOOST_TEST(*it == value); // TODO: improve test
}

BOOST_AUTO_TEST_CASE(erase_iterator)
{
  // TODO: Implement erase tests
}

BOOST_AUTO_TEST_CASE(erase_const_iterator)
{
  // TODO: Implement erase tests
}

BOOST_AUTO_TEST_CASE(erase_range)
{
  // TODO: Implement erase tests
}

BOOST_AUTO_TEST_CASE(erase_const_range)
{
  // TODO: Implement erase tests
}

BOOST_AUTO_TEST_CASE(remove_value)
{
  // TODO: Implement remove tests
}

BOOST_AUTO_TEST_CASE(remove_predicate)
{
  // TODO: Implement remove tests
}

BOOST_AUTO_TEST_CASE(reverse)
{
  // TODO: Implement reverse tests
}

BOOST_AUTO_TEST_CASE(unique)
{
  // TODO: Implement unique tests
}

BOOST_AUTO_TEST_CASE(unique_predicate)
{
  // TODO: Implement unique tests
}

BOOST_AUTO_TEST_CASE(sort)
{
  // TODO: Implement sort tests
}

BOOST_AUTO_TEST_CASE(sort_comparator)
{
  // TODO: Implement sort tests
}

BOOST_AUTO_TEST_CASE(clear)
{
  ListT list(88, 99);
  list.clear();
  BOOST_TEST(list.empty());
  testInvariants(list);
}

BOOST_AUTO_TEST_CASE(swap)
{
  // TODO: Implement swap tests
}

// TODO: Add tests: merge, splice, comparison operators

