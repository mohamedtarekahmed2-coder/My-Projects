#include <iostream>
#include <random>
#include <string>
using namespace std;

enum class Choice
{
    Rock = 1,
    Paper,
    Scissors
};

enum class RoundResult
{
    Draw,
    User_Win,
    Computer_Win
};

void show_welcome_message()
{
    cout << "======================================\n";
    cout << "         Welcome to my first game     \n";
    cout << "            Rock Paper Scissors       \n";
    cout << "======================================\n";
    cout << "     The first one get 5 will win!    \n";
    cout << "======================================\n";
}

int get_computer_choice()
{
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> distrib(1, 3);
    return distrib(gen);
}

string choice_to_string(int choice)
{
    switch (static_cast<Choice>(choice))
    {
    case Choice::Rock:
        return "Rock";
    case Choice::Paper:
        return "Paper";
    case Choice::Scissors:
        return "Scissors";
    default:
        return "Unknown";
    }
}

RoundResult round_winner(int user, int com)
{
    if (user == com) return RoundResult::Draw;
    else if (((user == static_cast<int>(Choice::Rock)) && (com == static_cast<int>(Choice::Scissors)))
         ||  ((user == static_cast<int>(Choice::Paper)) && (com == static_cast<int>(Choice::Rock))) 
         ||  ((user == static_cast<int>(Choice::Scissors)) && (com == static_cast<int>(Choice::Paper)))) 
            return RoundResult::User_Win;
    else
        return RoundResult::Computer_Win;
}

void play_round(int &user_score, int &computer_score)
{
    int user_choice;
    cout << "======================================\n";
    cout << "Rock[1] or Paper[2] or Scissors[3] : ";
    cin >> user_choice; 
    
    if (user_choice != 1 && user_choice != 2 && user_choice != 3)
    {
        cout << "Invalid choice! Please enter 1, 2, or 3.\n";
        return;
    }

    int computer_choice = get_computer_choice();
    cout << "You : " << choice_to_string(user_choice) << " , Com : " << choice_to_string(computer_choice) << '\n';

    RoundResult result = round_winner(user_choice, computer_choice);

    if (result == RoundResult::Draw)
    {
        cout << "No Win (Draw)\n";
    }
    else if (result == RoundResult::User_Win)
    {
        cout << "You Win this round!\n";
        user_score++;
    }
    else
    {
        cout << "Com Win this round!\n";
        computer_score++;
    }

    cout << "Your Score : " << user_score << " , Com Score : " << computer_score << '\n';
}

int main()
{
    show_welcome_message();

    char play_again = 'y';
    while (play_again == 'y' || play_again == 'Y')
    {
        int user_score = 0;
        int computer_score = 0;

        while (user_score < 5 && computer_score < 5)
        {
            play_round(user_score, computer_score);
        }

        cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";
        if (user_score == 5)
            cout << "CONGRATULATIONS! You Win the whole game! \n";
        else
            cout << "GAME OVER! Computer Wins the whole game! \n";
        cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";

        cout << "\nPlay again ? [y,n] ";
        cin >> play_again;
    }

    cout << "Thank you for playing!\n";
    return 0;
}