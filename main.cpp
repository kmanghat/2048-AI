/***************************************************************************//**
 * @file
 * @brief An algorithm to play and win the 2048 game.
 *
 * @mainpage Project 2 - 2048
 *
 * @authors Keshav Manghat, Lane Moseley
 *
 * @date February 28, 2019
 *
 * @par Instructor:
 *         Dr. Hinker
 *
 * @par Course:
 *         CSC 315
 *
 * @section program_section Program Information
 *
 * @details This program uses expectimax algorithm to play the 2048 board game.
 * Our algorithm is an implementation of the expectimax algorithm. The game
 * board is recursively checked to simulate the game alternating between player
 * and board.
 * Each path is graded by a heuristic function and the highest scoring path is
 * taken by the player.
 *
 * @section compile_section Compiling and Usage
 *     Testing was done on Ubuntu 18.04 machines with optimization on, running
 *     Intel i7 8th Gen Processors with 8gb of ram. Turn times during testing
 *     were near the 0.05 - 0.06 second ceiling.
 *     Tested also on opp lab machines with GUI.
 *
 * @par Compiling Instructions:
 *    -make
 *
 * @par Usage:
   @verbatim
   ./main
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug  No known bugs at this time.
 *
 * @todo All tasks completed at this time.
 *
 * @par Modifications and Development Timeline:
 * @verbatim
 * https://gitlab.mcs.sdsmt.edu/7393899/csc315_sp2019_project2/commits/master
 * @endverbatim
 *
 ******************************************************************************/
#include <iostream>
#include <GL/glut.h>
#include "util.h"

using namespace std;

/***************************************************************************//**
 * Standard startup code.  The first command line argument indicates the time
 * requested per 'ticks' of the timer.  Defaults to 2000ms (2 sec)
 ******************************************************************************/
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    int msec = 2000;
    if (argc > 1) msec = atoi(argv[1]);
    initOpenGL(msec);

    glutMainLoop();
    return 0;
}

/**************************************************************************//**
 * Standard OpenGL init plus the delay between ticks (msec)
 *****************************************************************************/
void initOpenGL(int msec)
{
    char name[] = "2048 Solver";
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(510, 510);

    glutInitWindowPosition(50,50);      // initial window  position
    glutCreateWindow(name);      // window title

    glClearColor(0,0,0,0);              // use black for glClear command
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glMatrixMode(GL_PROJECTION);

    glutDisplayFunc(display);           // how to redisplay window
    glutReshapeFunc(reshape);           // how to resize window
    glutKeyboardFunc(keyboard);         // how to handle a key press
    glutTimerFunc(msec, ticktock, msec);
}

