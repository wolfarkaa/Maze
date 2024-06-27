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