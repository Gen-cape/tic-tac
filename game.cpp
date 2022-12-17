#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <conio.h>
#include <cstdlib>
#include <ctime>

const int BOARD_SIZE = 3;

// Function prototypes
void drawBoard(const std::vector<std::vector<char>>& board);
bool checkWin(const std::vector<std::vector<char>>& board, char player);
bool checkTie(const std::vector<std::vector<char>>& board);
void playerTurn(std::vector<std::vector<char>>& board, char player);
void aiTurn(std::vector<std::vector<char>>& board, char ai);
int randomNumber();

/**
 * @brief Main function, initializes the game board and starts the game loop
 * 
 * @return 0
*/
int main()
{
    srand(time(NULL));
    std::vector<std::vector<char>> board(BOARD_SIZE, std::vector<char>(BOARD_SIZE, ' '));

    // Select player and AI's signs randomly
    char player, ai;
    if (randomNumber() == 0)
    {
        player = 'X';
        ai = 'O';
    }
    else
    {
        player = 'O';
        ai = 'X';
        aiTurn(board, ai);
    }
    // Main game loop
    while (true)
    {
        drawBoard(board);

        playerTurn(board, player);

        if (checkWin(board, player))
        {
            std::cout << "Player wins!" << std::endl;
            break;
        }

        if (checkTie(board))
        {
            std::cout << "It's a tie!" << std::endl;
            break;
        }

        aiTurn(board, ai);

        if (checkWin(board, ai))
        {
            std::cout << "AI wins!" << std::endl;
            break;
        }

        if (checkTie(board))
        {
            std::cout << "It's a tie!" << std::endl;
            break;
        }
    }
    drawBoard(board);
    std::cout << "Press any key to continue..." << std::endl;
    getch();

    return 0;
}
// Debug
// // Draws the game board to the console
// void drawBoard(const std::vector<std::vector<char>>& board)
// {
//     std::cout << "  0 1 2" << std::endl;
//     for (int i = 0; i < BOARD_SIZE; i++)
//     {
//         std::cout << i << " ";
//         for (int j = 0; j < BOARD_SIZE; j++)
//         {
//             std::cout << board[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }
// }


/**
 * @brief Draws the game board to the console
 * 
 * @param board The game board
 * @return void
*/
void drawBoard(const std::vector<std::vector<char>>& board)
{
    std::cout << "  +---+---+---+" << std::endl;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        std::cout << "  |";
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            std::cout << " " << board[i][j] << " ";
            std::cout << "|";
        }
        std::cout << std::endl;
        if (i < BOARD_SIZE - 1)
        {
            std::cout << "  +---+---+---+" << std::endl;
        }
    }
    std::cout << "  +---+---+---+" << std::endl;
}

/**
 * @brief Checks if the requested sign has won
 * 
 * @param board The game board
 * @param player The requested player sign check
 * @return true If the reqested player sign has won, false otherwise
*/
bool checkWin(const std::vector<std::vector<char>>& board, char player)
{
    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
        {
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
        {
            return true;
        }
    }

    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
    {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
    {
        return true;
    }

    return false;
}

/**
 * @brief Checks if the game is a tie
 * 
 * @param board The game board
 * @return true If the game is a tie, false otherwise
*/
bool checkTie(const std::vector<std::vector<char>>& board)
{
    // Check if there are any empty spaces on the board
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                return false;
            }
        }
    }

    // If there are no empty spaces, the game is a tie
    return true;
}

/**
 * @brief Allows the player to make a move on the game board using the numpad layout
 * 
 * @param board The game board
 * @param player The player's sign
 * @return void
*/
void playerTurn(std::vector<std::vector<char>>& board, char player)
{
    int move;
    while (true)
    {
        std::cout << "Enter your move using the numpad layout: ";
        std::cin >> move;

        // Map numpad numbers to rows and columns
        int row, col;
        switch (move)
        {
            case 7:
                row = 0;
                col = 0;
                break;
            case 8:
                row = 0;
                col = 1;
                break;
            case 9:
                row = 0;
                col = 2;
                break;
            case 4:
                row = 1;
                col = 0;
                break;
            case 5:
                row = 1;
                col = 1;
                break;
            case 6:
                row = 1;
                col = 2;
                break;
            case 1:
                row = 2;
                col = 0;
                break;
            case 2:
                row = 2;
                col = 1;
                break;
            case 3:
                row = 2;
                col = 2;
                break;
            default:
                std::cout << "Invalid move, try again." << std::endl;
                continue;
        }

        if (board[row][col] != ' ')
        {
            std::cout << "Space already occupied, try again." << std::endl;
        }
        else
        {
            board[row][col] = player;
            break;
        }
    }
}

/**
 * @brief Prompts the AI to make a move and updates the board accordingly, Allows the AI to make a move on the game board
 * 
 * @param board The current state of the tic-tac-toe board.
 * @param ai The character representing the AI sign.
 * 
 * @return void
*/
void aiTurn(std::vector<std::vector<char>>& board, char ai)
{
    // Check for winning move
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = ai;
                if (checkWin(board, ai))
                {
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // Check for blocking move
    char player = (ai == 'X') ? 'O' : 'X';
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = player;
                if (checkWin(board, player))
                {
                    board[i][j] = ai;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // Check for fork
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = ai;
                int forkCount = 0;
                for (int k = 0; k < BOARD_SIZE; k++)
                {
                    for (int l = 0; l < BOARD_SIZE; l++)
                    {
                        if (board[k][l] == ' ')
                        {
                            board[k][l] = ai;
                            if (checkWin(board, ai))
                            {
                                forkCount++;
                            }
                            board[k][l] = ' ';
                        }
                    }
                }
                board[i][j] = ' ';
                if (forkCount >= 2)
                {
                    board[i][j] = ai;
                    return;
                }
            }
        }
    }

    // Block opponent's fork
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = player;
                int forkCount = 0;
                for (int k = 0; k < BOARD_SIZE; k++)
                {
                    for (int l = 0; l < BOARD_SIZE; l++)
                    {
                        if (board[k][l] == ' ')
                        {
                            board[k][l] = player;
                            if (checkWin(board, player))
                            {
                                forkCount++;
                            }
                            board[k][l] = ' ';
                        }
                    }
                }
                board[i][j] = ' ';
                if (forkCount == 1)
                {
                    board[i][j] = ai;
                    return;
                }
            }
        }
    }

    // Block all forks
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = player;
                int forkCount = 0;
                for (int k = 0; k < BOARD_SIZE; k++)
                {
                    for (int l = 0; l < BOARD_SIZE; l++)
                    {
                        if (board[k][l] == ' ')
                        {
                            board[k][l] = player;
                            if (checkWin(board, player))
                            {
                                forkCount++;
                            }
                            board[k][l] = ' ';
                        }
                    }
                }
                board[i][j] = ' ';
                if (forkCount > 0)
                {
                    board[i][j] = ai;
                    return;
                }
            }
        }
    }
    // Make two in a row
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = ai;
                int twoInARowCount = 0;
                for (int k = 0; k < BOARD_SIZE; k++)
                {
                    for (int l = 0; l < BOARD_SIZE; l++)
                    {
                        if (board[k][l] == ' ')
                        {
                            board[k][l] = ai;
                            if (checkWin(board, ai))
                            {
                                twoInARowCount++;
                            }
                            board[k][l] = ' ';
                        }
                    }
                }
                board[i][j] = ' ';
                if (twoInARowCount > 0)
                {
                    board[i][j] = ai;
                    return;
                }
            }
        }
    }
    // Play center
    if (board[1][1] == ' ')
    {
        board[1][1] = ai;
        return;
    }
    // Play opposite corner
    if (board[0][0] == player && board[2][2] == ' ')
    {
        board[2][2] = ai;
        return;
    }
    if (board[0][2] == player && board[2][0] == ' ')
    {
        board[2][0] = ai;
        return;
    }
    if (board[2][0] == player && board[0][2] == ' ')
    {
        board[0][2] = ai;
        return;
    }
    if (board[2][2] == player && board[0][0] == ' ')
    {
        board[0][0] = ai;
        return;
    }

    // Play empty corner
    if (board[0][0] == ' ')
    {
        board[0][0] = ai;
        return;
    }
    if (board[0][2] == ' ')
    {
        board[0][2] = ai;
        return;
    }
    if (board[2][0] == ' ')
    {
        board[2][0] = ai;
        return;
    }
    if (board[2][2] == ' ')
    {
        board[2][2] = ai;
        return;
    }

    // Play empty side
    if (board[0][1] == ' ')
    {
        board[0][1] = ai;
        return;
    }
    if (board[1][0] == ' ')
    {
        board[1][0] = ai;
        return;
    }
    if (board[1][2] == ' ')
    {
        board[1][2] = ai;
        return;
    }
    if (board[2][1] == ' ')
    {
        board[2][1] = ai;
        return;
    }
}
/*
// This function generates a random integer between
//  0 and 1 using the Mersenne Twister 19937 random number
//  generator and the uniform_int_distribution class from the C++ Standard Library
// int randomNumber()
// {
//     std::random_device device;
//     std::mt19937 generator(device());
//     std::uniform_int_distribution<int> distribution(0, 1);
//     return distribution(generator);
// }
// int randomNumber() {
//     // Seed the random number generator with the current time
//     srand(time(0));

//     // Generate a random number between 0 and RAND_MAX
//     int rn = rand();

//     // Return 0 if the random number is less than RAND_MAX / 2, and 1 otherwise
//     return (rn < RAND_MAX / 2) ? 0 : 1;
// }
*/
// BAD IDEA, NOT STABLE, better version if debugged seed properly
// REFORMED WITH UNIFORM TO FIX

/* This function generates a random integer between
 0 and 1 using the Mersenne Twister 19937 random number
 generator and the uniform_int_distribution class from the C++ Standard Library 
*/
/**
 * @brief This function generates a random integer between 0 and 1 using the Mersenne Twister 19937 random number generator and the uniform_int_distribution class from the C++ Standard Library
 * 
 * @return int
*/
int randomNumber() {
    // // Seed the random number generator with the current time
    std::mt19937 generator(time(0));

    // Generate a random number between 0 and 1
    std::uniform_int_distribution<int> distribution(0, 1);
    int randomNumber = distribution(generator);

    return randomNumber;
}