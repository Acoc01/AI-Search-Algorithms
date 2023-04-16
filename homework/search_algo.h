#ifndef HEADER_SEARCH_ALGO
#define HEADER_SEARCH_ALGO

#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class algorithms {
public:
  void parcer(char *name, std::vector<std::vector<std::pair<int, int>>> &graph,
              std::vector<int> &heuristics, std::map<char, int> &a,
              std::map<int, char> &w, int &init, int &dest);

  void dfs(std::vector<std::vector<std::pair<int, int>>> graph, int ini,
           int dest, std::vector<int> &visited, std::vector<int> &expanded);

  void greedy(std::vector<std::vector<std::pair<int, int>>> graph, int ini,
              int dest, std::vector<int> &visited, std::vector<int> &expanded,
              std::vector<int> heuristics, std::vector<int> &path);

  void uniform(std::vector<std::vector<std::pair<int, int>>> graph, int ini,
               int dest, std::vector<int> &visited, std::vector<int> &expanded,
               std::vector<int> &path);
  void astar(std::vector<std::vector<std::pair<int, int>>> graph, int ini,
             int dest, std::vector<int> &visited, std::vector<int> &expanded,
             std::vector<int> &path, std::vector<int> heuristics);
};

#endif
