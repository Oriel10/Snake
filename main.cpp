#include <iostream>
#include <vector>
#include <assert.h>

#ifdef _WIN32
#include <conio.h>  // For _kbhit() and _getch() on Windows
#include <windows.h>  // For Sleep() on Windows
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#include "SnakeGame.hpp"

using namespace std;

void displayBoard(const SnakeGame& game, int dim) {
    std::cout << "+";
    for (int j = 0; j < dim; ++j) {
        std::cout << "---+";
    }
    std::cout << "\n";

    for (int i = 0; i < dim; ++i) {
        std::cout << "|";
        for (int j = 0; j < dim; ++j) {
          char vacantCell = ' ';
          Position currentPosition = {i, j};

          bool isSnake = game.getSnake().isSnakeAt(currentPosition);
          bool isFood = (game.getFoodPosition() == currentPosition);
          assert(!(isFood && isSnake));
          char drawChar = isSnake ? game.getSnake().getSnakeMark(currentPosition) : vacantCell;
          drawChar = isFood ? game.getFoodMark() : drawChar;

          std::cout << " " << drawChar << " |";
        }
        std::cout << "\n";
        
        std::cout << "+";
        for (int j = 0; j < dim; ++j) {
            std::cout << "---+";
        }
        std::cout << "\n";
    }
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

#ifdef __linux__
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    // Get the current terminal attributes and save them in oldt
    tcgetattr(STDIN_FILENO, &oldt);

    // Copy the old attributes to newt, which we will modify
    newt = oldt;

    // Disable canonical mode and echo mode
    newt.c_lflag &= ~(ICANON | ECHO);

    // Set the terminal attributes to the new values immediately
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Get the current file status flags for stdin and save them in oldf
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

    // Set the stdin file descriptor to non-blocking mode
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    // Read a character from stdin
    ch = getchar();

    // Restore the original terminal attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    // Restore the original file status flags for stdin
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    // Check if a character was read (i.e., not EOF)
    if (ch != EOF) {
        // If a character was read, push it back to stdin
        ungetc(ch, stdin);
        return 1; // Indicate that a key was hit
    }

    return 0; // Indicate that no key was hit
}

// Implements getchar, but without Canonical Mode, which requires to press 'Enter' to accept input,
// and without Echoing, which prints on the screen the character that was pressed.
int getch(void) {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

int main() {
    int boardDimension = 5;
    SnakeGame game(boardDimension);

    char input;
    while (true) {
        clearScreen();
        displayBoard(game, boardDimension);
        
        if (
#ifdef _WIN32
            _kbhit()
#else
            kbhit()
#endif
        ) {
            input = 
#ifdef _WIN32
                _getch();
#else
                getch();
#endif
            switch (input) {
                case 'w':
                    game.moveUp();
                    break;
                case 's':
                    game.moveDown();
                    break;
                case 'a':
                    game.moveLeft();
                    break;
                case 'd':
                    game.moveRight();
                    break;
                default:
                    cout << "Invalid input! Use w, a, s, d to move." << endl;
                    break;
            }
        }

#ifdef _WIN32
        Sleep(100);  // Sleep for 100 milliseconds
#else
        usleep(100000);  // Sleep for 100 milliseconds
#endif
    }

    return 0;
}
