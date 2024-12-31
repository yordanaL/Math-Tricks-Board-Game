#include <iostream>
using namespace std;

const size_t MIN_BOARD_LENGTH = 4, MIN_BOARD_WIDTH = 4;

int main() {
    size_t boardLength = MIN_BOARD_LENGTH, boardWidth = MIN_BOARD_WIDTH;
    cout << "To start the game enter the board size.";
    cout << "Enter the board length: ";
    cin >> boardLength;
    cout << "Enter the board width: ";
    cin >> boardWidth;
}