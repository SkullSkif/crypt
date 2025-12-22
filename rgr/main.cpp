#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstring>
#include <stdexcept>
#include "graph.hpp"

using namespace std;

// Класс для верификатора
class Verifier {
private:
    const Graph& graph;
    mt19937 rng;
    
public:
    Verifier(const Graph& g) : graph(g) {
        rng.seed(time(nullptr) + 1);
    }
    
    bool receiveCommitment(const vector<vector<int>>& encryptedGraph) {
        // Проверяем, что зашифрованный граф имеет правильный размер
        if (encryptedGraph.size() != (size_t)graph.n) {
            cout << "  Неверный размер зашифрованного графа" << endl;
            return false;
        }
        for (const auto& row : encryptedGraph) {
            if (row.size() != (size_t)graph.n) {
                cout << "  Неверный размер строки в зашифрованном графе" << endl;
                return false;
            }
        }
        return true;
    }
    
    int sendChallenge() {
        uniform_int_distribution<int> dist(0, 1);
        return dist(rng);
    }
    
    bool verifyResponse(int challenge, 
                       const vector<vector<int>>& encryptedGraph,
                       const vector<int>& response) {
        
        if (challenge == 0) {
            return verifyIsomorphism(response, encryptedGraph);
        } else {
            return verifyCycle(response, encryptedGraph);
        }
    }
    
private:
    bool verifyIsomorphism(const vector<int>& permutation, 
                          const vector<vector<int>>& encryptedGraph) {
        
        if (permutation.size() != (size_t)graph.n) {
            cout << "  Неверный размер перестановки" << endl;
            return false;
        }
        
        // Проверяем, что permutation - это перестановка вершин
        vector<bool> seen(graph.n, false);
        for (int v : permutation) {
            if (v < 0 || v >= graph.n) {
                cout << "  Неверный номер вершины в перестановке: " << v << endl;
                return false;
            }
            if (seen[v]) {
                cout << "  Вершина " << v << " повторяется в перестановке" << endl;
                return false;
            }
            seen[v] = true;
        }
        
        // Проверяем, что encryptedGraph изоморфен исходному графу
        for (int i = 0; i < graph.n; i++) {
            for (int j = i + 1; j < graph.n; j++) {
                bool originalEdge = graph.hasEdge(i, j);
                bool encryptedEdge = (encryptedGraph[permutation[i]][permutation[j]] == 1);
                if (originalEdge != encryptedEdge) {
                    cout << "  Несоответствие ребра: (" << i << "," << j << ") ";
                    cout << "оригинал=" << originalEdge << ", зашифровано=" << encryptedEdge << endl;
                    return false;
                }
            }
        }
        return true;
    }
    
    bool verifyCycle(const vector<int>& response,
                    const vector<vector<int>>& encryptedGraph) {
        
        if (response.empty()) {
            cout << "  Пустой ответ" << endl;
            return false;
        }
        
        // Первый элемент - длина цикла
        int cycleLength = response[0];
        if (cycleLength != graph.n + 1) {
            cout << "  Неверная длина цикла: " << cycleLength 
                 << ", ожидается " << graph.n + 1 << endl;
            return false;
        }
        
        if (response.size() < (size_t)cycleLength + 1) {
            cout << "  Недостаточно данных в ответе" << endl;
            return false;
        }
        
        // Извлекаем цикл из response
        vector<int> cycle(response.begin() + 1, response.begin() + 1 + cycleLength);
        
        // Проверяем, что цикл начинается и заканчивается в одной вершине
        if (cycle[0] != cycle.back()) {
            cout << "  Цикл не замкнут" << endl;
            return false;
        }
        
        // Проверяем, что все вершины (кроме первой/последней) различны
        vector<bool> visited(graph.n, false);
        for (int i = 0; i < graph.n; i++) {
            int v = cycle[i];
            if (v < 0 || v >= graph.n) {
                cout << "  Неверный номер вершины в цикле: " << v << endl;
                return false;
            }
            if (visited[v]) {
                cout << "  Вершина " << v << " повторяется в цикле" << endl;
                return false;
            }
            visited[v] = true;
        }
        
        // Проверяем все ребра цикла в зашифрованном графе
        for (int i = 0; i < graph.n; i++) {
            int u = cycle[i];
            int v = cycle[(i + 1) % cycleLength];
            if (encryptedGraph[u][v] != 1) {
                cout << "  Отсутствует ребро (" << u << "," << v << ") в зашифрованном графе" << endl;
                return false;
            }
        }
        
        return true;
    }
};

// Класс для доказывающего
class Prover {
private:
    const Graph& graph;
    const HamiltonianCycle& hamiltonianCycle;
    mt19937 rng;
    vector<int> permutation;
    
public:
    Prover(const Graph& g, const HamiltonianCycle& hc) 
        : graph(g), hamiltonianCycle(hc) {
        rng.seed(time(nullptr));
    }
    
    void preparePermutation() {
        permutation.resize(graph.n);
        for (int i = 0; i < graph.n; i++) {
            permutation[i] = i;
        }
        shuffle(permutation.begin(), permutation.end(), rng);
        
        // Выводим перестановку для отладки (первые 10 элементов)
        cout << "  Перестановка (первые 10): ";
        for (int i = 0; i < min(10, graph.n); i++) {
            cout << permutation[i] << " ";
        }
        if (graph.n > 10) cout << "...";
        cout << endl;
    }
    
    vector<vector<int>> createEncryptedGraph() {
        vector<vector<int>> encrypted(graph.n, vector<int>(graph.n, 0));
        
        // Применяем перестановку к исходному графу
        for (int i = 0; i < graph.n; i++) {
            for (int j = i + 1; j < graph.n; j++) {
                if (graph.hasEdge(i, j)) {
                    int u = permutation[i];
                    int v = permutation[j];
                    encrypted[u][v] = 1;
                    encrypted[v][u] = 1;
                }
            }
        }
        
        return encrypted;
    }
    
    vector<int> respondToChallenge0() {
        return permutation; // возвращаем перестановку
    }
    
    vector<int> respondToChallenge1() {
        vector<int> response;
        
        // Добавляем длину цикла
        response.push_back(hamiltonianCycle.cycle.size());
        
        // Преобразуем цикл согласно перестановке
        for (size_t i = 0; i < hamiltonianCycle.cycle.size(); i++) {
            int originalVertex = hamiltonianCycle.cycle[i];
            int encryptedVertex = permutation[originalVertex];
            response.push_back(encryptedVertex);
        }
        
        return response;
    }
};

// Протокол доказательства с нулевым разглашением
bool runZKPProtocol(const Graph& graph, const HamiltonianCycle& hc, int rounds = 20) {
    Prover prover(graph, hc);
    Verifier verifier(graph);
    
    int successCount = 0;
    
    for (int round = 0; round < rounds; round++) {
        cout << "\n=== Раунд " << round + 1 << " ===" << endl;
        
        // 1. Доказывающий готовится
        prover.preparePermutation();
        auto encryptedGraph = prover.createEncryptedGraph();
        
        // 2. Доказывающий отправляет зашифрованный граф
        if (!verifier.receiveCommitment(encryptedGraph)) {
            cout << "Доказывающий: ошибка при создании зашифрованного графа" << endl;
            return false;
        }
        
        // 3. Верификатор отправляет случайный запрос
        int challenge = verifier.sendChallenge();
        cout << "Верификатор выбирает запрос: " 
             << (challenge == 0 ? "раскрыть изоморфизм" : "раскрыть цикл") << endl;
        
        // 4. Доказывающий отвечает на запрос
        vector<int> response;
        if (challenge == 0) {
            response = prover.respondToChallenge0();
            cout << "Доказывающий: отправлена перестановка" << endl;
        } else {
            response = prover.respondToChallenge1();
            cout << "Доказывающий: отправлен зашифрованный цикл" << endl;
        }
        
        // 5. Верификатор проверяет ответ
        if (verifier.verifyResponse(challenge, encryptedGraph, response)) {
            cout << "✓ Проверка пройдена успешно" << endl;
            successCount++;
        } else {
            cout << "✗ Проверка не пройдена!" << endl;
            return false;
        }
    }
    
    cout << "\n=========================================" << endl;
    cout << "Все " << rounds << " раундов пройдены успешно!" << endl;
    cout << "Успешных раундов: " << successCount << "/" << rounds << endl;
    return true;
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 3) {
            cout << "Использование: " << argv[0] 
                 << " <файл_графа> <файл_цикла> [количество_раундов]" << endl;
            cout << "Пример: " << argv[0] << " graph.txt cycle.txt 10" << endl;
            return 1;
        }
        
        string graphFile = argv[1];
        string cycleFile = argv[2];
        int rounds = (argc > 3) ? atoi(argv[3]) : 10;
        
        if (rounds <= 0) {
            cout << "Количество раундов должно быть положительным числом" << endl;
            return 1;
        }
        
        cout << "=== Доказательство с нулевым разглашением для гамильтонова цикла ===" << endl;
        cout << "Файл графа: " << graphFile << endl;
        cout << "Файл цикла: " << cycleFile << endl;
        cout << "Количество раундов: " << rounds << endl;
        cout << "=========================================" << endl;
        
        // Загрузка графа
        Graph graph;
        graph.loadGraphFromFile(graphFile);
        cout << endl;
        
        // Загрузка гамильтонова цикла
        HamiltonianCycle hc;
        hc.loadCycleFromFile(cycleFile);
        cout << endl;
        
        // Проверка корректности цикла
        if (!hc.isValid(graph)) {
            cout << "ОШИБКА: Некорректный гамильтонов цикл!" << endl;
            return 1;
        }
        
        // Запуск протокола
        bool result = runZKPProtocol(graph, hc, rounds);
        
        if (result) {
            cout << "\n✓✓✓ ДОКАЗАТЕЛЬСТВО ПРИНЯТО! ✓✓✓" << endl;
            cout << "Доказывающий успешно доказал знание гамильтонова цикла." << endl;
            return 0;
        } else {
            cout << "\n✗✗✗ ДОКАЗАТЕЛЬСТВО ОТВЕРГНУТО! ✗✗✗" << endl;
            cout << "Доказывающему не удалось доказать знание гамильтонова цикла." << endl;
            return 1;
        }
        
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "Неизвестная ошибка" << endl;
        return 1;
    }
}