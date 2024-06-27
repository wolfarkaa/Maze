#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <queue>

using namespace std;

// Maze dimensions (should be odd numbers for convenience)
const int WIDTH = 15;
const int HEIGHT = 15;

// Symbols for displaying the maze
const char WALL = '#';
const char ROAD = ' ';
const char ENTRANCE = 'E';
const char EXIT = 'X';
const char TRAP = 'T';
const char TREASURE = '$';

// Structure of a maze cell
struct Cell {
    bool visited;
    bool road;
    bool hasTrap;
    bool hasTreasure;

    Cell() : visited(false), road(false), hasTrap(false), hasTreasure(false) {}
};

// 2D array for the maze
vector<vector<Cell>> maze(HEIGHT, vector<Cell>(WIDTH));

// Counters for traps and treasures
int trapCounter = 0;
int treasureCounter = 0;

// Function to display the maze on the console
void displayMaze() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                // Maze boundaries
                cout << WALL;
            }
            else if (i == 1 && j == 1) {
                // Entrance point
                cout << ENTRANCE;
            }
            else if (i == HEIGHT - 2 && j == WIDTH - 2) {
                // Exit point
                cout << EXIT;
            }
            else if (maze[i][j].hasTrap) {
                // Trap
                cout << TRAP;
            }
            else if (maze[i][j].hasTreasure) {
                // Treasure
                cout << TREASURE;
            }
            else {
                // Inner maze cells
                cout << (maze[i][j].road ? ROAD : WALL);
            }
        }
        cout << endl;
    }
}

// Function to check if a cell is valid
bool isValid(int x, int y) {
    return (x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH && !maze[x][y].visited);
}

// Euler's algorithm for maze generation
void generateMaze(int x, int y) {
    maze[x][y].visited = true;
    maze[x][y].road = true;

    // List of neighbors in random order
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

// Structure to store cell state and trap count on the path
struct PathState {
    int x, y, traps;
};

// Function to find all paths from entrance to exit with trap counting
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

// Function to add traps on the path from entrance to exit
void addTraps() {
    while (true) {
        // Clear traps
        for (int i = 1; i < HEIGHT - 1; ++i) {
            for (int j = 1; j < WIDTH - 1; ++j) {
                maze[i][j].hasTrap = false;
            }
        }
        trapCounter = 0;

        // Create a list of all road cells in the maze
        vector<pair<int, int>> roadCells;
        for (int i = 1; i < HEIGHT - 1; ++i) {
            for (int j = 1; j < WIDTH - 1; ++j) {
                if (maze[i][j].road) {
                    roadCells.push_back({ i, j });
                }
            }
        }

        // Shuffle the list of cells
        random_shuffle(roadCells.begin(), roadCells.end());

        // Generate a random number of traps from 0 to 5
        int numTraps = rand() % 6;
        numTraps = min(numTraps, static_cast<int>(roadCells.size())); // Limit traps to the number of available cells

        for (int i = 0; i < numTraps; ++i) {
            int x = roadCells[i].first;
            int y = roadCells[i].second;

            // Place a trap in the cell if it doesn't already have one
            if (!maze[x][y].hasTrap) {
                maze[x][y].hasTrap = true;
                trapCounter++;
            }
        }

        // Check if there is at least one safe path
        if (findPath()) {
            break;
        }
    }
}

// Function to add treasures on the path from entrance to exit
void addTreasures() {
    // Create a list of all road cells in the maze
    vector<pair<int, int>> roadCells;
    for (int i = 1; i < HEIGHT - 1; ++i) {
        for (int j = 1; j < WIDTH - 1; ++j) {
            if (maze[i][j].road) {
                roadCells.push_back({ i, j });
            }
        }
    }

    // Shuffle the list of cells
    random_shuffle(roadCells.begin(), roadCells.end());

    // Generate a random number of treasures from 0 to 1
    int numTreasures = rand() % 2;

    for (int i = 0; i < numTreasures && i < roadCells.size(); ++i) {
        int x = roadCells[i].first;
        int y = roadCells[i].second;

        // Place a treasure in the cell if it doesn't already have one
        if (!maze[x][y].hasTreasure) {
            maze[x][y].hasTreasure = true;
            treasureCounter++;
        }
    }
}

int main() {
    // Initialize the random number generator
    srand(time(0));

    // Generate the maze
    generateMaze(1, 1);

    // Add traps
    addTraps();

    // Add treasures
    addTreasures();

    // Display the maze on the console
    displayMaze();

    // Output the number of traps and treasures
    cout << "Number of traps: " << trapCounter << endl;
    cout << "Number of treasures: " << treasureCounter << endl;

    return 0;
}
