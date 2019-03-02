#ifndef __GRAPHICS_H_
#define __GRAPHICS_H_

void drawTexture(GLuint tex, int x1, int y1, int x2, int y2);
void bindImageToTexture(GLuint *, int, int, unsigned char *);
#endif
