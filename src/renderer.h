#ifndef RENDERER_H
#define RENDERER_H
#include <stdio.h>
#include <stdlib.h>
#include <types.h>
#include <common.h>

#include <GL/gl.h>
#include <GL/osmesa.h>





extern void InitGL();
extern int SetViewport(int width, int height);
extern void renderMatrix(mazeMatrix maze, renderData rd, int mode);
extern void drawSolveMatrix(mazeMatrix maze, renderData rd);
extern void drawGenerateMatrix(mazeMatrix maze, renderData rd);
extern int handleTextInput(SDL_Event e);
#endif // RENDERER_H
