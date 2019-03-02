#include "util.h"

void keyboard(unsigned char key, int x, int y)
{
    utilityCentral(new KeyboardEvent(key, x, y));
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    utilityCentral(new DisplayEvent);
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glLoadIdentity();           // initialize transformation matrix
    gluOrtho2D(0.0,w,0.0,h);
    glViewport(0,0,w,h);        // adjust viewport to new window
    glutPostRedisplay();
    utilityCentral(new ReshapeEvent(w, h));
}

void ticktock(int value)
{
    utilityCentral(new TickTockEvent);
    glutTimerFunc(value, ticktock, value);
}

void cleanUpAndCloseDown(Player *player, Game *game)
{
    delete player;
    delete game;
    std::cout << "Final Score: " << game->getScore() << std::endl;
    glutLeaveMainLoop();
}

void updateScore(Game *game)
{
    stringstream ss;
    ss << "Score = " << game->getScore();
    glutSetWindowTitle(ss.str().c_str());
}

void utilityCentral(Event *event)
{
    static Game *game = new Game;
    static Player *player = new Player(game);

    if (game->isGameOver())
    {
        std::cout << "GAME OVER!" << std::endl ;
        cleanUpAndCloseDown(player, game);
    }
    else
    {
        event->doAction(player, game);
        updateScore(game);
    }
    delete event;
}
