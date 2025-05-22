// #ifndef AVLTREE_HPP
// #define AVLTREE_HPP

// #include <iostream>
// #include <cstddef>
// #include <stdexcept>

// #include "iterator.hpp"
// #include "constIterator.hpp"

// namespace dribas
// {
//   template< class Key, class T >
//   struct Node
//   {
//     std::pair< Key, T > value;
//     Node< Key, T >* left;
//     Node< Key, T >* right;
//     Node< Key, T >* parent;
//     int height;
//     bool isFake;
//     Node(const std::pair< Key, T >&);
//     Node();
//     ~Node();
//   };

//   template< class Key, class T >
//   Node< Key, T >::Node():
//     value(),
//     left(nullptr),
//     right(nullptr),
//     parent(nullptr),
//     height(0),
//     isFake(true)
//   {}

//   template< class Key, class T >
//   Node< Key, T >::Node(const std::pair< Key, T >& val):
//     value(val),
//     left(new Node< Key, T >()),
//     right(new Node< Key, T>()),
//     parent(nullptr),
//     height(1),
//     isFake(false)
//   {
//     left->parent = this;
//     right->parent = this;
//   }

//   template< class Key, class T >
//   Node< Key, T >::~Node()
//   {
//     if (!isFake) {
//       delete left;
//       delete right;
//     }
//   }

//   template< class Key, class T, class Compare = std::less< Key > >
//   class AVLTree
//   {
//     using Tree = AVLTree< Key, T, Compare >;
//     using NodeType = Node< Key, T >;
//   public:
//     AVLTree();
//     AVLTree(const Tree&);
//     AVLTree(Tree&&);
//     ~AVLTree();

//     Tree& operator=(const Tree&);
//     Tree& operator=(Tree&&);

//     void swap(const Tree&);
//     void clear(NodeType*);

//   private:
//     NodeType* root_;
//     NodeType* fakeleaf_;
//     Compare comp;
//     NodeType* copyTree(const NodeType*);
//     NodeType* balance(NodeType*);
//     void updateHeight(NodeType*);
//     int getBalanceFactor(NodeType*) const;
//     NodeType* rotateRight(NodeType*);
//     NodeType* rotateLeft(NodeType*);

//   };
//   template< class Key, class T, class Compare >
//   void AVLTree< Key, T, Compare >::swap(const Tree& other)
//   {
//     std::swap(other.comp, comp);
//     std::swap(other.fakeleaf_, fakeleaf_);
//     std::swap(other.root_, root_);
//   }

//   template< class Key, class T, class Compare >
//   AVLTree< Key, T, Compare >::AVLTree()
//   {
//     fakeleaf_ = new Node< Key, T >();
//     fakeleaf_->left = fakeleaf_->right = fakeleaf_;
//     root_ = fakeleaf_;
//   }

//   template <class Key, class T, class Compare>
//   Node< Key, T > * AVLTree< Key, T, Compare >::copyTree(const NodeType* otherNode) {
//     if (otherNode->isFake) {
//       return fakeleaf_;
//     }
//     NodeType* newNode = new NodeType(otherNode->value);
//     newNode->left = copyTree(otherNode->left);
//     newNode->right = copyTree(otherNode->right);
//     newNode->height = otherNode->height;
//     return newNode;
// }

//   template< class Key, class T, class Compare >
//   AVLTree< Key, T, Compare >::~AVLTree()
//   {
//     clear(root_);
//     delete fakeleaf_;
//   }

//   template< class Key, class T, class Compare >
//   AVLTree< Key, T, Compare >::AVLTree(const Tree& other):
//     comp(other.comp)
//   {
//     fakeleaf_ = new NodeType();
//     fakeleaf_->left = fakeleaf_->right = fakeleaf_;
//     root_ = copyTree(other.root_);
//   }

//   template< class Key, class T, class Compare >
//   AVLTree< Key, T, Compare >& AVLTree< Key, T, Compare >::operator=(const Tree& other)
//   {
//     if (this != std::addressof(other)) {
//       Tree copy(other);
//       swap(copy);
//     }
//     return *this;
//   }

//   template< class Key, class T, class Compare >
//   AVLTree< Key, T, Compare >::AVLTree(Tree&& other):
//     root_(other.root_),
//     fakeleaf_(other.fakeleaf_),
//     comp(std::move(other.comp))
//   {
//     other.root_ = other.fakeleaf_;
//     other.fakeleaf_ = nullptr;
//   }

//   template< class Key, class T, class Compare >
//   AVLTree< Key, T, Compare >& AVLTree< Key, T, Compare >::operator=(Tree&& other)
//   {
//     if (this != std::addressof(other)) {
//       Tree copy(std::move(other));
//       swap(copy);
//     }
//     return *this;
//   }


// }

// #endif
