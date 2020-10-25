#include <iostream>
#include "../libs/list_queue.h"
#include "../libs/list_stack.h"
using namespace std;

void addToStack(int matrix[][5], int rows, Stack<pair<int, int> >& dfsStack, int x, int y, int val) {
    if(x < 0 || x > 4 || y < 0 || y > rows-1 || matrix[x][y] != 0) {
        return;
    }
    matrix[x][y] = val+1;
    dfsStack.push_back(make_pair<int, int>(x, y));
}

bool bfs(int matrix[][5], int rows, int startX, int startY, int endX, int endY) {
    Stack<pair<int, int> > dfsStack;
    matrix[startX][startY] = 2;
    dfsStack.push_back(make_pair(startX, startY));
    int x, y;
    while(!dfsStack.empty()) {
        x = dfsStack.getTop().first;
        y = dfsStack.getTop().second;
        dfsStack.pop_back();

        if(x == endX && y == endY) {
            return true;
        }

        if(matrix[x][y] < 2) {
            continue;
        }

        addToStack(matrix, rows, dfsStack, x-1, y, matrix[x][y]);
        addToStack(matrix, rows, dfsStack, x, y-1, matrix[x][y]);
        addToStack(matrix, rows, dfsStack, x+1, y, matrix[x][y]);
        addToStack(matrix, rows, dfsStack, x, y+1, matrix[x][y]);
    }

    return false;
}

int main () {
    int matrix[][5] = {
        {0, 0, 0, 0, 1},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {0, 1, 0, 1, 0}
    };

    cout<< bfs(matrix, 5, 0,0,4,4)<< endl;
    for(int i = 0; i< 5; ++i) {
        for(int j = 0; j< 5; ++j) {
            cout<< matrix[i][j]<< " ";
        }
        cout<< endl;
    }


    return 0;
}
