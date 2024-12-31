#include <iostream>
using namespace std;

const size_t MIN_BOARD_LENGTH = 4, MIN_BOARD_WIDTH = 4;

bool isInputBoardSizeValid(size_t boardLength, size_t boardWidth);

int main() {
    //read the board size from console
    size_t boardLength = MIN_BOARD_LENGTH, boardWidth = MIN_BOARD_WIDTH;
    cout << "To start the game enter the board size." << endl;
    cout << "Enter the board length: ";
    cin >> boardLength;
    cout << "Enter the board width: ";
    cin >> boardWidth;

    return 0;
}

bool isInputBoardSizeValid(size_t boardLength, size_t boardWidth) {
    bool isInputBoardLengthValid = boardLength >= MIN_BOARD_LENGTH;
    bool isInputBoardWidthValid = boardWidth >= MIN_BOARD_WIDTH;

    return (isInputBoardLengthValid && isInputBoardWidthValid);
}