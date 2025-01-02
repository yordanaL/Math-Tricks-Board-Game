#include <iostream>
using namespace std;

const size_t MIN_BOARD_LENGTH = 4, MIN_BOARD_WIDTH = 4;
const int NUMBER_OF_MATH_OPERATIONS = 5;

bool isInputBoardSizeValid(size_t boardLength, size_t boardWidth);
void clearConsole();
int calculateCoefficientOfDifficulty(size_t boardLength, size_t boardWidth);
int getRandomNumberInInterval(int maxValue);

void createGrid(char**& grid, size_t rows, size_t cols);
void createGrid(int**& grid, size_t rows, size_t cols);
void createGrid(bool**& grid, size_t rows, size_t cols);

void deleteGrid(char**& grid, size_t rows);
void deleteGrid(int**& grid, size_t rows);
void deleteGrid(bool**& grid, size_t rows);

void printGrid(const char**& grid, size_t rows, size_t cols);
void printGrid(const int**& grid, size_t rows, size_t cols);
void printGrid(const bool**& grid, size_t rows, size_t cols);

void randomGenMathOperationsArray(char*& mathOperationsArr, size_t mathOperationsArrLength);
char codeToMathOperation(int mathOperationCode);
void randomGenNumArray(int*& numArr, size_t numArrLength, int difficultyCoefficient);

bool isHalfBoardFulfillingBoardRequirements(char*& mathOperationsArr, size_t mathOperationsArrLength,
    int*& numArr, size_t numArrLength);

void generateHalfBoardUpToTheRequirements(char*& mathOperationsArr, size_t mathOperationsArrLength,
    int*& numArr, size_t numArrLength, int difficultyCoefficient);

int main() {
    //A seed for the random number function
    srand((unsigned)time(0));

    //Read the board size from the console
    size_t boardLength = MIN_BOARD_LENGTH, boardWidth = MIN_BOARD_WIDTH;
    cout << "To start the game enter the board size." << endl;
    cout << "Enter the board length (>= 4): ";
    cin >> boardLength;
    cout << "Enter the board width (>= 4): ";
    cin >> boardWidth;

    while (!isInputBoardSizeValid(boardLength, boardWidth)) {
        clearConsole();
        cout << "Invalid board size! Please, enter new board size." << endl;

        cout << "Enter the board length (>= 4): ";
        cin >> boardLength;
        cout << "Enter the board width (>= 4): ";
        cin >> boardWidth;
    }

    size_t mathOperationsArrLength = boardLength * boardWidth / 2;
    char* mathOperationsArr = new char[mathOperationsArrLength];

    size_t numArrLength = boardLength * boardWidth / 2;
    int* numArr = new int[numArrLength];

    int difficultyCoefficient = calculateCoefficientOfDifficulty(boardLength, boardWidth);

    char** mathOperationsGrid;
    createGrid(mathOperationsGrid, (boardWidth + 2), (boardLength + 2));

    int** numGrid;
    createGrid(numGrid, (boardWidth + 2), (boardLength + 2));

    delete[] mathOperationsArr;
    delete[] numArr;

    deleteGrid(mathOperationsGrid, (boardWidth + 2));
    deleteGrid(numGrid, (boardWidth + 2));

    return 0;
}

//Function to check whether the board length and width are minimum 4
bool isInputBoardSizeValid(size_t boardLength, size_t boardWidth) {
    bool isInputBoardLengthValid = boardLength >= MIN_BOARD_LENGTH;
    bool isInputBoardWidthValid = boardWidth >= MIN_BOARD_WIDTH;

    return (isInputBoardLengthValid && isInputBoardWidthValid);
}

//Function to clear the console for clearer interface
void clearConsole() {
    system("cls");
}

//A higher difficulty coefficient will give chance for bigger numbers to appear on the board
int calculateCoefficientOfDifficulty(size_t boardLength, size_t boardWidth) {
    size_t boardSize = boardLength * boardWidth;
    int difficultyCoefficient = (int)boardSize / 100 + 1;

    const int MIN_COEFFICIENT = 1, MAX_COEFFICIENT = 10;

    if (difficultyCoefficient > 10) {
        difficultyCoefficient = 10;
    }

    return difficultyCoefficient;
}

//Function to generate the numbers and math operations on the board 
//(random number >0 & <= maxValue)
int getRandomNumberInInterval(int maxValue) {
    int randomNumber = 1 + (rand() % maxValue);

    return randomNumber;
}

//Functions to create dynamic char, int and bool grids
void createGrid(char**& grid, size_t rows, size_t cols) {
    grid = new char*[rows];

    for (size_t i = 0; i < rows; i++) {
        grid[i] = new char[cols];
    }
}

void createGrid(int**& grid, size_t rows, size_t cols) {
    grid = new int* [rows];

    for (size_t i = 0; i < rows; i++) {
        grid[i] = new int[cols];
    }
}

void createGrid(bool**& grid, size_t rows, size_t cols) {
    grid = new bool* [rows];

    for (size_t i = 0; i < rows; i++) {
        grid[i] = new bool[cols];
    }
}

//Functions to delete dynamic char, int and bool grids
void deleteGrid(char**& grid, size_t rows) {
    for (size_t i = 0; i < rows; i++) {
        delete[] grid[i];
    }

    delete[] grid;
}

void deleteGrid(int**& grid, size_t rows) {
    for (size_t i = 0; i < rows; i++) {
        delete[] grid[i];
    }

    delete[] grid;
}

void deleteGrid(bool**& grid, size_t rows) {
    for (size_t i = 0; i < rows; i++) {
        delete[] grid[i];
    }

    delete[] grid;
}

//Functions to print char, int, bool grids 
void printGrid(const char**& grid, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void printGrid(const int**& grid, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void printGrid(const bool**& grid, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

//Generating random math operation array to later use it to build the game board
char codeToMathOperation(int mathOperationCode) {
    if (mathOperationCode == 1) {
        return ' ';
    }
    else if (mathOperationCode == 2) {
        return '+';
    }
    else if (mathOperationCode == 3) {
        return '-';
    }
    else if (mathOperationCode == 4) {
        return '*';
    }
    else if (mathOperationCode == 5) {
        return '/';
    }
}
void randomGenMathOperationsArray(char*& mathOperationsArr, size_t mathOperationsArrLength) {
    int mathOperationCode = 1; //1- "no sign"/"0"; 2 - "+"; 3 - "-"; 4 - "*"; 5 - "/"
    for (size_t i = 0; i < mathOperationsArrLength; i++) {
        mathOperationCode = getRandomNumberInInterval(NUMBER_OF_MATH_OPERATIONS);
        mathOperationsArr[i] = codeToMathOperation(mathOperationCode);
    }
}

//Generating random number array to later use it to build the game board
void randomGenNumArray(int*& numArr, size_t numArrLength, int difficultyCoefficient) {
    int maxValue = 10 * difficultyCoefficient;

    for (size_t i = 0; i < numArrLength; i++) {
        numArr[i] = getRandomNumberInInterval(maxValue);
    }
}

bool isHalfBoardFulfillingBoardRequirements(char*& mathOperationsArr, size_t mathOperationsArrLength,
    int*& numArr, size_t numArrLength) {
    bool metAddition = false;
    bool metSubtraction = false;
    bool metZero = false;
    bool metMultiplicationWithTwo = false;
    bool metDivisionByTwo = false;

    //mathOperationsArrLength = numArrLength
    //i = 1, because the cell (0, 0) will be later set to 0
    for (size_t i = 1; i < mathOperationsArrLength; i++) {
        if (mathOperationsArr[i] == '+') {
            metAddition = true;
        }
        else if (mathOperationsArr[i] == '-') {
            metSubtraction = true;
        }
        else if (mathOperationsArr[i] == ' ') {
            metZero = true;
        }
        else if (mathOperationsArr[i] == '*' && numArr[i] == 2) {
            metMultiplicationWithTwo = true;
        }
        else if (mathOperationsArr[i] == '/' && numArr[i] == 2) {
            metDivisionByTwo = true;
        }
        else {
            continue;
        }
    }

    return (metAddition && metSubtraction && metZero && metMultiplicationWithTwo && metDivisionByTwo);
}

//Generating half of the board game to later use it to build the whole game board
void generateHalfBoardUpToTheRequirements(char*& mathOperationsArr, size_t mathOperationsArrLength,
    int*& numArr, size_t numArrLength, int difficultyCoefficient) {
    randomGenMathOperationsArray(mathOperationsArr, mathOperationsArrLength);
    randomGenNumArray(numArr, numArrLength, difficultyCoefficient);

    size_t randomInd = 0;
    int lastInd = mathOperationsArrLength - 1;
    while (!isHalfBoardFulfillingBoardRequirements(mathOperationsArr, mathOperationsArrLength,
        numArr, numArrLength)) {

        randomInd = getRandomNumberInInterval(lastInd);
        mathOperationsArr[randomInd] = '+';
        randomInd = getRandomNumberInInterval(lastInd);
        mathOperationsArr[randomInd] = '-';
        randomInd = getRandomNumberInInterval(lastInd);
        mathOperationsArr[randomInd] = ' ';
        randomInd = getRandomNumberInInterval(lastInd);
        mathOperationsArr[randomInd] = '*';
        numArr[randomInd] = 2;
        randomInd = getRandomNumberInInterval(lastInd);
        mathOperationsArr[randomInd] = '/';
        numArr[randomInd] = 2;
    }
   
    for (size_t i = 1; i < numArrLength; i++) {
        if (mathOperationsArr[i] == ' ') {
            numArr[i] = 0;
        }
    }

    //Setting the two starting points (0, 0) and (N, M)
    mathOperationsArr[0] = ' ';
    numArr[0] = 0;
}