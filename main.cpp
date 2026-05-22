#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

/*
===========================================================
                    LOGIC QUEST
===========================================================

Is project me 5 games hain:

1. Sudoku
2. Tic Tac Toe
3. Hangman
4. Math Quiz
5. Number Guessing

IMPORTANT BUG FIXES:
--------------------
1. srand() ko constructor me ek hi baar call kiya
2. TicTacToe me invalid input handling add ki
3. system("clear") remove kiya
4. MathQuiz file reading fix ki
5. Hangman repeated guesses handle kiye
6. Sudoku random loading stable kiya

===========================================================
*/

class LogicQuest {

private:

    /*
    -------------------------------------------------------
    Constructor style initialization

    Yeh ek baar object create hone pe execute hoga.
    Random seed yahin set karna best practice hai.
    -------------------------------------------------------
    */
    int totalSudokuPuzzles = 5;

public:

    /*
    -------------------------------------------------------
    Constructor
    -------------------------------------------------------
    */
    LogicQuest() {

        // Random seed initialize
        srand(time(0));
    }

    /*
    =======================================================
                        MAIN MENU
    =======================================================

    Yeh pura game hub hai.

    User jo option choose karega
    uske according game launch hoga.
    */
    void menu() {

        int choice;

        do {

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
            cin >> choice;

            /*
            Agar user galat input de
            example:
            abc

            toh cin fail state me chala jata hai.
            */
            if(cin.fail()) {

                cin.clear();
                cin.ignore(1000, '\n');

                cout << "\nInvalid Input.\n";
                continue;
            }

            switch(choice) {

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
                    cout << "\nExiting Game...\n";
                    break;

                default:
                    cout << "\nInvalid Option.\n";
            }

        } while(choice != 6);
    }

    /*
    =======================================================
                        SUDOKU
    =======================================================

    Yeh function:
    1. File kholta hai
    2. Random Sudoku choose karta hai
    3. Sudoku print karta hai
    */
    void sudoku() {

        ifstream file("assets/sudoku_questions.txt");

        if(!file) {

            cout << "\nSudoku file not found.\n";
            return;
        }

        vector<string> puzzles;

        string line;

        /*
        File ki sari non-empty lines vector me store
        */
        while(getline(file, line)) {

            if(!line.empty())
                puzzles.push_back(line);
        }

        /*
        Random puzzle choose karna

        Har puzzle:
        9 rows ka hai
        */
        int randomPuzzle = rand() % totalSudokuPuzzles;

        int startIndex = randomPuzzle * 9;

        cout << "\n============= SUDOKU =============\n";

        for(int i = 0; i < 9; i++) {

            string row = puzzles[startIndex + i];

            for(char c : row) {

                /*
                Sudoku me 0 ka matlab:
                empty space
                */
                if(c == '0')
                    cout << ". ";
                else
                    cout << c << " ";
            }

            cout << endl;
        }

        cout << "\nSudoku Solver Future Update me ayega.\n";
    }

    /*
    =======================================================
                    TIC TAC TOE
    =======================================================

    3x3 board game

    Players:
    X
    O
    */
    void ticTacToe() {

        /*
        Board initialize

        Initially numbers store kar rahe hain
        taaki player easily choose kare.
        */
        char board[3][3] = {

            {'1','2','3'},
            {'4','5','6'},
            {'7','8','9'}
        };

        char currentPlayer = 'X';

        int turns = 0;

        while(turns < 9) {

            cout << "\n======= TIC TAC TOE =======\n\n";

            /*
            Board print
            */
            for(int i = 0; i < 3; i++) {

                for(int j = 0; j < 3; j++) {

                    cout << board[i][j] << " ";
                }

                cout << endl;
            }

            int move;

            cout << "\nPlayer "
                 << currentPlayer
                 << " choose position: ";

            cin >> move;

            /*
            Invalid move range check
            */
            if(move < 1 || move > 9) {

                cout << "\nMove should be between 1-9\n";
                continue;
            }

            /*
            Position ko row/column me convert
            */
            int row = (move - 1) / 3;
            int col = (move - 1) % 3;

            /*
            Check if already occupied
            */
            if(board[row][col] == 'X' ||
               board[row][col] == 'O') {

                cout << "\nPosition already occupied.\n";
                continue;
            }

            /*
            Move place karna
            */
            board[row][col] = currentPlayer;

            /*
            WIN CHECK
            */
            if(checkWinner(board, currentPlayer)) {

                cout << "\n";

                for(int i = 0; i < 3; i++) {

                    for(int j = 0; j < 3; j++) {

                        cout << board[i][j] << " ";
                    }

                    cout << endl;
                }

                cout << "\nPlayer "
                     << currentPlayer
                     << " Wins!\n";

                return;
            }

            /*
            Player switch
            */
            if(currentPlayer == 'X')
                currentPlayer = 'O';
            else
                currentPlayer = 'X';

            turns++;
        }

        cout << "\nMatch Draw!\n";
    }

    /*
    =======================================================
                    CHECK WINNER
    =======================================================

    TicTacToe me winner detect karta hai.
    */
    bool checkWinner(char board[3][3], char player) {

        /*
        Rows and Columns check
        */
        for(int i = 0; i < 3; i++) {

            // Row check
            if(board[i][0] == player &&
               board[i][1] == player &&
               board[i][2] == player)
                return true;

            // Column check
            if(board[0][i] == player &&
               board[1][i] == player &&
               board[2][i] == player)
                return true;
        }

        /*
        Diagonal checks
        */
        if(board[0][0] == player &&
           board[1][1] == player &&
           board[2][2] == player)
            return true;

        if(board[0][2] == player &&
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
    void hangman() {

        ifstream file("assets/words.txt");

        if(!file) {

            cout << "\nWords file not found.\n";
            return;
        }

        vector<string> words;

        string word;

        while(file >> word)
            words.push_back(word);

        /*
        Random word choose
        */
        string secret = words[rand() % words.size()];

        /*
        Example:

        secret = apple

        guessed = _____
        */
        string guessed(secret.length(), '_');

        int attempts = 6;

        vector<char> usedLetters;

        while(attempts > 0 &&
              guessed != secret) {

            cout << "\nWord: " << guessed << endl;

            cout << "Attempts Left: "
                 << attempts
                 << endl;

            char guess;

            cout << "Enter Letter: ";
            cin >> guess;

            /*
            Check repeated guess
            */
            bool alreadyUsed = false;

            for(char c : usedLetters) {

                if(c == guess) {

                    alreadyUsed = true;
                    break;
                }
            }

            if(alreadyUsed) {

                cout << "\nAlready guessed.\n";
                continue;
            }

            usedLetters.push_back(guess);

            bool found = false;

            /*
            Letter search
            */
            for(int i = 0; i < secret.length(); i++) {

                if(secret[i] == guess) {

                    guessed[i] = guess;
                    found = true;
                }
            }

            if(!found) {

                attempts--;

                cout << "\nWrong Guess!\n";
            }
        }

        if(guessed == secret)
            cout << "\nYou Won!\n";
        else
            cout << "\nYou Lost!\n";

        cout << "Correct Word: "
             << secret
             << endl;
    }

    /*
    =======================================================
                        MATH QUIZ
    =======================================================

    FILE FORMAT:

    5 + 7
    12

    9 * 6
    54
    */
    void mathQuiz() {

        ifstream file("assets/math_questions.txt");

        if(!file) {

            cout << "\nMath file not found.\n";
            return;
        }

        string question;
        string answerLine;

        int score = 0;

        cout << "\n========== MATH QUIZ ==========\n";

        /*
        Ek question
        + ek answer
        */
        while(getline(file, question)) {

            if(question.empty())
                continue;

            getline(file, answerLine);

            int correctAnswer = stoi(answerLine);

            int userAnswer;

            cout << "\nQuestion: "
                 << question
                 << endl;

            cout << "Answer: ";
            cin >> userAnswer;

            if(userAnswer == correctAnswer) {

                cout << "Correct!\n";

                score++;
            }
            else {

                cout << "Wrong!\n";

                cout << "Correct Answer: "
                     << correctAnswer
                     << endl;
            }
        }

        cout << "\nFinal Score: "
             << score
             << endl;
    }

    /*
    =======================================================
                    NUMBER GUESSING
    =======================================================
    */
    void numberGuess() {

        /*
        Random secret number
        */
        int secret = rand() % 100 + 1;

        int guess;

        int attempts = 0;

        cout << "\n====== NUMBER GUESSING ======\n";

        cout << "Guess Number Between 1-100\n";

        do {

            cout << "\nEnter Guess: ";
            cin >> guess;

            attempts++;

            if(guess > secret)
                cout << "Too High!\n";

            else if(guess < secret)
                cout << "Too Low!\n";

            else {

                cout << "\nCorrect Guess!\n";

                cout << "Total Attempts: "
                     << attempts
                     << endl;
            }

        } while(guess != secret);
    }
};

/*
===========================================================
                        MAIN FUNCTION
===========================================================

Program execution yahin se start hota hai.
*/
int main() {

    LogicQuest game;

    game.menu();

    return 0;
}