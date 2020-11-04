#include <iostream>
#include <queue>
#include <vector>

const int SIZE = 5;

struct pair_int {
    int left;
    int right;
    pair_int(int left, int right): left(left), right(right){}
};

// А cell is valid if it is on the map, has a value '#', and has not been visited yet
bool isValid(char map[SIZE][SIZE],
              bool visited[SIZE][SIZE],
              int i, int j) {
    return (i >= 0) && (i < SIZE) &&  
           (j >= 0) && (j < SIZE) &&  
           (map[i][j] == '#' && !visited[i][j]); 
}

void bfs(char map[SIZE][SIZE],
         bool visited[SIZE][SIZE],
         int k, int l) {

    int d_row[] = { -1, 0, 0, 1 }; 
    int d_col[] = { 0, -1, 1, 0 }; 

    std::queue<pair_int> q;
    q.push(pair_int(k, l));
    visited[k][l] = 1;

    while(!q.empty()) {    
        int left = q.front().left;
        int right = q.front().right;
        q.pop();

        for(size_t i = 0; i < 4; i++) {
            if(isValid(map, visited,
                            left + d_row[i],
                            right + d_col[i])) {
                visited[left + d_row[i]][right + d_col[i]] = true;
                q.push(pair_int(left + d_row[i], right + d_col[i]));
            }
        }
    }
}

int main()
{


    char map[5][5] = 
    {
        {'#', '.', '#', '#', '.'}, 
        {'#', '#', '#', '#', '.'},
        {'#', '.', '.', '.', '.'},
        {'#', '.', '#', '.', '#'},
        {'#', '.', '#', '.', '#'}
    };

    bool visited[5][5] = {{0}};

    int count = 0;

    for(size_t i = 0; i < 5; i++) {
        for(size_t j = 0; j < 5; j++) {
            if (map[i][j] == '#' && !visited[i][j]) { 
                bfs(map, visited, i, j); 
                count++; 
            } 
        }
    }

    std::cout << count << std::endl;


    return 0;
}