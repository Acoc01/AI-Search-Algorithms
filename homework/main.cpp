#include "search_algo.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>

void clean(std::vector<int> &v1, int value) {
  for (int i = 0; i < v1.size(); ++i) {
    v1[i] = value;
  }
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cout << "Ingresar nombre de grafo: ./c filename \n";
    return 1;
  }
  algorithms init;

  int beg, dest;

  std::vector<std::vector<std::pair<int, int>>> graph(8);
  std::vector<int> heuristics(8, 0);
  std::vector<int> visited(8, 0);
  std::vector<int> path(8, -1);
  std::vector<int> solution(8, 0);
  /*Solucion optima para comparar con DFS*/
  solution[0] = 1;
  solution[1] = 1;
  solution[3] = 1;
  solution[7] = 1;
  std::vector<int> expanded(8, 0);
  std::map<char, int> toNumbers;
  std::map<int, char> toLetters;

  init.parcer(argv[1], graph, heuristics, toNumbers, toLetters, beg, dest);

  for (int i = 0; i < graph.size(); ++i) {
    for (int j = 0; j < graph[i].size(); ++j) {
      std::cout << toLetters[graph[i][j].first] << ' ' << graph[i][j].second
                << ' ';
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  for (std::vector<int>::iterator it = heuristics.begin();
       it != heuristics.end(); ++it) {
    std::cout << *it << ' ';
  }
  std::cout << std::endl;
  std::cout << "Ejecutando algoritmo DFS..." << std::endl;
  init.dfs(graph, beg, dest, visited, expanded);

  std::cout << "Camino recorrido: \n";
  for (int i = 0; i < visited.size(); ++i) {
    if (visited[i] == 1)
      std::cout << toLetters[i] << ' ';
  }
  std::cout << std::endl;

  std::cout << "Nodos totales Expandidos: ";
  int total = 0;
  for (int i = 0; i < expanded.size(); ++i) {
    total += expanded[i];
  }
  std::cout << total << std::endl;

  std::cout << "Nodos en especifico expandidos: \n";

  for (int i = 0; i < expanded.size(); ++i) {
    std::cout << toLetters[i] << ": " << expanded[i] << std::endl;
  }
  std::cout << std::endl;

  std::cout << "¿Solución Optima?\n";

  if (solution == visited) {
    std::cout << "Solucion Optima encontrada.\n";
  } else {
    std::cout << "Solucion no Optima encontrada.\n";
  }

  /*Ejecutando BCU*/
  std::cout << "Ejecutando algoritmo BCU..." << std::endl;
  clean(visited, 0);
  clean(expanded, 0);
  init.uniform(graph, 0, 7, visited, expanded, path);

  /*Solución Optima para BCU*/

  std::cout << "Camino recorrido: \n";
  std::vector<int> aux;
  int pos = 7;
  while (pos != -1) {
    aux.push_back(pos);
    pos = path[pos];
  }
  std::sort(aux.begin(), aux.end());
  for (auto i : aux) {
    std::cout << toLetters[i] << ' ';
  }
  std::cout << std::endl;

  std::cout << "Nodos totales Expandidos: ";
  for (int i = 0; i < expanded.size(); ++i) {
    total += expanded[i];
  }
  std::cout << total << std::endl;

  std::cout << "Nodos en especifico expandidos: \n";

  for (int i = 0; i < expanded.size(); ++i) {
    std::cout << toLetters[i] << ": " << expanded[i] << std::endl;
  }
  std::cout << std::endl;

  std::cout << "¿Solución Optima?\n";

  if (path[7] == 3 && path[3] == 1 && path[1] == 0) {
    std::cout << "Solucion Optima encontrada.\n";
  } else {
    std::cout << "Solucion no Optima encontrada.\n";
  }
  /*Ejecutando Greedy*/
  std::cout << "Ejecutando algoritmo Greedy..." << std::endl;
  clean(visited, 0);
  clean(expanded, 0);
  clean(path, -1);
  init.greedy(graph, 0, 7, visited, expanded, heuristics, path);
  /*Solucion Optima para Greedy*/

  pos = 7;
  clean(aux, 0);
  while (pos != -1) {
    aux.push_back(pos);
    pos = path[pos];
  }
  std::sort(aux.begin(), aux.end());
  for (auto i : aux) {
    std::cout << toLetters[i] << ' ';
  }
  std::cout << std::endl;

  std::cout << "Nodos totales Expandidos: ";
  for (int i = 0; i < expanded.size(); ++i) {
    total += expanded[i];
  }
  std::cout << total << std::endl;

  std::cout << "Nodos en especifico expandidos: \n";

  for (int i = 0; i < expanded.size(); ++i) {
    std::cout << toLetters[i] << ": " << expanded[i] << std::endl;
  }
  std::cout << std::endl;

  std::cout << "¿Solución Optima?\n";

  if (path[7] == 3 && path[3] == 1 && path[1] == 0) {
    std::cout << "Solucion Optima encontrada.\n";
  } else {
    std::cout << "Solucion no Optima encontrada.\n";
  }
}
