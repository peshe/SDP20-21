#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>

template<typename T>
using grid_2D = std::vector<T>;

struct cell {
    size_t id;
    char parent;
        
    cell(size_t id, char parent): id(id), parent(parent){}
};

bool isValid(const grid_2D<char>& grid,
             const grid_2D<bool>& visited,
             int pos) {
    return (pos >= 0 && pos < grid.size()) &&
           (grid[pos] == '.' && !visited[pos]);
}

size_t eval_new_id(char direction, size_t curr_pos, size_t row_size) {
    if (direction == 'D') {
        return curr_pos - row_size;
    }
    else if (direction == 'R') {
        return curr_pos - 1;
    }
    else if (direction == 'L') {
        return curr_pos + 1;
    }
    else {
        return curr_pos + row_size;
    }
}

size_t count_print_parents(const grid_2D<cell>& parents, size_t row_size) {

    std::stack<char> directions;
    int i = parents.size() - 1;
    size_t j = eval_new_id(parents[i].parent, parents[i].id, row_size);
    int last_cell = i;
    while (i >= 0) {
        if (parents[i].id == j) {
            directions.push(parents[last_cell].parent);
            j = eval_new_id(parents[i].parent, parents[i].id, row_size);
            last_cell = i;
        }
        i--;
    }



    size_t counter = directions.size();

    while (!directions.empty()) {
        std::cout << directions.top() << ' ';
        directions.pop();
    }
    std::cout << std::endl;
    return counter;
}

int bfs(const grid_2D<char>& grid,
        int src_x, int src_y,
        int dest_x, int dest_y) {

    int d_row[] = { -1, 0, 0, 1 };
    int d_col[] = { 0, -1, 1, 0 };
    const short DIRECTIONS_SIZE = 4;


    std::queue<cell> q;

    size_t size = grid.size();
    grid_2D<bool> visited(size, 0);

    
    size_t row_size = sqrt(size);
    size_t destination_id = dest_x * row_size + dest_y;

    cell start(src_x * size + src_y, '\0');
    visited[src_x * size + src_y] = true;

    grid_2D<cell> parents;
    parents.push_back(start);

    q.push(start);

    while (!q.empty()) {
        cell front = q.front();
        q.pop();

        if (front.id == destination_id) {
            return count_print_parents(parents, row_size);
        }

        for (size_t i = 0; i < DIRECTIONS_SIZE; i++) {
            size_t new_pos = front.id + d_row[i] * row_size + d_col[i];
            if (isValid(grid, visited, new_pos)) {
                visited[new_pos] = true;
                switch (i) {
                case 0:
                {
                    cell current(new_pos, 'U');
                    q.push(current);
                    parents.push_back(current);
                    break;
                }
                case 1:
                {
                    cell current(new_pos, 'L');
                    q.push(current);
                    parents.push_back(current);
                    break;
                }
                case 2:
                {
                    cell current(new_pos, 'R');
                    q.push(current);
                    parents.push_back(current);
                    break;
                }
                case 3:
                {
                    cell current(new_pos, 'D');
                    q.push(current);
                    parents.push_back(current);
                    break;
                }
                }
            }
        }
    }

    return -1;
}

int main() {

    size_t n, src_x, src_y, dest_x, dest_y;
    std::cin >> n >> src_x >> src_y >> dest_x >> dest_y;

    size_t grid_size = n * n;
    grid_2D<char> grid(grid_size);
    for (size_t i = 0; i < grid_size; i++) {
        std::cin >> grid[i];
    }

    std::cout << bfs(grid, src_x, src_y, dest_x, dest_y) << std::endl;

    return 0;
}