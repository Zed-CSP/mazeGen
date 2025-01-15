#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>

const int ROWS = 100;
const int COLS = 100;

struct Cell {
    int x, y;
    bool visited;
    bool top_wall;
    bool bot_wall;
    bool left_wall;
    bool right_wall;

    Cell(int _x, int _y) : x(_x), y(_y), visited(false),
        top_wall(true), bot_wall(true), left_wall(true), right_wall(true) {}
};

void printMaze(const std::vector<std::vector<Cell>>& maze) {
    for (int i = 0; i < ROWS; ++i) {
        // Print the top walls
        for (int j = 0; j < COLS; ++j) {
            std::cout << (maze[i][j].top_wall ? "+---" : "+   ");
        }
        std::cout << "+" << std::endl;
        // Print the side walls
        for (int j = 0; j < COLS; ++j) {
            std::cout << (maze[i][j].left_wall ? "|   " : "    ");
        }
        std::cout << "|" << std::endl;
    }
    // Print the bottom wall of the maze
    for (int j = 0; j < COLS; ++j) {
        std::cout << "+---";
    }
    std::cout << "+" << std::endl;
}

void generateMaze(std::vector<std::vector<Cell>>& maze, int start_x, int start_y) {
    std::stack<Cell*> cell_stack;
    Cell* current = &maze[start_x][start_y];
    current->visited = true;
    cell_stack.push(current);

    while (!cell_stack.empty()) {
        current = cell_stack.top();
        cell_stack.pop();
        std::vector<Cell*> unvisited_neighbors;

        // Lambda to check cell validity
        auto add_valid_neighbor = [&](int x, int y) {
            if (x >= 0 && x < ROWS && y >= 0 && y < COLS && !maze[x][y].visited) {
                unvisited_neighbors.push_back(&maze[x][y]);
            }
        };

        // Check neighbors
        add_valid_neighbor(current->x - 1, current->y); // Up
        add_valid_neighbor(current->x + 1, current->y); // Down
        add_valid_neighbor(current->x, current->y - 1); // Left
        add_valid_neighbor(current->x, current->y + 1); // Right

        if (!unvisited_neighbors.empty()) {
            cell_stack.push(current);

            // Randomly select one unvisited neighbor
            int rand_index = rand() % unvisited_neighbors.size();
            Cell* next_cell = unvisited_neighbors[rand_index];

            // Remove the wall between the current cell and the chosen cell
            if (next_cell->x == current->x - 1) { // Neighbor is above
                current->top_wall = false;
                next_cell->bot_wall = false;
            } else if (next_cell->x == current->x + 1) { // Neighbor is below
                current->bot_wall = false;
                next_cell->top_wall = false;
            } else if (next_cell->y == current->y - 1) { // Neighbor is left
                current->left_wall = false;
                next_cell->right_wall = false;
            } else if (next_cell->y == current->y + 1) { // Neighbor is right
                current->right_wall = false;
                next_cell->left_wall = false;
            }

            next_cell->visited = true;
            cell_stack.push(next_cell);
        }
    }
}

int main() {
    srand(time(NULL));
    std::vector<std::vector<Cell>> maze(ROWS, std::vector<Cell>(COLS, Cell(0, 0)));

    // Initialize maze cells
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            maze[i][j] = Cell(i, j);
        }
    }

    generateMaze(maze, 0, 0);
    printMaze(maze);

    return 0;
}
