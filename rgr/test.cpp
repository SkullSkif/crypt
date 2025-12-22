#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

// Генератор случайного гамильтонова графа с известным циклом
void generateHamiltonianGraph(int n, double edgeDensity, 
                            const string& graphFile, 
                            const string& cycleFile) {
    
    mt19937 rng(time(nullptr));
    uniform_real_distribution<double> dist(0.0, 1.0);
    
    // Создаем случайный гамильтонов цикл
    vector<int> cycle(n + 1);
    for (int i = 0; i < n; i++) {
        cycle[i] = i;
    }
    shuffle(cycle.begin(), cycle.end() - 1, rng);
    cycle[n] = cycle[0]; // Замыкаем цикл
    
    // Создаем граф с гамильтоновым циклом
    vector<vector<bool>> adjacency(n, vector<bool>(n, false));
    
    // Добавляем ребра цикла
    for (int i = 0; i < n; i++) {
        int u = cycle[i];
        int v = cycle[i + 1];
        adjacency[u][v] = true;
        adjacency[v][u] = true;
    }
    
    // Добавляем случайные дополнительные ребра
    int m = n; // уже есть n ребер в цикле
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (!adjacency[i][j] && dist(rng) < edgeDensity) {
                adjacency[i][j] = true;
                adjacency[j][i] = true;
                m++;
            }
        }
    }
    
    // Сохраняем граф в файл
    ofstream gfile(graphFile);
    gfile << n << " " << m << endl;
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adjacency[i][j]) {
                gfile << i << " " << j << endl;
            }
        }
    }
    gfile.close();
    
    // Сохраняем цикл в файл
    ofstream cfile(cycleFile);
    cfile << n + 1 << endl;
    for (int v : cycle) {
        cfile << v << " ";
    }
    cfile.close();
    
    cout << "Сгенерирован граф с " << n << " вершинами и " << m << " ребрами" << endl;
    cout << "Гамильтонов цикл сохранен" << endl;
}

int main() {
    cout << "Генератор тестовых данных для задачи о гамильтоновом цикле" << endl;
    cout << "==========================================================" << endl;
    
    // Пример 1: маленький граф
    generateHamiltonianGraph(10, 0.3, "graph_small.txt", "cycle_small.txt");
    
    // Пример 2: средний граф
    generateHamiltonianGraph(20, 0.2, "graph_medium.txt", "cycle_medium.txt");
    
    // Пример 3: большой граф
    generateHamiltonianGraph(50, 0.1, "graph_large.txt", "cycle_large.txt");
    
    return 0;
}