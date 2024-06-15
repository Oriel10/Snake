#include <iostream>
#include <vector>
#include <unordered_map>
#include <deque>
#include <assert.h>

#ifdef _WIN32
#include <conio.h>  // For _kbhit() and _getch() on Windows
#include <windows.h>  // For Sleep() on Windows
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#define N (5)

using namespace std;

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1); // Combine the hash values
    }
};

void initializeBoard(vector<vector<char>>& board) {
    for(int i = 0; i < N; i++){
        vector<char> row(N, ' ');
        board.push_back(row);
    }
}

class Snake {
private:
    using Position = pair<int, int>;
    using Direction = pair<int, int>;
    using isLocated = bool;

    const char snakeBodyMark = '*';
    const Position initialPosition = {N/2, N/2};
    unordered_map<Position, isLocated, pair_hash> positionsSet;
    deque<Position> snakeBody;

public:
    Snake() {
        positionsSet[initialPosition] = true;
        snakeBody.push_front(initialPosition);
    }

    Position getHead() const {
        return snakeBody.front();
    }

    Position getTail() const {
        return snakeBody.back();
    }

    void deleteTail() {
        positionsSet.erase(getTail());
        snakeBody.pop_back();
    }

    void addHead(Position newHeadPosition) {
        snakeBody.push_front(newHeadPosition);
        positionsSet[newHeadPosition] = true;
    }

    void moveUp() {
        Direction up{-1,0};
        Move(up);
    }

    void moveDown() {
        Direction down{1,0};
        Move(down);
    }

    void moveRight() {
        Direction right{0,1};
        Move(right);
    }

    void moveLeft() {
        Direction left{0,-1};
        Move(left);
    }

    void Move(Direction d) {
        assert(d.first == 0 || d.second == 0);
        assert(d.first != 0 || d.second != 0);

        pair<int,int> newHeadPosition = {getHead().first + d.first, getHead().second + d.second};
        if(!checkLegitPosition(newHeadPosition)) {
            gameLost();
        }
        addHead(newHeadPosition);
        deleteTail();
    }

    void gameLost() {
        cout << "You lost!" << endl;
        cout << "Final Score: " << snakeBody.size() << endl;
        exit(0);
    }

    bool checkLegitPosition(Position headPosition) {
        int rowPosition = headPosition.first;
        int colPosition = headPosition.second;
        if(rowPosition < 0 || N <= rowPosition) {
            return false;
        }
        else if(colPosition < 0 || N <= colPosition) {
            return false;
        }
        else if(positionsSet.find({rowPosition, colPosition}) != positionsSet.end()) {
            return false;
        }
        return true;
    }

    bool isSnakeAt(int x, int y) const {
        return positionsSet.find({x, y}) != positionsSet.end();
    }

    char getBodyMark() const {
        return snakeBodyMark;
    }
};

void displayBoard(const std::vector<std::vector<char>>& board, const Snake& snake) {
    std::cout << "+";
    for (int j = 0; j < N; ++j) {
        std::cout << "---+";
    }
    std::cout << "\n";

    for (int i = 0; i < N; ++i) {
        std::cout << "|";
        for (int j = 0; j < N; ++j) {
            bool isLocated = snake.isSnakeAt(i, j);
            char drawChar = isLocated ? snake.getBodyMark() : ' ';
            std::cout << " " << drawChar << " |";
        }
        std::cout << "\n";
        
        std::cout << "+";
        for (int j = 0; j < N; ++j) {
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
    Snake snake;
    vector<vector<char>> snakeBoard;
    initializeBoard(snakeBoard);

    char input;
    while (true) {
        clearScreen();
        displayBoard(snakeBoard, snake);
        
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
                    snake.moveUp();
                    break;
                case 's':
                    snake.moveDown();
                    break;
                case 'a':
                    snake.moveLeft();
                    break;
                case 'd':
                    snake.moveRight();
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
