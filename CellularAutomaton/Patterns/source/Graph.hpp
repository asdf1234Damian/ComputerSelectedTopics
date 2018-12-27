#include "sstream"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

class Graph {
public:
  std::vector<std::string> nodes;
  std::vector<std::pair<std::string, std::string>> edges;
  Graph(std::string a, std::string b);
  bool belongs(std::string s);
  void addEdge(std::string a, std::string b);
  void addEdges(std::vector<std::string> v, std::string s);
  bool merge(Graph g);
  void print(std::string s);
  void print();
};
// No graph is created without at least an edge
Graph::Graph(std::string a, std::string b) { addEdge(a, b); }
// See if a given node is in the graph or vector
bool Graph::belongs(std::string s) {
  int l = 0, r = nodes.size() - 1;
  while (l <= r) {
    unsigned m = l + (r - l) / 2;
    if (nodes[m] == s)
      return true;
    if (nodes[m] < s)
      l = m + 1;
    else
      r = m - 1;
  }
  return false;
}
// Adds an edge and and its nodes to the graph
void Graph::addEdge(std::string a, std::string b) {
  if (!this->belongs(a)) {
    this->nodes.push_back(a);
  }
  if (a != b && !this->belongs(b)) {
    this->nodes.push_back(b);
  }
  std::sort(nodes.begin(), nodes.end());
  this->edges.push_back(std::pair<std::string, std::string>(a, b));
}
// Adds all the edges with the same end. If ends is already in the graph
void Graph::addEdges(std::vector<std::string> starts, std::string end) {
  nodes.insert(nodes.end(),starts.begin(),starts.end());
  std::sort(nodes.begin(),nodes.end());
  for (size_t i = 0; i < starts.size(); i++) {
    this->edges.push_back(std::make_pair(starts.at(i), end));
  }
}
// Function to print all the edges of the Graph to a file
void Graph::print(std::string s) {
  std::ofstream file;
  file.open(s);
  // file << "No. Nodes: " << nodes.size() << '\n';
  // file << "No. Edges: " << edges.size() << '\n';
  for (size_t i = 0; i < edges.size(); i++) {
    file << edges.at(i).first + ", " + edges.at(i).second << '\n';
  }
}
// Function to print all the edges of the Graph to stdout
void Graph::print() {
  std::cout << "G={" << nodes.size() << "," << edges.size() << "}" << '\n';
  for (size_t i = 0; i < edges.size(); i++) {
    std::cout << edges.at(i).first + ", " + edges.at(i).second << '\n';
  }
}
