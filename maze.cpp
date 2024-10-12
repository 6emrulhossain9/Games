#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Maze
{
private:
    vector<vector<char>> grid;
    pair<int, int> playerPosition;
    pair<int, int> exitPosition;
    int score;
    int lives;
    int collectiblesNeeded;
    vector<pair<int, int>> enemies;

    void placeCollectibles(int count)
    {
        for (int i = 0; i < count; ++i)
        {
            int x, y;
            do
            {
                x = rand() % (grid.size() - 2) + 1;
                y = rand() % (grid[0].size() - 2) + 1;
            } while (grid[x][y] != ' ');
            grid[x][y] = 'C';
        }
    }

    void moveEnemies()
    {
        for (auto &enemy : enemies)
        {
            int direction = rand() % 4;
            int newX = enemy.first, newY = enemy.second;

            switch (direction)
            {
            case 0:
                newX--;
                break;
            case 1:
                newX++;
                break;
            case 2:
                newY--;
                break;
            case 3:
                newY++;
                break;
            }

            if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size() && grid[newX][newY] != '#')
            {

                grid[enemy.first][enemy.second] = ' ';
                enemy.first = newX;
                enemy.second = newY;
                grid[newX][newY] = 'E';
            }
        }
    }

public:
    Maze(int level)
    {
        score = 0;
        lives = 3;
        collectiblesNeeded = 3;
        srand(static_cast<unsigned>(time(0)));

        grid = {
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', '@', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#'},
            {'#', ' ', '#', ' ', ' ', ' ', '#', 'C', ' ', '#'},
            {'#', ' ', '#', '#', '#', ' ', '#', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#'},
            {'#', '#', '#', ' ', '#', '#', '#', ' ', 'C', '#'},
            {'#', 'C', ' ', ' ', ' ', ' ', ' ', 'E', ' ', '#'},
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}};

        playerPosition = {1, 1};
        exitPosition = {7, 7};

        enemies.push_back({3, 3});
        enemies.push_back({6, 3});

        placeCollectibles(collectiblesNeeded);
    }

    void displayMaze()
    {
        system("clear");
        for (const auto &row : grid)
        {
            for (char cell : row)
            {
                cout << cell << " ";
            }
            cout << endl;
        }
        cout << "Score: " << score << " | Lives: " << lives << " | Collectibles needed: " << collectiblesNeeded << endl;
    }

    bool movePlayer(char direction)
    {

        int x = playerPosition.first;
        int y = playerPosition.second;

        int newX = x, newY = y;
        switch (direction)
        {
        case 'w':
            newX--;
            break;
        case 's':
            newX++;
            break;
        case 'a':
            newY--;
            break;
        case 'd':
            newY++;
            break;
        default:
            return false;
        }

        if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size() && grid[newX][newY] != '#')
        {

            if (grid[newX][newY] == 'C')
            {
                score += 10;
                collectiblesNeeded--;
                cout << "You collected a collectible! Score increased.\n";
            }

            for (const auto &enemy : enemies)
            {
                if (enemy.first == newX && enemy.second == newY)
                {
                    lives--;
                    cout << "You were caught by an enemy! Lives left: " << lives << endl;
                    if (lives <= 0)
                    {
                        return false;
                    }
                }
            }

            grid[x][y] = ' ';
            grid[newX][newY] = 'P';

            playerPosition = {newX, newY};

            moveEnemies();

            return true;
        }
        else
        {
            return false;
        }
    }

    bool isGameOver() const
    {
        return playerPosition == exitPosition && collectiblesNeeded <= 0;
    }

    int getLives() const
    {
        return lives;
    }
};

int main()
{
    int level = 1;
    Maze maze(level);
    char move;

    cout << "\n--- Welcome to the Complex Maze Game ---\n";
    cout << "Instructions: Use 'w' (up), 's' (down), 'a' (left), and 'd' (right) to move.\n";

    while (!maze.isGameOver() && maze.getLives() > 0)
    {
        maze.displayMaze();

        cout << "Enter your move: ";
        cin >> move;

        if (maze.movePlayer(move))
        {
            cout << "Move successful!\n";
        }
        else
        {
            cout << "Invalid move! You hit a wall or were caught by an enemy.\n";
        }

        cout << endl;
    }

    if (maze.isGameOver())
    {
        cout << "Congratulations! You collected all items and found the exit!\n";
    }
    else
    {
        cout << "Game over! You ran out of lives.\n";
    }

    return 0;
}
