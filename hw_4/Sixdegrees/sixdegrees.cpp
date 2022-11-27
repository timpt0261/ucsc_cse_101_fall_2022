#include <iostream>
#include <algorithm>
#include <array>
#include <cstring>
#include <deque>
#include <fstream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <string>
#include <utility>
#include <vector>

using namespace std;
// ref https://www.youtube.com/watch?v=drpdVQq5-mk&t=177s
class Graph{
  int V;// number of vertexes
  int E; // number of Edges
  vector<string> _v;
  //Adj List
  map<string, list<pair<string, string>>> l;
  public:

    // creates new edge for graph
    // Input : string of actor names
    // Output : void
    void addEdge(string actor_a, string actor_b,string movie_name ){
      if( actor_a == actor_b)// case of duplicates
        return;
      l[actor_a].push_back(make_pair(actor_b, movie_name));
      l[actor_b].push_back(make_pair(actor_a, movie_name));
      return;

    }


};

// string breadith_first_search(string actor_1, string actor_2){
//   queue<string> Q;
//   vector<string> pred(movie_list.size());
//   vector<bool> visited;
  
//   pred[actor_1] = 
//   visited[actor_1] = true;
//   while(!Q.empty){
//     string u = Q.top();
//     Q.pop();
//     // for every adjacent list 
//     for(int i = 0; i < ].size(); i++){
//       // if visted  is false 
//         // visited is true
//         // pred[v] = u
//         // enque (Q, u)
//     }

//   }

// }

int main(int argc, char** argv) {
  if (argc < 3)  // must provide two arguments as input
  {
    throw std::invalid_argument("Usage: ./sixdegree <INPUT FILE> <OUTPUT FILE>");  // throw error
  }

  ifstream input;
  ofstream output;
  fstream movie;

  string movie_file = "cleaned_movielist.txt";
  movie.open(movie_file, ios::in);
  input.open(argv[1]);
  output.open(argv[2]);

  string command, curr_line;
  char *com,*d_1, *rank_str;

  

  // create graph
  // https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
  while(getline(movie, curr_line)){
    if(curr_line.length() == 0){continue;}
    vector <string> tokens;
    stringstream check1(curr_line);
    string intermediate;

    while(getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }

    string movie_name = tokens[0];
  }
  
  movie.close();
  input.close();
  output.close();
  return 0;
}