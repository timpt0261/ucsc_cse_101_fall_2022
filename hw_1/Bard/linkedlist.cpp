//Reuben Chavez 
// Filename: linkedlist.cpp
// 
// Contains the class LinkedList that represents a linked list. This contains some basic operations, such as insert, delete, find, length
// 
// Japheth Frolick, August 2019
// C. Seshadhri, Jan 2020

#include "linkedlist.h"
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

LinkedList :: LinkedList()
{
	head = NULL;
}


//Inspirartion from Class 9-27-2022, Idea is to recursevly search the linked list for specific word
Node* LinkedList :: find_rec(string word, Node* start){
  if(start == NULL){return NULL;} // is the start is null, NULL is returned
  if(start->word.compare(word) == 0){return start;} // return node if comapred
  return find_rec(word, start->next);
}

Node* LinkedList :: find(string word)
{
  return find_rec(word,head);   
}

// Insert(string word): Inserts the string word into list, at the head of the list. Case there are multiple copies find is implemented inser os called
// Input: string to insert into the linked list
// Output: Void, just inserts new Node
void LinkedList :: insert(string word)
{
    Node *new_word = new Node; // create new instance of Node
    new_word->word = word; // set node to parameater
    new_word->occur = 0;
    new_word->next = head; // link node to existing head
    head = new_word; //setting head to new_word
    return;
}

// Idea is to find node based on postion, and to easily implement Merge Sort
// Input: int to insert 
// output node at that postion or null if out of bunds
Node* LinkedList :: find_ith(int pos){
  Node *curr = head;
  if(pos <= 0 || pos == 1){
    return  pos <= 0 ?head: head->next;
  }

  while(curr !=NULL){
    if(pos == 0){
      break;
    }
    curr = curr->next;
    pos--;
  }

  return curr;
}

// should return postion of the node in the linked list, with Head being zero and tail being the len - 1
// Input: node to search for
// Output: node postion in linked list , else return negat one to show it doesn't exist in list
int LinkedList :: find_postion(Node *entry){
  Node* curr = head;
  int postion = 0;
  
  if(entry == NULL || entry == head){
    return entry == head ? 0: -1;
  }

  while(curr != NULL){
    if(curr == entry){
      break;
    }
    postion++;
    curr= curr->next;
  }
  
  return postion;
}


// Idea is to determine the mid point of the linked list using the Tortis and Hare Algorthim
// Input: Node where to star 
// Output: Node point where the mid is found

void LinkedList :: find_mid(Node *source, Node** sub_a, Node** sub_b){
 Node *slow = source;
 Node *fast= source->next;

 while(fast != NULL){
   fast = fast->next;
   if(fast != NULL){
     slow = slow->next;
     fast = fast->next;
   }
   
 }
 *sub_a = source;
 *sub_b = slow->next;
 slow->next = NULL;
}



// Updates the given node val
void LinkedList :: update(Node* node){
  node->occur++;return;
}


Node* LinkedList :: deleteNode(string word)
{
  Node* prev  = NULL;
  Node* curr = head;
  if(head == NULL){return NULL;} // base Case
  while(curr != NULL)
  {
    if(curr->word.compare(word) == 0){ // sees if word is found

      if(prev == NULL){  // case the word is in the head
        Node *temp = head;
        head = head->next;
        temp->next = NULL;
        return temp; 
      }else{  // case the word is in the middle of the list
        Node *temp = curr;
        prev->next = curr->next;
        temp->next = NULL;
        return temp;
      }
    }
    prev = curr;
    curr = curr->next;
  }
  return NULL; // case word not fond throught out list return NULL
}

// Inspriation form Section G 9-28-2022
void LinkedList :: deleteAndFreeNode(string word)
{
  Node *ptr = deleteNode(word);
  if(ptr != NULL){
    ptr->next = NULL;
    delete(ptr);
  }
  return;
}

// Deletes all repeated nodes and updates the occurances when list is in order(only works when list is organized)
// Input : Nothing
// Output: Shorthened lilnked list
void LinkedList :: trim(){
  if(head == NULL){return;}
  Node *curr = head;
  Node *trim;
  Node *ref = head;
  trim = ref;
  string entry = head->word; // word to search for in list  
  while(curr != NULL){
    if(curr->word != entry){
      entry = curr->word;
      ref->next = curr;
      ref = ref->next;
    }
    update(ref);
    curr = curr->next;
  }
  head = trim;
  return;
}

// Deletes every Node to prevent memory leaks.
// Input: None
// Output: Void, just deletes every Node of the list
void LinkedList :: deleteList()
{
  Node *curr = head; // curr is the current Node as it progresses through the linked list. Initialized to head to start at the head of the list
  Node *temp = NULL;

	// curr will loop over list. At every iteration, we first store a pointer to the next Node, and then delete the current Node.
  while(curr != NULL){ // Looping over list
    temp = curr->next; // store pointer to next Node in the list
	  delete(curr); // delete the current Node
	  curr = temp; // update curr to proceed through list
	}
	head = NULL;
  return;
}

// Prints list in order
// Input: None
// Output: string that has all elements of the list in order
string LinkedList :: print()
{
  string list_str = ""; // string that has list
	Node *curr = head; // curr is the current Node as it progresses through the linked list. Initialized to head to start at the head of the list
	// curr will loop over list. It prints the content of curr, and then moves curr to next Node.
	while(curr != NULL){ // looping over list
    list_str = list_str +"[word: \'"+ curr->word +"\'|occur:" + to_string(curr->occur) +"]"+ " "; //append string with current Node's data
		curr = curr->next; // proceed through list
	}

  if (list_str.length() > 0) // string is non-empty
    list_str.pop_back(); // remove the last (extra) space from string
  return list_str;
}

// Computes the length of the linked list
// Input: None
// Output: Int, length of list
int LinkedList :: length()
{
  int length = 0; // initialize length to zero
	Node *curr = head; // curr is ths current Node as it progresses through the linked list. Initialized to head to start at the head of the list
	
	while(curr != NULL){ // looping over list
		length++; // increment length
		curr = curr->next; // proceed to next Node
	}
	return length;
}

//Ideal merges two subsets of a linked list recurseively 
//Input: Two Node pointers sub_a ,sub_b
//Output: New Node to head oh merged list
//
// Refrences : https://www.programiz.com/dsa/merge-sort
//             https://www.geeksforgeeks.org/merge-sort/
//             https://www.geeksforgeeks.org/merge-sort-for-linked-list/
Node* LinkedList :: merge(Node* sub_a, Node* sub_b)
{
    Node* result = NULL;
 
    // base cases 
    if (sub_a == NULL)
        return (sub_b);
    else if (sub_b == NULL)
        return (sub_a);

    // Has hierachy to determine order
    if (sub_a->occur > sub_b->occur) { // First check is sub_a has more occurances than sub_b
      result = sub_a; // store result
      result->next = merge(sub_a->next, sub_b); //set next node after result to  
    }else if(sub_a->occur < sub_b->occur){ // Second check if sub_b has more occurances than sub_a 
      result = sub_b;
      result->next = merge(sub_a, sub_b->next);
    }else if (sub_a->word.compare(sub_b->word) < 0) { // Third compare sub_a and sub_b word to see which is lexographically first
      result = sub_a;
      result->next = merge(sub_a->next, sub_b);
    }else{ //Fourth, sub_b most likely follows after sub_a 
      result = sub_b;
          result->next = merge(sub_a, sub_b->next);
    }
    return (result);
}

// private method to continue recursision 
// Input: Double pointer to head of linked list of head sub list
// Output: Nothing
// Refrences : https://www.programiz.com/dsa/merge-sort
//             https://www.geeksforgeeks.org/merge-sort/
//             https://www.geeksforgeeks.org/merge-sort-for-linked-list/
void LinkedList :: merge_sort_rec(Node **headref){ 
  Node *start = *headref;
  Node *pt1;
  Node *pt2;
  if(start == NULL || start->next == NULL){return;}
  find_mid(start, &pt1, &pt2);
  merge_sort_rec(&pt1);
  merge_sort_rec(&pt2);
  *headref = merge(pt1, pt2);
  return;
}



// Sort the existing LinkedList recursively  using a merge sorting order from most frequent to least frequent the smallest
// Input: Nothing
// Output: Linked List is in order base on lexographical, frequncy, or frequency then alphabetical
// Refrences : https://www.programiz.com/dsa/merge-sort
//             https://www.geeksforgeeks.org/merge-sort/
//             https://www.geeksforgeeks.org/merge-sort-for-linked-list/
void LinkedList :: merge_sort(){
 
  Node *pt1;
  Node *pt2;
  if(head == NULL || head->next == NULL){return;} // base case for head
  
  find_mid(head, &pt1, &pt2); //Splits the linked list in two subsets by finding the mid
  merge_sort_rec(&pt1); // recursively  merge sort first subsets
  merge_sort_rec(&pt2); // recurseively merge sort second subsets
  head = merge(pt1, pt2); // set head equal to merge
  return;
}



