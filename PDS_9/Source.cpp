#include "Header.h"
#include <queue>
#include<sstream>
bool readGraphFromFile(const string& filePath, vector<vector<unsigned int>>& graph) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Не вдалося відкрити файл. Перевірте шлях." << endl;
        return false;
    }

    graph.clear();
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        unsigned int node;
        vector<unsigned int> neighbors;

        while (iss >> node) {
            neighbors.push_back(node - 1);
        }

        graph.push_back(neighbors);
    }
    file.close();
    return true;
}

void printGraph(const vector<vector<unsigned int>>& graph) {
    cout << "Список суміжностей графа:" << endl;
    for (unsigned int i = 0; i < graph.size(); ++i) {
        cout << i + 1 << ": ";
        for (unsigned int neighbor : graph[i]) {
            cout << neighbor + 1 << " ";
        }
        cout << endl;
    }
}

void printQueue(const queue<int>& q) {
    queue<int> temp = q;
    cout << "[";
    bool first = true;
    while (!temp.empty()) {
        if (!first) cout << ", ";
        cout << temp.front() + 1;
        temp.pop();
        first = false;
    }
    cout << "]";
}

void bfs(int start, const vector<vector<unsigned int>>& adjList) {
    vector<bool> visited(adjList.size(), false);
    vector<int> bfsNumber(adjList.size(), -1);
    queue<int> q;
    int bfsCount = 0;

    q.push(start);
    visited[start] = true;
    bfsNumber[start] = ++bfsCount;

    cout << setw(20) << "Поточна вершина"
        << setw(20) << "BFS-номер"
        << setw(20) << "Черга" << endl;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
      
        cout << setw(20) << current + 1
            << setw(20) << bfsNumber[current]
            << setw(20);
        printQueue(q);
        cout << endl;

        for (int neighbor : adjList[current]) {
            if (neighbor < adjList.size() && neighbor >= 0) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    bfsNumber[neighbor] = ++bfsCount;
                    q.push(neighbor);
                }
            }
            else {
                cerr << "Попередження: сусід " << neighbor + 1 << " виходить за межі графа!" << endl;
            }
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string filePath;
    cout << "Введіть шлях до файлу: ";
    getline(cin, filePath);

    vector<vector<unsigned int>> graph;

    if (!readGraphFromFile(filePath, graph)) {
        return 1;
    }

    printGraph(graph);

    unsigned int startVertex;
    cout << "Введіть номер початкової вершини: ";
    cin >> startVertex;

    if (startVertex < 1 || startVertex > graph.size()) {
        cerr << "Помилка: номер вершини поза межами." << endl;
        return 1;
    }

    cout << "Протокол обходу графу:" << endl;
    bfs(startVertex - 1, graph);

    return 0;
}