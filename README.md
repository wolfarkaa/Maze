# Maze Generator Program for Distributed Lab
## Description
### Overview
This program generates a maze with specific features such as an entrance, exit, traps, and treasures. It ensures there is at least one valid path from the entrance to the exit while limiting the number of traps encountered along the way.

### Key Components
#### Maze Representation:
The maze is represented as a 2D grid using a custom Cell struct. Each cell can be a wall, road, contain traps, or treasures.
Dimensions: WIDTH x HEIGHT (both odd numbers for symmetry and convenience).
#### Maze Generation (Euler's Algorithm):
Algorithm: Uses Euler's algorithm for maze generation, starting from an entrance and creating pathways randomly using depth-first search (DFS) principles.
Implementation: The maze is initialized with walls (#) and roads ( ). Starting from the entrance (E), roads are carved out using randomized DFS to connect all cells.
#### Pathfinding with Trap Limitation:
Functionality: After maze generation, the program ensures there exists a path from the entrance to the exit (X) with a limited number of traps encountered (up to 2 traps).
Approach: Utilizes BFS (breadth-first search) to find all possible paths while tracking the number of traps encountered. This ensures player safety by validating path feasibility.
#### Trap and Treasure Placement:
Trap Placement: Randomly places traps (T) throughout the maze, ensuring there are enough road cells to accommodate them without blocking the exit path.
Treasure Placement: Adds treasures ($) on available road cells, enhancing gameplay with optional collectibles.
#### Output:
Display: Prints the maze to the console with graphical symbols for walls, roads, entrance, exit, traps, and treasures.
Statistics: Outputs the total number of traps and treasures generated in the maze.

### How to run code

1) In the maze folder there is a file maze.sln, if you have the Visual Studio program, you can open this file in it.
2) In the maze/maze folder there is a file maze.cpp, which you can compile yourself, for example using the g++ compiler, since the program is written in C++.

### Solution in big O notation

#### Analyzing the findPath function

The trapCount vector is initialized with dimensions HEIGHT x WIDTH, which takes 𝑂(HEIGHT x WIDTH).
A queue is initialized, and a starting state is pushed onto the queue, which takes 𝑂(1).

The while loop continues until the queue is empty. In the worst case, every cell in the maze might be visited once, leading to a maximum of HEIGHT×WIDTH iterations.
Each iteration involves popping the front of the queue, which is O(1).

For each cell, we check its 4 possible neighbors. This checking involves:
Calculating new coordinates nx and ny, which is O(1).
Checking if the new cell is a road and if moving to it would result in fewer traps than previously recorded. This is O(1).
Pushing a new state to the queue if the conditions are met, which is O(1).

Given these operations, let's summarize the time complexity:
Initializing trapCount takes O(HEIGHT×WIDTH).
The main loop runs up to O(HEIGHT×WIDTH) times.
Each iteration of the loop checks 4 neighbors, so the total complexity for all iterations is O(4×HEIGHT×WIDTH), which simplifies to O(HEIGHT×WIDTH).
Combining these, the overall time complexity of the findPath function is O(HEIGHT×WIDTH)

#### Analyzing the addTraps and addTreasures functions

Clearing Traps:
Iterates through (HEIGHT−2)×(WIDTH−2) cells, resulting in O(HEIGHT×WIDTH).
Creating List of Road Cells:
Iterates through the same number of cells to check if each cell is a road and add it to the list, also O(HEIGHT×WIDTH).
Shuffling and Placing Traps:
Shuffling the list of road cells takes O(N), where N is the number of road cells, which in the worst case can be O(HEIGHT×WIDTH).
Placing traps in up to 5 cells takes O(1) since the number of traps is limited to a constant (5).
Path Check:
The findPath function runs with a complexity of O(HEIGHT×WIDTH).

Given the operations inside the loop, the time complexity of each iteration of the loop is O(HEIGHT×WIDTH)

#### Therefore, the complexity of this solution is O(HEIGHT×WIDTH)



