#include <iostream>
#include "../libs/list_queue.h"
#include "../libs/list_stack.h"
using namespace std;

void addToQueue(int matrix[8][8], Queue<pair<int, int> >& bfsQueue, int x, int y, int val) {
    if(x < 0 || x > 7 || y < 0 || y > 7 || matrix[x][y] != 0) {
        return;
    }
    matrix[x][y] = val+1;
    bfsQueue.enqueue(make_pair<int, int>(x, y));
}

bool bfs(int matrix[8][8], int startX, int startY, int endX, int endY) {
    Queue<pair<int, int> > bfsQueue;
    matrix[startX][startY] = 1;
    bfsQueue.enqueue(make_pair(startX, startY));
    int x, y;
    while(!bfsQueue.empty()) {
        x = bfsQueue.getFront().first;
        y = bfsQueue.getFront().second;
        bfsQueue.dequeue();

        if(x == endX && y == endY) {
            return true;
        }

        addToQueue(matrix, bfsQueue, x-1, y-2, matrix[x][y]);
        addToQueue(matrix, bfsQueue, x-2, y-1, matrix[x][y]);

        addToQueue(matrix, bfsQueue, x-1, y+2, matrix[x][y]);
        addToQueue(matrix, bfsQueue, x+2, y-1, matrix[x][y]);

        addToQueue(matrix, bfsQueue, x+1, y-2, matrix[x][y]);
        addToQueue(matrix, bfsQueue, x-2, y+1, matrix[x][y]);

        addToQueue(matrix, bfsQueue, x+1, y+2, matrix[x][y]);
        addToQueue(matrix, bfsQueue, x+2, y+1, matrix[x][y]);
    }

    return false;
}

int main() {
    int chessboard[8][8] = {{0}};

    bfs(chessboard, 7, 0, 5, 4);

    for(int i = 0; i< 8; ++i) {
        for(int j = 0; j< 8; ++j) {
            cout<< chessboard[i][j]<< " ";
        }
        cout<< endl;
    }
    cout<< chessboard[5][4]<< endl;


    return 0;
}
