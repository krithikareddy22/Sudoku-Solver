#include <iostream>
#include <string>
using namespace std;

const int N = 9;

bool isValid(int grid[N][N], int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (grid[startRow + r][startCol + c] == num)
                return false;

    return true;
}

bool solveSudoku(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isValid(grid, row, col, num)) {
                        grid[row][col] = num;
                        if (solveSudoku(grid))
                            return true;
                        grid[row][col] = 0; // backtrack
                    }
                }
                return false; // no valid number found
            }
        }
    }
    return true; // puzzle solved
}

void printGrid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    int grid[N][N] = {0};
    string input;

    cout << "Enter the Sudoku puzzle (81 digits, use 0 for blanks):\n";

    while (input.length() < 81) {
        string line;
        getline(cin, line);
        for (char ch : line)
            if (isdigit(ch)) input += ch;

        if (input.length() < 81)
            cout << "Need " << 81 - input.length() << " more digits.\n";
    }

    for (int i = 0; i < 81; i++)
        grid[i / 9][i % 9] = input[i] - '0';

    if (solveSudoku(grid)) {
        cout << "\nSolved Sudoku:\n";
        printGrid(grid);
    } else {
        cout << "\nNo solution exists.\n";
    }

    return 0;
}
