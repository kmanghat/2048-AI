#ifndef __LOADBMP_H
#define __LOADBMP_H
#include <iostream>
#include <GL/freeglut.h>

typedef unsigned char byte;

bool loadBMP(const char *imagepath, int &width, int &height, unsigned char * &image);
#endif
