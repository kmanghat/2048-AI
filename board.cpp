#include "board.h"

Board::Board() : gameOver(false), score(0)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            board[i][j].num = 0;

    addValue();
    addValue();
}

Board::Board(const Board& b)
{
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            board[i][j] = b.board[i][j];

    score = b.score;
}

int Board::getCellVal(int i, int j) {
    return board[i][j].num ;
}

void Board::setCellVal(int i, int j, int val) {
    board[i][j].num  = val;
}

bool Board::isGameOver() {
    return gameOver ;
}

bool Board::addValue()
{
    bool foundEmpty = false;
    vector<Cell*> emptyCells;
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (!board[i][j].num)
            {
                emptyCells.push_back(&board[i][j]);
                foundEmpty = true;
            }

    if (!foundEmpty)
    {
        gameOver = true;
        return false;
    }

    int randCell = rand() % emptyCells.size();
    int num = 2;
    if (rand() % 100 >= 90) num = 4;
    emptyCells[randCell]->num = num;

    return true;
}

int Board::maxVal()
{
    int maxV = 0;
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (maxV < board[i][j].num)
                maxV = board[i][j].num;

    return maxV;
}

int Board::getScore() {
    return score ;
}

void Board::printBoard()
{
    for (int i = 0 ; i < 4 ; i++)
    {
        for (int j = 0 ; j < 4 ; j++)
            cout << setw(5) << board[i][j];
        cout << endl;
    }
}

bool Board::makeMove(ValidMove move)
{
    bool retVal = false;
    switch (move)
    {
    case LEFT  :
        retVal = moveLeft();
        break;
    case RIGHT :
        retVal = moveRight();
        break;
    case UP    :
        retVal = moveUp();
        break;
    case DOWN  :
        retVal = moveDown();
        break;
    }
    if (retVal) addValue();
    return retVal;
}

bool Board::checkMove(ValidMove move)
{
    bool retVal = false;
    switch (move)
    {
    case LEFT  :
        retVal = moveLeft();
        break;
    case RIGHT :
        retVal = moveRight();
        break;
    case UP    :
        retVal = moveUp();
        break;
    case DOWN  :
        retVal = moveDown();
        break;
    }
    return retVal;
}

bool Board::moveLeft()
{
    bool didMove = false;
    for (int row = 0 ; row < 4 ; row++)
    {
        vector<bool> canChange {true, true, true, true};
        for (int startCol = 1 ; startCol < 4 ; startCol++)
        {
            int col = startCol;
            while (col > 0)
            {
                if (board[row][col-1] == 0 && board[row][col] != 0)
                {
                    board[row][col-1] = board[row][col];
                    board[row][col] = 0;
                    didMove = true;
                }
                else if (board[row][col-1] != 0 && board[row][col-1] == board[row][col] && canChange[col-1] && canChange[col])
                {
                    board[row][col-1] += board[row][col];
                    board[row][col] = 0;
                    canChange[col-1] = false;
                    score += board[row][col-1].num;
                    didMove = true;
                }
                col--;
            }
        }
    }
    return didMove;
}

bool Board::moveUp()
{
    bool didMove = false;
    for (int col = 0 ; col < 4 ; col++)
    {
        vector<bool> canChange {true, true, true, true};
        for (int startRow = 1 ; startRow < 4 ; startRow++)
        {
            int row = startRow;
            while (row > 0)
            {
                if (board[row][col] != 0 && board[row-1][col] == 0)
                {
                    board[row-1][col] = board[row][col];
                    board[row][col] = 0;
                    didMove = true;
                }
                else if (board[row][col] != 0 && board[row][col] == board[row-1][col] && canChange[row-1] && canChange[row])
                {
                    board[row-1][col] += board[row][col];
                    board[row][col] = 0;
                    canChange[row-1] = false;
                    score += board[row-1][col].num;
                    didMove = true;
                }
                row--;
            }
        }
    }
    return didMove;
}

bool Board::moveDown()
{
    bool didMove = false;
    for (int col = 0; col < 4 ; col++)
    {
        vector<bool> canChange {true, true, true, true};
        for (int startRow = 2 ; startRow >= 0 ; startRow--)
        {
            int row = startRow;
            while (row <= 2)
            {
                if (board[row][col] != 0 && board[row+1][col] == 0)
                {
                    board[row+1][col] = board[row][col];
                    board[row][col] = 0;
                    didMove = true;
                }
                else if (board[row][col] != 0 && board[row][col] == board[row+1][col] && canChange[row+1] && canChange[row])
                {
                    board[row+1][col] += board[row][col];
                    board[row][col] = 0;
                    canChange[row+1] = false;
                    score += board[row+1][col].num;
                    didMove = true;
                }
                row++;
            }
        }
    }
    return didMove;
}

bool Board::moveRight()
{
    bool didMove = false;
    for (int row = 0 ; row < 4 ; row++)
    {
        vector<bool> canChange {true, true, true, true};
        for (int startCol = 2 ; startCol >= 0 ; startCol--)
        {
            int col = startCol;
            while (col <= 2)
            {
                if (board[row][col] != 0 && board[row][col+1] == 0)
                {
                    board[row][col+1] = board[row][col];
                    board[row][col] = 0;
                    didMove = true;
                }
                else if (board[row][col] != 0 && board[row][col] == board[row][col+1] && canChange[col+1] && canChange[col])
                {
                    board[row][col+1] += board[row][col];
                    board[row][col] = 0;
                    canChange[col+1] = false;
                    score += board[row][col+1].num;
                    didMove = true;
                }
                col++;
            }
        }
    }
    return didMove;
}

ostream& operator<<(ostream& os, Cell c)
{
    os << c.num;
    return os;
}

istream& operator>>(istream& is, Cell& c)
{
    is >> c.num;
    return is;
}

bool operator==(const Cell &a, const Cell &b)
{
    return (a.num == b.num);
}

bool operator!=(const Cell &a, const Cell &b)
{
    return !(a.num == b.num);
}
