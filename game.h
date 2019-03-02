#ifndef __GAME_H
#define __GAME_H
#include <map>
#include <sstream>
#include <GL/freeglut.h>
#include "board.h"
#include "loadBMP.h"
#include "graphics.h"

class Game
{
    Board board;
    bool gameOver;
    int  score;
    std::map<int, GLuint> tiles;
    GLuint gameBoard;

public:
    Game();
    bool isGameOver();
    void gameIsOver();
    int  getScore();
    Board getBoard();
    void draw();
    bool makeMove(ValidMove);

private:
    void loadImages();
};
#endif
