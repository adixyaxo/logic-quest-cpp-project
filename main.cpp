#include <iostream>
#include <cstdio>

using namespace std;

class sudoku
{
private:
    int s_vec[9][9] = {
        {0, 7, 0, 0, 9, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 8, 0, 0, 1},
        {0, 0, 0, 2, 0, 0, 0, 5, 0},
        {0, 0, 1, 0, 0, 0, 7, 0, 0},
        {0, 0, 0, 4, 0, 1, 0, 0, 0},
        {0, 0, 9, 0, 0, 0, 3, 0, 0},
        {0, 8, 0, 0, 0, 6, 0, 0, 0},
        {6, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 2, 0, 8, 0, 0, 4, 0}
    };

public:
    sudoku(FILE *file);
    ~sudoku();

    void print_sudoku()
    {
        cout << "-------------------------\n";

        for (int i = 0; i < 9; i++)
        {
            cout << "| ";

            for (int j = 0; j < 9; j++)
            {
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

sudoku::sudoku(FILE *file)
{
    if (file == NULL)
    {
        cout << "No file loaded.\n";
    }
    else
    {
        char buffer[100];

        fgets(buffer, sizeof(buffer), file);

        cout << buffer << endl;

        fclose(file);
    }
}

sudoku::~sudoku()
{
    cout << "Sudoku object destroyed.\n";
}

int main()
{
    FILE *file = NULL;

    sudoku a(file);

    a.print_sudoku();

    return 0;
}