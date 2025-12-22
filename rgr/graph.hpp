#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <utility>

struct Graph {
    int n; // количество вершин
    int m; // количество ребер
    std::vector<std::pair<int, int>> edges; // список ребер
    std::vector<std::vector<int>> adjacency; // матрица смежности
    
    Graph(int n = 0);
    void addEdge(int u, int v);
    bool hasEdge(int u, int v) const;
    void loadGraphFromFile(const std::string& filename);
    void print() const;
};

struct HamiltonianCycle {
    std::vector<int> cycle; // последовательность вершин цикла
    bool isValid(const Graph& graph) const;
    void loadCycleFromFile(const std::string& filename);
    void print() const;
};

#endif