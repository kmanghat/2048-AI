#include <GL/freeglut.h>

void drawTexture(GLuint tex, int x1, int y1, int x2, int y2)
{
    glBindTexture(GL_TEXTURE_2D, tex);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    glVertex2i(x1, y1);
    glTexCoord2i(0,1);
    glVertex2i(x1, y2);
    glTexCoord2i(1,1);
    glVertex2i(x2, y2);
    glTexCoord2i(1,0);
    glVertex2i(x2, y1);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void bindImageToTexture(GLuint *tex, int w, int h, unsigned char *img)
{
    glGenTextures(1, tex);
    glBindTexture(GL_TEXTURE_2D, *tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, img);
    glBindTexture(GL_TEXTURE_2D, 0);
}
