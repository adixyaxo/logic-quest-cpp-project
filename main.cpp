#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <algorithm>

using namespace std;

/*
===========================================================
                    LOGIC QUEST
===========================================================

FULL WORKING VERSION

Games Included:
1. Sudoku Viewer
2. Tic Tac Toe
3. Hangman
4. Math Quiz
5. Number Guessing

FEATURES:
✔ Proper input validation
✔ Random puzzle/word selection
✔ Winner detection
✔ Replay-safe logic
✔ File handling
✔ Stable random generator
✔ Clean implementation

FILES REQUIRED:
----------------
assets/
│
├── sudoku_questions.txt
├── words.txt
└── math_questions.txt

===========================================================
*/

class LogicQuest
{

private:
    int totalSudokuPuzzles = 5;

public:
    /*
    =======================================================
                        CONSTRUCTOR
    =======================================================
    */
    LogicQuest()
    {

        srand((unsigned)time(0));
    }

    /*
    =======================================================
                    SAFE INTEGER INPUT
    =======================================================
    */
    int getIntegerInput()
    {

        int value;

        while (true)
        {

            cin >> value;

            if (cin.fail())
            {

                cin.clear();

                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n');

                cout << "Invalid input. Enter number: ";
            }
            else
            {

                return value;
            }
        }
    }

    /*
    =======================================================
                        MAIN MENU
    =======================================================
    */
    void menu()
    {

        int choice;

        do
        {

            cout << "\n";
            cout << "=====================================\n";
            cout << "           LOGIC QUEST               \n";
            cout << "=====================================\n";

            cout << "1. Sudoku\n";
            cout << "2. Tic Tac Toe\n";
            cout << "3. Hangman\n";
            cout << "4. Math Quiz\n";
            cout << "5. Number Guessing\n";
            cout << "6. Exit\n";

            cout << "\nChoose Game: ";

            choice = getIntegerInput();

            switch (choice)
            {

            case 1:
                sudoku();
                break;

            case 2:
                ticTacToe();
                break;

            case 3:
                hangman();
                break;

            case 4:
                mathQuiz();
                break;

            case 5:
                numberGuess();
                break;

            case 6:
                cout << "\nExiting Logic Quest...\n";
                break;

            default:
                cout << "\nInvalid Option.\n";
            }

        } while (choice != 6);
    }

    /*
    =======================================================
                        SUDOKU
    =======================================================
    */
    /*
===========================================================
                    SUDOKU IMPLEMENTATION
===========================================================

ADD THESE FUNCTIONS INSIDE CLASS LogicQuest
Replace old sudoku() with this full version.

FEATURES:
✔ Playable Sudoku
✔ Input numbers manually
✔ Sudoku validation
✔ Win detection
✔ Quit anytime with -1

===========================================================
*/

    /*
    ===========================================================
                    PRINT SUDOKU BOARD
    ===========================================================
    */
    void printSudoku(int board[9][9])
    {

        cout << "\n";

        for (int i = 0; i < 9; i++)
        {

            if (i % 3 == 0)
                cout << "-------------------------------\n";

            for (int j = 0; j < 9; j++)
            {

                if (j % 3 == 0)
                    cout << "| ";

                if (board[i][j] == 0)
                    cout << ". ";
                else
                    cout << board[i][j] << " ";
            }

            cout << "|\n";
        }

        cout << "-------------------------------\n";
    }

    /*
    ===========================================================
                    VALIDATE SUDOKU MOVE
    ===========================================================
    */
    bool isValidSudokuMove(
    int board[9][9],
    int row,
    int col,
    int num
) {

    /*
    Row Check
    */
    for(int i = 0; i < 9; i++) {

        if(i != col &&
           board[row][i] == num)
            return false;
    }

    /*
    Column Check
    */
    for(int i = 0; i < 9; i++) {

        if(i != row &&
           board[i][col] == num)
            return false;
    }

    /*
    3x3 Grid Check
    */
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for(int i = 0; i < 3; i++) {

        for(int j = 0; j < 3; j++) {

            int currentRow = startRow + i;
            int currentCol = startCol + j;

            /*
            Skip current cell itself
            */
            if(currentRow == row &&
               currentCol == col)
                continue;

            if(board[currentRow][currentCol] == num)
                return false;
        }
    }

    return true;
}

    /*
    ===========================================================
                    CHECK SUDOKU COMPLETE
    ===========================================================
    */
    bool sudokuComplete(int board[9][9])
    {

        for (int i = 0; i < 9; i++)
        {

            for (int j = 0; j < 9; j++)
            {

                if (board[i][j] == 0)
                    return false;
            }
        }

        return true;
    }

    /*
    ===========================================================
                        PLAYABLE SUDOKU
    ===========================================================
    */
    void sudoku()
    {

        ifstream file("assets/sudoku_questions.txt");

        if (!file)
        {

            cout << "\nSudoku file not found.\n";
            return;
        }

        vector<string> puzzles;

        string line;

        while (getline(file, line))
        {

            if (!line.empty())
                puzzles.push_back(line);
        }

        int totalPuzzles = puzzles.size() / 9;

        if (totalPuzzles == 0)
        {

            cout << "\nNo Sudoku puzzles found.\n";
            return;
        }

        int randomPuzzle = rand() % totalPuzzles;

        int startIndex = randomPuzzle * 9;

        int board[9][9];

        /*
        Load Puzzle
        */
        for (int i = 0; i < 9; i++)
        {

            string row = puzzles[startIndex + i];

            for (int j = 0; j < 9; j++)
            {

                board[i][j] = row[j] - '0';
            }
        }

        /*
        Original board save
        taaki fixed cells edit na ho
        */
        int original[9][9];

        for (int i = 0; i < 9; i++)
        {

            for (int j = 0; j < 9; j++)
            {

                original[i][j] = board[i][j];
            }
        }

        cout << "\n=========== SUDOKU ===========\n";

        while (true)
        {

            printSudoku(board);

            /*
            Win Check
            */
            if (sudokuComplete(board))
            {

                cout << "\n🎉 Sudoku Completed!\n";
                return;
            }

            cout << "\nEnter Row (1-9)";
            cout << " OR -1 to Quit: ";

            int row = getIntegerInput();

            /*
            Quit to main menu
            */
            if (row == -1)
            {

                cout << "\nReturning to Main Menu...\n";
                return;
            }

            cout << "Enter Column (1-9): ";
            int col = getIntegerInput();

            cout << "Enter Number (1-9): ";
            int num = getIntegerInput();

            /*
            Range Validation
            */
            if (row < 1 || row > 9 ||
                col < 1 || col > 9 ||
                num < 1 || num > 9)
            {

                cout << "\nInvalid Input.\n";
                continue;
            }

            row--;
            col--;


            /*
            Fixed Cell Check
            */
            if (original[row][col] != 0)
            {

                cout << "\nCannot edit fixed cells.\n";
                continue;
            }

            /*
            Temporarily clear current cell
            */
            board[row][col] = 0;

            /*
            Sudoku rule validation
            */
           board[row][col] = 0;
            if (isValidSudokuMove(
                    board,
                    row,
                    col,
                    num))
            {

                board[row][col] = num;

                cout << "\n✅ Number Added.\n";
            }
            else
            {

                cout << "\n❌ Invalid Sudoku Move.\n";
            }
        }
    }
    /*
    =======================================================
                    TIC TAC TOE
    =======================================================
    */
    void ticTacToe()
    {

        char board[3][3] = {

            {'1', '2', '3'},
            {'4', '5', '6'},
            {'7', '8', '9'}};

        char currentPlayer = 'X';

        int turns = 0;

        while (turns < 9)
        {

            cout << "\n======= TIC TAC TOE =======\n\n";

            printBoard(board);

            cout << "\nPlayer "
                 << currentPlayer
                 << " choose position (1-9): ";

            int move = getIntegerInput();

            if (move < 1 || move > 9)
            {

                cout << "\nInvalid position.\n";
                continue;
            }

            int row = (move - 1) / 3;
            int col = (move - 1) % 3;

            /*
            Already occupied?
            */
            if (board[row][col] == 'X' ||
                board[row][col] == 'O')
            {

                cout << "\nPosition already occupied.\n";
                continue;
            }

            board[row][col] = currentPlayer;

            if (checkWinner(board, currentPlayer))
            {

                cout << "\n";
                printBoard(board);

                cout << "\nPlayer "
                     << currentPlayer
                     << " Wins!\n";

                return;
            }

            /*
            Switch Player
            */
            currentPlayer =
                (currentPlayer == 'X') ? 'O' : 'X';

            turns++;
        }

        cout << "\nMatch Draw!\n";
    }

    /*
    =======================================================
                        PRINT BOARD
    =======================================================
    */
    void printBoard(char board[3][3])
    {

        for (int i = 0; i < 3; i++)
        {

            for (int j = 0; j < 3; j++)
            {

                cout << board[i][j];

                if (j != 2)
                    cout << " | ";
            }

            cout << endl;

            if (i != 2)
                cout << "--+---+--\n";
        }
    }

    /*
    =======================================================
                        CHECK WINNER
    =======================================================
    */
    bool checkWinner(char board[3][3], char player)
    {

        /*
        Rows + Columns
        */
        for (int i = 0; i < 3; i++)
        {

            if (board[i][0] == player &&
                board[i][1] == player &&
                board[i][2] == player)
                return true;

            if (board[0][i] == player &&
                board[1][i] == player &&
                board[2][i] == player)
                return true;
        }

        /*
        Diagonals
        */
        if (board[0][0] == player &&
            board[1][1] == player &&
            board[2][2] == player)
            return true;

        if (board[0][2] == player &&
            board[1][1] == player &&
            board[2][0] == player)
            return true;

        return false;
    }

    /*
    =======================================================
                        HANGMAN
    =======================================================
    */
    void hangman()
    {

        ifstream file("assets/words.txt");

        if (!file)
        {

            cout << "\nWords file not found.\n";
            return;
        }

        vector<string> words;

        string word;

        while (file >> word)
        {

            words.push_back(word);
        }

        if (words.empty())
        {

            cout << "\nNo words found.\n";
            return;
        }

        string secret =
            words[rand() % words.size()];

        transform(
            secret.begin(),
            secret.end(),
            secret.begin(),
            ::tolower);

        string guessed(secret.length(), '_');

        vector<char> usedLetters;

        int attempts = 6;

        while (attempts > 0 &&
               guessed != secret)
        {

            cout << "\n======= HANGMAN =======\n";

            cout << "\nWord: " << guessed << endl;

            cout << "Attempts Left: "
                 << attempts
                 << endl;

            cout << "Used Letters: ";

            for (char c : usedLetters)
                cout << c << " ";

            cout << "\n\nEnter Letter: ";

            char guess;
            cin >> guess;

            guess = tolower(guess);

            /*
            Repeated check
            */
            if (find(
                    usedLetters.begin(),
                    usedLetters.end(),
                    guess) != usedLetters.end())
            {

                cout << "\nAlready guessed.\n";
                continue;
            }

            usedLetters.push_back(guess);

            bool found = false;

            for (int i = 0; i < secret.length(); i++)
            {

                if (secret[i] == guess)
                {

                    guessed[i] = guess;
                    found = true;
                }
            }

            if (found)
            {

                cout << "\nCorrect Guess!\n";
            }
            else
            {

                attempts--;

                cout << "\nWrong Guess!\n";
            }
        }

        if (guessed == secret)
        {

            cout << "\n🎉 YOU WON!\n";
        }
        else
        {

            cout << "\n💀 YOU LOST!\n";
        }

        cout << "Correct Word: "
             << secret
             << endl;
    }

    /*
    =======================================================
                        MATH QUIZ
    =======================================================
    */
    void mathQuiz()
    {

        ifstream file("assets/math_questions.txt");

        if (!file)
        {

            cout << "\nMath file not found.\n";
            return;
        }

        string question;
        string answerLine;

        int score = 0;

        int totalQuestions = 0;

        cout << "\n========== MATH QUIZ ==========\n";

        cout << "Enter 1 anytime to quit.\n";

        while (getline(file, question))
        {

            if (question.empty())
                continue;

            if (!getline(file, answerLine))
                break;

            int correctAnswer;

            try
            {

                correctAnswer = stoi(answerLine);
            }
            catch (...)
            {

                continue;
            }

            cout << "\nQuestion: "
                 << question
                 << endl;

            cout << "Answer: ";

            int userAnswer =
                getIntegerInput();

            /*
            Quit Condition
            */
            if (userAnswer == 1)
            {

                cout << "\nReturning to Main Menu...\n";
                return;
            }

            totalQuestions++;

            if (userAnswer == correctAnswer)
            {

                cout << "✅ Correct!\n";

                score++;
            }
            else
            {

                cout << "❌ Wrong!\n";

                cout << "Correct Answer: "
                     << correctAnswer
                     << endl;
            }
        }

        cout << "\n=========== RESULT ===========\n";

        cout << "Score: "
             << score
             << "/"
             << totalQuestions
             << endl;
    }

    /*
    =======================================================
                    NUMBER GUESSING
    =======================================================
    */
    void numberGuess()
    {

        int secret = rand() % 100 + 1;

        int guess;

        int attempts = 0;

        cout << "\n====== NUMBER GUESSING ======\n";

        cout << "Guess Number Between 1-100\n";

        do
        {

            cout << "\nEnter Guess: ";

            guess = getIntegerInput();

            attempts++;

            if (guess > secret)
            {

                cout << "Too High!\n";
            }
            else if (guess < secret)
            {

                cout << "Too Low!\n";
            }
            else
            {

                cout << "\n🎯 Correct Guess!\n";

                cout << "Attempts: "
                     << attempts
                     << endl;
            }

        } while (guess != secret);
    }
};

/*
===========================================================
                        MAIN FUNCTION
===========================================================
*/

int main()
{

    LogicQuest game;

    game.menu();

    return 0;
}