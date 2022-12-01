#include <iostream>
#include <algorithm>
#include <array>
#include <deque>
#include <fstream>
#include <iterator>
#include <list>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <map>
#include <utility>
#include <vector>

using namespace std;

// ref https://www.youtube.com/watch?v=drpdVQq5-mk&t=177s
// https://www.youtube.com/watch?v=oDqjPvD54Ss
class Graph
{
  int V;                                     // number of vertexes
  set<string> _v;                            // Set of  vectecies
  map<string, list<pair<string, string>>> l; // Adj list

public:
  // creates new edge for graph
  // Input : string of actor names
  // Output : void
  void addEdge(string actor_a, string actor_b, string movie_name)
  {
    if (actor_a == actor_b) // case of duplicates
      return;
    l[actor_a].push_back(make_pair(actor_b, movie_name));
    l[actor_b].push_back(make_pair(actor_a, movie_name));
    _v.insert(actor_a);
    _v.insert(actor_b);
    V = _v.size();
    return;
  }
  // Returns deque of all adjacent movie names of all actors in given path
  // Input: two deque <strings>, one to return adj another that has given path
  // Output: void
  void find_adj(deque<string> &adj, deque<string> path)
  {
    // iterates every string in path
    for (deque<string>::iterator a = path.begin(); a < path.end(); a++)
    {
      auto n = next(a, 1); // vaules next to a
      // iterate through list of pird tofind movie in refrence
      for (auto s : l[*a])
      {
        if (s.first == *n)
        {
          adj.push_front(s.second);
          break;
        }
      }
    }
  }

  string reconstructed(string start, string end, map<string, string> prev)
  {
    deque<string> path;
    deque<string> adj; // stores adjacent names

    for (auto at = end; !at.empty(); at = prev[at])
      path.push_front(at);

    if (path[0] == start)
    {
      string out = "";
      find_adj(adj, path); // finds movie names betwen adjacent

      for (auto a : path)
      {
        out += a;
        if (!adj.empty())
        {
          out += " -(" + adj.front() + ")- ";
          adj.pop_front();
        }
      }
      return out;
    }
    return "Not present";
  }

  string bfs(string start, string end)
  {
    if (start == end)
      return start;
    if (_v.find(start) == _v.end())
      return "Not present";
    deque<string> Q;           // initlize queue
    Q.push_back(start);        // enqueue start
    map<string, bool> visited; // initlize vector of bool to false wisth size of the number of vectors
    map<string, string> prev;  // initilaize string vector of prev
    for (auto a : _v)
    {
      visited[a] = false;
      prev[a] = "";
    }
    visited[start] = true;

    while (!Q.empty())
    {
      string u = Q.front(); // u = dequeue of Q
      Q.pop_front();

      auto neighbors = l[u]; // set of neighbors of current u

      // itrerate throught the neightbors
      for (auto next = neighbors.begin(); next != neighbors.end(); next++)
      {
        // int next_index = GetIndex(_v, next->first); // get index of current string
        if (!visited[next->first])
        { // check is visted
          visited[next->first] = true;
          prev[next->first] = u;
          Q.push_back(next->first);
        }
      }
    }

    return reconstructed(start, end, prev);
  }
};

int main(int argc, char **argv)
{
  if (argc < 3) // must provide two arguments as input
  {
    throw std::invalid_argument("Usage: ./sixdegrees <INPUT FILE> <OUTPUT FILE>"); // throw error
  }

  ifstream input;
  ofstream output;
  fstream movie;

  string movie_file = "cleaned_movielist.txt";
  movie.open(movie_file, ios::in);
  input.open(argv[1]);
  output.open(argv[2]);

  string command, curr_line; // to store the next command and operation
  Graph G;

  // create graph
  // https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
  while (getline(movie, curr_line))
  {
    if (curr_line.length() == 0)
    {
      continue;
    }
    deque<string> tokens;
    stringstream check1(curr_line);
    string intermediate;
    while (getline(check1, intermediate, ' '))
      tokens.push_back(intermediate);

    string movie_name = tokens.front();
    tokens.pop_front();
    for (auto i : tokens)
    {
      for (auto j : tokens)
      {
        if (i == j)
          continue;
        G.addEdge(i, j, movie_name);
      }
    }
  }

  while (getline(input, command))
  {
    if (command.length() == 0)
    {
      continue;
    }
    deque<string> com;

    stringstream check2(command);
    string intermediate;

    while (getline(check2, intermediate, ' '))
    {
      com.push_back(intermediate);
    }

    string out = G.bfs(com.at(0), com.at(1));
    output << out << endl;
  }

  movie.close();
  input.close();
  output.close();
  return 0;
}