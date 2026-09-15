#include <iostream>
#include <vector>

void printBoard (const std::vector<std::vector<bool>>& v) {
    int n = v.size();
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if(v.at(r).at(c)) std::cout << "Q ";
            else std::cout << ". ";
        }
        std::cout << std::endl;
    }
}

bool checkSafety (const std::vector<std::vector<bool>>& V, int row, int col) {
    for (int i = 0; i < row; i++) {
        if (V.at(i).at(col)) return false;
    }
    int r = row;
    int c = col;
    while (r >= 0 && c < V.size()) {
        if (V.at(r).at(c) == true) return false;
        r--;
        c++;
    }
    r = row;
    c = col;
    while (r >= 0 && c >= 0) {
        if (V.at(r).at(c) == true) return false;
        r--;
        c--;
    }
    return true;
}

bool placeQueens (int N, std::vector < std::vector <bool> >& board, int row) {
    int column = 0;
    if (row == N) return true;
    while (column < N) {
        if (checkSafety(board, row, column)) {
            board.at(row).at(column) = true;
            if (placeQueens(N, board, row + 1)) return true;
            board.at(row).at(column) = false;
        }
        column++;
    }
    return false;    
}

int main () {
    int N = 0;
    while (N <= 0) {
        std::cout << "How many queens to place on the board? ";
        std::cin >> N;
    }
    std::vector<std::vector<bool>> board (N, std::vector<bool> (N, false));
    if(placeQueens(N, board, 0)) printBoard(board);
    else std::cout << "No solution found to place " << N << " queens on a " << N << " by " << N << " chess board" << std::endl;
    return 0;
}