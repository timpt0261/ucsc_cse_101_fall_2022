// Reuben Chavez  Fall 2022
// Using Refence code for linked list

// Filename: linkedlist.h
// 
// Header file for the class LinkedList that represents a linked list
// 
// Japheth Frolick, August 2019
// C. Seshadhri, Jan 2020

#ifndef LIST_H
#define LIST_H

#include <string>
#include <iostream>

using namespace std;

// node struct to hold data
struct Node{
    int occur;
    string word; // word within node
    Node *next; // Next Node
};

class LinkedList
{
	private:
		Node* head; // Stores head of linked list
    Node* find_rec(string , Node*);
    Node* delete_rec(string, Node*);
    int find_postion(Node*);
    int NodeDist(Node*, Node*);
    Node* merge(Node*, Node*);
    void find_mid(Node *, Node**, Node**);
    void merge_sort_rec(Node**);
 
	public:
		LinkedList(); // Default constructor sets head to null
    Node* find(string); // find given word in list
    Node* find_ith(int); // finds the kth node within the linkedlist
    void update(Node*);
    Node* deleteNode(string); // remove a node with int (if it exists), and return pointer to deleted node. This does not delete all nodes with the value.
    void deleteAndFreeNode(string); // remove a node with int (if it exists), and free the memory.
		void deleteList(); // deletes every node to prevent memory leaks, and frees memory
    void trim(); // deltes repeated node and uppdates the occurances
    void insert(string); // insert word in linkded list, if found update occurances of word
    string print(); // Construct string with data of list in order 
    int length(); // Returns the length of the linked list
    void merge_sort();// Recursively sorts the Linked List based on Nodes occurances
};

#endif
