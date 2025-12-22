#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

void analyzeFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл: " << filename << endl;
        return;
    }
    
    cout << "\nАнализ файла: " << filename << endl;
    cout << "=================================" << endl;
    
    // Читаем первую строку
    string firstLine;
    getline(file, firstLine);
    cout << "Первая строка: '" << firstLine << "'" << endl;
    
    // Парсим первую строку
    int declared_n, declared_m;
    stringstream ss(firstLine);
    ss >> declared_n >> declared_m;
    cout << "Объявлено: n=" << declared_n << ", m=" << declared_m << endl;
    
    // Читаем остальные строки
    int line_count = 1;
    int edge_count = 0;
    int empty_lines = 0;
    int comment_lines = 0;
    int malformed_lines = 0;
    
    string line;
    while (getline(file, line)) {
        line_count++;
        
        // Пропускаем пустые строки
        if (line.empty()) {
            empty_lines++;
            continue;
        }
        
        // Проверяем на комментарии (строки, начинающиеся с # или //)
        if (line[0] == '#' || (line.size() > 1 && line[0] == '/' && line[1] == '/')) {
            comment_lines++;
            continue;
        }
        
        stringstream ss_line(line);
        int u, v;
        
        if (ss_line >> u) {
            if (ss_line >> v) {
                edge_count++;
                // Проверяем, есть ли еще что-то в строке
                string extra;
                if (ss_line >> extra) {
                    cout << "  Строка " << line_count << ": дополнительные данные: '" << extra << "'" << endl;
                }
            } else {
                malformed_lines++;
                cout << "  Строка " << line_count << ": только одна вершина: '" << line << "'" << endl;
            }
        } else {
            malformed_lines++;
            cout << "  Строка " << line_count << ": не содержит чисел: '" << line << "'" << endl;
        }
    }
    
    file.close();
    
    cout << "\nСтатистика:" << endl;
    cout << "  Всего строк в файле: " << line_count << endl;
    cout << "  Пустых строк: " << empty_lines << endl;
    cout << "  Строк-комментариев: " << comment_lines << endl;
    cout << "  Некорректных строк: " << malformed_lines << endl;
    cout << "  Строк с ребрами: " << edge_count << endl;
    cout << "\n  Объявлено ребер (m): " << declared_m << endl;
    cout << "  Фактически найдено ребер: " << edge_count << endl;
    
    if (edge_count != declared_m) {
        cout << "\n  ВНИМАНИЕ: Несоответствие! Разница: " << abs(edge_count - declared_m) << endl;
        if (edge_count > declared_m) {
            cout << "  Возможно в файле есть комментарии или лишние данные" << endl;
        } else {
            cout << "  Возможно не все ребра указаны" << endl;
        }
    }
    
    cout << "=================================\n" << endl;
}

int main() {
    cout << "Анализатор файлов графов" << endl;
    
    analyzeFile("./graph_medium.txt");
    analyzeFile("./cycle_medium.txt");
    
    // Создадим корректный тестовый файл
    cout << "\nСоздание корректного тестового файла..." << endl;
    ofstream out("test_correct.txt");
    out << "5 5" << endl;
    out << "0 1" << endl;
    out << "1 2" << endl;
    out << "2 3" << endl;
    out << "3 4" << endl;
    out << "4 0" << endl;
    out.close();
    
    cout << "Создан файл test_correct.txt" << endl;
    
    return 0;
}