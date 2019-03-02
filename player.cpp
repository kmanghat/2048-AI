/***************************************************************************//**
 * @file
 ******************************************************************************/
#include "player.h"

/**************************************************************************//**
 * @par Description:
 * This is the constructor for the player class.
 *****************************************************************************/
Player::Player(Game *game) : game(game) { }

/**************************************************************************//**
 * @par Description:
 * This function chooses a move for the player using our ai.
 *****************************************************************************/
void Player::makeMove()
{
    // If the game is over, you won't be able to make a valid move, return
    if (game->isGameOver()) return;

    bool didNotMove;

    // Initialize move using our player implementation
    int move = findBestMove(game->getBoard());
    didNotMove = !game->makeMove(moves[move]);

    // Safe guard in case heuristic function fails to choose a valid move
    //Should never go here but since it was segfaulting, better safe than sorry
    move = 0;
    while(didNotMove && move < 4)
    {
        didNotMove = !game->makeMove(moves[move]);
        move++;
    }

    // If the game is over, signal the game object
    if (didNotMove)
    {
        game->gameIsOver();
    }
}

/**************************************************************************//**
 * @author Keshav Manghat, Lane Moseley
 *
 * @par Description:
 * This function provides a way of evaluating the position of the tiles on the
 * board. Score is given based on the weighted matrix which has a snake like
 * pattern with the bottom left having the lowest value and the top left having
 * the greatest. Other heuristics like, possible merges and
 * number of empty cells are also considered.
 *
 * @param[in]      board - the game board to evaluate
 * @returns        a score for the board
 *
 *****************************************************************************/
int Player::heuristicFunction( Board board )
{
    int score = 0;

    //Prefer to have larger numbered tiles in top right corner
    for(int i = 0 ; i < 4; i++)
    {
        for(int j = 0 ; j < 4; j ++)
        {
            if(board.getCellVal(i,j) != 0)
            {
                score += matrix[i][j] * board.getCellVal(i,j);
            }
        }
    }

    //Count possible merges
    int di[4] = {1,-1,0,0};
    int dj[4] = {0,0,1,-1};
    int possibleMerges = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
            if(board.getCellVal(i,j) != 0)
            {
                for(int k = 0 ; k < 4; k++)
                {
                    int newI = i + di[k];
                    int newJ = j + dj[k];
                    if(newI >= 0 && newI < 4 && newJ >= 0 && newJ < 4)
                    {
                        if(abs(board.getCellVal(i,j)-board.getCellVal(newI,newJ)) == 0)
                        {
                            possibleMerges++;
                        }
                    }
                }
            }
        }
    }

    //Reward for empty tiles and possible merges
    possibleMerges /= 2;
    int emptyCells = getEmptyCells(board);

    //Award for limiting randomness and increasing merges on board
    if(emptyCells >= 1 && emptyCells <= 4)
    {
        score += EMPTY_BONUS;
    }

    if(possibleMerges >= 2 && possibleMerges <= 4)
    {
        score += MERGE_BONUS;
    }

    return score;
}

/**************************************************************************//**
 * @author Keshav Manghat, Lane Moseley
 *
 * @par Description:
 * This function will return an integer representing which move the player
 * should make. The function checks all four move directions and returns highest
 * scoring direction.
 *
 * @param[in]      board - the current game board
 * @returns        an integer indicating which move the player should make
 *
 *****************************************************************************/
int Player::findBestMove(Board board)
{
    int score = INT_MIN;
    int bestMove = 0;
    //Loops through all moves and finds the best one possible
    for(int i = 0 ; i < 4; i++)
    {
        Board newBoard = board;
        //Only pursue the move if you can actually do it
        if(newBoard.checkMove(moves[i]))
        {
            int newScore = 0;
            newBoard.makeMove(moves[i]);

            //Run increased depth whenever time permits,
            //less tiles = less nodes to visit
            if(getEmptyCells(board) <= EMPTY_THRESHHOLD)
            {
                newScore = bestScore(newBoard,MAX_RECURSION_DEPTH,false);
            }
            else if(getDistinctCells(board) >= DISTINCT_THRESHHOLD)
            {
                newScore = bestScore(newBoard,MED_RECURSION_DEPTH,false);
            }
            else
            {
                newScore = bestScore(newBoard,MIN_RECURSION_DEPTH,false);
            }

            //Save the current best score and move
            if(newScore > score)
            {
                bestMove = i;
                score = newScore;
            }
        }
    }

    return bestMove;
}

/**************************************************************************//**
 * @author Keshav Manghat, Lane Moseley
 *
 * @par Description:
 * This function recursively checks all valid moves to a given depth and returns
 * the resulting score. All empty spots are checked with two's only becaue
 * probability of 4's are low.
 *
 * @param[in]      board - the game board
 * @param[in]      depth - the depth of recursion
 * @param[in]      isPlayer - if true function will spawn tiles in empty spots
 *
 *****************************************************************************/
int Player::bestScore(Board board, int depth, bool isPlayer)
{
    //Base case
    if(depth == 0)
    {
        return heuristicFunction(board);

    }
    //If current turn is of player, check moves
    if(isPlayer)
    {
        int score = INT_MIN;
        //Generate all possible board moves and select max score
        for(int i = 0 ; i < 4; i++)
        {
            Board newBoard = board;
            int newScore = 0;
            //Dont pursue dead paths
            if(newBoard.makeMove(moves[i]))
            {
                newScore = bestScore(newBoard, depth-1, false);
                score = max(newScore,score);
            }
        }
        return score;
    }
    //If turn is of board then create 2 at spot, ignore 4's
    else
    {
        int score = 0;
        int emptyCells = getEmptyCells(board);
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0 ; j < 4; j++)
            {
                if(board.getCellVal(i,j) == 0)
                {
                    Board newBoard = board;
                    int newScore = 0;

                    //Check the spot with 2 in it
                    newBoard = board;
                    newBoard.setCellVal(i,j,2);

                    newScore = bestScore(newBoard, depth-1, true);

                    if(newScore != INT_MIN)
                    {
                        score += newScore;
                    }
                }
            }
        }

        //A way to weight the score depending on number of empty tiles
        if(emptyCells > 0)
        {
            score /= emptyCells;
        }
        return score;
    }
}

/**************************************************************************//**
 * @author Keshav Manghat, Lane Moseley
 *
 * @par Description:
 * A function to determine how many empty cells the board has.
 *
 * @param[in]      board - the game board to check
 * @returns        the number of empty cells
 *
 *****************************************************************************/
int Player::getEmptyCells(Board board)
{
    int emptyCells = 0;
    for(int i = 0 ; i < 4; i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
            if(board.getCellVal(i,j) == 0)
            {
                emptyCells++;
            }
        }
    }
    return emptyCells;
}

/**************************************************************************//**
 * @author Keshav Manghat, Lane Moseley
 *
 * @par Description:
 * This is a function to check how many distinct number cells are present
 * on the game board.
 *
 * @param[in]      board - the game board to check
 * @returns        the number of distinct cells on the board
 *
 *****************************************************************************/
int Player::getDistinctCells(Board board)
{
    set<int>distinct;
    //Gets all distinct cells including zeroes
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
            distinct.insert(board.getCellVal(i,j));
        }
    }
    return distinct.size();
}


