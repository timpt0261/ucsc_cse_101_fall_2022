// Reuben Chavez Fall 2022
//
// Contains my implemntaion of the AVL tree
// Using code from Sesh

#include <algorithm>
#include <array>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <vector>

#include "avl.h"
using namespace std;

int main(int argc, char** argv) {
  if (argc < 3)  // must provide two arguments as input
  {
    throw std::invalid_argument("Usage: ./treewrapper <INPUT FILE> <OUTPUT FILE>");  // throw error
  }

  ifstream input;   // stream for input file
  ofstream output;  // stream for output file

  input.open(argv[1]);   // open input file
  output.open(argv[2]);  // open output file

  string command;                                // to store the next command and operation
  char *com, *dummy, *valstr_1, *valstr_2, *op;  // for using with strtok, strtol
  string val_1, val_2;                      // the value from the command
  AVL myAVL;                                     // initializing the linked list

  while (getline(input, command))  // get next line of input, store as repeat
  {
    if (command.length() == 0)  // command is empty
      continue;
    com = strdup(command.c_str());  // annoying, first copy string into a "C-style" string
    op = strtok(com, " \t");        // tokenize command on whitespace, first token is operation

    valstr_1 = strtok(NULL, " \t");  // next token is value, as string (check out documentation on
                                     // strtok, to understand the parsing)
    if (valstr_1 != NULL) {      // first check if there is actually anything to convert into int
      val_1 = string(valstr_1);  // convert initial portion of valstr into an integer val_1, with
                                 // base 10. Check out documentation on strtol for more details.
      cout << val_1 << endl;
    }

    valstr_2 = strtok(NULL, " \t");
    if (valstr_2 != NULL) {
      val_2 = string(valstr_2);
      cout << val_2 << endl;
    }

    if(strcmp(op,"i") == 0) // insert into list
    {
        cout << "Insert "+val_1 << endl;
        myAVL.insert(val_1);
    }
    if(strcmp(op,"r") == 0) // ranges queries
    {
      cout << "Range("<<val_1 << " ," << val_2 << ")" <<endl;
      output << myAVL.range(val_1, val_2)<<endl;
    }
    // if(strcmp(op,"d") == 0) // delete from list
    // {
    //     cout << "Delete "+val_1 << endl;
    //     free(myAVL.deleteKey(val_1)); // delete the value, and free the memory
    // }
    // if(strcmp(op,"f") == 0) // find from list
    // {
    //     string message;
    //     if(myAVL.find(val_1)) // yes, val_1is found in AVL
    //         message = " found";
    //     else
    //         message = " not found";
    //     cout << val_1 + message << endl;
    //     output << val_1+ message << endl;
    //}
  }
  myAVL.deleteAVL();  // delete the tree from memory
  input.close();
  output.close();
}
