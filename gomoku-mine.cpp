#include <iostream>
#include <vector>
#include <limits>

enum class Status {ONGOING, WHITE_WIN, BLACK_WIN, DRAW};
enum class Stones {BLACK, WHITE, EMPTY};

std::vector<std::vector<Stones>> makeBoard(int r, int c){

    return std::vector<std::vector<Stones>>(r, std::vector<Stones>(c, Stones::EMPTY));

}

void displayBoard(const std::vector<std::vector<Stones>>& board){
    std::cout << "\n   ";
    int size = board.size();
    

    for(int col = 1; col < size + 1; ++col){
        std::cout << (col < 10 ? " " : "") << col << " ";
    }
    std::cout << '\n';

    for(int row = 0; row < size; ++row) {

        for(int r = 1; r < size + 1; ++r){
            if (r == 1) {
                std::cout << ((row+1) < 10 ? " " : "") << (row+1) << " ";
            }
        }

        for(const auto& cell : board.at(row)) {

            if (cell == Stones::EMPTY){

                std::cout << " . ";

            }else if (cell == Stones::BLACK){

                std::cout << " B ";

            }else if (cell == Stones::WHITE){

                std::cout << " W ";

            }
        }

        std::cout << '\n';
    }

}

int getCount(const std::vector<std::vector<Stones>>& board){
    int count = 0;
    for(const auto& row : board){
        for(const auto& cell : row){
            if(cell != Stones::EMPTY) ++count;
        }
    }
    return count;
}

Stones getPlayerStone(const std::vector<std::vector<Stones>>& board){
    return (getCount(board) % 2 == 0) ? Stones::BLACK : Stones::WHITE;
}

Status gameStatus(const std::vector<std::vector<Stones>>& board){
    int rows = static_cast<int>(board.size());
    int col = static_cast<int>(board[0].size());

    // check rows
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c <= col - 5; ++c) {
            if (board[r][c] != Stones::EMPTY &&
                board[r][c] == board[r][c + 1] &&
                board[r][c] == board[r][c + 2] &&
                board[r][c] == board[r][c + 3] &&
                board[r][c] == board[r][c + 4]) {

                    return (board[r][c] == Stones::BLACK) ? Status::BLACK_WIN : Status::WHITE_WIN;
                // if (r[c] == Stones::BLACK) {
                //     std::cout << "Black wins!\n";
                // } else {
                //     std::cout << "White wins!\n";
                // }
                // return;
            }
        }
    }

    if (getCount(board) == rows * col) return Status::DRAW;
    return Status::ONGOING;
}

void play(std::vector<std::vector<Stones>>& board, int row, int col){

    if (board.at(row).at(col) == Stones::EMPTY) {
        board.at(row).at(col) = getPlayerStone(board);
        return;
    }
}

bool validateRow(int& row, int size){

    if(std::cin.fail()){
        std::cout << "Invalid input. Please enter numeric values only.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;

    }else if(row < 1){

       std::cout << "Row must be between 1 and " << size << ". Please try again.\n";
       return false;

    }else if (row > size){

        std::cout << "Row must be between 1 and " << size << ". Please try again.\n";
        return false;

    }else{
        return true;
    }
}

bool validateCol(int& col, int size){
    if(col < 1){

       std::cout << "Column must be between 1 and " << size << ". Please try again.\n";
       return false;

    }else if (col > size){

        std::cout << "Column must be between 1 and " << size << ". Please try again.\n";
        return false;

    }else if(std::cin.fail()){
        std::cout << "Invalid input. Please enter numeric values only.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;

    }else{
        return true;
    }
}



int main(){

    std::cout << "------Welcome to Gomoku!------\n";

    std::cout << "========Here are the rules========\n\n";
    std::cout << "1. The game is played on a 13x13 grid.\n";
    std::cout << "2. Players take turns placing their stones (Black goes first).\n";
    std::cout << "3. To place a stone, enter the row and column numbers.\n";
    std::cout << "4. Here's the catch: You can only win by forming a straight line horizontally. You have fewer paths of victory you can take, so choose wisely.\n";
    std::cout << "\n========Let's Begin!========\n";

    auto board = makeBoard(13, 13);

    while(true){
        std::cout << "\n========Let's Begin!========\n";
        auto board = makeBoard(13, 13);

        while(gameStatus(board) == Status::ONGOING){
        displayBoard(board);
        std::cout << ((getPlayerStone(board) == Stones::BLACK) ? "Black's turn.\n" : "White's turn.\n");
        std::cout << "------Enter your move (row and column)------\n ";
        int row;
        int col;

        std::cout << "Row: ";
        std::cin >> row;
        if(!validateRow(row, 13)){

            continue;
        }

        std::cout << "Column: ";
        std::cin >> col;
        if(!validateCol(col, 13)){

            continue;
        }

        play(board, row - 1, col - 1);
    }

        displayBoard(board);
        
        if (gameStatus(board) == Status::BLACK_WIN) {
            std::cout << "Black wins!\n";

        }else if (gameStatus(board) == Status::WHITE_WIN) {

            std::cout << "White wins!\n";

        } else if (gameStatus(board) == Status::DRAW) {

            std::cout << "It's a draw!\n";

        }
        
        std::cout << "Game over.";
        std::cout << "Do you want to play again? [1] Yes [2] No: ";

        int choice;
        std::cin >> choice;

    

        if (choice != 1) {
            std::cout << "Thank you for playing Gomoku! Goodbye!\n";
            return false;
        }
}

    // while(gameStatus(board) == Status::ONGOING){
    //     displayBoard(board);
    //     std::cout << ((getPlayerStone(board) == Stones::BLACK) ? "Black's turn.\n" : "White's turn.\n");
    //     std::cout << "------Enter your move (row and column)------\n ";
    //     int row;
    //     int col;

    //     std::cout << "Row: ";
    //     std::cin >> row;
    //     if(!validateRow(row, 13)){

    //         continue;
    //     }

    //     std::cout << "Column: ";
    //     std::cin >> col;
    //     if(!validateCol(col, 13)){

    //         continue;
    //     }

    //     play(board, row - 1, col - 1);
    // }

    // displayBoard(board);

    
    // if (gameStatus(board) == Status::BLACK_WIN) {

    //     std::cout << "Black wins!\n";

    // } else if (gameStatus(board) == Status::WHITE_WIN) {

    //     std::cout << "White wins!\n";

    // } else if (gameStatus(board) == Status::DRAW) {

    //     std::cout << "It's a draw!\n";

    // }
    
    // std::cout << "Game over.";
    // std::cout << "Do you want to play again? [1] Yes [2] No: ";

    // int choice;
    // std::cin >> choice;

    // if (choice != 1) {
    //     std::cout << "Thank you for playing Gomoku! Goodbye!\n";
    //     return false;
    // }
    return 0;

}