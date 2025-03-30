#ifndef TREE_HPP
#define TREE_HPP
#include <functional>
#include "node.hpp"

namespace demehin
{
  template< typename Key, typename T, typename Cmp = std::less< Key > >
  class Tree
  {
  public:
    Tree();



    ~Tree();
  private:
    using Node = demehin::TreeNode< Key, T >;

    Node* fakeRoot_;
    Cmp cmp_;
    size_t size_;
  };

  template< typename Key, typename T, typename Cmp >
  Tree< Key, T, Cmp >::Tree():
    fakeRoot_(reinterpret_cast< Node* >(new char[sizeof(Node)])),
    cmp_(Cmp()),
    size_(0)
  {}

  template< typename Key, typename T, typename Cmp >
  Tree< Key, T, Cmp >::~Tree()
  {
    delete[] reinterpret_cast< char* >(fakeRoot_);
  }
}


#endif
