#include <cstdio>
#include <iostream>
#include <random>
#include <fstream>


using namespace std;

// with this effect i will be able to write the comments in the code

class sudoku {
private:
  int s_vec[9][9] = {{0, 7, 0, 0, 9, 0, 2, 0, 0}, {0, 0, 0, 0, 0, 8, 0, 0, 1},
                     {0, 0, 0, 2, 0, 0, 0, 5, 0}, {0, 0, 1, 0, 0, 0, 7, 0, 0},
                     {0, 0, 0, 4, 0, 1, 0, 0, 0}, {0, 0, 9, 0, 0, 0, 3, 0, 0},
                     {0, 8, 0, 0, 0, 6, 0, 0, 0}, {6, 0, 0, 1, 0, 0, 0, 0, 0},
                     {0, 0, 2, 0, 8, 0, 0, 4, 0}};

public:
  sudoku(FILE *file);
  ~sudoku();

  void print_sudoku() {
    cout << "-------------------------\n";

    for (int i = 0; i < 9; i++) {
      cout << "| ";

      for (int j = 0; j < 9; j++) {
        cout << s_vec[i][j] << " ";

        // vertical section divider
        if ((j + 1) % 3 == 0)
          cout << "| ";
      }

      cout << endl;

      // horizontal section divider
      if ((i + 1) % 3 == 0)
        cout << "-------------------------\n";
    }
  }

  void get_sudoku();
};

sudoku::sudoku(FILE *file) {
  if (file == NULL) {
    cout << "No file loaded.\n";
  } else {
    char buffer[100];

    fgets(buffer, sizeof(buffer), file);

    cout << buffer << endl;

    fclose(file);
  }
}

sudoku::~sudoku() { cout << "Sudoku object destroyed.\n"; }

void sudoku::get_sudoku(){

  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(1,20);
  int sudoku_roll = distribution(generator); // generates a number in range 1 , 20
  // we know every sudoku starts at 10*n+1 index so we will read the sudoku from 10*n+1th row

  try
  {
    ifstream file("sudoku_sample.txt");

    string line;
    int targetRow = sudoku_roll;
    int currentRow = 0;

    while (getline(file, line)) {

        if (currentRow >= targetRow && currentRow<targetRow+10) {
            // we will assign all the elements to the sudoku
                char buffer[1];

                cout << buffer << endl;
            currentRow++;
            continue;
        }
        currentRow++;
    }

    file.close();

  }
  catch(const std::exception& e)
  {
    cout << "Couldnt open the Sudoku Questions due to and error incountered in opening the text file!!!!\n";
    std::cerr << e.what() << '\n'<<endl;
  }



}









// This is the main function of the code
int main() {



  FILE *file = NULL;

  sudoku a(file);

  a.print_sudoku();

  return 0;
}
