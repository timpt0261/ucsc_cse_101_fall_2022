// Reuben Chavez Fall 2022 September 28, 2022
// Refenced code from LinkedList

#include <iostream>
#include "linkedlist.h"
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector> 
#include <sstream>
#include <cstring>
using namespace std;


#define L_MAX 200
#define OFFSET 5

// CREATE FUNCTION THAT WILL ITERATE THROUGH SHAKESPEAR ONCE AND STORE IN ARRAY OF LINKED List

int main(int argc, char** argv){
  if (argc < 3) // must provide two arguments as input
  {
        throw std::invalid_argument("Usage: ./wordcount <INPUT FILE> <OUTPUT FILE>"); // throw error
  }

  fstream shakespeare;
  string fname = "shakespeare-cleaned5.txt";

  ifstream input;
  ofstream output;
 
  shakespeare.open(fname, ios::in); // to read  
  input.open(argv[1]);
  output.open(argv[2]);

  LinkedList mylist[L_MAX]; //initialize array of linked List
  int iter,length,rank; //iter itrates through inputed file, length and rank are assigned current length and rank from list
  string command,checker; // to store current line when opening file
  Node *found;// store found node in linked list
  char *com,*d_1,*d_2,*len_str, *rank_str; // refrenced by LinkedList (use for strtok, strtol)

  while(getline(shakespeare, checker)){ // iterate through shakespear file 
    if(checker.length() == 0){continue;}
    int len = checker.length() - OFFSET;
    mylist[len].insert(checker);
  }

  for(int i = 0; i<L_MAX;i++){ // itreates through each linked list to be ordered and shortened
    mylist[i].merge_sort(); // oranianizes all element in alphabetical
    mylist[i].trim(); // removes repeated phrases and updates frequency of words
    mylist[i].merge_sort();// re-organizes lists in expected order 
  }


  iter = 0;
  // while getting next line of code from input code
  while(getline(input, command)){
    if(command.length() == 0){continue;}
    com = strdup(command.c_str()); // Converts to c string but allso alloacate memory for copy
    len_str = strtok(com, " \t"); // word length is first token
    rank_str = strtok(NULL, " \t" ); // word rank is second token

    if(len_str != NULL && rank_str != NULL){
      length = strtol(len_str, &d_1, 10) - OFFSET; // stores inputed length
      rank = strtol(rank_str, &d_2, 10);// stores inputed rank    
    }
    
    if(length < 0 || length > L_MAX || rank < 0 || rank > mylist[length].length()){// case length or rank are out of expected range
      cout << "-" <<endl;
      output << "-"<<endl;
      continue;
    } 

    found = mylist[length].find_ith(rank); // set node equal to rank of word
    if(found != NULL){
      cout << found->word <<endl;
      output << found->word <<endl;
    }else{
      cout << "-" <<endl;
      output << "-"<<endl;
    }

    iter++;
  }

  for(int i = 0; i < L_MAX;i++){
    mylist[i].deleteList();
  }
  shakespeare.close();
  input.close();
  output.close();
  return 0;
}