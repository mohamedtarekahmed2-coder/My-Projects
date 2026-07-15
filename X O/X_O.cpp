#include <iostream>
#include <ctime>
#include <vector>
#include <limits>
using namespace std;

void print_board(const vector<char> &board)
{
    cout << " ";
    for (int i = 0; i < (int)board.size(); i++)
    {
        cout << board[i];
        if (i % 3 == 2 && i != 8)
            cout << "\n-----------\n ";
        else if (i != 8)
            cout << " | ";
    }
    cout << "\n\n";
}

vector<char> initialize_board()
{
    vector<char> board(9);
    for (int i = 0; i < 9; i++)
        board[i] = static_cast<char>(i + '1');
    return board;
}

char get_random_starting_player()
{
    return (rand() % 2 == 0) ? 'X' : 'O';
}

bool is_winner(const vector<char> &board)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i] == board[i + 3] && board[i] == board[i + 6])
            return true;
    }

    for (int i = 0; i < 9; i += 3)
    {
        if (board[i] == board[i + 1] && board[i] == board[i + 2])
            return true;
    }

    if (board[0] == board[4] && board[0] == board[8])
        return true;
    else if (board[2] == board[4] && board[2] == board[6])
        return true;

    return false;
}

bool is_board_full(const vector<char> &board)
{
    for (int i = 0; i < (int)board.size(); i++)
    {
        if (board[i] != 'X' && board[i] != 'O')
        {
            return false;
        }
    }
    return true;
}

bool empty_space(int space, const vector<char> &board)
{
    return board[space] != 'O' && board[space] != 'X';
}

int get_strategic_move(const vector<char> &board, char test)
{
    for (int i = 0; i < 9; i += 3)
    {
        if (board[i] == board[i + 1] && board[i] == test && empty_space(i + 2, board))
            return i + 2;
        else if (board[i] == board[i + 2] && board[i] == test && empty_space(i + 1, board))
            return i + 1;
        else if (board[i + 1] == board[i + 2] && board[i + 1] == test && empty_space(i, board))
            return i;
    }

    for (int i = 0; i < 3; i++)
    {
        if (board[i] == board[i + 3] && board[i] == test && empty_space(i + 6, board))
            return i + 6;
        else if (board[i] == board[i + 6] && board[i] == test && empty_space(i + 3, board))
            return i + 3;
        else if (board[i + 3] == board[i + 6] && board[i + 3] == test && empty_space(i, board))
            return i;
    }

    if (board[0] == board[4] && board[0] == test && empty_space(8, board))
        return 8;
    else if (board[0] == board[8] && board[0] == test && empty_space(4, board))
        return 4;
    else if (board[4] == board[8] && board[4] == test && empty_space(0, board))
        return 0;

    if (board[2] == board[4] && board[2] == test && empty_space(6, board))
        return 6;
    else if (board[2] == board[6] && board[2] == test && empty_space(4, board))
        return 4;
    else if (board[4] == board[6] && board[4] == test && empty_space(2, board))
        return 2;

    return -1;
}

int computer_choice(const vector<char> &board)
{
    int choice = get_strategic_move(board, 'O');
    if (choice != -1)
        return choice;

    choice = get_strategic_move(board, 'X');
    if (choice != -1)
        return choice;

    while (true)
    {
        choice = rand() % 9;
        if (board[choice] != 'X' && board[choice] != 'O')
            return choice;
    }
}

char player_computer()
{
    vector<char> board = initialize_board();
    char user = 'X';
    char computer = 'O';

    char current_player;
    if (get_random_starting_player() == 'X')
        current_player = user;
    else
        current_player = computer;

    int num;
    while (!is_board_full(board))
    {
        if (current_player == computer)
        {
            board[computer_choice(board)] = 'O';
        }
        else
        {
            print_board(board);
            cout << "Player " << current_player << ", enter your choice (1-9): ";

            if (!(cin >> num))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                system("cls");
                cout << "=========== Invalid Input! Please enter a number. ===========\n";
                continue;
            }

            if (num < 1 || 9 < num || board[num - 1] == 'O' || board[num - 1] == 'X')
            {
                system("cls");
                cout << "=========== Invalid or taken slot! Choose again. ===========\n";
                continue;
            }

            board[num - 1] = current_player;
        }

        if (is_winner(board))
        {
            system("cls");
            print_board(board);
            return current_player;
        }

        current_player = (current_player == 'X') ? 'O' : 'X';
        system("cls");
    }

    print_board(board);
    return 'N';
}

char two_players()
{
    vector<char> board = initialize_board();
    char current_player = get_random_starting_player();

    cout << "\nPlayer " << current_player << " will start\n";

    int num;
    for (int turn = 1; turn < 10; turn++)
    {
        print_board(board);
        cout << "Player " << current_player << ", enter your choice (1-9): ";

        if (!(cin >> num))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            system("cls");
            cout << "=========== Invalid Input! Please enter a number. ===========\n";
            turn--;
            continue;
        }

        if (num < 1 || 9 < num || board[num - 1] == 'O' || board[num - 1] == 'X')
        {
            system("cls");
            cout << "=========== Invalid or taken slot! Choose again. ===========\n";
            turn--;
            continue;
        }

        board[num - 1] = current_player;

        if (is_winner(board))
        {
            system("cls");
            print_board(board);
            return current_player;
        }

        current_player = (current_player == 'X') ? 'O' : 'X';
        system("cls");
    }

    print_board(board);
    return 'N';
}

void show_welcome_message()
{
    cout << "======================================\n";
    cout << "       Welcome to my second game      \n";
    cout << "                 X  O                 \n";
    cout << "======================================\n";
}

void player_vs_player()
{
    char winner = two_players();

    if (winner != 'N')
    {
        cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";
        cout << "CONGRATULATIONS! Player " << winner << " wins the game! \n";
        cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";
    }
    else
    {
        cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";
        cout << "               No Winner (Draw)              \n";
        cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";
    }
}

void player_vs_computer()
{
    char winner = player_computer();

    if (winner == 'X')
    {
        cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";
        cout << "CONGRATULATIONS! Player " << winner << " wins the game! \n";
        cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";
    }
    else if (winner == 'O')
    {
        cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";
        cout << "You are the loser, AI will take your place in the future. \n";
        cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";
    }
    else
    {
        cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";
        cout << "               No Winner (Draw)              \n";
        cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";
    }
}

int main()
{
    srand(time(0));
    show_welcome_message();

    char play_again = 'y';
    while (play_again == 'y' || play_again == 'Y')
    {
        cout << "(Player VS Player)[1] or (Player VS Computer)[2] ? [1,2] ";
        int choice;
        cin >> choice;

        if (choice == 1)
            player_vs_player();
        else
            player_vs_computer();

        cout << "\nPlay again ? [y,n] ";
        cin >> play_again;
        system("cls");
    }

    cout << "Thank you for playing!\n";
    return 0;
}