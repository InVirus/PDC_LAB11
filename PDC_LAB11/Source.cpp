#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <stack>

const int INF = 1000000000;

void loadGraph(const char* filename, int**& matrix, int& n, int& m) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Помилка відкриття файлу." << std::endl;
        return;
    }

    file >> n >> m;

    matrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = INF;
        }
        matrix[i][i] = 0;
    }

    int u, v, w;
    for (int i = 0; i < m; ++i) {
        file >> u >> v >> w;
        matrix[u - 1][v - 1] = w;
    }

    file.close();
}

void floydWarshall(int** matrix, int n, int**& dist, int**& next) {
    dist = new int* [n];
    next = new int* [n];
    for (int i = 0; i < n; ++i) {
        dist[i] = new int[n];
        next[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            dist[i][j] = matrix[i][j];
            if (matrix[i][j] != INF) {
                next[i][j] = j;
            }
            else {
                next[i][j] = -1;
            }
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

void printMatrix(int** matrix, int n, std::ofstream& outFile) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == INF) {
                std::cout << "INF ";
                outFile << "INF ";
            }
            else {
                std::cout << matrix[i][j] << " ";
                outFile << matrix[i][j] << " ";
            }
        }
        std::cout << std::endl;
        outFile << std::endl;
    }
}

void printPath(int** next, int start, int end, std::ofstream& outFile) {
    if (next[start][end] == -1) {
        std::cout << "Немає шляху." << std::endl;
        outFile << "Немає шляху." << std::endl;
        return;
    }

    std::stack<int> path;
    for (int at = start; at != end; at = next[at][end]) {
        path.push(at);
    }
    path.push(end);

    std::cout << "Шлях: ";
    outFile << "Шлях: ";
    while (!path.empty()) {
        std::cout << path.top() + 1 << " ";
        outFile << path.top() + 1 << " ";
        path.pop();
    }
    std::cout << std::endl;
    outFile << std::endl;
}

void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const char* inputFilename = "in.txt";
    const char* outputFilename = "out.txt";
    int n, m;
    int** matrix = nullptr;

    loadGraph(inputFilename, matrix, n, m);

    int** dist = nullptr;
    int** next = nullptr;
    floydWarshall(matrix, n, dist, next);

    std::ofstream outFile(outputFilename);
    if (!outFile) {
        std::cerr << "Помилка відкриття файлу для запису." << std::endl;
        return 1;
    }

    std::cout << "Матриця відстаней:" << std::endl;
    outFile << "Матриця відстаней:" << std::endl;
    printMatrix(dist, n, outFile);

    int start, end;
    std::cout << "Введіть початкову вершину: ";
    std::cin >> start;
    std::cout << "Введіть кінцеву вершину: ";
    std::cin >> end;

    std::cout << "Найкоротший шлях між " << start << " та " << end << ": ";
    outFile << "Найкоротший шлях між " << start << " та " << end << ": ";
    printPath(next, start - 1, end - 1, outFile);

    outFile.close();

    freeMatrix(matrix, n);
    freeMatrix(dist, n);
    freeMatrix(next, n);

    return 0;
}
