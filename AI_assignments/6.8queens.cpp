#include <iostream>
#include <vector>
using namespace std;

#define N 8

void printBoard(vector<vector<int>>& board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << (board[i][j] ? "Q " : ". ");
        cout << "\n";
    }
    cout << "\n";
}

bool isSafe(vector<vector<int>>& board, int row, int col) {
    for (int i = 0; i < col; i++)
        if (board[row][i]) return false;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;

    for (int i = row, j = col; i < N && j >= 0; i++, j--)
        if (board[i][j]) return false;

    return true;
}

bool solveNQUtil(vector<vector<int>>& board, int col) {
    if (col >= N) return true;

    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1;

            if (solveNQUtil(board, col + 1))
                return true;

            board[i][col] = 0;
        }
    }
    return false;
}

int main() {
    vector<vector<int>> board(N, vector<int>(N, 0));

    if (solveNQUtil(board, 0) == false) {
        cout << "Solution does not exist\n";
        return 0;
    }

    cout << "One of the solutions to 8-Queens Problem:\n\n";
    printBoard(board);
    return 0;
}


//o/p
// PS E:\AI_LAB> g++ "6.8queens.cpp" -o queens
// >> 
// PS E:\AI_LAB> ./queens
// >> 
// One of the solutions to 8-Queens Problem:

// Q . . . . . . . 
// . . . . . . Q . 
// . . . . Q . . . 
// . . . . . . . Q 
// . Q . . . . . . 
// . . . Q . . . . 
// . . . . . Q . . 
// . . Q . . . . . 
