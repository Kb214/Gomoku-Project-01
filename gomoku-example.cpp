
#include <iostream>
#include <vector>
#include <limits>


const int BOARD_SIZE = 13;
const char EMPTY = '.';
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';

void printBoard(const std::vector<std::vector<char>>& board) {
    std::cout << "   ";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << (i < 10 ? " " : "") << i << " ";
    }

    std::cout << std::endl;
    
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << (i < 10 ? " " : "") << i << " ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << " " << board.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
}

bool isWin(const std::vector<std::vector<char>>& board, int row, int col, char player) {
    const int directions[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} };
    for (auto& dir : directions) {
        int count = 1;
        for (int d = -1; d <= 1; d += 2) {
            int r = row + dir[0] * d, c = col + dir[1] * d;
            while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board.at(r).at(c) == player) {
                ++count;
                r += dir[0] * d;
                c += dir[1] * d;
            }
        }
        if (count >= 5) return true;
    }
    return false;
}

bool isDraw(const std::vector<std::vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == EMPTY) return false;
        }
    }
    return true;
}

void playGomoku() {
    std::vector<std::vector<char>> board(BOARD_SIZE, std::vector<char>(BOARD_SIZE, EMPTY));
    char currentPlayer = PLAYER1;
    int moveCount = 0;
    while (true) {
        printBoard(board);
        std::cout << "Player " << (currentPlayer == PLAYER1 ? "1 (X)" : "2 (O)") << "'s turn. Enter row and column: ";
        int row, col;
        while (true) {
            std::cin >> row >> col;
            if (std::cin.fail() || row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board.at(row).at(col) != EMPTY) {
                std::cout << "Invalid move. Try again: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                break;
            }
        }
        board.at(row).at(col) = currentPlayer;
        ++moveCount;
        if (isWin(board, row, col, currentPlayer)) {
            printBoard(board);
            std::cout << "Player " << (currentPlayer == PLAYER1 ? "1 (X)" : "2 (O)") << " wins!\n";
            break;
        }
        if (isDraw(board)) {
            printBoard(board);
            std::cout << "It's a draw!\n";
            break;
        }
        currentPlayer = (currentPlayer == PLAYER1 ? PLAYER2 : PLAYER1);
    }
}


int main(){

    playGomoku();
    return 0;
}