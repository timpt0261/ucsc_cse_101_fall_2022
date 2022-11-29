#include <iostream>
#include <algorithm>
#include <array>
#include <cstring>
#include <deque>
#include <fstream>
#include <list>
#include <unordered_map>
#include <queue>
#include <set>
#include <unordered_set>
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
    // https://www.youtube.com/watch?v=oDqjPvD54Ss
  int V;                                     // number of vertexes
  set<string> _v;                            // Set of  vectecies
  unordered_map<string, list<pair<string, string>>> l; // Adj list
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

    string reconstructed(string start, string end, vector<string> prev)
    {
      vector<string> path;

      for (string at = end; at.empty(); at = prev[GetIndex(_v, at)]){
        // string movie_name = at != end ? prev[GetIndex(_v, at)].second: "";
        path.push_back(at);
      }
      reverse(path.begin(), path.end());
      auto a = l[start];
      

      if (path[0] == start){
        string out = "";
        for (list<pair<string, string>>::iterator curr = a.begin(); curr != a.end(); curr++)
        {
          if(curr->first == ){

          }

             
        }
        
      }
      return "";
    }

    string bfs(string start, string end)
    {
      queue<string> Q; // initlize queue
      Q.emplace(start); // enqueue start
      vector<bool> visited(V, false); // initlize bool vector of visited
      int index = GetIndex(_v, start); // get the index of the start string
      visited[index] = true;
      vector<string> prev(V, NULL); // initilaize string vector of prev

      while(!Q.empty()){
        string u = Q.front(); // u = dequeue of Q
        Q.pop();
        auto neighbors = l[u]; // set of neighbors 

        for(int i = 0; i < neighbors.size(); i++){
          string next = neighbors.front().first;
          // string adj = neighbors.front().second;
          neighbors.pop_front();
          int next_index = GetIndex(_v, next);

          if(!visited[next_index]){
            visited[next_index] = true;
            prev[next_index] = u;
            Q.push(next);
          }
          
        }
      }

      return reconstructed(start, end, prev);
    }
};

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

  string command, curr_line;                  // to store the next command and operation
  char *com, *dummy, *valstr, *op;            // for using with strtok, strtol
  Graph G;

  // create graph
  // https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
  while(getline(movie, curr_line)){
    if(curr_line.length() == 0){continue;}
    deque <string> tokens;
    stringstream check1(curr_line);
    string intermediate;

    while(getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }

    string movie_name = tokens.front();
    tokens.pop_front();
    for(int i = 0; i< tokens.size(); i++){
      for (int j = 0; i < tokens.size(); j++)
      {
        if( i == j)
          continue;
        G.addEdge(tokens.at(i), tokens.at(j),movie_name);
      }
    } 
  }


  while(getline(input, command)){
    if(command.length() == 0){continue;}
    deque<string> com;

    stringstream check2(command);
    string intermediate;

    while (getline(check2, intermediate, ' '))
    {
      com.push_back(intermediate);
    }

    output << G.bfs(com.at(0), com.at(1)) << endl;


  }
  
  
  movie.close();
  input.close();
  output.close();
  return 0;
}