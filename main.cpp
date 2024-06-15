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

// #include "Snake.hpp"
// #include "Board.hpp"
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
          char drawChar = isSnake ? game.getSnake().getBodyMark() : vacantCell;
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

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

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
