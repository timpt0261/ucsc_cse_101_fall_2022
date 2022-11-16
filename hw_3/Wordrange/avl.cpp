// Filename: avl.c

#include "avl.h"

#include <cstdlib>

#include <iostream>

#include <vector>

#include <algorithm>

#include <string>

#include <stack>

using namespace std;

// Default constructor sets head and tail to null
AVL::AVL()
{
  root = NULL;
}

int AVL ::range_high(Node *start, string high)
{ // searches in subtree for all nodes less than high

  if (start == NULL) // base case
    return 0;
  int x = start->key <= high ? 1 : 0; // add 1 if within range, else add 0
  return range_high(start->left, high) + range_high(start->right, high) + x;
}

int AVL ::range_low(Node *start, string low)
{                    // searches in subtree for all nodes
  if (start == NULL) // base case
    return 0;
  int x = start->key >= low ? 1 : 0; // add 1 if within range, else add 0
  return range_low(start->left, low) + range_low(start->right, low) + x;
}

int AVL ::range(Node *start, string low, string high)
{
  if (start == NULL)
    return 0; // base case 0
  if (start->key < low)
    return range(start->right, low, high); // base case 1
  else if (start->key > high)
    return range(start->left, low, high); // base case 2

  return range_low(start->left, low) + range_high(start->right, high) + 1;
}

int AVL ::range(string low, string high) { return range(root, low, high); }

int AVL::height(Node *node)
{
  if (node == NULL)
    return 0;
  return node->height;
}

int AVL::max(int x, int y)
{
  return (x > y) ? x : y;
}

int AVL::BalanceFactor(Node *start) // returns the Balance Factor of the current node
{
  if (start == NULL)
  {
    return 0;
  }
  return height(start->left) - height(start->right);
}

Node *AVL::left_rotate(Node *x)
{
  if (x == NULL || x->left == NULL || x->right == NULL)
  {
    return x == NULL ? NULL : x;
  }

  Node *parent = x == root ? NULL : x->parent;
  Node *y = x->right;
  Node *T2 = y->left;

  // perform left_rotaion
  y->left = x;
  x->right = T2;

  // update parent
  if (x == root)
  {
    root = y;
  }
  else if (parent->left == x)
  {
    parent->left = y;
  }
  else
  {
    parent->right = y;
  }

  y->parent = parent;
  x->parent = y;

  // update heights
  x->height = max(height(x->right), height(x->left)) + 1;
  y->height = max(height(y->right), height(y->left)) + 1;

  return x;
}

Node *AVL::right_rotate(Node *y)
{
  if (y == NULL || y->left == NULL || y->right == NULL)
  {
    return y == NULL ? NULL : y;
  }
  Node *parent = y == root ? NULL : y->parent;
  Node *x = y->left;
  Node *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // update parent
  if (y == root)
  {
    root = x;
  }
  else if (parent->left == y)
  {
    parent->left = x;
  }
  else
  {
    parent->right = x;
  }

  x->parent = parent;
  y->parent = x;

  // update heights
  y->height = max(height(y->right), height(y->left)) + 1;
  x->height = max(height(x->right), height(x->left)) + 1;

  return x;
}

void AVL::insert(string key)
{
  Node *to_insert = new Node(key); // create a new Node with the value val
  if (root == NULL)                // tree is currently empty
    root = to_insert;              // make new node the root
  else
  {
    insert(root, to_insert); // make call to recursive insert, starting from root
  }

  
  // // 2. Update height of ancestor
  // start->height = max(height(start->left), height(start->right)) + 1;

  // // 3. Calculate balance of nodes
  // int balance = BalanceFactor(start);

  // if (balance > 1)
  // {
  //   if (to_insert->key < start->left->key)
  //   {
  //     return right_rotate(start);
  //   }
  //   else if (to_insert->key > start->left->key)
  //   {
  //     start->left = left_rotate(start->left);
  //     return right_rotate(start);
  //   }
  // }
  // if (balance < -1)
  // {
  //   if (to_insert->key > start->right->key)
  //   {
  //     return left_rotate(start);
  //   }
  //   else if (to_insert->key < start->right->key)
  //   {
  //     start->right = right_rotate(start->right);
  //     return left_rotate(start);
  //   }
  // }


  return;
}
// insert(Node* node, Node* to_insert): Inserts the Node to_insert into tree rooted at node. We will always call with node being non-null. Note that there may be multiple copies of val in the list.
// Input: Int to insert into the subtree
// Output: Void, just inserts new Node
Node *AVL::insert(Node *start, Node *to_insert)
{
  if (start == NULL) // in general, this should not happen. We never call insert from a null tree
    return;
  if (to_insert->key <= start->key) // inserted node has smaller (or equal) key, so go left
  {
    if (start->left == NULL)
    {
      start->left = to_insert;   // make this node the left child
      to_insert->parent = start; // set the parent pointer
      return;
    }
    else // need to make recursive call
    {
      insert(start->left, to_insert);
      return;
    }
  }
  else // inserted node has larger key, so go right
  {
    if (start->right == NULL)
    {
      start->right = to_insert;  // make this node the right child
      to_insert->parent = start; // set the parent pointer
      return;
    }
    else // need to make recursive call
    {
      insert(start->right, to_insert);
      return;
    }
  }
}

// find(string val): Finds a Node with key "val"
// Input: int to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
// Technically, it finds the first Node with val, at it traverses down the tree
Node *AVL::find(string val)
{
  return find(root, val); // call the recursive function starting at root
}

// find(Node* start, string val): Recursively tries to find a Node with key "val", in subtree rooted at val
// Input: int to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
// Technically, it finds the first Node with val, at it traverses down the tree
Node *AVL::find(Node *start, string val)
{
  if (start == NULL || start->key == val) // tree is empty or we found val
    return start;
  if (val < start->key) // val is smaller, so go left
    return find(start->left, val);
  else // val is larger, so go right
    return find(start->right, val);
}

// minNode(Node* start): gets the minimum Node in subtree rooted at start
// Input: Pointer to subtree root
// Output: pointer to the minimum node in the subtree
Node *AVL::minNode(Node *start)
{
  if (start == NULL) // typically, this should not happen. But let's return the safe thing
    return NULL;
  if (start->left == NULL) // Base case: we have found the minimum
    return start;
  else
    return minNode(start->left); // recursive call in left subtree
}

// maxNode(Node* start): gets the maximum Node in subtree rooted at start
// Input: Pointer to subtree root
// Output: pointer to the maximum node in the subtree
Node *AVL::maxNode(Node *start)
{
  if (start == NULL) // typically, this should not happen. But let's return the safe thing
    return NULL;
  if (start->right == NULL) // Base case: we have found the maximum
    return start;
  else
    return maxNode(start->right); // recursive call in left subtree
}

// deleteNode(string val): Delete a Node with key val, if it exists. Otherwise, do nothing.
// Input: int to be removed
// Output: pointer to Node that was deleted. If no Node is deleted, return NULL. If there are multiple Nodes with val, only the first Node in the list is deleted.
Node *AVL::deleteKey(string val)
{
  return deleteNode(find(val)); // get a node with the value and delete that node
}

// deleteNode(Node* to_delete): Delete the input node, and return pointer to the deleted node. The node will be isolated from the tree, to prevent memory leaks
// Input: Node to be removed
// Output: pointer to Node that was deleted. If no Node is deleted, return NULL.
Node *AVL::deleteNode(Node *to_delete)
{
  if (to_delete == NULL) // val not present in tree, so return NULL
    return NULL;

  bool isRoot = (to_delete == root) ? true : false; // determine if node to delete is root
  bool isLeftChild = false;
  if (!isRoot)                                                           // if this is not the root
    isLeftChild = (to_delete->parent->left == to_delete) ? true : false; // determine if node is left child of parent. Note that line throws error iff to_delete is root

  bool isDeleted = false; // convenient flag for writing code

  // if to_delete's left child is NULL, then we can splice this node off. We set the appropriate
  // pointer of the parent to the right child of to_delete
  if (to_delete->left == NULL)
  {
    if (isRoot) // if deleting root, then we reset root
    {
      root = to_delete->right;
      if (root != NULL)
        root->parent = NULL; // set parent to be NULL
    }
    else
    {
      if (isLeftChild)                                // node is left child of parent
        to_delete->parent->left = to_delete->right;   // setting left child of parent to be right child of node
      else                                            // node is right child of parent
        to_delete->parent->right = to_delete->right;  // setting right child of parent to be right child of node
      if (to_delete->right != NULL)                   // to_delete is not a leaf
        to_delete->right->parent = to_delete->parent; // update parent of the child of the deleted node, to be parent of deleted node
    }
    isDeleted = true; // delete is done
  }
  // suppose node is not deleted yet, and it's right child is NULL. We splice off as before, by setting parent's child pointer to to_delete->left
  if (!isDeleted && to_delete->right == NULL)
  {
    if (isRoot) // if deleting root, then we reset root
    {
      root = to_delete->left;
      if (root != NULL)
        root->parent = NULL; // set parent to be NULL
    }
    else
    {
      if (isLeftChild)                               // node is left child of parent
        to_delete->parent->left = to_delete->left;   // setting left child of parent to be left child of node
      else                                           // node is right child of parent
        to_delete->parent->right = to_delete->left;  // setting right child of parent to be left child of node
      if (to_delete->left != NULL)                   // to delete is not a leaf
        to_delete->left->parent = to_delete->parent; // update parent of the child of deleted node, to be parent of deleted node
    }
    isDeleted = true; // delete is done
  }
  if (isDeleted) // so node has been deleted
  {
    to_delete->left = to_delete->right = NULL;
    return to_delete;
  }

  // phew. The splicing case is done, so now for the recursive case. Both children of to_delete are not null, so we replace the data in to_delete by the successor. Then we delete the successor node
  // first, get the minimum node of right subtree
  Node *succ = minNode(to_delete->right);
  to_delete->key = succ->key;
  //     cout << "Replacing with "+to_string(succ->key) << endl;
  return deleteNode(succ); // make recursive call on succ. Note that succ has one null child, so this recursive call will terminate without any other recursive calls
}

// Deletes every Node to prevent memory leaks.
// Input: None
// Output: Void, just deletes every Node of the list
void AVL::deleteAVL()
{
  deleteAVL(root);
}

// Deletes every Node in subtree rooted at startto prevent memory leaks.
// Input: Node* start
// Output: Void, just deletes every Node of the list
void AVL::deleteAVL(Node *start)
{
  if (start == NULL) // tree is already empty
    return;
  deleteAVL(start->left);  // delete left subtree
  deleteAVL(start->right); // delete right subtree
  delete (start);          // delete node itself
}

// Prints tree in order. Calls the recursive function from the root
// Input: None
// Output: string that has all elements of the tree in order
string AVL ::printInOrder()
{
  return printInOrder(root);
}

// Prints tree Preorder. Calls the recursive function from the root
// Input: None
// Output: string that has all elements of the tree pre order
string AVL ::printPreOrder()
{
  return printPreOrder(root);
}

// Prints tree Postorder. Calls the recursive function from the root
// Input: None
// Output: string that has all elements of the tree post order
string AVL ::printPostOrder()
{
  return printPostOrder(root);
}

// Prints rooted subtree tree in order, by making recursive calls
// Input: None
// Output: string that has all elements of the rooted tree in order
string AVL ::printInOrder(Node *start)
{
  if (start == NULL) // base case
    return "";       // return empty string
  string leftpart = printInOrder(start->left);
  string rightpart = printInOrder(start->right);
  string output = start->key;
  if (leftpart.length() != 0)          // left part is empty
    output = leftpart + " " + output;  // append left part
  if (rightpart.length() != 0)         // right part in empty
    output = output + " " + rightpart; // append right part
  return output;
}

// Prints rooted subtree tree preorder, by making recursive calls
// Input: None
// Output: string that has all elements of the rooted tree preorder
string AVL ::printPreOrder(Node *start)
{
  if (start == NULL) // base case
    return "";       // return empty string
  string leftpart = printPreOrder(start->left);
  string rightpart = printPreOrder(start->right);
  string output = start->key;
  if (leftpart.length() != 0)          // left part is empty
    output = output + " " + leftpart;  // append left part
  if (rightpart.length() != 0)         // right part in empty
    output = output + " " + rightpart; // append right part
  return output;
}

// Prints rooted subtree tree postorder, by making recursive calls
// Input: None
// Output: string that has all elements of the rooted tree in post order
string AVL ::printPostOrder(Node *start)
{
  if (start == NULL) // base case
    return "";       // return empty string
  string leftpart = printPostOrder(start->left);
  string rightpart = printPostOrder(start->right);
  string output = start->key;
  if (rightpart.length() != 0)         // right part is empty
    output = rightpart + " " + output; // append left part
  if (leftpart.length() != 0)          // left part in empty
    output = leftpart + " " + output;  // append right part
  return output;
}