#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

struct Game {
    size_t gridLength;
    size_t gridWidth;
    char** MOGrid; //Math Operations
    int** NGrid; //Numbers
    int** VCGrid; //VisitedCoordinates
    double scoreOne;
    double scoreTwo;
    int totalMoves;
};

const size_t MIN_BOARD_LENGTH = 4, MIN_BOARD_WIDTH = 4;
const int NUMBER_OF_MATH_OPERATIONS = 5;
const int MAX_DIGITS = 3;
const int MARGIN = 2;

const int BLACK_TEXT_WHITE_BACKGROUND = 240; //0 + 15*16
const int WHITE_TEXT_BLACK_BACKGROUND = 15; //15 + 0*16
const int GREY_TEXT_BLACK_BACKGROUND = 7; //7 + 0*16
const int WHITE_TEXT_BLUE_BACKGROUND = 63; //15 + 3*16
const int YELLOW_TEXT_BLUE_BACKGROUND = 62; //14+ 3*16
const int WHITE_TEXT_GREEN_BACKGROUND = 47; //15 + 2*16
const int YELLOW_TEXT_GREEN_BACKGROUND = 46; //14 + 2*16
const int CORAL_TEXT_WHITE_BACKGROUND = 252; //12 + 15*16

void startMenu(int& gameMode);
void readingBoardLengthAndWidth(size_t& boardLength, size_t& boardWidth);

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

void setColor(int color);

void colorCell(int** visitedCoordinates, size_t i, size_t j);

void printGameBoard(char** mathOperationsGrid, int** numGrid,
    size_t gridLength, size_t gridWidth, int** visitedCoordinates);

void getNewValidMove(int& playerX, int& playerY, int** visitedCoordinates);

void initializeVisitedCoordinatesBoard(int** visitedCoordinates,
    size_t gridWidth, size_t gridLength, size_t boardWidth, size_t boardLength);

void saveGameProgress(fstream& fileGR, Game gameRecord);
void restoreGameProgress(fstream& fileGR, Game gameRecord);

int main() {
    //A seed for the random number function
    srand((unsigned)time(0));

    int gameMode = 0;
    startMenu(gameMode);

    size_t boardLength = MIN_BOARD_LENGTH, boardWidth = MIN_BOARD_WIDTH;
    size_t mathOperationsArrLength = 0;
    char* mathOperationsArr = nullptr;
    size_t numArrLength =0;
    int* numArr = nullptr;

    int difficultyCoefficient=0;
    size_t gridLength = 0;
    size_t gridWidth = 0;
    char** mathOperationsGrid = nullptr;
    int** numGrid = nullptr;
    int** visitedCoordinates = nullptr;

    int playerOneX = 1;
    int playerOneY = 1;
    double playerOneScore = 0;

    int playerTwoX = (int)boardLength;
    int playerTwoY = (int)boardWidth;
    double playerTwoScore = 0;

    int newX = 0;
    int newY = 0;

    int totalMoves = 0;

    fstream fileGameRecords;

    if (gameMode == 1) {
        clearConsole();
        readingBoardLengthAndWidth(boardLength, boardWidth);

        //Generating game board
        mathOperationsArrLength = boardLength * boardWidth / 2;
        mathOperationsArr = new char[mathOperationsArrLength];

        numArrLength = boardLength * boardWidth / 2;
        numArr = new int[numArrLength];

        difficultyCoefficient = calculateCoefficientOfDifficulty(boardLength, boardWidth);

        gridLength = boardLength + 2;
        gridWidth = boardWidth + 2;
        mathOperationsGrid = nullptr;
        createGrid(mathOperationsGrid, gridWidth, gridLength);

        numGrid = nullptr;
        createGrid(numGrid, gridWidth, gridLength);

        generateGameBoard(mathOperationsArr, mathOperationsArrLength,
            numArr, numArrLength, difficultyCoefficient,
            boardLength, boardWidth, mathOperationsGrid, numGrid);

        visitedCoordinates = nullptr;
        createGrid(visitedCoordinates, gridWidth, gridLength);
        initializeVisitedCoordinatesBoard(visitedCoordinates, gridWidth, gridLength,
            boardWidth, boardLength);
    }
    else if (gameMode == 2) {
        Game gameRecord = { gridLength, gridWidth, mathOperationsGrid, numGrid,
        visitedCoordinates, playerOneScore, playerTwoScore, totalMoves };

        restoreGameProgress(fileGameRecords, gameRecord);
    }

    clearConsole();

    while (!isGameOver(playerOneX, playerOneY, playerTwoX,
        playerTwoY, visitedCoordinates, gridLength, gridWidth)) {
        if (playerOnMove(totalMoves) == 1) {
            printGameBoard(mathOperationsGrid, numGrid, gridLength, gridWidth, visitedCoordinates);
            cout << endl;

            setColor(BLACK_TEXT_WHITE_BACKGROUND);

            cout << "Score of player one: " << playerOneScore << '\t'
                << '\t' << "Score of player two: " << playerTwoScore;
            cout << endl;

            visitedCoordinates[playerOneY][playerOneX] = 1;

            cout << endl;
            cout << "Player One's turn." << endl;
            getNewValidMove(playerOneX, playerOneY, visitedCoordinates);
            visitedCoordinates[playerOneY][playerOneX] = 11;

            clearConsole();
            setColor(WHITE_TEXT_BLACK_BACKGROUND);
            scoreUpdate(playerOneScore, playerOneX, playerOneY, mathOperationsGrid, numGrid);
        }
        else {
            printGameBoard(mathOperationsGrid, numGrid, gridLength, gridWidth, visitedCoordinates);
            cout << endl;

            setColor(BLACK_TEXT_WHITE_BACKGROUND);

            cout << "Score of player one: " << playerOneScore << '\t'
                << '\t' << "Score of player two: " << playerTwoScore;
            cout << endl;

            visitedCoordinates[playerTwoY][playerTwoX] = 2;

            cout << endl;
            cout << "Player Two's turn." << endl;
            getNewValidMove(playerTwoX, playerTwoY, visitedCoordinates);
            visitedCoordinates[playerTwoY][playerTwoX] = 22;

            clearConsole();
            setColor(WHITE_TEXT_BLACK_BACKGROUND);
            scoreUpdate(playerTwoScore, playerTwoX, playerTwoY, mathOperationsGrid, numGrid);
        }

        totalMoves++;

        Game gameRecord = { gridLength, gridWidth, mathOperationsGrid, numGrid,
        visitedCoordinates, playerOneScore, playerTwoScore, totalMoves };
        saveGameProgress(fileGameRecords, gameRecord);

        clearConsole();
    }

    fileGameRecords.open("Game Records.txt", ios::out);
    fileGameRecords << " ";
    fileGameRecords.close();

    printGameBoard(mathOperationsGrid, numGrid, gridLength, gridWidth, visitedCoordinates);
    cout << endl << endl;

    setColor(BLACK_TEXT_WHITE_BACKGROUND);

    cout << "Score of player one: " << playerOneScore << '\t'
        << '\t' << "Score of player two: " << playerTwoScore;
    cout << endl << endl;
    
    setColor(CORAL_TEXT_WHITE_BACKGROUND);
    if (playerOneScore > playerTwoScore) {
        cout << "CONGRATULATIONS PLAYER ONE ON YOUR VICTORY!" << endl;
    }
    else if (playerOneScore < playerTwoScore) {
        cout << "CONGRATULATIONS PLAYER TWO ON YOUR VICTORY!" << endl;
    }
    else {
        cout << "TIE!" << endl;
    }

    setColor(GREY_TEXT_BLACK_BACKGROUND);

    delete[] mathOperationsArr;
    delete[] numArr;

    deleteGrid(mathOperationsGrid, gridWidth);
    deleteGrid(numGrid, gridWidth);
    //deleteGrid(visualBoard, visualBoardWidth);
    deleteGrid(visitedCoordinates, gridWidth);

    return 0;
}

void startMenu(int& gameMode) {
    int NGOrRG = 0;

    cout << "Welcome to Math Tricks!" << endl << endl;
    cout << "To continue choose one of the options below: " << endl;
    cout << "1) New Game" << endl;
    cout << "2) Resume Game" << endl;
    cout << "Please enter your choice(1 or 2): ";
    cin >> NGOrRG;

    if (NGOrRG == 1) {
        gameMode = 1;
    }
    else if (NGOrRG == 2) {
        gameMode = 2;
    }
    else {
        clearConsole();
        startMenu(gameMode);
    }
}

void readingBoardLengthAndWidth(size_t& boardLength, size_t& boardWidth) {
    //Read the board size from the console
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
        return '>';
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
    else {
        return -1;
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
        int midRow = (int)(boardWidth + 2) / 2;
        int midCol = (int)(boardLength + 2) / 2;

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

    if (newX > currentX + 1 || newX < currentX - 1) {
        return false;
    }

    if (newY > currentY + 1 || newY < currentY - 1) {
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
        for (size_t j = playerOneX - 1; j <= playerOneX + 1; j++) {
            if (takenCoordinates[i][j] == 0)
                isThereUnvisitedNeighbour = true;
        }
    }
    if (isThereUnvisitedNeighbour == false) {
        return true;
    }

    isThereUnvisitedNeighbour = false;
    for (size_t i = playerTwoY - 1; i <= playerTwoY + 1; i++) {
        for (size_t j = playerTwoX - 1; j <= playerTwoX+ 1; j++) {
            if (takenCoordinates[i][j] == 0)
                isThereUnvisitedNeighbour = true;
        }
    }
    if (isThereUnvisitedNeighbour == false) {
        return true;
    }

    for (size_t i = 0; i < gridLength; i++) {
        for (size_t j = 0; j < gridWidth; j++) {
            if (takenCoordinates[i][j] == 0)
                return false;
        }
    }

    return true;
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

    if (score < 0) {
        score = 0;
    }
}

//Function to color the text and the background in the console
void setColor(int color) {
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

//Function to color only one cell on the board
void colorCell(int** visitedCoordinates, size_t i, size_t j) {
    if (visitedCoordinates[i][j] == 0) {
        setColor(BLACK_TEXT_WHITE_BACKGROUND);
    }
    else if (visitedCoordinates[i][j] == 1) {
        setColor(WHITE_TEXT_BLUE_BACKGROUND);
    }
    else if (visitedCoordinates[i][j] == 11) {
        setColor(YELLOW_TEXT_BLUE_BACKGROUND);
    }
    else if (visitedCoordinates[i][j] == 2) {
        setColor(WHITE_TEXT_GREEN_BACKGROUND);
    }
    else if (visitedCoordinates[i][j] == 22) {
        setColor(YELLOW_TEXT_GREEN_BACKGROUND);
    }
}

void printGameBoard(char** mathOperationsGrid, int** numGrid,
    size_t gridLength, size_t gridWidth, int** visitedCoordinates) {
    int firstLoopStop = (int)gridWidth - 1;
    int secondLoopStop = (int)gridLength - 1;

    for (size_t i = 0; i < firstLoopStop; i++) {
        for (size_t j = 0; j < secondLoopStop; j++) {
            if (i == 0) {
                cout << j << '\t'<<"   ";
                continue;
            }
            if (j == 0) {
                cout << i << '\t';
                continue;
            }

            if (numGrid[i][j] < 10) {
                colorCell(visitedCoordinates, i, j);
                cout << mathOperationsGrid[i][j] << "  " << numGrid[i][j] << "\t";
                setColor(WHITE_TEXT_BLACK_BACKGROUND);
            }
            else if (numGrid[i][j] >= 10) {
                colorCell(visitedCoordinates, i, j);
                cout << mathOperationsGrid[i][j] << " " << numGrid[i][j] << "\t";
                setColor(WHITE_TEXT_BLACK_BACKGROUND);
            }
            else {
                colorCell(visitedCoordinates, i, j);
                cout << mathOperationsGrid[i][j] << numGrid[i][j] << "\t";
                setColor(WHITE_TEXT_BLACK_BACKGROUND);
            }
        }
        if (i == 0) {
            cout << endl << endl;
        }
        cout << endl << endl;
    }
}

void initializeVisitedCoordinatesBoard(int** visitedCoordinates, 
    size_t gridWidth, size_t gridLength, size_t boardWidth, size_t boardLength) {
    for (size_t i = 0; i < gridWidth; i++) {
        for (size_t j = 0; j < gridLength; j++) {
            visitedCoordinates[i][j] = 0;
        }
    }

    int lastCol = (int)gridLength - 1;
    for (size_t i = 0; i < gridWidth; i++) {
        visitedCoordinates[i][0] = 3;
        visitedCoordinates[i][lastCol] = 3;
    }

    int lastRow = (int)gridWidth - 1;
    for (size_t j = 0; j < gridLength; j++) {
        visitedCoordinates[0][j] = 3;
        visitedCoordinates[lastRow][j] = 3;
    }

    visitedCoordinates[1][1] = 11;
    visitedCoordinates[boardWidth][boardLength] = 22;
}

void getNewValidMove(int& playerX, int& playerY, int** visitedCoordinates) {
    int newX = 0;
    int newY = 0;

    while (!isMovePossible(playerX, playerY, newX, newY, visitedCoordinates)) {
        cout << "Enter next move: ";
        cin >> newX >> newY;

       // cout << '\r';
    }

    playerX = newX;
    playerY = newY;
}

void saveGameProgress(fstream& fileGR, Game gameRecord) {
    fileGR.open("Game Records.txt", ios::out);

    fileGR << gameRecord.gridLength << " " << gameRecord.gridWidth << endl;

    for (size_t i = 0; i < gameRecord.gridWidth; i++) {
        for (size_t j = 0; j < gameRecord.gridLength; j++) {
            fileGR << gameRecord.MOGrid[i][j] << " ";
        }
        //fileGR << endl;
    }
    fileGR << endl;

    for (size_t i = 0; i < gameRecord.gridWidth; i++) {
        for (size_t j = 0; j < gameRecord.gridLength; j++) {
            fileGR << gameRecord.NGrid[i][j] << " ";
        }
        //fileGR << endl;
    }
    fileGR << endl;

    for (size_t i = 0; i < gameRecord.gridWidth; i++) {
        for (size_t j = 0; j < gameRecord.gridLength; j++) {
            fileGR << gameRecord.VCGrid[i][j] << " ";
        }
        //fileGR << endl;
    }
    fileGR << endl;


    fileGR << gameRecord.scoreOne << " " << gameRecord.scoreTwo
        << " " << gameRecord.totalMoves << endl;

    fileGR.close();
}

void restoreGameProgress(fstream& fileGR, Game gameRecord) {
    fileGR.open("Game Records.txt", ios::in);

    fileGR >> gameRecord.gridLength >> gameRecord.gridWidth;

    for (size_t i = 0; i < gameRecord.gridWidth; i++) {
        for (size_t j = 0; j < gameRecord.gridLength; j++) {
            fileGR >> gameRecord.MOGrid[i][j];
        }
    }

    for (size_t i = 0; i < gameRecord.gridWidth; i++) {
        for (size_t j = 0; j < gameRecord.gridLength; j++) {
            fileGR >> gameRecord.NGrid[i][j];
        }
    }

    for (size_t i = 0; i < gameRecord.gridWidth; i++) {
        for (size_t j = 0; j < gameRecord.gridLength; j++) {
            fileGR >> gameRecord.VCGrid[i][j];
        }
    }

    fileGR >> gameRecord.scoreOne >> gameRecord.scoreTwo >> gameRecord.totalMoves;

    fileGR.close();
}