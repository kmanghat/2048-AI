#ifndef _BOARD_H_
#define _BOARD_H_
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <thread>

using namespace std;

enum ValidMove {LEFT, RIGHT, UP, DOWN};

typedef unsigned char byte;

struct Cell
{
    int num;

    Cell(int n=0): num(0) {}
    Cell& operator+=(const Cell& a)
    {
        num += a.num;
        return *this;
    }
};

class Board
{
    Cell board[4][4];
    bool gameOver;
    int score;
    int recordMove;

public:
    Board();
    Board(const Board&);

    void printBoard();
    bool makeMove(ValidMove);
    bool checkMove(ValidMove);
    int getScore();
    int maxVal();
    int getCellVal(int, int);
    void setCellVal(int, int, int);
    bool isGameOver();

private:
    void clearCanChange();
    bool addValue();
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();
    void draw();
};

ostream& operator<<(ostream&, Cell);
istream& operator>>(istream&, Cell);
bool operator==(const Cell &, const Cell &);
bool operator!=(const Cell &, const Cell &);
#endif
