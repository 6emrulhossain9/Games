#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class RockPaperScissors
{
public:
    void playGame()
    {
        string userChoice;
        string computerChoice;

        cout << "Welcome to Rock, Paper, Scissors!" << endl;
        cout << "Choose one: rock, paper, or scissors: ";
        cin >> userChoice;

        computerChoice = getComputerChoice();

        cout << "Computer chose: " << computerChoice << endl;

        string result = determineWinner(userChoice, computerChoice);
        cout << result << endl;
    }

private:
    string getComputerChoice()
    {
        srand(time(0));
        int randomChoice = rand() % 3;

        switch (randomChoice)
        {
        case 0:
            return "rock";
        case 1:
            return "paper";
        case 2:
            return "scissors";
        default:
            return "";
        }
    }

    string determineWinner(string userChoice, string computerChoice)
    {
        if (userChoice == computerChoice)
        {
            return "It's a tie!";
        }
        else if ((userChoice == "rock" && computerChoice == "scissors") ||
                 (userChoice == "paper" && computerChoice == "rock") ||
                 (userChoice == "scissors" && computerChoice == "paper"))
        {
            return "You win!";
        }
        else
        {
            return "Computer wins!";
        }
    }
};

int main()
{
    RockPaperScissors game;
    game.playGame();
    return 0;
}
