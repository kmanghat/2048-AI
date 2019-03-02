#include "event.h"

void cleanUpMemory() {}

KeyboardEvent::KeyboardEvent(unsigned char k, int x, int y) : key(k), x(x), y(y) {}

void KeyboardEvent::doAction(Player *player, Game *game)
{
    if (key == ESCAPE_KEY)
    {
        cleanUpMemory();
        glutLeaveMainLoop();
    }
}

void DisplayEvent::doAction(Player *player, Game *game)
{
    game->draw();
}

ReshapeEvent::ReshapeEvent(int w, int h) : w(w), h(h) {}

void TickTockEvent::doAction(Player *player, Game *game)
{
    player->makeMove();
    glutPostRedisplay();
}
