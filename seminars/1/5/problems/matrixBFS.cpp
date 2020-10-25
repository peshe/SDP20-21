#include <iostream>
#include "../libs/list_queue.h"
#include "../libs/list_stack.h"
using namespace std;

void addToQueue(int matrix[][5], int rows, Queue<pair<int, int> >& bfsQueue, int x, int y, int val) {
    if(x < 0 || x > 4 || y < 0 || y > rows-1 || matrix[x][y] != 0) {
        return;
    }
    matrix[x][y] = val+1;
    bfsQueue.enqueue(make_pair<int, int>(x, y));
}

bool bfs(int matrix[][5], int rows, int startX, int startY, int endX, int endY) {
    Queue<pair<int, int> > bfsQueue;
    matrix[startX][startY] = 2;
    bfsQueue.enqueue(make_pair(startX, startY));
    int x, y;
    while(!bfsQueue.empty()) {
        x = bfsQueue.getFront().first;
        y = bfsQueue.getFront().second;
        bfsQueue.dequeue();

        if(x == endX && y == endY) {
            return true;
        }

        addToQueue(matrix, rows, bfsQueue, x-1, y, matrix[x][y]);
        addToQueue(matrix, rows, bfsQueue, x+1, y, matrix[x][y]);
        addToQueue(matrix, rows, bfsQueue, x, y-1, matrix[x][y]);
        addToQueue(matrix, rows, bfsQueue, x, y+1, matrix[x][y]);
    }

    return false;
}

int main () {
    int matrix[][5] = {
        {0, 1, 0, 0, 1},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {0, 1, 0, 1, 0}
    };

    cout<< bfs(matrix, 5, 0,0,2,2)<< endl;
    for(int i = 0; i< 5; ++i) {
        for(int j = 0; j< 5; ++j) {
            cout<< matrix[i][j]<< " ";
        }
        cout<< endl;
    }


    return 0;
}
