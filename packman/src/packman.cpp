#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;

class Pacman {
public:
    Pacman() {
        x = WIDTH / 2;
        y = HEIGHT / 2;
        score = 0;
    }

    void move(int direction) {
        switch (direction) {
            case 0: // up
                if (y > 0) {
                    y--;
                }
                break;
            case 1: // down
                if (y < HEIGHT - 1) {
                    y++;
                }
                break;
            case 2: // left
                if (x > 0) {
                    x--;
                }
                break;
            case 3: // right
                if (x < WIDTH - 1) {
                    x++;
                }
                break;
        }
    }

    void eat() {
        score++;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    int getScore() {
        return score;
    }

private:
    int x;
    int y;
    int score;
};

class Ghost {
public:
    Ghost(int startX, int startY) {
        x = startX;
        y = startY;
    }

    void move() {
        int direction = rand() % 4;
        switch (direction) {
            case 0: // up
                if (y > 0) {
                    y--;
                }
                break;
            case 1: // down
                if (y < HEIGHT - 1) {
                    y++;
                }
                break;
            case 2: // left
                if (x > 0) {
                    x--;
                }
                break;
            case 3: // right
                if (x < WIDTH - 1) {
                    x++;
                }
                break;
        }
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

private:
    int x;
    int y;
};

class Board :public Pacman{
public:
    Board() {
        for (int i = 0; i < HEIGHT; i++) {
            vector<char> row;
            for (int j = 0; j < WIDTH; j++) {
                if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                    row.push_back('#');
                } else {
                    row.push_back('.');
                }
            }
            board.push_back(row);
        }
        pacman = new Pacman();
        ghosts.push_back(new Ghost(1, 1));
        ghosts.push_back(new Ghost(WIDTH - 2, 1));
        ghosts.push_back(new Ghost(1, HEIGHT - 2));
        ghosts.push_back(new Ghost(WIDTH - 2, HEIGHT - 2));
    }

    ~Board() {
        delete pacman;
        for (int i = 0; i < ghosts.size(); i++) {
            delete ghosts[i];
        }
    }

    void draw() {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (i == pacman->getY() && j == pacman->getX()) {
                    cout << '@';
                } else {
                    bool ghostDrawn = false;
                    for (int k = 0; k < ghosts.size(); k++) {
                        if (i == ghosts[k]->getY() && j == ghosts[k]->getX()) {
                            cout << 'C';
                            ghostDrawn = true;
                            break;
                        }
                    }
                    if (!ghostDrawn) {
                        cout << board[i][j];
                    }
                }
            }
            cout << endl;
        }
        cout << "Score: " << pacman->getScore() << endl;
    }

    void movePacman(int direction) {
        pacman->move(direction);
        int x = pacman->getX();
        int y = pacman->getY();
        if (board[y][x] == '.') {
            pacman->eat();
            board[y][x] = ' ';
        }
    }

    void moveGhosts() {
        for (int i = 0; i < ghosts.size(); i++) {
            ghosts[i]->move();
        }
    }

    bool isGameOver() {
        for (int i = 0; i < ghosts.size(); i++) {
            if (ghosts[i]->getX() == pacman->getX() && ghosts[i]->getY() == pacman->getY()) {
                return true;
            }
        }
        return false;
    }

private:
    Pacman* pacman;
    vector<Ghost*> ghosts;
    vector<vector<char>> board;
};

int main() {
    srand(time(NULL));
    Board board;

    while (!board.isGameOver()) {
        system("clear"); // يتم استدعاء النظام لمسح الشاشة

        board.draw();

        int direction;
        cout << "Enter direction (0: up, 1: down, 2: left, 3: right): ";
        cin >> direction;

        board.movePacman(direction);
        board.moveGhosts();
    }

    cout << "Game over! Your score is " << board.getScore() << endl;

    return 0;
}