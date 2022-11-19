// Filename : avl.h
//
// Header file for the AVL that represent Adelson-Velsky and Landis tree
//
// Reuben C. Fall 2022

#ifndef AVL_H
#define AVL_H

#include <string>

using namespace std;

class Node
{
public:
  string key;
  int height;
  Node *left, *right, *parent;

  Node() // default constructor
  {
    left = right = parent = NULL; // setting everything to NULL
  }

  Node(string val) // constructor that sets key to val
  {
    key = val;
    height = 1;
    left = right = parent = NULL; // setting everything to NULL
  }
};

class AVL
{
private:
  Node *root; // Stores root of tree
public:
  AVL(); // Default constructor sets root to null

  // Range Query
  int range_high(Node *, string high); // searches in subtree for all nodes less than high
  int range_low(Node *, string low);   // searches in subtree for all nodes greather than equal to low
  int range(Node *start, string low, string high);
  int range(string low, string high); // searches for nodes within low high

  // AVL Imlpementation
  int max(int, int);          // return max
  int height(Node *);         // returns height of the node
  int BalanceFactor(Node *);  // returns the Balance Factor of the current node
  void left_rotate(Node *);  // Complete a left rotation
  void right_rotate(Node *); // Completes a right rotation
  void reconstruct(Node*, string);

  void insert(string);
  void insert(Node *, Node *);       // simple BST insertion plus a rotation
  Node *find(string);                 // find int in tree, and return pointer to node with that int. If there are multiple copies, this only finds one copy
  Node *find(Node *, string);         // recursive version that finds in a rooted subtree
  Node *minNode(Node *);              // gets minimum node in rooted subtree
  Node *maxNode(Node *);              // gets maximum node in rooted subtree
  Node *deleteKey(string);            // remove a node with string (if it exists), and return pointer to deleted node. This does not delete all nodes with the value.
  Node *deleteNode(Node *);           // try to delete node pointed by argument. This also returns the node, isolated from the tree.
  void deleteAVL();                   // deletes every node to prevent memory leaks, and frees memory
  void deleteAVL(Node *start);        // deletes every Node in subtree rooted at startto prevent memory leaks.
  string printInOrder();              // Construct string with tree printed InOrder
  string printInOrder(Node *start);   // Construct string with rooted subtree printed InOrder
  string printPreOrder();             // Construct string with tree printed PreOrder
  string printPreOrder(Node *start);  // Construct string with rooted subtree printed PreOrder
  string printPostOrder();            // Construct string with tree printed PostOrder
  string printPostOrder(Node *start); // Construct string with rooted subtree printed PostOrder
};

#endif