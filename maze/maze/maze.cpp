#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <queue>

using namespace std;

// Размеры лабиринта (должны быть нечетными числами для удобства)
const int WIDTH = 15;
const int HEIGHT = 15;

// Символы для отображения лабиринта
const char WALL = '#';
const char ROAD = ' ';
const char ENTRANCE = 'E';
const char EXIT = 'X';
const char TRAP = 'T';
const char TREASURE = '$';

// Структура клетки лабиринта
struct Cell {
    bool visited;
    bool road;
    bool hasTrap;
    bool hasTreasure;

    Cell() : visited(false), road(false), hasTrap(false), hasTreasure(false) {}
};

// Двумерный массив для лабиринта
vector<vector<Cell>> maze(HEIGHT, vector<Cell>(WIDTH));

// Счетчик ловушек и сокровищ
int trapCounter = 0;
int treasureCounter = 0;

// Функция для отображения лабиринта в консоли
void displayMaze() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                // Границы лабиринта
                cout << WALL;
            }
            else if (i == 1 && j == 1) {
                // Начальная точка
                cout << ENTRANCE;
            }
            else if (i == HEIGHT - 2 && j == WIDTH - 2) {
                // Конечная точка
                cout << EXIT;
            }
            else if (maze[i][j].hasTrap) {
                // Ловушка
                cout << TRAP;
            }
            else if (maze[i][j].hasTreasure) {
                // Сокровище
                cout << TREASURE;
            }
            else {
                // Внутренние клетки лабиринта
                cout << (maze[i][j].road ? ROAD : WALL);
            }
        }
        cout << endl;
    }
}

// Функция для проверки доступности клетки
bool isValid(int x, int y) {
    return (x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH && !maze[x][y].visited);
}

// Алгоритм Эйлера для генерации лабиринта
void generateMaze(int x, int y) {
    maze[x][y].visited = true;
    maze[x][y].road = true;

    // Список соседей в случайном порядке
    vector<pair<int, int>> neighbors = { {x - 2, y}, {x + 2, y}, {x, y - 2}, {x, y + 2} };
    random_shuffle(neighbors.begin(), neighbors.end());

    for (auto neighbor : neighbors) {
        int nx = neighbor.first;
        int ny = neighbor.second;

        if (isValid(nx, ny)) {
            maze[nx][ny].visited = true;
            maze[(x + nx) / 2][(y + ny) / 2].road = true;
            generateMaze(nx, ny);
        }
    }
}

// Структура для хранения состояния клетки и количества ловушек на пути
struct PathState {
    int x, y, traps;
};

// Функция для поиска всех путей от входа до выхода с подсчетом ловушек
bool findPath() {
    vector<vector<int>> trapCount(HEIGHT, vector<int>(WIDTH, INT_MAX));
    queue<PathState> q;
    q.push({ 1, 1, 0 });
    trapCount[1][1] = 0;

    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    while (!q.empty()) {
        PathState current = q.front();
        q.pop();

        if (current.x == HEIGHT - 2 && current.y == WIDTH - 2) {
            return true;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            int newTraps = current.traps + (maze[nx][ny].hasTrap ? 1 : 0);

            if (maze[nx][ny].road && newTraps < trapCount[nx][ny] && newTraps <= 2) {
                trapCount[nx][ny] = newTraps;
                q.push({ nx, ny, newTraps });
            }
        }
    }
    return false;
}

// Функция для добавления ловушек на путь от начала до конца
void addTraps() {
    while (true) {
        // Очищаем ловушки
        for (int i = 1; i < HEIGHT - 1; ++i) {
            for (int j = 1; j < WIDTH - 1; ++j) {
                maze[i][j].hasTrap = false;
            }
        }
        trapCounter = 0;

        // Создаем список всех проходимых клеток в лабиринте
        vector<pair<int, int>> roadCells;
        for (int i = 1; i < HEIGHT - 1; ++i) {
            for (int j = 1; j < WIDTH - 1; ++j) {
                if (maze[i][j].road) {
                    roadCells.push_back({ i, j });
                }
            }
        }

        // Перемешиваем список клеток
        random_shuffle(roadCells.begin(), roadCells.end());

        // Генерируем случайное количество ловушек от 0 до 5
        int numTraps = rand() % 6;
        numTraps = min(numTraps, static_cast<int>(roadCells.size())); // Ограничиваем количество ловушек до размера доступных клеток

        for (int i = 0; i < numTraps; ++i) {
            int x = roadCells[i].first;
            int y = roadCells[i].second;

            // Помещаем ловушку в клетку, если там еще нет ловушки
            if (!maze[x][y].hasTrap) {
                maze[x][y].hasTrap = true;
                trapCounter++;
            }
        }

        // Проверяем, есть ли хотя бы один безопасный путь
        if (findPath()) {
            break;
        }
    }
}

// Функция для добавления сокровищ на путь от начала до конца
void addTreasures() {
    // Создаем список всех проходимых клеток в лабиринте
    vector<pair<int, int>> roadCells;
    for (int i = 1; i < HEIGHT - 1; ++i) {
        for (int j = 1; j < WIDTH - 1; ++j) {
            if (maze[i][j].road) {
                roadCells.push_back({ i, j });
            }
        }
    }

    // Перемешиваем список клеток
    random_shuffle(roadCells.begin(), roadCells.end());

    // Генерируем случайное количество сокровищ от 0 до 1
    int numTreasures = rand() % 2;

    for (int i = 0; i < numTreasures && i < roadCells.size(); ++i) {
        int x = roadCells[i].first;
        int y = roadCells[i].second;

        // Помещаем сокровище в клетку, если там еще нет сокровища
        if (!maze[x][y].hasTreasure) {
            maze[x][y].hasTreasure = true;
            treasureCounter++;
        }
    }
}

int main() {
    // Инициализация генератора случайных чисел
    srand(time(0));

    // Генерация лабиринта
    generateMaze(1, 1);

    // Добавление ловушек
    addTraps();

    // Добавление сокровищ
    addTreasures();

    // Отображаем лабиринт в консоли
    displayMaze();

    // Выводим количество ловушек и сокровищ
    cout << "Number of traps: " << trapCounter << endl;
    cout << "Number of treasures: " << treasureCounter << endl;

    return 0;
}
