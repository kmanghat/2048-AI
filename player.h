/***************************************************************************//**
 * @file
 ******************************************************************************/
#ifndef __PLAYER_H
#define __PLAYER_H
#include <climits>
#include <set>
#include <math.h>
#include "game.h"

const int EMPTY_BONUS = 10000;  /*!< A bonus for having empty cells */
const int MERGE_BONUS = 20000;  /*!< A bonus for having tiles that can merge */

const int MAX_RECURSION_DEPTH = 8;  /*!< Max recursive depth */
const int MED_RECURSION_DEPTH = 6;  /*!< Medium recursive depth */
const int MIN_RECURSION_DEPTH = 4;  /*!< Minimum recursive depth */

const int EMPTY_THRESHHOLD = 5;     /*!< Empty threshold used for setting recursion level */
const int DISTINCT_THRESHHOLD = 8;  /*!< Distinct tile threshold for setting resurcion level */

/*!
 * @brief This is the ai player class
 */
class Player
{
    Game *game;     /*!< A pointer to the game */

    /*!< The weight matrix used by the heuristic function */
    int matrix[4][4] =
    {
        {32768,16384,8192,4096},
        {256, 512, 1024, 2048},
        {128,64,32,16},
        {1,2,4,8}
    };

    ValidMove moves[4] = {UP,RIGHT,DOWN,LEFT};  /*!< The valid move choices */
    int heuristicFunction(Board board);
    int bestScore(Board board, int depth, bool isPlayer);
    int findBestMove(Board board);
    int getEmptyCells(Board board);
    int getDistinctCells(Board board);

public:
    Player (Game *);
    void makeMove();
};


#endif

