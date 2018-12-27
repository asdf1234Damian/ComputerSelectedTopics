#include "Graph.hpp"
unsigned int size;    // Size of the array
short us, ls, ub, lb; // Parameter for the rule


bool belongs(std::vector<std::string> v, std::string s) {
  int l = 0, r = v.size() - 1;
  while (l <= r) {
    unsigned m = l + (r - l) / 2;
    if (v[m] == s)
      return true;
    if (v[m] < s)
      l = m + 1;
    else
      r = m - 1;
  }
  return false;
}
bool belongs(std::vector<std::pair<unsigned, unsigned>> v,
             std::pair<unsigned, unsigned> p) {
  for (size_t i = 0; i < v.size(); i++) {
    if (v.at(i) == p) {
      return true;
    }
  }
  return false;
}
// Auxiliar function for getting the 2d position in the 1d
int getIndex(int x, int y) { return y * size + x; }
// Auxiliar fucntion for toroid structure of the grid
int getVal(std::string perm, int x, int y) {
  if (x < 0) {
    x = size - 1;
  } else if (x >= (int)size) {
    x = 0;
  }
  if (y < 0) {
    y = size - 1;
  } else if (y >= (int)size) {
    y = 0;
  }
  if (perm[getIndex(x, y)] == '1') {
    return 1;
  }
  return 0;
}
// Gets the sum of the Moove Neightborhood
int neighSum(std::string perm, int x, int y) {
  return (getVal(perm, x - 1, y + 1) + getVal(perm, x - 1, y) +
          getVal(perm, x - 1, y - 1) + getVal(perm, x, y + 1) +
          getVal(perm, x, y - 1) + getVal(perm, x + 1, y + 1) +
          getVal(perm, x + 1, y) + getVal(perm, x + 1, y - 1));
}
// Compares neighSum value with the ones in the rule
bool rule(short int x, short int y, std::string perm) {
  bool alive = getVal(perm, x, y);
  if (alive && neighSum(perm, x, y) >= ls && neighSum(perm, x, y) <= us) {
    return true;
  } else if (!alive && neighSum(perm, x, y) >= lb &&
             neighSum(perm, x, y) <= ub) {
    return true;
  } else {
    return false;
  }
}
// Returns the String for the next state of the automaton
std::string nextState(std::string cPerm) {
  std::string nPerm(size * size, '0');
  for (size_t y = 0; y < size; y++) {
    for (size_t x = 0; x < size; x++) {
      if (rule(x, y, cPerm)) {
        nPerm[getIndex(x, y)] = '1';
      }
    }
  }
  return nPerm;
}
// https://stackoverflow.com/questions/5056645/sorting-stdmap-using-value
template <typename A, typename B>
std::pair<B, A> flip_pair(const std::pair<A, B> &p) {
  return std::pair<B, A>(p.second, p.first);
}

template <typename A, typename B>
std::multimap<B, A> flip_map(const std::map<A, B> &src) {
  std::multimap<B, A> dst;
  std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
                 flip_pair<A, B>);
  return dst;
}
// Main Program
int main(int argc, char const *argv[]) {
  // Get parameters form the terminal
  size = (unsigned int)std::stoi(argv[1]);
  ls = std::stoi(argv[2]);
  us = std::stoi(argv[3]);
  lb = std::stoi(argv[4]);
  ub = std::stoi(argv[5]);
  // Generates the array of size 'size*size' with 'i' 1s in it
  std::string perm; // string of current perm
  std::string next; // string of next perm
  // Holds all the edges
  std::vector<std::pair<std::string, std::string>> E;
  // Holds all the graphs
  std::vector<Graph> G;
  // Holds the nodes already added to the graphs vector
  std::vector<std::string> N;
  // This part of the code is dedicated to create the perms and add them to
  // pems.
  std::cout << "Creating all edges..." << '\n';
  for (size_t i = 0; i <= size * size; i++) {
    perm = "";
    for (size_t j = 0; j < size * size - i; j++) {
      perm.append("0");
    }
    for (size_t k = 0; k < i; k++) {
      perm.append("1");
    }
    do {
      next = nextState(perm);
      if (next == perm) {
        G.push_back(Graph(perm, next));
        N.push_back(perm);
      } else {
        E.push_back(std::make_pair(perm, nextState(perm)));
        // std::cout <<perm<< ", " <<nextState(perm)<< '\n';
      }
    } while (std::next_permutation(perm.begin(), perm.end()));
  }
  std::cout << "Done!" << '\n';
  std::cout << "Finding hubs..." << '\n';
  // Holds the nodes with more links
  std::map<std::string, int> hubs;
  // Holds all the hubs previous states
  std::map<std::string, std::vector<std::string>> links;
  for (size_t i = 0; i < E.size(); i++) {
    hubs[E.at(i).second]++;
    links[E.at(i).second].push_back(E.at(i).first);
  }
  for (auto i = hubs.begin(); i != hubs.end(); ++i) {
    std::cout << i->first<<", "<<i->second << '\n';
  }
  E.clear();
  getchar();
  std::cout << "Sortting by link value" << '\n';
  std::multimap<int, std::string> sorted = flip_map(hubs);
  std::cout << "Done!" << '\n';
  std::cout << "Linking edges..." << '\n';
  bool sameG;
  do {
    sameG=false;
    for (auto it = sorted.begin(); it != sorted.end();) {
      std::string cHub = it->second;
      if (belongs(N, cHub)) {
        sameG=true;
        for (size_t i = 0; i < G.size(); i++) {
          if (belongs(G.at(i).nodes, cHub)) {
            std::vector<std::string> origins=links.at(cHub);
            G.at(i).addEdges(origins, cHub);
            N.insert(N.end(), origins.begin(),origins.end());
            std::sort(N.begin(),N.end());
            auto aux = it;
            ++aux;
            sorted.erase(it);
            it = aux;
          }
        }
      }else{
        ++it;
      }
    }
    if (sameG==false) {
      std::cout << "😊" << '\n';



      getchar();
    }
  } while (!sorted.empty());
  std::cout << "Done!\n#G = " << '\n';
  std::cout << G.size() << '\n';

  for (size_t i = 0; i < G.size(); i++) {
    G.at(i).print();
  }
}
