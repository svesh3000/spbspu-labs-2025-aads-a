#include "TwoThreeTree.hpp"
#include <iostream>
#include <string>

int main()
{
  gavrilova::TwoThreeTree< int, std::string > tree;
  tree.push(5, "5s");
  std::cout << "get: ";
  std::cout << tree.get(5) << "\n";
  std::cout << "size: ";
  std::cout << tree.size() << "\n";
  std::cout << "\n";
  tree.push(9, "9s");
  std::cout << "get: ";
  std::cout << tree.get(9) << "\n";
  std::cout << "size: ";
  std::cout << tree.size() << "\n";
  std::cout << "\n";
  tree.push(1, "1s");
  std::cout << "get: ";
  std::cout << tree.get(1) << "\n";
  std::cout << "size: ";
  std::cout << tree.size() << "\n";
  std::cout << "\n";
  tree.push(12, "12s");
  std::cout << "get: ";
  std::cout << tree.get(12) << "\n";
  std::cout << "size: ";
  std::cout << tree.size() << "\n";
  std::cout << "\n";
  tree.push(4, "4s");
  std::cout << "get: ";
  std::cout << tree.get(4) << "\n";
  std::cout << "size: ";
  std::cout << tree.size() << "\n";
  std::cout << "\n";
  tree.push(6, "6s");
  std::cout << "get: ";
  std::cout << tree.get(6) << "\n";
  std::cout << "size: ";
  std::cout << tree.size() << "\n";
  std::cout << "\n";
  tree.push(20, "20s");
  std::cout << "get: ";
  std::cout << tree.get(20) << "\n";
  std::cout << "size: ";
  std::cout << tree.size() << "\n";
  std::cout << "\n";
  tree.push(2, "2s");
  std::cout << "get: ";
  std::cout << tree.get(2) << "\n";
  std::cout << "size: ";
  std::cout << tree.size() << "\n";
  std::cout << "\n";
  tree.push(3, "3s");
  std::cout << "get: ";
  std::cout << tree.get(3) << "\n";
  std::cout << "size: ";
  std::cout << tree.size() << "\n";
  std::cout << "\n";
  tree.push(100, "100s");
  std::cout << "get: ";
  std::cout << tree.get(100) << "\n";
  std::cout << "size: ";
  std::cout << tree.size() << "\n";
  tree.push(30, "30s");
  std::cout << "get: ";
  std::cout << tree.get(30) << "\n";
  std::cout << "size: ";
  std::cout << tree.size() << "\n";
  std::cout << "\n";
  tree.push(8, "8s");
  std::cout << "get: ";
  std::cout << tree.get(12) << "\n";
  std::cout << "size: ";
  std::cout << tree.size() << "\n";
  std::cout << "\n";
  tree.push(45, "45");
  std::cout << "get: ";
  std::cout << tree.get(12) << "\n";
  std::cout << "size: ";
  std::cout << tree.size() << "\n";

}