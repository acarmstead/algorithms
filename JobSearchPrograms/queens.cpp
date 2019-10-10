//
//  The N-Queens problem asks us to find the number of
//  ways to place N queens on an N x N chess board such
//  that none of the queens are actively attacking
//  any other queen.
//  Solution uses recursion and backtracking.
//

#include <iostream>

// Returns in |count| the number of solutions to the N-Queens
// problem using an N x N board. Called using search(0, <count variable>)
//
// row: row we are trying to place a queen onto
// count: running count of unique solutions
// n: size of board (number of rows/columns)
// cols[]: whether a queen is present in a given column
// diag1[]: diagonals from left to right, top to bottom
// diag2[]: diagonals from left to right, bottom to top
void search(int row, int& count, int n, bool* cols, bool* diag1, bool* diag2) {
    if (row == n) {  // solution found
        ++count;
        return;
    }
    for (int col = 0; col < n; ++col) { // find a column in |row| for next queen
        if (cols[col] || diag1[col + row] || diag2[col - row + n - 1]) {
            continue;
        }
        cols[col] = diag1[col + row] = diag2[col - row + n - 1] = true;
        search(row + 1, count, n, cols, diag1, diag2);
        cols[col] = diag1[col + row] = diag2[col - row + n - 1] = false;
    }
}

int main(int argc, const char * argv[]) {
    // Gather size of board using stdin
    int n;
    std::cout << "Enter size of board: ";
    std::cin >> n;
    bool cols[n], diag1[2*(n-1)], diag2[2*(n-1)];
    
    int count = 0;
    
    // Initialize
    for (int i = 0; i < n; ++i) {
        cols[i] = diag1[i] = diag2[i] = false;
    }
    for (int i = n; i < 2 * (n-1); ++i) {
        diag1[i] = diag2[i] = false;
    }
    
    // Call backtracking algorithm
    search(0, count, n, cols, diag1, diag2);
    
    std::cout << "Solutions found: " << count << std::endl;
    return 0;
}
