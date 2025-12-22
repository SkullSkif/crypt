#include "graph.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

Graph::Graph(int n) : n(n), m(0) {
    adjacency.resize(n, vector<int>(n, 0));
}

void Graph::addEdge(int u, int v) {
    if (u >= 0 && u < n && v >= 0 && v < n && u != v) {
        if (!hasEdge(u, v)) {
            edges.push_back({u, v});
            adjacency[u][v] = 1;
            adjacency[v][u] = 1;
        }
    }
}

bool Graph::hasEdge(int u, int v) const {
    if (u < 0 || u >= n || v < 0 || v >= n) return false;
    return adjacency[u][v] == 1;
}

void Graph::loadGraphFromFile(const std::string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл графа: " + filename);
    }
    
    file >> n >> m;
    cout << "Чтение графа: n=" << n << ", m=" << m << endl;
    
    adjacency.clear();
    adjacency.resize(n, vector<int>(n, 0));
    edges.clear();
    
    int edges_read = 0;
    for (int i = 0; i < m; i++) {
        int u, v;
        
        if (!(file >> u >> v)) {
            throw runtime_error("Ошибка чтения ребра " + to_string(i));
        }
        
        if (u < 0 || u >= n || v < 0 || v >= n) {
            throw runtime_error("Неверные номера вершин в ребре: " + 
                               to_string(u) + " " + to_string(v));
        }
        
        addEdge(u, v);
        edges_read++;
    }
    
    if (edges_read != m) {
        cout << "Предупреждение: прочитано " << edges_read << " ребер вместо " << m << endl;
        m = edges_read;
    }
    
    file.close();
    cout << "Граф успешно загружен: " << n << " вершин, " << m << " ребер" << endl;
}

void Graph::print() const {
    cout << "Граф (n=" << n << ", m=" << m << "):" << endl;
    cout << "Ребра: ";
    for (const auto& [u, v] : edges) {
        cout << "(" << u << "," << v << ") ";
    }
    cout << endl;
    
    cout << "Матрица смежности:" << endl;
    for (int i = 0; i < min(n, 10); i++) { // показываем только первые 10 строк
        for (int j = 0; j < min(n, 10); j++) { // и первые 10 столбцов
            cout << adjacency[i][j] << " ";
        }
        if (n > 10) cout << "...";
        cout << endl;
    }
    if (n > 10) cout << "... (показаны только первые 10x10 элементов)" << endl;
}

bool HamiltonianCycle::isValid(const Graph& graph) const {
    if (cycle.empty()) {
        cout << "Цикл пуст!" << endl;
        return false;
    }
    
    // Проверяем, что цикл начинается и заканчивается в одной вершине
    if (cycle[0] != cycle.back()) {
        cout << "Цикл не замкнут: первая вершина=" << cycle[0] 
             << ", последняя=" << cycle.back() << endl;
        return false;
    }
    
    // Проверяем длину цикла
    int expectedLength = graph.n + 1;
    if (cycle.size() != expectedLength) {
        cout << "Неверная длина цикла: ожидается " << expectedLength 
             << ", получено " << cycle.size() << endl;
        return false;
    }
    
    // Проверяем, что все вершины графа присутствуют ровно один раз
    vector<bool> visited(graph.n, false);
    for (size_t i = 0; i < cycle.size() - 1; i++) {
        int v = cycle[i];
        if (v < 0 || v >= graph.n) {
            cout << "Неверный номер вершины: " << v << endl;
            return false;
        }
        if (visited[v]) {
            cout << "Вершина " << v << " встречается более одного раза!" << endl;
            return false;
        }
        visited[v] = true;
    }
    
    // Проверяем все ли вершины посещены
    for (int i = 0; i < graph.n; i++) {
        if (!visited[i]) {
            cout << "Вершина " << i << " не посещена!" << endl;
            return false;
        }
    }
    
    // Проверяем все ребра цикла
    for (size_t i = 0; i < cycle.size() - 1; i++) {
        int u = cycle[i];
        int v = cycle[i + 1];
        if (!graph.hasEdge(u, v)) {
            cout << "Ребро (" << u << "," << v << ") отсутствует в графе!" << endl;
            return false;
        }
    }
    
    cout << "Гамильтонов цикл корректен!" << endl;
    return true;
}

void HamiltonianCycle::loadCycleFromFile(const std::string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл цикла: " + filename);
    }
    
    int size;
    if (!(file >> size)) {
        throw runtime_error("Ошибка чтения размера цикла");
    }
    
    cycle.resize(size);
    for (int i = 0; i < size; i++) {
        if (!(file >> cycle[i])) {
            throw runtime_error("Ошибка чтения вершины " + to_string(i));
        }
    }
    
    file.close();
    cout << "Цикл загружен: " << size << " вершин" << endl;
}

void HamiltonianCycle::print() const {
    cout << "Гамильтонов цикл (" << cycle.size() << " вершин): ";
    int limit = min(static_cast<int>(cycle.size()), 15);
    for (int i = 0; i < limit; i++) {
        cout << cycle[i] << " ";
    }
    if (cycle.size() > 15) {
        cout << "... " << cycle.back();
    }
    cout << endl;
}