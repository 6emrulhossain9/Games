#include <iostream>
#include <cmath>
using namespace std;

class Sudoku
{
private:
    int grid[9][9];

public:
    Sudoku()
    {
        int initial[9][9] = {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}};

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                grid[i][j] = initial[i][j];
            }
        }
    }

    void displayGrid()
    {
        cout << "Current Sudoku Grid:" << endl;
        for (int i = 0; i < 9; i++)
        {
            if (i % 3 == 0)
            {
                cout << "+-------+-------+-------+" << endl;
            }
            for (int j = 0; j < 9; j++)
            {
                if (j % 3 == 0)
                {
                    cout << "| ";
                }
                if (grid[i][j] == 0)
                {
                    cout << ". ";
                }
                else
                {
                    cout << grid[i][j] << " ";
                }
            }
            cout << "|" << endl;
        }
        cout << "+-------+-------+-------+" << endl;
    }

    bool isValid(int row, int col, int num)
    {

        for (int i = 0; i < 9; i++)
        {
            if (grid[row][i] == num)
            {
                return false;
            }
        }

        for (int i = 0; i < 9; i++)
        {
            if (grid[i][col] == num)
            {
                return false;
            }
        }

        int startRow = row / 3 * 3;
        int startCol = col / 3 * 3;
        for (int i = startRow; i < startRow + 3; i++)
        {
            for (int j = startCol; j < startCol + 3; j++)
            {
                if (grid[i][j] == num)
                {
                    return false;
                }
            }
        }

        return true;
    }

    bool placeNumber(int row, int col, int num)
    {
        if (row < 0 || row >= 9 || col < 0 || col >= 9 || num < 1 || num > 9)
        {
            cout << "Invalid input! Row, column, and number must be between 1 and 9." << endl;
            return false;
        }
        if (grid[row][col] != 0)
        {
            cout << "Cell already filled! Please choose an empty cell." << endl;
            return false;
        }
        if (isValid(row, col, num))
        {
            grid[row][col] = num;
            return true;
        }
        else
        {
            cout << "Number cannot be placed here! It violates Sudoku rules." << endl;
            return false;
        }
    }

    bool isSolved()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (grid[i][j] == 0)
                {
                    return false;
                }
            }
        }
        return true;
    }
};

int main()
{
    Sudoku game;
    int row, col, num;

    cout << "Welcome to Sudoku!" << endl;

    while (!game.isSolved())
    {
        game.displayGrid();
        cout << "Enter row (1-9), column (1-9), and number (1-9) to place (enter 0 to quit): ";
        cin >> row;
        if (row == 0)
        {
            cout << "Exiting the game..." << endl;
            break;
        }
        cin >> col >> num;

        if (game.placeNumber(row - 1, col - 1, num))
        {
            cout << "Number placed successfully!" << endl;
        }
        else
        {
            cout << "Please try again!" << endl;
        }
    }

    if (game.isSolved())
    {
        cout << "Congratulations! You solved the Sudoku!" << endl;
    }

    return 0;
}
