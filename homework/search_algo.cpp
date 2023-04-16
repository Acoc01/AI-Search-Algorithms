#include "search_algo.h"
#include <stdlib.h>
#include <time.h>

void algorithms::parcer(char *name,
                        std::vector<std::vector<std::pair<int, int>>> &graph,
                        std::vector<int> &heuristics, std::map<char, int> &a,
                        std::map<int, char> &w, int &init, int &dest) {

  std::ifstream Myfile(name);
  w[0] = 'A';
  w[1] = 'B';
  w[2] = 'C';
  w[3] = 'D';
  w[4] = 'E';
  w[5] = 'F';
  w[6] = 'G';
  w[7] = 'H';
  a['A'] = 0;
  a['B'] = 1;
  a['C'] = 2;
  a['D'] = 3;
  a['E'] = 4;
  a['F'] = 5;
  a['G'] = 6;
  a['H'] = 7;

  /*This reads the init node and the dest node and converts them to int*/
  std::string line;

  std::getline(Myfile, line);

  std::stringstream ss(line);

  std::string aux;

  ss >> aux;
  ss >> aux;

  std::getline(Myfile, line);
  std::stringstream ss2(line);

  std::string aux2;

  ss2 >> aux2;
  ss2 >> aux2;

  init = a[aux[0]];
  dest = a[aux2[0]];
  /*-----------------------------------------------------------------*/

  /*The only way i can know if i'm reading a node with his heuristic is the
   * number of spaces or if it is separated by a comma or the number of words in
   * the line*/

  while (getline(Myfile, line)) {

    std::stringstream ss3(line);
    std::vector<std::string> words;

    int hascomma = 0;

    for (int i = 0; i < line.size(); ++i) {
      if (line[i] == ',')
        hascomma = 1;
    }

    if (hascomma) {
      int u, v, c;

      while (ss3.good()) {

        std::string substr;
        getline(ss3, substr, ' ');
        // std::cout << substr << std::endl;
        words.push_back(substr);
      }

      u = a[words[0][0]];
      v = a[words[1][0]];
      c = std::stoi(words[2]);

      graph[u].push_back(std::make_pair(v, c));

    } else {
      int u, h;
      std::string substr;

      ss3 >> substr;
      u = a[substr[0]];
      ss3 >> substr;
      h = std::stoi(substr);

      heuristics[u] = h;
    }
  }
}

void algorithms::dfs(std::vector<std::vector<std::pair<int, int>>> graph,
                     int ini, int dest, std::vector<int> &visited,
                     std::vector<int> &expanded) {
  visited[ini] = 1;
  expanded[ini] += 1;
  std::srand(time(NULL));
  if (ini == dest)
    return;
  int next = rand() % graph[ini].size();
  dfs(graph, graph[ini][next].first, dest, visited, expanded);
  return;
}

void algorithms::greedy(std::vector<std::vector<std::pair<int, int>>> graph,
                        int ini, int dest, std::vector<int> &visited,
                        std::vector<int> &expanded, std::vector<int> heuristics,
                        std::vector<int> &path) {

  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      pq;

  visited[ini] = 1;
  pq.push(std::make_pair(heuristics[ini], ini));
  while (!pq.empty()) {
    int u = pq.top().second;
    expanded[u] += 1;
    std::cout << "Expandiendo : " << u << "Con heuristica : " << heuristics[u]
              << std::endl;
    pq.pop();
    path[u] = 1;
    if (u == dest)
      return;
    else {
      for (auto i : graph[u]) {
        if (visited[i.first] == 0) {
          std::cout << "Visitando : " << i.first
                    << "Con heuristica : " << heuristics[i.first] << std::endl;
          visited[i.first] = 1;
          pq.push(std::make_pair(heuristics[i.first], i.first));
        }
      }
    }
  }
  return;
}
void algorithms::uniform(std::vector<std::vector<std::pair<int, int>>> graph,
                         int ini, int dest, std::vector<int> &visited,
                         std::vector<int> &expanded, std::vector<int> &path) {

  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      pq;

  visited[ini] = 1;
  int dist = 0;
  pq.push(std::make_pair(dist, ini));
  while (!pq.empty()) {
    int u = pq.top().second;
    dist = pq.top().first;
    // std::cout << "Expandiendo : " << u << "Costo + Distancia ac: " << dist
    //           << std::endl;
    expanded[u] += 1;
    pq.pop();
    if (u == dest)
      return;
    else {
      for (auto i : graph[u]) {
        if (visited[i.first] == 0) {
          // std::cout << "Visitando: " << i.first << ' ' << i.second <<
          // std::endl;
          visited[i.first] = 1;
          path[i.first] = u;
          pq.push(std::make_pair(dist + i.second, i.first));
        }
      }
      // path[pq.top().second] = u;
    }
  }
}
void algorithms::astar(std::vector<std::vector<std::pair<int, int>>> graph,
                       int ini, int dest, std::vector<int> &visited,
                       std::vector<int> &expanded, std::vector<int> &path,
                       std::vector<int> heuristics) {

  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      pq;

  visited[ini] = 1;
  int dist = 0;
  std::vector<int> cost(8, 0);
  pq.push(std::make_pair(dist, ini));
  while (!pq.empty()) {
    int u = pq.top().second;
    dist = cost[u];
    std::cout << "Expandiendo: " << u << " Costo + heuristica + Path: " << dist
              << std::endl;
    expanded[u] += 1;
    pq.pop();
    if (u == dest)
      return;
    else {
      for (auto i : graph[u]) {
        if (visited[i.first] == 0 || dist + i.second + heuristics[i.first]) {
          visited[i.first] = 1;
          cost[i.first] = dist + i.second;
          path[i.first] = u;
          std::cout << "Visitando: " << i.first << ' ' << i.second
                    << "C+H: " << cost[i.first] + heuristics[i.first]
                    << std::endl;
          pq.push(std::make_pair(cost[i.first] + heuristics[i.first], i.first));
        }
      }
      // path[pq.top().second] = u;
    }
  }
}
