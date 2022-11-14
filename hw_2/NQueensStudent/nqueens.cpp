// Reuben Chavez

#include <iostream>
#include <stack>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;
#define MAX_E 5000
#define OFFSET 1

class coordinate {
   public:
      int col;
      int row;
};

class Pair {
   public:
      int col; // stores current col
      vector<vector<int>> board; // stores current associated board
};
// Simple insertion sort helper function
// ref https://programmercave0.github.io/blog/2017/08/20/C++-Insertion-Sort-using-STL-(Sorting)
void sort(vector<coordinate> &queen) {
   for (int j = 0; j < queen.size(); j++) {
      coordinate key = queen[j];
      int i = j - 1;
      while (i >= 0 && queen[i].col > key.col) {
         queen[i + 1] = queen[i];
         i--;
      }
      queen[i+1] = key;

   }
   return;
}

// Helper Function to see code
void print_board(vector<vector<int>> board) {
   int N = board.size();
   for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
         printf("%d", board[i][j]);
      }
      printf("\n");
   }
   printf("\n");
}

// Checks if queen can be placed on the board by checking all directions
bool isAttacking(vector < vector < int >> board, int row, int col) {
   int N = board.size();
   if (row >= N || col >= N) // base case (out of range)
      return false;
   if (board[row][col] != 0) // base case (space is alread occupied)
      return false;
   // check all rows and columns
   for (int i = 0; i < N; i++) {
      if (board[row][i] != 0 || board[i][col] != 0)
         return false;
   }
   // check all left and right diagonals
   for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
         if ((i + j == row + col || i - j == row - col) && board[i][j] != 0)
            return false;
      }
   }
   return true;
}

// solve_q_rec is a recursive function that looks for first possible postion for queens
// Input: int col(current columsn on board), vector<vector<int>> board(refrence to board), vector<coordinate> *fixed(maintians all fixed cordinates)
// Output: None 
void solve_q_rec(int col, vector<vector<int>> board, vector<coordinate> *fixed) { // has to consider existing queens
   int N = board.size();
   if(col == N){ // base case
      for(int i = 0; i < N; i++) {
         for(int j = 0; j < N; j++) {
            if(board[i][j] == 1){
               coordinate queen;
               queen.row = i;
               queen.col = j;
               fixed->push_back(queen);
            }
         }
      }
      return;
   }
   for (int i = 0; i < N; i++) { // iterate for all queens
      if (isAttacking(board, i, col)) { // else if it can be placed
         board[i][col] = 1; // set queen to board
         solve_q_rec(col + 1, board, fixed);
         if (fixed -> size() == N) // case fixed has all solution save on next recursive call
            return;
      } else if (!isAttacking(board, i, col) && board[i][col] == 2) { // if cannot be placed becuase occupied by pre_existing
         solve_q_rec(col + 1, board, fixed);
         if (fixed -> size() == N)// case fixed has all solution save on next recursive call
            return;
      }

      // case to backtrack with queens involved
      if (board[i][col] == 2) { // if at current pre-existing queen
         continue; // continue to next itertation
      } else{
         board[i][col] = 0; // simple back tracking 
      }
   }
   return;
}
// Starter Function of SolveNQueens
// Input : vector<vector<int>>  (matirx refrence), vector <coordinate> * pre_queen (vectors with prexisitng queens)
// Output: vector of corrdinate classe containing all coordinates of all queens
vector <coordinate> solveNQ(vector<vector<int>> board, vector <coordinate> * pre_queen) {
   int N = board.size();
   vector <coordinate> final_output( *pre_queen);
   solve_q_rec(0, board, &final_output);
   return final_output;
}
// Stack Implemtaition of the NQueens Problem
// Input: refrence to the board matrix, and vector of  corrdinates of pre_existing queens 
// Output: Vector of Cooordinates with 
vector <coordinate> solveNQStacks(vector<vector<int>> board, vector <coordinate> *pre_queen) {
   int N = board.size();
   vector <class coordinate> final_output(*pre_queen); // relaiazed if remain is intilized then its empty need to initliaxe empty then use use push back properly
   stack <class Pair> recurStack;
   Pair init, top;
   init.board = board;
   init.col = 0;
   recurStack.push(init);
   while (!recurStack.empty()) {

      top = recurStack.top(); // get the top pair in stack 
      recurStack.pop(); // remove the top element of stack

      if (top.col == N) { // base case
        vector <class coordinate> temp = final_output; // create copy of final_output
        // iterate through current board
        for(int i = 0; i < N; i++) {
         for(int j = 0; j < N; j++) {
            // push back in temp all cordinates with 1
            if(top.board[i][j] == 1){
               coordinate queen;
               queen.row = i;
               queen.col = j;
               temp.push_back(queen);
            }
          }
        }
        // if temp == N -> current board has all queens placed
        if(temp.size() == N){final_output = temp;break;}
        continue; // countinue till next
        
      }
      for (int i = 0; i < N; i++) { // iterate for all queens
         if (isAttacking(top.board, i, top.col)) { //  if it can be placed
            Pair to_push;
            to_push.board = top.board;
            to_push.board[i][top.col] = 1;
            to_push.col = top.col +1;
            recurStack.push(to_push);  
        
         } else if (!isAttacking(top.board, i,top.col) && top.board[i][top.col] == 2) { // if cannot be placed becuase occupied by pre_existing queen
            Pair to_push;
            to_push.board = top.board;
            to_push.col = top.col +1;
            recurStack.push(to_push);
         }

      }
   }
   return final_output;
}
int main(int argc, char ** argv) {
   if (argc < 3) {
      throw std::invalid_argument("Usage: ./n_queens <INPUT FILE> <OUTPUT FILE>"); // throw error
   }

   ifstream input;
   ofstream output;

   input.open(argv[1]);
   output.open(argv[2]);

   int N, row, col; //stores board size, row and col
   string command; // to store current line when opening file
   char * com, * d_1,* token; // refrenced by LinkedList (use for strtok, strtol)
   
   //iterate through file 
   while (getline(input, command)) {
      vector < coordinate > queens; // saves all queen pos
      vector < int > coor; // stores coordinates

      if (command.length() == 0) {continue;}
      
      com = strdup(command.c_str()); // Converts to c string but allso alloacate memory for copy
      token = strtok(com, " \t"); // first token is string length
      // iterate through string to get all points
      while (token != NULL) {coor.push_back(strtol(token, & d_1, 10)); token = strtok(NULL, " \t");}
      
      if (coor.size() % 2 == 0) {output << "No Solution" << endl;continue;} // in case current line in invalid input, missing row or col
      
      N = coor.front(); // first elment of coor is size of board
      coor.erase(coor.begin()); // erase point to get coordinate of prexisting queens
      
      vector < vector < int >> board(N); // create board
      for (int i = 0; i < N; i++) {board[i] = vector < int > (N, 0);}// init matrix with 0
      
      if (coor.size() > 0) { // in the case the line has postion for pre-existin queen(s) -> isAttacking on board + save in queens vector
         
         int add = 0; // varible set to check is all pre_queen are placed
         coordinate pre_q;
         
         for (int i = 0; i < coor.size(); i += 2) {
            row = coor.at(i) - OFFSET; // get row and offset to fit index
            col = coor.at(i + 1) - OFFSET; // get col and offset to fit index
         
            if (isAttacking(board, row, col)) { // check if coordinate can be placed on board and saves cordinates in queens var -> if not break
               board[row][col] = 2;
               pre_q.col = col;
               pre_q.row = row;
               queens.push_back(pre_q); // push to queen vector
               add++;
            } else {
               break;
            }
         }
         
         if (add != coor.size() / 2) // if prexisting queens cant be placed on board w/o attacking -> no solution so skip line
         {
            output << "No Solution" << endl;
            continue;
         }
      }
      queens = solveNQStacks(board, &queens); // solves for  all queen combination
      sort(queens); // sorts coordinate type through inertion sort
      if (queens.size() == N) { // stream output to all
         for (int i = 0; i < N; i++) {
            output << queens[i].col + OFFSET << " " << queens[i].row + OFFSET << " ";
         }
         output << endl;
      } else {
         output << "No Solution" << endl;
      }

   }
   input.close();
   output.close();
   return 0;
}