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

// Helper function that returns the index of a set
//https://www.geeksforgeeks.org/find-index-of-an-element-in-a-set-in-c/
int GetIndex(set<string> S, string k){
  int index = 1;
  for(auto u : S){
    if(u == k)
      return index;
    index++;
  }
  return -1;
}
// ref https://www.youtube.com/watch?v=drpdVQq5-mk&t=177s
class Graph{
  int V;// number of vertexes
  set<string> _v; // Set of  vectecies
  map<string, list<pair<string, string>>> l; // Adj list
  private:
    string reconstructed(start, end, prev){
      string  output;
      return output;
    } 
  public :
    // creates new edge for graph
    // Input : string of actor names
    // Output : void
    void addEdge(string actor_a, string actor_b, string movie_name){
      if( actor_a == actor_b)// case of duplicates
        return;
      l[actor_a].push_back(make_pair(actor_b, movie_name));
      l[actor_b].push_back(make_pair(actor_a, movie_name));
      _v.insert(actor_a);
      _v.insert(actor_b);
      V = _v.size();
      return;
    }

    string bfs(string start,string end){
      queue<string> Q; // initlize queue
      Q.emplace(start); // enqueue start
      vector<bool> visited(V, false); // initlize bool vector of visited
      int index = GetIndex(_v, start); // get the index of the start string
      visited[index] = true;
      vector<string>prev(V, NULL); // initilaize string vector of prev

      while(!Q.empty()){
        string u = Q.front(); // u = dequeue of Q
        Q.pop();
        auto neighbors = l[u]; // set neighbors 

        for(auto& next:: neighbors){

          int next_index = GetIndex(_v, next);
          if(!visited[next_index]){
            visited[next_index] = true;
            prev[next_index] = u;
            Q.emplace(next);
          }

        }
      }
      return "ab";
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