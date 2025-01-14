#include <iostream>
#include <windows.h>
using namespace std;

const size_t MIN_BOARD_LENGTH = 4, MIN_BOARD_WIDTH = 4;
const int NUMBER_OF_MATH_OPERATIONS = 5;
const int MAX_DIGITS = 3;
const int MARGIN = 2;

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

void printGrid(char** grid, size_t rows, size_t cols);
void printGrid(int** grid, size_t rows, size_t cols);
void printGrid(bool** grid, size_t rows, size_t cols);

void randomGenMathOperationsArray(char*& mathOperationsArr, size_t mathOperationsArrLength);
char codeToMathOperation(int mathOperationCode);
void randomGenNumArray(int*& numArr, size_t numArrLength, int difficultyCoefficient);

bool isHalfBoardFulfillingBoardRequirements(char*& mathOperationsArr, size_t mathOperationsArrLength,
    int*& numArr, size_t numArrLength);
void generateHalfBoardUpToTheRequirements(char*& mathOperationsArr, size_t mathOperationsArrLength,
    int*& numArr, size_t numArrLength, int difficultyCoefficient);
void generateGameBoard(char*& mathOperationsArr,
    size_t mathOperationsArrLength,
    int*& numArr,
    size_t numArrLength,
    int difficultyCoefficient,
    size_t boardLength,
    size_t boardWidth,
    char**& mathOperationsGrid,
    int**& numGrid);

void gridToArray(char** grid, size_t rows, size_t cols, char* arr);
void gridToArray(int** grid, size_t rows, size_t cols, int* arr);

char digitToChar(int digit);

void initialInitializationOfVisualBoard(char**& visualBoard, size_t visualBoardWidth, size_t visualBoardLength);

void buildVisualBoard(char**& visualBoard, size_t visualBoardLength, size_t visualBoardWidth,
    char** mathOperationsGrid, int** numGrid, size_t gridLength, size_t gridWidth,
    size_t boardLength, size_t boardWidth);

bool isMovePossible(int currentX, int currentY, int newX, int newY, int** takenCoordinates);

int playerOnMove(int totalMoves);

bool isGameOver(int playerOneX, int playerOneY,
    int playerTwoX, int playerTwoY,
    int** takenCoordinates, size_t gridLength, size_t gridWidth);

void scoreUpdate(double& score, int coordinateX, int coordinateY,
    char** mathOperationsGrid, int** numGrid);

void colorSet(int color);

void printGameBoard(char** mathOperationsGrid, int** numGrid,
    size_t gridLength, size_t gridWidth);

void getNewValidMove(int playerX, int playerY);

void initializeVisitedCoordinatesBoard(int** visitedCoordinates,
    size_t gridWidth, size_t gridLength, size_t boardWidth, size_t boardLength);

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

    //Generating game board
    size_t mathOperationsArrLength = boardLength * boardWidth / 2;
    char* mathOperationsArr = new char[mathOperationsArrLength];

    size_t numArrLength = boardLength * boardWidth / 2;
    int* numArr = new int[numArrLength];

    int difficultyCoefficient = calculateCoefficientOfDifficulty(boardLength, boardWidth);

    size_t gridLength = boardLength + 2;
    size_t gridWidth = boardWidth + 2;
    char** mathOperationsGrid = nullptr;
    createGrid(mathOperationsGrid, gridWidth, gridLength);

    int** numGrid = nullptr;
    createGrid(numGrid, gridWidth, gridLength);

    generateGameBoard(mathOperationsArr, mathOperationsArrLength,
        numArr, numArrLength, difficultyCoefficient,
        boardLength, boardWidth, mathOperationsGrid, numGrid);

    size_t visualBoardLength = boardLength + MAX_DIGITS * boardLength + MARGIN * (boardLength + 1);
    size_t visualBoardWidth = boardWidth + (boardLength + 1);
    char** visualBoard = nullptr;
    createGrid(visualBoard, visualBoardWidth, visualBoardLength);
    initialInitializationOfVisualBoard(visualBoard, visualBoardWidth, visualBoardLength);
    buildVisualBoard(visualBoard, visualBoardLength, visualBoardWidth,
        mathOperationsGrid, numGrid, gridLength, gridWidth,
        boardLength, boardWidth);

    clearConsole();
    //printGrid(visualBoard, visualBoardWidth, visualBoardLength);

    //Game moves
    int playerOneX = 1;
    int playerOneY = 1;
    double playerOneScore = 0;

    int playerTwoX = boardLength;
    int playerTwoY = boardWidth;
    double playerTwoScore = 0;

    int newX = 0;
    int newY = 0;

    int totalMoves = 0;

    int** visitedCoordinates = nullptr;
    createGrid(visitedCoordinates, gridWidth, gridLength);
    initializeVisitedCoordinatesBoard(visitedCoordinates, gridWidth, gridLength,
        boardWidth, boardLength);

    printGrid(visitedCoordinates, gridWidth, gridWidth);

    //while (1) {//gameover
        if (playerOnMove(totalMoves) == 1) {
            printGameBoard(mathOperationsGrid, numGrid, gridLength, gridWidth);
            cout << endl;
            cout << "Score of player one: " << playerOneScore << '\t'
                << '\t' << "Score of player two: " << playerTwoScore;
            cout << endl;

            cout << endl;
            cout << "Enter next move: ";
            cout << endl;
        }
        else {
        }
   // }

    delete[] mathOperationsArr;
    delete[] numArr;

    deleteGrid(mathOperationsGrid, gridWidth);
    deleteGrid(numGrid, gridWidth);
    deleteGrid(visualBoard, visualBoardWidth);
    deleteGrid(visitedCoordinates, gridWidth);

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
void printGrid(char** grid, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void printGrid(int** grid, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void printGrid(bool** grid, size_t rows, size_t cols) {
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

//Generating half of the game board to later use it to build the whole game board
void generateHalfBoardUpToTheRequirements(char*& mathOperationsArr, size_t mathOperationsArrLength,
    int*& numArr, size_t numArrLength, int difficultyCoefficient) {
    randomGenMathOperationsArray(mathOperationsArr, mathOperationsArrLength);
    randomGenNumArray(numArr, numArrLength, difficultyCoefficient);

    size_t randomInd = 0;
    int lastInd = (int)mathOperationsArrLength - 1;
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

//Building the whole game board
void generateGameBoard(char*& mathOperationsArr,
    size_t mathOperationsArrLength,
    int*& numArr,
    size_t numArrLength,
    int difficultyCoefficient,
    size_t boardLength,
    size_t boardWidth,
    char**& mathOperationsGrid,
    int**& numGrid) {
    generateHalfBoardUpToTheRequirements(mathOperationsArr, mathOperationsArrLength,
        numArr, numArrLength, difficultyCoefficient);

    size_t gridFirstRowInd = 1;
    size_t gridLastRowInd = boardWidth;
    size_t gridFirstColInd = 1;
    size_t gridLastColInd = boardLength;

    size_t mathOperationsArrInd = 0;
    for (size_t i = gridFirstRowInd; i <= gridLastRowInd; i++) {
        for (size_t j = gridFirstColInd; j <= gridLastColInd; j++) {
            mathOperationsGrid[i][j] = mathOperationsArr[mathOperationsArrInd];
            mathOperationsArrInd++;

            if (mathOperationsArrInd == mathOperationsArrLength) {
                break;
            }
        }
        if (mathOperationsArrInd == mathOperationsArrLength) {
            break;
        }
    }

    mathOperationsArrInd = 0;
    for (size_t i = gridLastRowInd; i >= gridFirstRowInd; i--) {
        for (size_t j = gridLastColInd; j >= gridFirstColInd; j--) {
            mathOperationsGrid[i][j] = mathOperationsArr[mathOperationsArrInd];
            mathOperationsArrInd++;

            if (mathOperationsArrInd == mathOperationsArrLength) {
                break;
            }
        }
        if (mathOperationsArrInd == mathOperationsArrLength) {
            break;
        }
    }

    size_t numArrInd = 0;
    for (size_t i = gridFirstRowInd; i <= gridLastRowInd; i++) {
        for (size_t j = gridFirstColInd; j <= gridLastColInd; j++) {
            numGrid[i][j] = numArr[numArrInd];
            numArrInd++;

            if (numArrInd == numArrLength) {
                break;
            }
        }
        if (numArrInd == numArrLength) {
            break;
        }
    }

    numArrInd = 0;
    for (size_t i = gridLastRowInd; i >= gridFirstRowInd; i--) {
        for (size_t j = gridLastColInd; j >= gridFirstColInd; j--) {
            numGrid[i][j] = numArr[numArrInd];
            numArrInd++;

            if (numArrInd == numArrLength) {
                break;
            }
        }
        if (numArrInd == numArrLength) {
            break;
        }
    }

    if ((boardLength * boardWidth) % 2 != 0) {
        int midRow = (boardWidth + 2) / 2;
        int midCol = (boardLength + 2) / 2;

        int randomMathOperationCode = getRandomNumberInInterval(NUMBER_OF_MATH_OPERATIONS);
        mathOperationsGrid[midRow][midCol] = codeToMathOperation(randomMathOperationCode);

        int maxValue = 10 * difficultyCoefficient;
        numGrid[midRow][midCol] = getRandomNumberInInterval(maxValue);
    }
}

//Functions to convert grid to array
void gridToArray(char** grid, size_t rows, size_t cols, char* arr) {
    size_t arrInd = 0;

    size_t lastRowInd = rows - 2;
    size_t lastColInd = cols - 2;
    for (size_t i = 1; i <= lastRowInd; i++) {
        for (size_t j = 1; j <= lastColInd; j++) {
            arr[arrInd] = grid[i][j];
            arrInd++;
        }
    }
}
void gridToArray(int** grid, size_t rows, size_t cols, int* arr) {
    size_t arrInd = 0;

    size_t lastRowInd = rows - 2;
    size_t lastColInd = cols - 2;
    for (size_t i = 1; i <= lastRowInd; i++) {
        for (size_t j = 1; j <= lastColInd; j++) {
            arr[arrInd] = grid[i][j];
            arrInd++;
        }
    }
}

//Function to convert digit to char
char digitToChar(int digit) {
    return (digit + '0');
}

//Initialize an empty visual board
void initialInitializationOfVisualBoard(char**& visualBoard, size_t visualBoardWidth, size_t visualBoardLength) {
    for (size_t i = 0; i < visualBoardWidth; i++) {
        for (size_t j = 0; j < visualBoardLength; j++) {
            visualBoard[i][j] = ' ';
        }
    }
}

//The already generated boards will construct the board that will be print in the console
void buildVisualBoard(char**& visualBoard, size_t visualBoardLength, size_t visualBoardWidth,
    char** mathOperationsGrid, int** numGrid, size_t gridLength, size_t gridWidth,
    size_t boardLength, size_t boardWidth) {
    size_t firstRowInd = 1;
    size_t firstColInd = 2;

    size_t arrayLength = boardLength * boardWidth;
    char* mathOperations = new char[arrayLength];
    gridToArray(mathOperationsGrid, gridWidth, gridLength, mathOperations);
    int* numbers = new int[arrayLength];
    gridToArray(numGrid, gridWidth, gridLength, numbers);

    size_t mathOperationsInd = 0;
    size_t numbersInd = 0;
    int currentNum = 0;
    int ones = 0;
    int tens = 0;
    int hundreds = 0;
    for (size_t i = firstRowInd; i < visualBoardWidth; ) {
        for (size_t j = firstColInd; j < visualBoardLength; ) {
            visualBoard[i][j] = mathOperations[mathOperationsInd];
            j++;

            currentNum = numbers[numbersInd];
            ones = currentNum % 10;
            tens = (currentNum / 10) % 10;
            hundreds = currentNum / 100;

            visualBoard[i][j] = digitToChar(hundreds);
            j++;
            visualBoard[i][j] = digitToChar(tens);
            j++;
            visualBoard[i][j] = digitToChar(ones);
            j += MARGIN + 1;

            mathOperationsInd++;
            numbersInd++;

            if (numbersInd == arrayLength) {
                break;
            }
        }
        if (numbersInd == arrayLength) {
            break;
        }

        i += MARGIN;
    }

    delete[] mathOperations;
    delete[] numbers;
}

//Function to check whether a player is possible to move to given coordinates 
bool isMovePossible(int currentX, int currentY, int newX, int newY, int** takenCoordinates) {
    if (takenCoordinates[newY][newX] != 0) {
        return false;
    }
    
    //During every move a player have to move from their current coordinates
    if (newX == currentX && newY == currentY) {
        return false;
    }

    if (!(newX == currentX + 1 || newX == currentX - 1)) {
        return false;
    }

    if (!(newY == currentY + 1 || newY == currentY - 1)) {
        return false;
    }

    return true;
}

//Function to switch turns 
int playerOnMove(int totalMoves) {
    if (totalMoves % 2 == 0) {
        return 1;
    }
    else {
        return 2;
    }
}

//Function to check if the game can continue
bool isGameOver(int playerOneX, int playerOneY,
    int playerTwoX, int playerTwoY,
    int** takenCoordinates, size_t gridLength, size_t gridWidth) {

    bool isThereUnvisitedNeighbour = false;
    for (size_t i = playerOneY - 1; i <= playerOneY + 1; i++) {
        for (size_t j = playerOneX - 1; j <= playerOneY + 1; j++) {
            if (takenCoordinates[i][j] == 0)
                isThereUnvisitedNeighbour = true;
        }
    }
    if (isThereUnvisitedNeighbour = false) {
        return false;
    }

    isThereUnvisitedNeighbour = false;
    for (size_t i = playerTwoY - 1; i <= playerTwoY + 1; i++) {
        for (size_t j = playerTwoX - 1; j <= playerTwoY + 1; j++) {
            if (takenCoordinates[i][j] == 0)
                isThereUnvisitedNeighbour = true;
        }
    }
    if (isThereUnvisitedNeighbour = true) {
        return false;
    }

    for (size_t i = 0; i < gridLength; i++) {
        for (size_t j = 0; j < gridWidth; j++) {
            if (takenCoordinates[i][j] == 0)
                return true;
        }
    }

    return false;
}

//Function to update the score after after every move
void scoreUpdate(double& score, int coordinateX, int coordinateY,
    char** mathOperationsGrid, int** numGrid) {

    switch (mathOperationsGrid[coordinateY][coordinateX])
    {
    case ' ': score *= 0;
        break;
    case '+': score += numGrid[coordinateY][coordinateX];
        break;
    case '-': score -= numGrid[coordinateY][coordinateX];
        break;
    case '*': score *= numGrid[coordinateY][coordinateX];
        break;
    case '/': score /= numGrid[coordinateY][coordinateX];
        break;
    }

    if (score<0) {
        score = 0;
    }
}

//Function to color the text and the background in the console
void colorSet(int color) {
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void printGameBoard(char** mathOperationsGrid, int** numGrid,
    size_t gridLength, size_t gridWidth) {
    for (size_t i = 1; i < gridWidth-1; i++) {
        for (size_t j = 1; j < gridLength-1; j++) {
            if (numGrid[i][j] < 10) {
                cout << mathOperationsGrid[i][j] << "  " << numGrid[i][j] << "\t";
            }
            else if (numGrid[i][j] >= 10) {
                cout << mathOperationsGrid[i][j] << " " << numGrid[i][j] << "\t";
            }
            else {
                cout << mathOperationsGrid[i][j] << numGrid[i][j] << "\t";
            }
        }
        cout << endl << endl;
    }
}

void getNewValidMove(int playerX, int playerY) {
    int newX = 0;
    int newY = 0;

    cout << "Enter next move: ";
    while (isMovePossible);
}

void initializeVisitedCoordinatesBoard(int** visitedCoordinates, 
    size_t gridWidth, size_t gridLength, size_t boardWidth, size_t boardLength) {
    for (size_t i = 0; i < gridWidth; i++) {
        for (size_t j = 0; j < gridLength; j++) {
            visitedCoordinates[i][j] = 0;
        }
    }

    for (size_t i = 0; i < gridWidth; i++) {
        visitedCoordinates[i][0] = 3;
        visitedCoordinates[i][gridLength - 1] = 3;
    }
    for (size_t j = 0; j < gridLength; j++) {
        visitedCoordinates[0][j] = 3;
        visitedCoordinates[gridWidth - 1][j] = 3;
    }

    visitedCoordinates[1][1] = 1;
    visitedCoordinates[boardWidth][boardLength] = 2;
}