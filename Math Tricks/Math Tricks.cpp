#include <iostream>
using namespace std;

const size_t MIN_BOARD_LENGTH = 4, MIN_BOARD_WIDTH = 4;

bool isInputBoardSizeValid(size_t boardLength, size_t boardWidth);
void clearConsole();

int main() {
    //read the board size from console
    size_t boardLength = MIN_BOARD_LENGTH, boardWidth = MIN_BOARD_WIDTH;
    cout << "To start the game enter the board size." << endl;
    cout << "Enter the board length (>= 4): ";
    cin >> boardLength;
    cout << "Enter the board width (>= 4): ";
    cin >> boardWidth;
    cout << endl;

    clearConsole();

    return 0;
}

//function to check whether the board length and width are minimum 4
bool isInputBoardSizeValid(size_t boardLength, size_t boardWidth) {
    bool isInputBoardLengthValid = boardLength >= MIN_BOARD_LENGTH;
    bool isInputBoardWidthValid = boardWidth >= MIN_BOARD_WIDTH;

    return (isInputBoardLengthValid && isInputBoardWidthValid);
}

//function to clear the console for clearer interface
void clearConsole() {
    system("cls");
}