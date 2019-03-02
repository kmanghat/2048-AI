#include "game.h"

/**************************************************************************//**
 * The game object plays the game.  There's not much to do.  The constructor
 * loads the tile images.  The makeMove method takes a ValidMove and applies
 * it to the game board and updates the game score.
 *****************************************************************************/
Game::Game() : gameOver(false), score(0)
{
    loadImages();
}

/**************************************************************************//**
 * makeMove takes a ValidMove and applies it to the current game board
 *
 * @returns true of the move was successful, false if the game is over
 *****************************************************************************/
bool Game::makeMove(ValidMove move)
{
    bool retVal;
    if ((gameOver = isGameOver()) == true)
        retVal = false;
    else
    {
        retVal = board.makeMove(move);
        score = board.getScore();
    }
    return retVal;
}

/**************************************************************************//**
 * Accessor for  the game stat
 *****************************************************************************/
void Game::gameIsOver() {
    gameOver = true;
}

/**************************************************************************//**
 * Checks the game board to see if it's possible to make a move.  If not, it
 * returns 'true'
 *
 * @returns true iff there are no longer any valid moves
 *****************************************************************************/
bool Game::isGameOver()
{
    for (ValidMove move : {
                DOWN, LEFT, RIGHT, UP
            })
    {
        Board temp(board);
        gameOver = gameOver || temp.checkMove(move);
    }
    gameOver = !gameOver;
    return gameOver;
}

/**************************************************************************//**
 * Returns a copy of the current game board
 *
 * @returns current game board
 *****************************************************************************/
Board Game::getBoard()
{
    Board tmp(board);
    return tmp;
}

/**************************************************************************//**
 * Loads .png files that represent the game tiles
 *****************************************************************************/
void Game::loadImages()
{
    stringstream ss;
    unsigned char *image;
    int width;
    int height;

    for (int i = 2 ; i < 32768 ; i *= 2)
    {
        ss << "Images/" << i << "Tile.bmp";
        loadBMP(ss.str().c_str(), width, height, image);
        GLuint tex;
        bindImageToTexture(&tex, width, height, image);
        delete []image;
        tiles[i] = tex;
        ss.str("");
    }

    ss << "Images/Board.bmp";
    loadBMP(ss.str().c_str(), width, height, image);
    bindImageToTexture(&gameBoard, width, height, image);
    delete []image;
}

/**************************************************************************//**
 * Returns the current score
 *****************************************************************************/
int Game::getScore() {
    return score ;
}

/**************************************************************************//**
 * Draws the game board
 *****************************************************************************/
void Game::draw()
{
    drawTexture(gameBoard, 0, 0, 500, 500);
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
        {
            int val = board.getCellVal(j, i);
            if (val != 0)
            {
                int x1 = 14 + (i*122);
                int y1 = 500 - (j*122) - 122;

                drawTexture(tiles[val], x1, y1, x1+108, y1+108);
            }
        }
    glFlush();
}
