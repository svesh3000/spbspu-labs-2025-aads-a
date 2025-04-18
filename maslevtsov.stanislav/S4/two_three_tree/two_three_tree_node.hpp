#ifndef TWO_THREE_TREE_NODE_HPP
#define TWO_THREE_TREE_NODE_HPP

namespace maslevtsov {
  template< class T >
  struct TwoThreeTreeNode
  {
    T data1_;
    T data2_;
    TwoThreeTreeNode* parent_;
    TwoThreeTreeNode* left_;
    TwoThreeTreeNode* middle_;
    TwoThreeTreeNode* right_;
    bool is_two;
  };
}

#endif
